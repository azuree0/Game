#include <iostream>

using namespace std;

char square[10] = {'0',  '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int checkwin() {
    // Winning combinations
    int winConditions[8][3] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, // Rows
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, // Columns
        {1, 5, 9}, {3, 5, 7}             // Diagonals
    };

    // Check for a win
    for (int i = 0; i < 8; i++) {
        if (square[winConditions[i][0]] == square[winConditions[i][1]] &&
            square[winConditions[i][1]] == square[winConditions[i][2]]) {
            return 1;
        }
    }

    // Check for a draw
    for (int i = 1; i <= 9; i++) {
        if (square[i] == '0' + i) { // Assuming square[i] contains '1' to '9' for empty
            return -1; // Not yet finished
        }
    }

    return 0; // Draw
}    

void board() {
    system("cls");
    cout << "\n\nTic Tac Toe Game \n\n"; 
    cout << "Player 1 (X) Player 2 (O)" << endl << endl; 

    for (int i = 1; i <= 9; i += 3) {
        cout << " " << square[i] << "   |   " << square[i + 1] << "   |   " << square[i + 2] << endl;
        if (i < 7) { // Print the separator only between rows
            cout << "_____|___|____" << endl;
        }
    }
    cout << "          |       |         " << endl << endl;
}

#include <iostream>
using namespace std;

// Assume necessary functions and global variables (like square) are defined above this

int main() {
    int player = 1; // Start with player 1
    int choice;     // Variable for user input
    int i;          // Variable to hold the result of checkwin

    do {
        board(); // Display the current board
        i = checkwin(); // Check for a win or draw

        if (i == -1) { // Game is still ongoing
            cout << "Player " << player << ", enter the number: ";
            cin >> choice; // Input choice

            char mark = (player == 1) ? 'X' : 'O'; // Determine mark for the current player

            // Update the square if the chosen position is valid
            if (choice >= 1 && choice <= 9 && square[choice] == '0' + choice) {
                square[choice] = mark; // Mark the square
                player = (player % 2) + 1; // Toggle player (1 to 2 or 2 to 1)
            } else {
                cout << "INVALID MOVE! Try again." << endl;
                cin.ignore(); // Clear the input buffer
                cin.get();    // Wait for user input to continue
            }
        }
    } while (i == -1); // Continue until there is a win or draw

    board(); // Final board display

    if (i == 1) {
        cout << "\aCONGRATULATIONS! PLAYER " << (player == 1 ? 2 : 1) << " WINS!";
    } else {
        cout << "\aGAME DRAW!";
    }

    cin.ignore(); // Wait for user input before exiting
    cin.get();
    return 0;
}