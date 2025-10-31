/**
 * @file tic-tac-toe.c
 * @author
 *  - [vivekboss99](https://github.com/vivekboss99)
 *  - [Krishna Vedala](https://github.com/kvedala)
 *  - [Prem-2006](https://github.com/prem-2006)
 * @brief [Tic-Tac-Toe game](https://en.wikipedia.org/wiki/Tic-tac-toe)
 * @details
 * Simple console Tic-Tac-Toe game supporting single-player (vs computer)
 * and double-player (vs human) modes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ---- Function Declarations ----
static void singlemode(void);
static void doublemode(void);
static void placex(int pos);
static void place_computer(void);
static void placey(int pos);
static int checkwin(void);
static int get_valid_input(void);

// ---- Global Board ----
static char game_table[9];

// ---- Helper Functions ----
static void print_board(void) {
    printf("\n");
    for (int i = 0; i < 9; i++) {
        printf("%c ", game_table[i]);
        if ((i + 1) % 3 == 0)
            printf("\n");
    }
    printf("\n");
}

// ---- Input Validation ----
static int get_valid_input(void) {
    char input[50];
    int pos = 0;

    while (1) {
        printf("Enter position (1-9): ");
        if (!fgets(input, sizeof(input), stdin))
            continue;

        if (sscanf(input, "%d", &pos) != 1 || pos < 1 || pos > 9) {
            fprintf(stderr, "Invalid input! Try again.\n");
            continue;
        }

        if (game_table[pos - 1] == 'x' || game_table[pos - 1] == 'o') {
            fprintf(stderr, "Position already taken! Try again.\n");
            continue;
        }

        return pos;
    }
}

// ---- Player Move ----
static void placex(int pos) {
    game_table[pos - 1] = 'x';
}

// ---- Player 2 Move ----
static void placey(int pos) {
    game_table[pos - 1] = 'o';
}

// ---- Computer Move ----
static void place_computer(void) {
    int e;
    do {
        e = rand() % 9;
    } while (game_table[e] == 'x' || game_table[e] == 'o');

    game_table[e] = 'o';
    printf("Computer placed at %d\n", e + 1);
}

// ---- Check Win ----
static int checkwin(void) {
    int wins[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };

    for (int i = 0; i < 8; i++) {
        int a = wins[i][0], b = wins[i][1], c = wins[i][2];
        if (game_table[a] == game_table[b] && game_table[b] == game_table[c]) {
            if (game_table[a] == 'x')
                return -1; // X wins
            if (game_table[a] == 'o')
                return -2; // O wins
        }
    }
    return 0; // No win
}

// ---- Single Player ----
static void singlemode(void) {
    printf("\n--- You vs Computer ---\n");
    int moves = 0;
    print_board();

    while (moves < 9) {
        printf("Your move (X)\n");
        int pos = get_valid_input();
        placex(pos);
        moves++;
        print_board();

        if (checkwin() == -1) {
            printf("🎉 You WIN!\n");
            return;
        }

        if (moves >= 9) break;

        printf("Computer's move (O)\n");
        place_computer();
        moves++;
        print_board();

        if (checkwin() == -2) {
            printf("💻 Computer WINS!\n");
            return;
        }
    }

    printf("🤝 It's a DRAW!\n");
}

// ---- Double Player ----
static void doublemode(void) {
    printf("\n--- Player 1 (X) vs Player 2 (O) ---\n");
    int moves = 0;
    print_board();

    while (moves < 9) {
        printf("Player 1 (X):\n");
        int p1 = get_valid_input();
        placex(p1);
        moves++;
        print_board();

        if (checkwin() == -1) {
            printf("🎉 Player 1 WINS!\n");
            return;
        }

        if (moves >= 9) break;

        printf("Player 2 (O):\n");
        int p2 = get_valid_input();
        placey(p2);
        moves++;
        print_board();

        if (checkwin() == -2) {
            printf("🎉 Player 2 WINS!\n");
            return;
        }
    }

    printf("🤝 It's a DRAW!\n");
}

// ---- Main ----
int main(void) {
    srand((unsigned int)time(NULL));
    int play_again = 1;

    while (play_again) {
        for (int i = 0; i < 9; i++)
            game_table[i] = '*';

        printf("\n============================\n");
        printf("        TIC TAC TOE         \n");
        printf("============================\n");
        printf("1. You vs Computer\n");
        printf("2. You vs Player\n");
        printf("3. Exit\n");
        printf("Choose option: ");

        int choice = 0;
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                singlemode();
                break;
            case 2:
                doublemode();
                break;
            case 3:
                printf("Thanks for playing!\n");
                return 0;
            default:
                printf("Invalid option!\n");
                break;
        }

        printf("\nPlay again? (1 = Yes / 0 = No): ");
        scanf("%d", &play_again);
        getchar();
    }

    printf("Goodbye!\n");
    return 0;
}
