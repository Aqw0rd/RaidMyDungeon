# Weapon & gear system

**Status:** In progress. Steps 1–3 done, Steps 4–5 pending.

## Progress tracker

Check off a step here as it's completed, so a future session can tell at a
glance where to pick up. Each step below has more detail further down.

- [x] Step 1 — `ResourceManager` (shared texture cache)
- [x] Step 2 — Layered ("paperdoll") rendering on `GameObject`
- [x] Step 3 — Data-driven `ItemDef` + JSON loader + generic weapon socket (retired `Item`/`Weapon`/`IronSword`)
- [ ] Step 4 — `Inventory` + `Equipment`, world pickups, minimal UI
- [ ] Step 5 — `Stats` aggregation surfaced end-to-end

**Next up: Step 4.** See "Decisions already made" below before starting — some
open questions for step 4 were already answered.

## Context

The long-term vision for this project is a roguelike dungeon-crawler where
players eventually design and share dungeons for others to "raid." Before
going further down that road, the goal is a solid engine foundation. The
first concrete piece being built is a weapon & gear system with two hard
requirements from experience playing other ARPGs:

1. Loot should be **data-driven and generic** — adding a new weapon or armor
   piece should never require writing a new C++ class or a bespoke animation.
2. Equipped gear should **visually change the character** (paperdoll-style
   layering on top of the base sprite), not require redrawing the whole
   character per gear combination.

This plan also covers the minimal inventory needed to actually hold and
equip that loot. It deliberately does **not** cover the level editor /
community dungeon-sharing vision, or the unused `Ability`/`Melee`
scaffolding — both are separate efforts better tackled once the loot loop
itself is proven.

One resolved question: SFML's graphics module (`sf::RenderWindow`/`Sprite`/
`Texture`, used throughout) is built on OpenGL and is already
GPU-accelerated — there was no "software vs. hardware rendering" gap to
close, so no rendering-pipeline work is in this plan.

## Decisions already made

These came up while building steps 1–3 and apply to steps 4–5 too, so they
don't need to be re-asked:

- **Stat modifiers use flat named fields** on `ItemDef` (`attackBonus`,
  `defenseBonus`, `maxHpBonus`, `maxEnergyBonus`, `speedBonus`), not a
  generic key/value list.
- **World pickups use auto-pickup on contact** (walking into a dropped item
  adds it to the inventory immediately), not an interact-button prompt.
- **A weapon is always visible while equipped**; attacking just rotates it
  through a swing arc and returns it to rest. (An earlier version hid it
  after every swing — that was a latent bug inherited from the original
  `IronSword`, not intended behavior.)
- **A `Player` can be unarmed** — `Player::weapon` is a nullable
  `std::unique_ptr<EquippedWeapon>`, and everything that uses it is
  null-checked.
- **A weapon's rotation pivot and rest-facing angle are measured from the
  actual art, not guessed**, and stored as data (`ItemDef::gripX/gripY/
  restAngle`) rather than hand-tuned per-direction constants in code. The
  original `IronSword`-derived version guessed an "origin" offset per
  direction, which visibly orbited/pivoted on the blade tip instead of the
  hilt — see step 3 below for how to measure these for a new weapon icon.

## Current architecture (post steps 1–3)

- **`ResourceManager`** (`ResourceManager.h/.cpp`) — `static getTexture(path)`
  returns a shared, cached `sf::Texture`. `GameObject` and `EquippedWeapon`
  load textures through it. `Map`'s tileset does not yet (still loads its
  own texture directly) — fine for now, one tileset per map.
- **`GameObject`** (`GameObject.h/.cpp`) owns a `body` `SpriteLayer` plus an
  array of optional gear `SpriteLayer`s (`GearLayer::Legs/Chest/Head`), all
  sliced into the same `[animation frame][direction]` grid as the body via
  `sliceFrames()`. `setLayerTexture(layer, path)` / `clearLayerTexture(layer)`
  are public — call them to equip/unequip a gear layer. `drawLayers()` /
  `setLayersPosition()` draw/position the body plus every equipped layer in
  z-order (Legs → Chest → Head). `spriteScale` (public, `= 2`) is the pixel
  scale everything (body, gear, weapon) should render at.
