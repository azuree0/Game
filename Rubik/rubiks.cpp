#include <iostream>
#include <vector>

class RubiksCube {
public:
    RubiksCube() {
        // Initialize the cube with colors (6 faces, each face with 3x3 grid)
        cube = {
            {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, // Red
            {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'}, // Green
            {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'}, // Blue
            {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // Orange
            {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'}, // White
            {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'}  // Yellow
        };
    }

    void rotateFace(int face) {
        // Rotate the face clockwise
        std::vector<char> temp = cube[face];
        cube[face][0] = temp[6];
        cube[face][1] = temp[3];
        cube[face][2] = temp[0];
        cube[face][3] = temp[7];
        cube[face][4] = temp[4];
        cube[face][5] = temp[1];
        cube[face][6] = temp[8];
        cube[face][7] = temp[5];
        cube[face][8] = temp[2];

        // Rotate adjacent faces
        switch (face) {
            case 0: // Red
                std::swap(cube[1][0], cube[4][0]); // G -> O
                std::swap(cube[1][1], cube[4][1]);
                std::swap(cube[1][2], cube[4][2]);
                std::swap(cube[2][0], cube[1][0]); // B -> G
                std::swap(cube[2][0], cube[2][0]); // No need to swap
                std::swap(cube[3][0], cube[2][0]); // O -> B
                break;
            case 1: // Green
                // Implement Green face rotation logic
                break;
            case 2: // Blue
                // Implement Blue face rotation logic
                break;
            case 3: // Orange
                // Implement Orange face rotation logic
                break;
            case 4: // White
                // Implement White face rotation logic
                break;
            case 5: // Yellow
                // Implement Yellow face rotation logic
                break;
        }
    }

    void printCube() {
        for (int i = 0; i < 6; ++i) {
            std::cout << "Face " << i << ":\n";
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    std::cout << cube[i][j * 3 + k] << ' ';
                }
                std::cout << '\n';
            }
            std::cout << '\n';
        }
    }

private:
    std::vector<std::vector<char>> cube; // 6 faces with 9 squares each
};

int main() {
    RubiksCube myCube;
    myCube.printCube();

    std::cout << "Rotating face 0 (Red) clockwise...\n";
    myCube.rotateFace(0);
    myCube.printCube();

    return 0;
}