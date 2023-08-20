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
- [Note on Parsing Tabulations](#note-on-parsing-tabulations)
- [Collaborators](#collaborators)
- [License](#license)

## Introduction

Cub3D is an ongoing project that aims to recreate the 'immersive' gameplay experience of the original Wolfenstein and DOOM games, utilizing MLX and perspective rendering techniques to achieve an atmosphere that pays homage to the retro classics.

## Features

 - Cub3D utilizes perspective rendering techniques to provide a sense of depth in a 2D environment, delivering an experience reminiscent of the original games.
 - Experience familiar textures and environments through texture mapping, capturing the visual essence of the classic games.
 - Cub3D employs a map configuration system using `.cub` files as input. These files specify elements like textures, colors, and the layout of the game world.

## Project Progress

- The map parsing phase has been successfully completed and the map has been parsed into a 2D matrix. As of August 19, 2023, the project is currently focused on graphical booting using the MiniLibX screen display.

## Getting Started

### Prerequisites

- Ensure you have the MiniLibX library installed on your system.

### Installation

1. Clone this repository: `git clone <repository_url>`
2. Navigate to the project directory: `cd Cub3D`
3. Compile the project: `make`
4. Run the game: `./cub3D <filename.cub>`

### Usage

- Launch the game by providing a `.cub` file as a command-line argument.
- Move around using the arrow keys (not yet implemented).
- Interact with the environment (not yet implemented).

## Note on Parsing Tabulations

As the project guidelines do not specify how to parse tabulations, we have applied the following rule:
- Each tab is equivalent to 8 spaces.
- This rule is based on the common practice of text editors.
- Please be aware that creating a map in VS Code may not accurately reflect the actual map appearance, as each tab in that editor is equal to 4 spaces.

## Collaborators

- [Tiago Pereira](https://github.com/t-pereira06)
- [Rafael Soares](https://github.com/RafaSoares1)
- [José Pedro](https://github.com/ZPedro99)

## License

- This project is being developed as part of the 42 Porto curriculum.