- **`ItemDef`** (`ItemDef.h/.cpp`) — plain data struct for one item: id,
  name, `EquipSlot` (`Weapon/Head/Chest/Legs`), stat bonuses, `spritePath`
  (doubles as inventory icon and equipped-visual for now), and
  `attackPattern` (weapon only, only `"slash"` exists today). Weapon items
  also carry `gripX`/`gripY` (pixel coords in the icon where the hand holds
  it; defaults to the icon's center) and `restAngle` (the compass direction,
  0=right/90=down/180=left/270=up clockwise, the art points at 0° sprite
  rotation) — see "Measuring a new weapon icon" under step 3.
- **`ItemDatabase`** (`ItemDatabase.h/.cpp`) — `loadFromFile(path)` parses a
  JSON array of items (mirrors `Map::loadMap`'s jsoncpp usage) into a
  `static` lookup table; `get(id)` returns `const ItemDef*` or `nullptr`.
  Loaded once in `App::App()` from `Resources/Items/items.json`.
- **`EquippedWeapon`** (`Items/EquippedWeapon.h/.cpp`) — the one class that
  handles every weapon. Takes a `const ItemDef&` + the wielding `GameObject&`.
  The icon's `sf::Sprite` origin is set to `gripX`/`gripY`, so rotation
  always pivots on the hand, not a corner. Two small per-direction tables:
  `restFacingAngleFor(direction)` (which compass direction, same convention
  as `restAngle`, the wielder should hold the weapon at rest — combined with
  `restAngle` to get the actual sprite rotation) and `socketOffsetFor(direction)`
  (where the hand sits relative to `GameObject::getBodyCenter()`, in world
  pixels — a property of the wielder's body, not the weapon, so it's shared
  by every item). `socketOffsetFor`'s numbers are still a first-pass
  approximation (see "Known rough edges"), but the rotation math itself is
  measured/verified, not guessed. `strike()` locks in `restRotation` for the
  swing (so spinning the mouse mid-attack can't snap it) and starts a sweep
  centered on it, `swingRange` degrees wide, at `swingDegreesPerSecond` (so
  swing duration is framerate-independent). Only the `"slash"` pattern is
  implemented (inline, not yet dispatched on `attackPattern` — add a branch
  there when a second pattern is needed).

  **Measuring a new weapon icon's `gripX`/`gripY`/`restAngle`:** don't
  eyeball them — analyze the actual pixel art. For a script that finds a
  sprite's opaque-pixel bounding box and principal axis (giving the blade's
  native pointing angle) plus any color-cluster centroid you want to treat
  as the grip (e.g. the handle color), see the analysis done for
  `sword_iron.png` in this session's history — it's a short PIL/numpy
  script, not a saved file. `restAngle` is the compass angle (this doc's
  0/90/180/270 convention) from the grip toward the tip.
- **`Player`** (`Objects/Player.h/.cpp`) — `equipWeapon(const ItemDef*)`
  builds (or clears, if `nullptr`) the `EquippedWeapon`. No weapon is
  hardcoded in the constructor anymore.
- **Content**: `Resources/Items/items.json` has 4 items today (`iron_sword`,
  `leather_helm`, `leather_chest`, `leather_legs`). Their gear art is
  placeholder — flat colored blocks in `Resources/Sprites/Gear/*_test.png`,
  aligned to `Squarey.png`'s 16×16 tile / 8-column / 4-row grid, meant to be
  replaced with real art whenever it exists.
- **Still temporary**: `States/PlayState.cpp`'s constructor hardcodes
  equipping those 4 test items onto `player` by id, clearly commented as
  temporary. Step 4 replaces this with real pickups + an `Equipment`
  component.

## Steps

### 1. `ResourceManager` — shared texture cache — ✅ done
A `path -> shared_ptr<sf::Texture>` cache so gear/weapon art loaded from many
places doesn't get loaded (or leaked) redundantly.

### 2. Layered ("paperdoll") rendering on `GameObject` — ✅ done
Generalized the single body sprite grid into an ordered stack of layers
(Body → Legs → Chest → Head). Every layer texture must share the body's
exact frame grid, so one `spriteX`/`spriteY` index drives all of them in
lockstep — this is what makes gear "generic." Validated with placeholder
overlays and a screenshot showing them animating in lockstep with the body.

### 3. Data-driven `ItemDef` + generic weapon socket — ✅ done
Replaced the `Item`/`Weapon`/`IronSword` class-per-item hierarchy with
`ItemDef` (data) + `ItemDatabase` (JSON loader) + `EquippedWeapon` (one
generic weapon controller). Validated by equipping the 4 JSON-defined items
onto the player and screenshotting all 4 facing directions plus a swing.

The first version of `EquippedWeapon` reused ad-hoc per-direction "origin"
offsets guessed from the old `IronSword` code; once actually seen running,
these visibly orbited around a point outside the icon (right/down) or
pivoted on the blade tip instead of the hilt (left/up), and the swing was a
slow, one-sided 180° rotation with a fixed screen position regardless of
facing direction. This was reworked (still within step 3, same day) to pivot
on a measured grip point and aim using a measured native pointing angle
(`ItemDef::gripX/gripY/restAngle` — see "Current architecture" above),
anchor position to `GameObject::getBodyCenter()` plus a per-direction
offset instead of one fixed point, and swing framerate-independently over a
shorter, centered arc. `iron_sword`'s values (`gripX: 13, gripY: 13,
restAngle: 225`) were measured directly from `sword_iron.png`'s pixels, not
eyeballed. Verified for all 4 directions plus mid-swing frames — see
"Verification" for the technique used.

### 4. `Inventory` + `Equipment` — ⬜ not started
New `Inventory.h/.cpp` and `Equipment.h/.cpp`:
- `Inventory`: a list of item-instance references (`ItemDef` id + stack
  count for stackables) the player carries.
- `Equipment`: one optional item instance per `EquipSlot` on `Player`.
  `equip()`/`unequip()` moves an item between `Inventory` and the slot,
  calls `GameObject::setLayerTexture`/`clearLayerTexture` (gear) or
  `Player::equipWeapon` (weapon) to update rendering, and (step 5) recomputes
  aggregated `Stats`.
- World pickups: a trivial drawable using the item's icon that adds to
  `Inventory` on player contact (**auto-pickup, decided above**) — drop 2-3
  test items into the existing `Resources/Levels/Dungeon 1.json` play area.
- UI: factor the `sf::Text` menu pattern already duplicated in
  `MainMenuState.cpp` into a small reusable helper rather than copy-pasting
  it again, then use it for a minimal inventory grid (toggle key,
  equip/unequip action). Keep visuals bare for v1.
- This is also where `PlayState.cpp`'s temporary hardcoded test-equip block
  gets deleted, replaced by real pickups (or an empty inventory at spawn).

### 5. `Stats` aggregation — ⬜ not started
A small `Stats` struct: base `GameObject` stats + sum of every equipped
item's bonuses, recomputed whenever `Equipment` changes. Surface it
somewhere even simple (debug text is enough) to prove pick-up → stat change
→ visual change end-to-end.

## Verification

- Rebuild after each step (`cmake --build build`) and run
  `./build/RaidMyDungeon` to confirm no regressions in movement, animation,
  or weapon swinging.
- Since there's no input-simulation tool in this environment, visual checks
  so far have used a temporary debug patch (jump straight to `PlayState`,
  screenshot with `grim`, then revert the patch) rather than playing through
  the real Intro → Menu → Play flow. Same approach works for verifying
  step 4/5.
  **Timing gotcha learned the hard way:** don't drive the debug state with a
  time-based cycle (e.g. "switch direction every N seconds") and then take
  screenshots across several separate tool calls timed by `sleep` — real
  wall-clock time keeps passing for the background game process during the
  (unpredictable) time between tool calls, so the assumed phase and the
  actual one drift apart. What worked reliably: have the debug code read a
  command from a file every frame (e.g. `/tmp/rmd_cmd.txt` with a direction
  and a strike counter) and write its current state to a status file every
  frame; from the shell, write the command, poll the status file in a loop
  until it confirms the change landed, *then* screenshot — all inside one
  Bash call so no cross-call timing gap can sneak in.
- After step 4: pick up a world item, open the inventory, equip it, confirm
  the visual layer/weapon change.
- After step 5: confirm the stat readout changes to match what's equipped.

## Known rough edges / follow-ups (not blocking, but worth knowing about)

- `EquippedWeapon::socketOffsetFor()`'s per-direction position offsets (where
  the hand sits relative to the body center) are still a reasonable-guess
  first pass, unlike the rotation math which is now measured — there's no
  real character art yet with an actual hand position to measure against.
  Revisit once there is.
- `ItemDef::spritePath` currently serves double duty as both the inventory
  icon and the equipped-visual texture. Fine while they're the same
  placeholder file; may want to split into two fields once there's real
  inventory UI and the icon/equipped-art diverge.
- `Map`'s tileset texture still loads directly rather than through
  `ResourceManager` (mentioned as "eventually" in the original plan, not
  needed yet since there's only one map).
