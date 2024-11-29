#include <iostream>
#include <vector>
#include <iomanip>
#include <stack>

class GoBoard {
public:
    static const int SIZE = 19; // Size of the Go board
    std::vector<std::vector<std::string>> board; // Using std::string for board representation
    std::stack<std::pair<int, int>> moveHistory;

    GoBoard() {         // Initialize a 19x19 board with empty spaces
        board.resize(SIZE, std::vector<std::string>(SIZE, "."));

        board[3][3] = "◘";   
        board[3][15] = "◘"; 
        board[15][3] = "◘";  
        board[15][15] = "◘"; 

        board[9][3] = "◘"; 
        board[3][9] = "◘"; 
        board[9][15] = "◘"; 
        board[15][9] = "◘"; 

        board[9][9] = "◘"; 
    }

    void display() { // Initial space for column numbers
        std::cout << "  "; 
        for (int i = 0; i < SIZE; ++i) {
            std::cout << std::setw(2) << i + 1; // Column numbers from 1 to 19
        }
        std::cout << '\n';

        for (int i = 0; i < SIZE; ++i) {
            std::cout << std::setw(2) << i + 1; // Row numbers
            for (int j = 0; j < SIZE; ++j) {  // Display circles based on the board state
                if (board[i][j] == "◘") {
                    std::cout << std::setw(2) << "◘";
                } else if (board[i][j] == "b") { 
                    std::cout << std::setw(2) << "⚫"; 
                } else if (board[i][j] == "w") {
                    std::cout << std::setw(2) << "⚪"; 
                } else {
                    std::cout << std::setw(2) << '+'; 
                }
            }
            std::cout << '\n';
        }
    }

    bool placeStone(int x, int y, const std::string& stone) { 
        // Check for valid move
        if (x < 1 || x > SIZE || y < 1 || y > SIZE || (stone != "b" && stone != "w")) {
            std::cout << "Invalid move!\n";
            return false;
        }
        board[x - 1][y - 1] = stone; // Place the stone
        moveHistory.push({x - 1, y - 1}); 
        return true;
    }

    void undo() {
        if (moveHistory.empty()) {
            std::cout << "No moves to undo!\n";
            return;
        }
        // Get the last move
        auto lastMove = moveHistory.top();
        moveHistory.pop();
        // Remove the stone
        board[lastMove.first][lastMove.second] = "."; // Reset the position to empty
        std::cout << "Last move undone.\n";
    }
};

int main() {
    GoBoard goBoard;
    goBoard.display(); // Display the board with initial setup

    int row, col;
    std::string stone;

    // Example of placing stones interactively
    while (true) {
        std::cout << "Enter row (1-19), column (1-19), and stone (b/w) or '0' to exit: ";
        std::cin >> row;

        // Exit condition
        if (row == 0) {
            break;
        }
        std::cin >> col >> stone;

        // Attempt to place the stone
        if (stone == "0") { // If the user wants to undo
            goBoard.undo();
        } else if (!goBoard.placeStone(row, col, stone)) {
            std::cout << "Try again.\n";
        }

        goBoard.display(); // Display the board after each move
    }

    return 0;
}    