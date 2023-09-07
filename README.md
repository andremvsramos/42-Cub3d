# 42-Cub3D Project

Welcome to the Cub3D project, a recreation of the nostalgic ambiance from the original Wolfenstein and DOOM games. Using the MiniLibX (MLX) library and perspective rendering techniques, Cub3D brings back the retro gaming experience. Please note that Cub3D does not feature true 3D graphics but aims to recapture the essence of those iconic games.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Project Progress](#project-progress)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
- [Note on Parsing Map File Tabulations](#note-on-parsing-map-file-tabulations)
- [Collaborators](#collaborators)
- [License](#license)

## Introduction

Cub3D is an ongoing project that aims to recreate the 'immersive' gameplay experience of the original Wolfenstein and DOOM games, utilizing MLX and perspective rendering techniques to achieve an atmosphere that pays homage to the retro classics.

## Features

 - Cub3D utilizes perspective rendering techniques to provide a sense of depth in a 2D environment, delivering an experience reminiscent of the original games.
 - Experience familiar textures and environments through texture mapping, capturing the visual essence of the classic games.
 - Cub3D employs a map configuration system using `.cub` files as input. These files specify elements like textures, colors, and the layout of the game world.

## Project Progress

- **Parsing Phase Completion (August 19, 2023):** The map parsing phase has been successfully completed, and the map data has been successfully parsed into a 2D matrix. This crucial step lays the foundation for the game world.
  
- **Texture Parsing Milestone (August 23, 2023):** We're excited to share our recent accomplishment - the successful completion of the texture parsing phase on August 23, 2023. This advancement marks a pivotal moment in our journey, as we've triumphantly decoded texture files. This achievement opens the door to texture mapping within our gaming universe, a significant stride toward enriching visual depth and intricate detailing.

- **Graphical Booting Milestone (August 23, 2023):** On August 23, 2023, we achieved a key milestone in our project. We successfully implemented graphical booting using the MiniLibX screen display. This accomplishment lays the groundwork for rendering. However, we're continuing our efforts to refine rendering processes, as detailed in our raycasting progress below.

- **Minimap Prototype (September 06, 2023):** We've added a prototype for a minimap bonus feature (commented out of the rendering). This feature will provide players with a top-down view of the game world, enhancing navigation and orientation.

- **Raycasting Implementation (September 06, 2023):** We're thrilled to announce that raycasting has been successfully implemented as of September 06, 2023. This marks a significant milestone in our project, as it forms the basis for rendering the 3D environment and creating immersive gameplay.

- **Erratic Movement (In Progress):** While basic player movement exists, it currently exhibits erratic behavior. Movement speed is excessively fast, and there are issues with screen rendering when applying movement in certain directions. We are actively working on resolving these issues to ensure smooth and accurate movement within the game world.

- **Texture Implementation (Future Feature):** Our next major goal is to start implementing external textures using XPM files. This will significantly enhance the visual quality of the game, replacing simple colors for walls and opening the door to exciting future features like doors, textures, and more.

## Getting Started

### Prerequisites

- Ensure you have the MiniLibX library installed on your system.

### Installation

1. Clone this repository as such: `git clone git@github.com:andremvsramos/42-Cub3d.git CUB3D`
2. Navigate to the project directory: `cd CUB3D`
3. Compile the project: `make`
4. Run the game: `./cub3D <filename.cub>`

### Usage

- Launch the game by providing a `.cub` file as a command-line argument.
- Move around using the arrow keys (not yet implemented).
- Interact with the environment (not yet implemented).

## Note on Parsing Map File Tabulations

As the project guidelines do not specify how to parse tabulations, we have applied the following rule:
- Each tab is equivalent to 8 spaces.
- This rule is based on the common practice of text editors.
- Please be aware that creating a map in VS Code may not accurately reflect the actual map appearance, as each tab in that editor is equal to 4 spaces.

## Collaborators

- [Tiago Pereira](https://github.com/t-pereira06)

## License

- This project is being developed as part of the 42 Porto curriculum.
