#include <stdio.h>
#include <stdlib.h>
#define PLAYER1 'X'
#define PLAYER2 'Y'
char columns[7][6];

void initializeBoard() {
    for (int col = 0; col < 7; col++) {
        for (int row = 0; row < 6; row++) {
            columns[col][row] = ' ';
        }
    }
}

void drawBoard() {
    printf("\n\n     A   B   C   D   E   F   G\n");
    printf("   -----------------------------\n");
    printf(" 6 | %c | %c | %c | %c | %c | %c | %c |\n", columns[0][5], columns[1][5], columns[2][5], columns[3][5], columns[4][5], columns[5][5], columns[6][5]);
    printf("   |---+---+---+---+---+---+---|\n");
    printf(" 5 | %c | %c | %c | %c | %c | %c | %c |\n", columns[0][4], columns[1][4], columns[2][4], columns[3][4], columns[4][4], columns[5][4], columns[6][4]);
    printf("   |---+---+---+---+---+---+---|\n");
    printf(" 4 | %c | %c | %c | %c | %c | %c | %c |\n", columns[0][3], columns[1][3], columns[2][3], columns[3][3], columns[4][3], columns[5][3], columns[6][3]);
    printf("   |---+---+---+---+---+---+---|\n");
    printf(" 3 | %c | %c | %c | %c | %c | %c | %c |\n", columns[0][2], columns[1][2], columns[2][2], columns[3][2], columns[4][2], columns[5][2], columns[6][2]);
    printf("   |---+---+---+---+---+---+---|\n");
    printf(" 2 | %c | %c | %c | %c | %c | %c | %c |\n", columns[0][1], columns[1][1], columns[2][1], columns[3][1], columns[4][1], columns[5][1], columns[6][1]);
    printf("   |---+---+---+---+---+---+---|\n");
    printf(" 1 | %c | %c | %c | %c | %c | %c | %c |\n", columns[0][0], columns[1][0], columns[2][0], columns[3][0], columns[4][0], columns[5][0], columns[6][0]);
    printf("   -----------------------------\n");
}

int columnToIndex(char choice) {
    if (choice >= 'a' && choice <= 'g') {
        choice -= 32;
    }
    if (choice >= 'A' && choice <= 'G') {
        return choice - 'A';
    }
    return -1;
}

int dropPiece(int column, char player) {
    for (int row = 0; row < 6; row++) {
        if (columns[column][row] == ' ') {
            columns[column][row] = player;
            return row;
        }
    }
    return -1;
}

int checkHorizontal(int row, char player) {
    int count = 0;
    for (int col = 0; col < 7; col++) {
        if (columns[col][row] == player) {
            count++;
            if (count == 4) {
                return 1;
            }
        } else {
            count = 0;
        }
    }
    return 0;
}

int checkVertical(int column, char player) {
    int count = 0;
    for (int row = 0; row < 6; row++) {
        if (columns[column][row] == player) {
            count++;
            if (count == 4) {
                return 1;
            }
        } else {
            count = 0;
        }
    }
    return 0;
}

int checkDiagonal1(int col, int row, char player) {
    int count = 0;
    for (int i = -3; i <= 3; i++) {
        int x = col + i;
        int y = row + i;
        if (x >= 0 && x < 7 && y >= 0 && y < 6 && columns[x][y] == player) {
            count++;
            if (count == 4) {
                return 1;
            }
        } else {
            count = 0;
        }
    }
    return 0;
}

int checkDiagonal2(int col, int row, char player) {
    int count = 0;
    for (int i = -3; i <= 3; i++) {
        int x = col + i;
        int y = row - i;
        if (x >= 0 && x < 7 && y >= 0 && y < 6 && columns[x][y] == player) {
            count++;
            if (count == 4) {
                return 1;
            }
        } else {
            count = 0;
        }
    }
    return 0;
}

int checkWin(int col, int row, char player) {
    return checkHorizontal(row, player) || checkVertical(col, player) || checkDiagonal1(col, row, player) || checkDiagonal2(col, row, player);
}

int checkDraw() {
    for (int col = 0; col < 7; col++) {
        if (columns[col][5] == ' ') {
            return 0;
        }
    }
    return 1;
}

int main() {
    char currentPlayer = PLAYER1;
    initializeBoard();
    while (1) {
        char choice;
        drawBoard();
        printf("%c, choose a column: ", currentPlayer);
        scanf(" %c", &choice);
        int column = columnToIndex(choice);
        if (column == -1) {
            printf("Invalid column.\n");
            continue;
        }
        int row = dropPiece(column, currentPlayer);
        if (row == -1) {
            printf("Column is full.\n");
            continue;
        }
        if (checkWin(column, row, currentPlayer)) {
            drawBoard();
            printf("%c wins!\n", currentPlayer);
            break;
        }
        if (checkDraw()) {
            drawBoard();
            printf("It's a draw!\n");
            break;
        }
        currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    }
    return 0;
}