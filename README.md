# Raid My Dungeon

A small 2D dungeon-crawler prototype written in C++17 with SFML 3. This was an early hobby/learning project (built ~January–November 2018), picked back up as the start of a roguelike dungeon-crawler with data-driven loot and (eventually) community-designed, shareable dungeons.

It's an unfinished prototype rather than a playable game — there's a main menu, a movable player character on a loaded dungeon map, and a data-driven item/gear system with no inventory UI yet. See [`docs/plans/`](docs/plans/) for what's actively being worked on.

## Features

- **State machine** driving the app: `IntroState` → `MainMenuState` → `PlayState`, with states pushed/popped on a stack (`StateMachine`).
- **Tile-based maps** loaded from [Tiled](https://www.mapeditor.org/) JSON exports (`Resources/Levels/`) via `jsoncpp`, rendered layer by layer (`Map` / `MapLayer`).
- **Player character** with WASD movement (including normalized diagonal movement), sprite-sheet walk animation, and mouse-driven facing direction.
- **Data-driven items** (`ItemDef`/`ItemDatabase`): weapons and gear are defined in `Resources/Items/*.json`, not C++ classes — adding a new item needs no new code.
- **Layered ("paperdoll") gear rendering**: `GameObject` composites a body sprite with optional Legs/Chest/Head layers sharing the same animation grid, so equipped gear changes the character's appearance without redrawing it. A single generic `EquippedWeapon` class (not one class per weapon) renders and swings whatever's equipped.
- **`Ability`/`Melee`/`NormalAttack` scaffolding**: unused so far, intended as the foundation for a future ability system.
- **Framerate-independent updates** — movement speed is scaled by the frame's gametick so gameplay doesn't speed up/slow down with FPS.

## Controls

| Input | Action |
|---|---|
| `W` / `A` / `S` / `D` | Move up / left / down / right |
| `Up` / `Down` (main menu) | Change selected menu option |
| `Enter` (main menu) | Confirm selection (Play / Exit) |
| Left mouse button | Strike with weapon |
| `Escape` | Return to the previous state |

## Project structure

```
main.cpp              Entry point — creates the App and runs the main loop
App.*                 Owns the SFML window, Config, and StateMachine
Config.*               Global settings (resolution, resource paths, current map)
State.*, StateMachine.* Base state class and the state stack
States/                IntroState, MainMenuState, PlayState
ResourceManager.*      Shared, cached texture loading
GameObject.*           Base class for anything with position/HP/energy/layered sprites
Objects/Player.*       Player-specific movement, animation, and input handling
ItemDef.*, ItemDatabase.* Data-driven item definitions, loaded from Resources/Items/*.json
Items/EquippedWeapon.* Generic weapon rendering/swinging, driven by an ItemDef
Ability.*, Abilities/  Ability base class, Melee base class, NormalAttack (unused scaffolding)
Map.*, MapLayer.*      Tiled JSON map loading and rendering
Resources/             Fonts, sprites, images, item definitions, and Tiled level files
docs/plans/             In-progress feature plans, with a step-by-step status tracker
```

## Building

### Dependencies

- CMake ≥ 3.9
- A C++17 compiler
- [SFML 3](https://www.sfml-dev.org/) (graphics, window, system, audio)
- [JsonCpp](https://github.com/open-source-parsers/jsoncpp)

On Arch/CachyOS:

```bash
sudo pacman -S cmake sfml jsoncpp
```

On Debian/Ubuntu:

```bash
sudo apt install cmake libsfml-dev libjsoncpp-dev
```

### Build & run

```bash
mkdir -p build && cd build
cmake ..
make
./RaidMyDungeon
```

Run the resulting binary from the project root (or copy it there) so it can find the `Resources/` directory using its relative paths.

## Known limitations

- No combat is actually resolved yet — a strike swings the weapon but doesn't deal damage.
- There's no inventory or equipment UI yet — `PlayState`'s constructor hardcodes a fixed set of test items onto the player at spawn. See [`docs/plans/weapon-and-gear-system.md`](docs/plans/weapon-and-gear-system.md) for the in-progress plan.
- Only one level (`Dungeon 1.json`) exists, and there's no win/lose condition.
- The `Ability`/`Melee`/`NormalAttack` hierarchy isn't wired into `Player` or `EquippedWeapon` yet; it's unused scaffolding for a future ability system.
- The gear art in `Resources/Sprites/Gear/` is placeholder (flat colored blocks), not real art.

## In-progress plans

- [`docs/plans/weapon-and-gear-system.md`](docs/plans/weapon-and-gear-system.md) — data-driven weapons/gear, paperdoll rendering, inventory. Each plan file has a step-by-step progress tracker at the top, so a new session can see what's done and what's next at a glance.
