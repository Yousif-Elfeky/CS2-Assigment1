# CS2 Assignment 1

## Overview

This project is a small turn-based game simulation written in C++. It models a
game where entities are grouped into opposing teams and take turns until one
team no longer has any active entities.

The simulation runs through a central `GameEngine`. The engine manages the
entities, prepares each round, determines turn order, validates possible
targets, processes actions, and displays the result when the game ends.

## Features

- Turn-based round and queue management
- Player-controlled and environment-controlled turns
- Entity health and active-state tracking
- Team-based target validation
- Console output for rounds, turns, actions, and results
- CMake-based build configuration

## Building

Requirements:

- A C++ compiler with C++26 support
- CMake 3.20 or newer

From the project directory, run:

```bash
cmake -S . -B build
cmake --build build
```

## Running

After building, run the executable with:

```bash
./build/CS2_Assigment1
```

The game is played through the terminal. Follow the prompts during
player-controlled turns. The simulation ends automatically when the game-over
condition is reached.

## Project Structure

- `include/` - Public headers and data structures
- `src/` - Game engine and entity implementation
- `main.cpp` - Creates a game and starts the simulation
- `CMakeLists.txt` - Build configuration