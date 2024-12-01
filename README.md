# C Games Collection

A collection of classic console games implemented in C. This repository includes three well-known games: **Blackjack**, **Connect Four**, and **Tic Tac Toe**. Each game is implemented with modular code, showcasing fundamental programming concepts and providing a simple, interactive terminal-based experience.

## Table of Contents
- [Introduction](#introduction)
- [Games Included](#games-included)
- [Features](#features)
- [How to Play](#how-to-play)
- [How to Contribute](#how-to-contribute)
- [Code Structure](#code-structure)

## Introduction
This repository is a collection of simple console games implemented in C. Each game is designed to run in the terminal with a focus on clean, organized code and basic game mechanics. The project demonstrates how to structure small games, manage state, handle user input, and output results to the terminal.

## Games Included
1. **Blackjack**:  
   A feature-rich implementation of the classic card game, including multiple decks, dynamic leaderboards, and data persistence. It allows players to choose game modes, track their progress, and interact with the game via a simple terminal interface.

2. **Battleship**:
   This is a text-based implementation of the classic Battleship game, where players strategically place ships on a grid and attempt to sink the opponent's fleet. The game is played in turns, with each player choosing coordinates to target the enemy's ships. The goal is to be the first to sink all of the opponent's ships. This game is designed for two players, with a simple, clean user interface that is played in the terminal. The code structure is modular, allowing for easy updates or customizations.

3. **Connect Four**:  
   A two-player strategy game where players aim to connect four discs in a row. The implementation focuses on game mechanics, handling user input, and checking for winning conditions.

4. **Tic Tac Toe**:  
   A simple, classic two-player game where players take turns marking spaces on a 3x3 grid, with the goal of aligning three marks in a row.

## Features
- **Modular design**: The code is organized into separate files and functions to keep it clean, maintainable, and easy to understand.
- **File I/O**: The Blackjack game supports saving and loading game state, player stats, and leaderboards, making it more dynamic and persistent.
- **User interface**: Each game provides an interactive text-based interface that runs directly in the terminal.
- **Replayability**: Games like Blackjack track player progress, with features like leaderboards and achievements.

## How to Play
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/c_games.git
   ```
   
2. Navigate to the game folder:
   ```bash
   cd c_games/blackjackfolder   # For Blackjack game
   cd c_games/battleshipfolder  # For Battleship game
   cd c_games/connectfourfolder # For Connect Four game
   cd c_games/tictactoefolder   # For Tic Tac Toe game
   ```

3. Compile the game using a C compiler:
   ```bash
   gcc blackjack.c cardsystem.c printingsystem.c savingsystem.c -o blackjack
   gcc battleship.c printingsystem.c soundsystem.c -Wall -I/usr/include/SDL2 -lSDL2 -lSDL2_mixer -o battleship
   gcc connectfour.c -o connectfour
   gcc tictactoe.c -o tictactoe
   ```

4. Run the compiled executable:
   ```bash
   ./blackjack   # For Blackjack game
   ./battleship  # For Battleship game
   ./connectfour # For Connect Four game
   ./tictactoe   # For Tic Tac Toe game
   ```

## How to Contribute
This project is open to contributions. You can contribute by:
- Fixing bugs or improving existing features.
- Adding new features, such as additional game modes, improved AI, or multiplayer support.
- Refactoring code for optimization and readability.

To contribute:
1. Fork the repository.
2. Create a new branch for your changes.
3. Submit a pull request with a description of the changes you made.

## Code Structure
The repository is organized into separate folders for each game, with the following files:

- **Blackjack**:
  - `blackjack.c`: Main game logic.
  - `cardsystem.c`/`cardsystem.h`: Card deck management.
  - `printingsystem.c`/`printingsystem.h`: Game interface and output.
  - `savingsystem.c`/`savingsystem.h`: Saving and loading game state.

- **Battleship**:
  - `battleship.c`: Main game logic for Battleship.
  - `printingsystem.c`: Game interface and output.
  - `soundsystem.c`: Handles sound init, sound play and sound cleanup.

- **Connect Four**:
  - `connectfour.c`: Main game logic for Connect Four.

- **Tic Tac Toe**:
  - `tictactoe.c`: Main game logic for Tic Tac Toe.

---
