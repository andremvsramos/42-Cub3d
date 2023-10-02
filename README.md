# 42-Cub3D Project

Welcome to the Cub3D project, a recreation of the nostalgic ambiance from the original Wolfenstein and DOOM games. Using the MiniLibX (MLX) library and perspective rendering techniques, Cub3D brings back the retro gaming experience. Please note that Cub3D does not feature true 3D graphics but aims to recapture the essence of those iconic games.

## Project Completion and Submission

- **Completion Date:** October 2nd, 2023
- **Project Submission:** Successfully submitted with a score of 125/125

![Screenshot from 2023-10-02 15-22-43](https://github.com/andremvsramos/42-Cub3d/assets/115324164/11e7b98c-71af-477e-bc50-5d9c422f5775)


## Table of Contents

- [42-Cub3D Project](#42-cub3d-project)
  - [Project Completion and Submission](#project-completion-and-submission)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
    - [Usage](#usage)
  - [Note on Parsing Map File Tabulations](#note-on-parsing-map-file-tabulations)
  - [Project Screenshots](#project-screenshots)
  - [Collaborators](#collaborators)
  - [License](#license)

## Introduction

Cub3D is an ongoing project that aims to recreate the 'immersive' gameplay experience of the original Wolfenstein and DOOM games, utilizing MLX and perspective rendering techniques to achieve an atmosphere that pays homage to the retro classics.

## Features

 - Cub3D utilizes perspective rendering techniques to provide a sense of depth in a 2D environment, delivering an experience reminiscent of the original games.
 - Experience familiar textures and environments through texture mapping, capturing the visual essence of the classic games.
 - Cub3D employs a map configuration system using `.cub` files as input. These files specify elements like textures, colors, and the layout of the game world.

## Getting Started

### Prerequisites

- Ensure you have the MiniLibX library installed on your system.

### Installation

1. Clone this repository as such: `git clone git@github.com:andremvsramos/42-Cub3d.git CUB3D`
2. Navigate to the project directory: `cd CUB3D`
3. Compile the project: `make` for mandatory (no door or door textures allowed) ; `make bonus` for bonus (must have       door texture pathing).
4. Run the game: `./cub3D <filename.cub>` | `./cub3D_Bonus <filename.cub>`

### Usage

- Launch the game by providing a `.cub` file as a command-line argument.
- Move around using the arrow keys (not yet implemented).
- Interact with the environment (not yet implemented).

## Note on Parsing Map File Tabulations

As the project guidelines do not specify how to parse tabulations, we have applied the following rule:
- Each tab is equivalent to 8 spaces.
- This rule is based on the common practice of text editors.
- Please be aware that creating a map in VS Code may not accurately reflect the actual map appearance, as each tab in that editor is equal to 4 spaces.
Please refer to the provided map files for references.

## Project Screenshots

Here are some screenshots showcasing different aspects of the project:

- Main Menu: ![Screenshot from 2023-10-02 15-12-29](https://github.com/andremvsramos/42-Cub3d/assets/115324164/110f4f93-bdf9-4f22-bea7-4df5a329f0f2)


- Gameplay 1: ![Screenshot from 2023-10-02 15-12-38](https://github.com/andremvsramos/42-Cub3d/assets/115324164/bb1837b4-1417-4576-a076-e5332f9cf74f)

- Gameplay 2: ![Screenshot from 2023-10-02 15-13-11](https://github.com/andremvsramos/42-Cub3d/assets/115324164/363ee4be-53ae-41fa-875b-6bb1129db647)


## Collaborators

- [Tiago Pereira](https://github.com/t-pereira06)

## License

- This project is being developed as part of the 42 Porto curriculum.
