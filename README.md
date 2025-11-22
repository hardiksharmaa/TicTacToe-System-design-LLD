# TicTacToe-System-design-LLD (C++)


![pic](https://github.com/user-attachments/assets/15d42309-820f-464f-80d7-246b11a10578)


A robust, object-oriented implementation of the classic Tic-Tac-Toe game designed for N x N grids. This project demonstrates clean code architecture, extensibility using design patterns, and algorithmic optimization suitable for Machine Coding Rounds.

   Features

Dynamic Grid Size: Supports any N x N grid (3x3, 4x4, 10x10, etc.).

Game Modes: - Human vs. Human (Hotseat)

Human vs. Bot (Random AI)

Smart Validations: Handles out-of-bounds errors and occupied cells gracefully.

Optimized Win checking: Uses an $O(N)$ algorithm instead of the standard $O(N^2)$ approach.

   Low-Level Design (LLD)

The system is architected using SOLID principles to ensure modularity. The core logic is decoupled from the game flow.

Class Breakdown

Class

Responsibility

PlayingPiece

Represents the entity on the board (X or O).

Board

Manages the Grid state, validates moves, and checks for win conditions. It is purely a data holder and rule enforcer.

Player (Abstract)

Interface for players. It enforces the makeMove() contract, allowing polymorphism.

HumanPlayer

Implementation of Player that reads input from the console.

BotPlayer

Implementation of Player that generates moves programmatically (Random Strategy).

TicTacToeGame

The Controller. It manages the game loop, turn rotation, and initializes the board/players.

   Visual Architecture

classDiagram
    class TicTacToeGame {
        - deque<Player*> players
        - Board* board
        + startGame()
    }
    class Board {
        - int size
        - vector grid
        + checkWin()
        + addPiece()
    }
    class Player {
        <<abstract>>
        + makeMove()
    }
    class HumanPlayer
    class BotPlayer

    TicTacToeGame --> Board : manages
    TicTacToeGame --> Player : contains
    Player <|-- HumanPlayer : inherits
    Player <|-- BotPlayer : inherits


   Design Patterns Used

1. Strategy Pattern (via Polymorphism)

The Player class is an abstract base class. The TicTacToeGame loop does not know if it is playing against a Human or a Machine. It simply calls:

player->makeMove(board);


This allows us to introduce a Minimax AI or a Hard Mode Bot later without changing a single line of the main game loop.

2. Single Responsibility Principle (SRP)

The Board only cares about the grid.

The Player only cares about picking a coordinate.

The Game only cares about whose turn it is.

  Algorithmic Optimization

A naive approach to check for a winner involves scanning the entire board ($O(N^2)$) after every turn.

   My approach:
I implemented an optimized check that only inspects the Row, Column, and Diagonal specific to the last move made.

Time Complexity: $O(N)$ per move.

Space Complexity: $O(N^2)$ for the grid.

   How to Run

Compile the code:

g++ tictactoe.cpp -o game


Run the executable:

./game


   Future Improvements

[ ] Implement Minimax Algorithm for an unbeatable AI.

[ ] Add an "Undo" feature using a Stack data structure.

[ ] Save/Load game state.


