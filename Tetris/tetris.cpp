#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 10, HEIGHT = 20;
vector<vector<int>> field(HEIGHT, vector<int>(WIDTH, 0));
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Color codes
enum Colors {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3,
    RED = 4, MAGENTA = 5, BROWN = 6, LIGHTGRAY = 7,
    DARKGRAY = 8, LIGHTBLUE = 9, LIGHTGREEN = 10,
    LIGHTCYAN = 11, LIGHTRED = 12, LIGHTMAGENTA = 13,
    YELLOW = 14, WHITE = 15
};

// Define Tetris shapes
int shapes[7][4][4] = {
    { {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }, // Line
    { {1, 1, 1}, {0, 1, 0}, {0, 0, 0} },                         // T-shape
    { {1, 1, 0}, {0, 1, 1}, {0, 0, 0} },                       // Z-shape
    { {0, 1, 1}, {1, 1, 0}, {0, 0, 0} },                       // S-shape
    { {1, 0, 0}, {1, 1, 1}, {0, 0, 0} },                       // L-shape
    { {0, 0, 1}, {1, 1, 1}, {0, 0, 0} },                       // J-shape
    { {1, 1}, {1, 1}, {0, 0} }                                 // O-shape
};

void setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void draw() {
    system("cls");
    for (const auto& row : field) {
        for (int cell : row) {
            setColor(cell ? (cell + 10) : 7);  // Color for blocks, white for empty
            cout << (cell ? "#" : ".");
        }
        cout << endl;
    }
}

bool checkCollision(int piece[4][4], int offsetX, int offsetY) {
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (piece[y][x] && (x + offsetX < 0 || x + offsetX >= WIDTH || y + offsetY >= HEIGHT || (y + offsetY >= 0 && field[y + offsetY][x + offsetX])))
                return true;
    return false;
}

void placePiece(int piece[4][4], int offsetX, int offsetY, int color) {
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (piece[y][x]) field[y + offsetY][x + offsetX] = color; // Store color
}

void clearLines() {
    for (int y = HEIGHT - 1; y >= 0; y--) {
        if (all_of(field[y].begin(), field[y].end(), [](int cell) { return cell; })) {
            field.erase(field.begin() + y);
            field.insert(field.begin(), vector<int>(WIDTH, 0));
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int currentPieceIndex = rand() % 7; // Randomly select a piece
    int offsetX = WIDTH / 2 - 2, offsetY = 0;
    int currentColor = (rand() % 7) + 2; // Random color for the piece

    while (true) {
        draw();
        if (checkCollision(shapes[currentPieceIndex], offsetX, offsetY + 1)) {
            placePiece(shapes[currentPieceIndex], offsetX, offsetY, currentColor);
            clearLines();
            currentPieceIndex = rand() % 7; // Randomize next piece
            offsetX = WIDTH / 2 - 2; offsetY = 0;
            currentColor = (rand() % 7) + 2; // Random color for the next piece
            if (checkCollision(shapes[currentPieceIndex], offsetX, offsetY)) break;  // Game over
        } else {
            offsetY++;
        }

        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a' && !checkCollision(shapes[currentPieceIndex], offsetX - 1, offsetY)) offsetX--;
            if (ch == 'd' && !checkCollision(shapes[currentPieceIndex], offsetX + 1, offsetY)) offsetX++;
            if (ch == 's' && !checkCollision(shapes[currentPieceIndex], offsetX, offsetY + 1)) offsetY++;
        }
        Sleep(500);
    }
    setColor(RED); // Red for Game Over
    cout << "Game Over!" << endl;
    return 0;
}