# Supercell Coding Test
Hi! This is the base code structure for the Supercell coding test.
The code below is a very basic and intensionally broken version of a generic platformer game.

## Info
This C++ code base is built using  [SFML](https://www.sfml-dev.org/index.php) and is configured to generate XCode and Visual Studio projects.

[CMake](https://cmake.org/) version 3.22 or later is required to generate the projects.  
>The project is configured for a limited purpose (i.e. to generate an XCode or VS project easily).  It is not setup to build within CMake or be installed etc.

## How to generate project files

### Visual Studio 2022
One you have the project cloned to your PC.  Open a command prompt and from the source code directory run:
`cmake -B./build -G"Visual Studio 17 2022"`

Open `platformer_test.sln` from `/build`

### Visual Studio 2019
One you have the project cloned to your PC.  Open a command prompt and from the source code directory run:
`cmake -B./build -G"Visual Studio 16 2019"`

Open `platformer_test.sln` from `/build`

## Game Instructions

**Keyboard Controls:**
- Jump: Space/Up arrow
- Move Left/Right: Left/Right arrow keys
- Developer Menu: F1

**Xbox Gamepad formation- Controls:**
- Jump: A
- Move Left/Right: L/R

<!-- ### XCode -
One you have the project cloned to your MAC.  Open a terminal and from the source code directory run:
`cmake -B./build -GXcode`

Open `platformer_test.xcodeproj` from `/build`
You'll also have to select `Platformer` from the project selection dropdown menu in XCsode. -->
