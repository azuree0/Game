#include <iostream>
#include <vector>

class GoBoard {
public:
    GoBoard(int size) : size(size), board(size, std::vector<char>(size, '.')) {}

    void display() const {
        std::cout << "   ";
        for (int i = 0; i < size; ++i) {
            std::cout << i + 1 << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < size; ++i) {
            std::cout << i + 1 << "  ";
            for (int j = 0; j < size; ++j) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool placeStone(int x, int y, char player) {
        if (x < 1 || x > size || y < 1 || y > size) {
            std::cout << "Invalid position!" << std::endl;
            return false;
        }
        if (board[x - 1][y - 1] != '.') {
            std::cout << "Position already occupied!" << std::endl;
            return false;
        }
        board[x - 1][y - 1] = player;
        return true;
    }

private:
    int size;
    std::vector<std::vector<char>> board;
};

int main() {
    GoBoard board(9);
    char currentPlayer = 'X';
    int x, y;

    while (true) {
        board.display();
        std::cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        std::cin >> x >> y;

        if (!board.placeStone(x, y, currentPlayer)) {
            continue; // Invalid move, prompt again
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}