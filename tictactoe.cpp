#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <cstdlib>
#include <ctime>

using namespace std;

enum PieceType { X, O, EMPTY };

class PlayingPiece {
public:
    PieceType type;
    PlayingPiece(PieceType type) : type(type) {}
};


class Board {
    int size;
    vector<vector<PieceType>> grid;
    int freeCells;

public:
    Board(int size) : size(size), freeCells(size * size) {
        grid.resize(size, vector<PieceType>(size, EMPTY));
    }

    int getSize() { return size; }

    void printBoard() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                char symbol = '-';
                if (grid[i][j] == X) symbol = 'X';
                else if (grid[i][j] == O) symbol = 'O';
                
                cout << " " << symbol << " ";
                if (j < size - 1) cout << "|";
            }
            cout << endl;
            if (i < size - 1) {
                for(int k=0; k<size; k++) cout << "--- ";
                cout << endl;
            }
        }
        cout << endl;
    }

    bool isValidMove(int row, int col) {
        return (row >= 0 && row < size && col >= 0 && col < size && grid[row][col] == EMPTY);
    }

    bool addPiece(int row, int col, PieceType pieceType) {
        if (!isValidMove(row, col)) return false;
        grid[row][col] = pieceType;
        freeCells--;
        return true;
    }

    vector<pair<int, int>> getFreeCells() {
        vector<pair<int, int>> cells;
        for(int i=0; i<size; i++) {
            for(int j=0; j<size; j++) {
                if(grid[i][j] == EMPTY) cells.push_back({i, j});
            }
        }
        return cells;
    }

    bool isFull() {
        return freeCells == 0;
    }

    bool checkWin(int row, int col, PieceType pieceType) {
        bool rowMatch = true, colMatch = true, diagMatch = true, antiDiagMatch = true;

        for (int i = 0; i < size; i++) {
            if (grid[row][i] != pieceType) rowMatch = false;
        }
        
        for (int i = 0; i < size; i++) {
            if (grid[i][col] != pieceType) colMatch = false;
        }

        for (int i = 0; i < size; i++) {
            if (grid[i][i] != pieceType) diagMatch = false;
        }

        for (int i = 0; i < size; i++) {
            if (grid[i][size - 1 - i] != pieceType) antiDiagMatch = false;
        }

        return rowMatch || colMatch || diagMatch || antiDiagMatch;
    }
};


class Player {
public:
    string name;
    PieceType piece;

    Player(string name, PieceType piece) : name(name), piece(piece) {}

    virtual pair<int, int> makeMove(Board& board) = 0; 
};

class HumanPlayer : public Player {
public:
    HumanPlayer(string name, PieceType piece) : Player(name, piece) {}

    pair<int, int> makeMove(Board& board) override {
        int r, c;
        cout << "Player " << name << " (" << (piece == X ? "X" : "O") << ") turn." << endl;
        cout << "Enter row and column (0-" << board.getSize()-1 << "): ";
        cin >> r >> c;
        return {r, c};
    }
};

class BotPlayer : public Player {
public:
    BotPlayer(string name, PieceType piece) : Player(name, piece) {}

    pair<int, int> makeMove(Board& board) override {
        cout << "Bot " << name << " is thinking..." << endl;
        vector<pair<int, int>> moves = board.getFreeCells();
        if(moves.empty()) return {-1, -1}; 
        
        int idx = rand() % moves.size();
        return moves[idx];
    }
};

class TicTacToeGame {
    Board* board;
    deque<Player*> players;

public:
    TicTacToeGame() {
        board = nullptr;
    }

    void initializeGame() {
        int n;
        cout << "Enter Board Size (N): ";
        cin >> n;
        board = new Board(n);

        string name1;
        cout << "Enter Player 1 Name: ";
        cin >> name1;
        
        char symbolChoice;
        cout << "Choose Symbol for " << name1 << " (X/O): ";
        cin >> symbolChoice;

        PieceType p1Type = (symbolChoice == 'X' || symbolChoice == 'x') ? X : O;
        PieceType p2Type = (p1Type == X) ? O : X;

        players.push_back(new HumanPlayer(name1, p1Type));

        int mode;
        cout << "Select Opponent: 1. Human  2. AI Bot: ";
        cin >> mode;

        string name2;
        if (mode == 1) {
            cout << "Enter Player 2 Name: ";
            cin >> name2;
            players.push_back(new HumanPlayer(name2, p2Type));
        } else {
            players.push_back(new BotPlayer("Terminator", p2Type));
        }
    }

    void startGame() {
        bool noWinner = true;
        
        while (noWinner) {
            board->printBoard();
            
            Player* currentPlayer = players.front();
            
            bool validMoveMade = false;
            int r, c;

            while(!validMoveMade) {
                pair<int, int> move = currentPlayer->makeMove(*board);
                r = move.first;
                c = move.second;

                if(board->addPiece(r, c, currentPlayer->piece)) {
                    validMoveMade = true;
                } else {
                    cout << "Invalid Move! Try again." << endl;
                }
            }

            if (board->checkWin(r, c, currentPlayer->piece)) {
                board->printBoard();
                cout << "Congratulations! " << currentPlayer->name << " has won!" << endl;
                return;
            }

            if (board->isFull()) {
                board->printBoard();
                cout << "It's a Draw!" << endl;
                return;
            }
            players.pop_front();
            players.push_back(currentPlayer);
        }
    }
};

int main() {
    srand(time(0));
    TicTacToeGame game;
    game.initializeGame();
    game.startGame();
    return 0;
}