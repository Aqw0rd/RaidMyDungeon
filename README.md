# Raid My Dungeon

A small 2D dungeon-crawler prototype written in C++17 with SFML 3. This was an early hobby/learning project (built ~January–November 2018) exploring game architecture patterns: a state machine, a `GameObject`/`Item`/`Ability` class hierarchy, and Tiled-based map loading.

It's an unfinished prototype rather than a playable game — there's a main menu, a movable player character on a loaded dungeon map, and the beginnings of an item/weapon/ability system.

## Features

- **State machine** driving the app: `IntroState` → `MainMenuState` → `PlayState`, with states pushed/popped on a stack (`StateMachine`).
- **Tile-based maps** loaded from [Tiled](https://www.mapeditor.org/) JSON exports (`Resources/Levels/`) via `jsoncpp`, rendered layer by layer (`Map` / `MapLayer`).
- **Player character** with WASD movement (including normalized diagonal movement), sprite-sheet walk animation, and mouse-driven facing direction.
- **Item / Weapon / Ability scaffolding**: a base `GameObject` class, an `Item` → `Weapon` → `IronSword` hierarchy, and an `Ability` → `Melee` → `NormalAttack` hierarchy, intended as the foundation for combat.
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
GameObject.*           Base class for anything with position/HP/energy/sprite
Objects/Player.*       Player-specific movement, animation, and input handling
Item.*, Items/         Item base class, Weapon base class, IronSword
Ability.*, Abilities/  Ability base class, Melee base class, NormalAttack
Map.*, MapLayer.*      Tiled JSON map loading and rendering
Resources/             Fonts, sprites, images, and Tiled level files
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

This was a learning project and was left unfinished:

- No combat is actually resolved yet — the `Ability`/`Weapon` classes exist but a strike doesn't deal damage.
- Only one level (`Dungeon 1.json`) exists, and there's no win/lose condition.
- `Item` isn't actually the parent of `Weapon` despite the naming (`Weapon` duplicates its own texture/sprite members instead of inheriting), and `Item`'s constructor is declared but never defined — it's dead code left over from an earlier design.
- The `Ability`/`Melee`/`NormalAttack` hierarchy isn't wired into `Player` or `Weapon` yet; it's unused scaffolding for a future ability system.
