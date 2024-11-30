#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "printingsystem.h"

// Function to disable raw mode
void disable_raw_mode(struct termios *orig_termios) {
    tcsetattr(STDIN_FILENO, TCSANOW, orig_termios);
}

// Function to enable raw mode
void enable_raw_mode(struct termios *orig_termios) {
    struct termios raw;

    // Get current terminal attributes
    tcgetattr(STDIN_FILENO, orig_termios);

    // Modify the terminal attributes
    raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON); // Disable echo and canonical mode

    // Set the new attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

int startupscreen() {
    const int max_offset = 15; // Maximum horizontal movement for ships
    const int frame_delay = 15000; // Frame delay in microseconds (150ms)
    int direction = 1; // Direction of ship movement (1 = right, -1 = left)
    int offset = 0; // Offset for the first ship
    const int wave_width = 76; // Width matching the battleship logo
    int wave_cycle = 0; // Used to animate the wave movement
    int counter = 0; //For when the loop should stop
    char choice;

    while (counter++ <= 60) {
        printf(CLEARSCREEN); // Clear the screen

        printf(DARKBLUE "██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗\n");
        printf(         "██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗\n");
        printf(LIGHTBLUE"██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██████╔╝\n");
        printf(         "██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██╔═══╝\n");
        printf(RESET    "██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██║\n");
        printf(         "╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝\n\n");

        // Ship and wave rendering
        for (int i = 0; i < offset; i++) printf(" ");
        printf("\033[1;33m|__/___                         |__/___\033[0m\n");

        for (int i = 0; i < offset; i++) printf(" ");
        printf("\033[1;33m|_____/______|                  |_____/______|\033[0m\n");

        for (int i = 0; i < offset; i++) printf(" ");
        printf("\033[1;33m|_______/_____\\_____________    |_______/_____\\_____________\033[0m\n");

        for (int i = 0; i < offset; i++) printf(" ");
        printf("\033[1;33m|________________> > >_____/    |_____> > >________________/\033[0m\n");

        // Wave animation
        for (int i = 0; i < 2; i++) {
            int num_colors = 4;
            const char *colors[] = {
                OCEANBLUE,
                LIGHTCYAN,
                BRIGHTBLUE,
                WHITE
            };

            // Loop through the width of the wave
            for (int i = 0; i < wave_width; i++) {
                printf("%s~", colors[(i + wave_cycle) % num_colors]);
            }

            printf(RESET"\n"); // Reset color at the end of the line
        }

        // Update ship position
        offset += direction;

        // Reverse direction at bounds
        if (offset == max_offset || offset == 0) {
            direction *= -1;
        }

        wave_cycle++; // Increment the cycle for wave animation

        usleep(frame_delay); // Delay for smooth animation

    }

    printf(SYSTEM "Welcome to Battleship!\n");
    printf("Choose gamemode:\n1. VS Player\n2. VS AI\n");

    scanf("%c", &choice);
    while(choice!='1'){
        printf(RED "Invalid choice! Enter again: " SYSTEM);
        while(getchar()!='\n');
        scanf("%c", &choice);
    }

    return(choice - '0'); // Exit the function
}

void getname(char player[], int which, int size){
    printf(SYSTEM "Input player %d name: %s", which, PLAYERS);
    fgets(player, size, stdin);
    // Remove the newline character if present
    size_t len = strlen(player);
    if (len > 0 && player[len - 1] == '\n') {
        player[len - 1] = '\0';
    }
}

void display_board(int map[][10][10], int bigturn, int x_pos, int y_pos, int size, int looking_side){
    printf(BOARD "    ---------------------\n" RESET);
    for (int j = 9; j >= 0; j--) {
        printf(BOARD "%2d |%s", j, RESET);
        for (int i = 0; i < 10; i++) {
            int ship_to_place = 0;

            // Check if the ship is at the current position
            for (int s = 0; s < size; s++) {
                int sx = x_pos, sy = y_pos;
                if (looking_side == 0) {       // Right
                    sx += s;
                } else if (looking_side == 1) { // Up
                    sy += s;
                } else if (looking_side == 2) { // Left
                    sx -= s;
                } else if (looking_side == 3) { // Down
                    sy -= s;
                }
                if (i == sx && j == sy) {
                    ship_to_place = 1;
                    break;
                }
            }
            
            if(map[bigturn][i][j]==1) printf(RED " X" RESET);
            else if(map[bigturn][i][j] == -1) printf(WHITE " X" RESET);
            else if (ship_to_place) printf(GREEN " O" RESET);
            else printf(LIGHTBLUE " ~" RESET);

        }
        printf(BOARD " |\n" RESET);
    }
    printf(BOARD "    ---------------------\n" RESET);
    printf(BOARD "     0 1 2 3 4 5 6 7 8 9\n" RESET);
}

void ship_setup(char player1[], char player2[], int bigturn, int ship_placement[][10][10]){

    struct termios orig_termios;
    enable_raw_mode(&orig_termios);

    for (int k = 0; k < 2; k++) {
        int size;
        int x_pos, y_pos, looking_side; // Looking side: 0 right, 1 up, 2 left, 3 down

        printf(CLEARSCREEN);
        printf(PLAYERS "%s%s, make sure the opponent isn't watching the screen while you are making the placements\n" RESET, (bigturn == 0) ? player1 : player2, SYSTEM);
        usleep(1500000);

        for (int l = 5; l > 0; l--){
            x_pos = 0, y_pos = 0, looking_side = 0;
            int done = 0;

            // Determine ship size
            if(l == 5) size = 5;
            else if(l == 4) size = 4;
            else if(l == 3 || l == 2) size = 3;
            else size = 2;

            while (!done) {
                // Clear the screen and display the board
                printf(CLEARSCREEN);
                display_board(ship_placement, bigturn, x_pos, y_pos, size, looking_side);

                // Instructions
                printf(SYSTEM "Use arrow keys to move, 'R' to rotate, and Enter to place the ship.\n");

                // Read input
                char c = getchar();
                if(c == 'R' || c == 'r'){
                    // Rotate the ship
                    looking_side = (looking_side + 1) % 4;
                }
                else if(c == '\033'){ // Escape character
                    // Read the next two characters for arrow keys
                    char seq[2];
                    seq[0] = getchar();
                    seq[1] = getchar();

                    int new_x = x_pos, new_y = y_pos;

                    if(seq[0] == '['){
                        switch (seq[1]){
                            case 'A':
                                // Up arrow
                                new_y += 1;
                                break;
                            case 'B':
                                // Down arrow
                                new_y -= 1;
                                break;
                            case 'C':
                                // Right arrow
                                new_x += 1;
                                break;
                            case 'D':
                                // Left arrow
                                new_x -= 1;
                                break;
                        }

                        // Check if new position is within bounds
                        if(new_x >= 0 && new_x < 10 && new_y >= 0 && new_y < 10){
                            x_pos = new_x;
                            y_pos = new_y;
                        }
                    }
                } 
                else if(c == '\n'){
                    // Attempt to place the ship
                    int valid = 1;
                    for (int s = 0; s < size; s++) {
                        int sx = x_pos, sy = y_pos;

                        if(looking_side == 0) sx += s;
                        else if(looking_side == 1) sy += s;
                        else if (looking_side == 2) sx -= s;
                        else if (looking_side == 3) sy -= s;

                        // Check if position is within bounds
                        if (sx < 0 || sx >= 10 || sy < 0 || sy >= 10) {
                            valid = 0;
                            break;
                        }
                        // Check for overlap
                        if (ship_placement[bigturn][sx][sy]) {
                            valid = 0;
                            break;
                        }
                    }
                    if(valid){
                        // Place the ship
                        for (int s = 0; s < size; s++) {
                            int sx = x_pos, sy = y_pos;
                            if (looking_side == 0) {       // Right
                                sx += s;
                            } else if (looking_side == 1) { // Up
                                sy += s;
                            } else if (looking_side == 2) { // Left
                                sx -= s;
                            } else if (looking_side == 3) { // Down
                                sy -= s;
                            }
                            ship_placement[bigturn][sx][sy] = 1;
                        }
                        done = 1;
                    } 
                    else{
                        printf(RED "Invalid placement. Try again.\n" RESET);
                        usleep(1000000);
                    }
                }
            }
        }

        // Switch player
        bigturn = 1 - bigturn;
    }
    printf(CLEARSCREEN);
    disable_raw_mode(&orig_termios);
}

int gameplay(char player1[], char player2[], int bigturn, int ship_placement[][10][10]){
    struct termios orig_termios;
    enable_raw_mode(&orig_termios);

    int ship_bomb[2][10][10] = {0};
    int x_pos, y_pos;
    int ships_hit[2] = {0};

    while(1){
        x_pos = 0, y_pos = 0;
        int oldbigturn = bigturn;
        printf(PLAYERS "%s%s, it is your turn to play!\n", (bigturn==0) ? player1 : player2, SYSTEM);
        usleep(1000000);

        while(oldbigturn == bigturn && ships_hit[bigturn] < 17){
            printf(CLEARSCREEN);
            display_board(ship_bomb, bigturn, x_pos, y_pos, 1, 0);

            printf(PLAYERS "%s%s, use arrow keys to move and Enter to bomb the square.\n", (bigturn==0) ? player1 : player2, SYSTEM);

            char c = getchar();
            if(c == '\033'){ // Escape character
                // Read the next two characters for arrow keys
                char seq[2];
                seq[0] = getchar();
                seq[1] = getchar();

                int new_x = x_pos, new_y = y_pos;

                if(seq[0] == '['){
                    switch (seq[1]){
                        case 'A':
                            // Up arrow
                            new_y += 1;
                            break;
                        case 'B':
                            // Down arrow
                            new_y -= 1;
                            break;
                        case 'C':
                            // Right arrow
                            new_x += 1;
                            break;
                        case 'D':
                            // Left arrow
                            new_x -= 1;
                            break;
                    }
                }
                // Check if new position is within bounds
                if(new_x >= 0 && new_x < 10 && new_y >= 0 && new_y < 10){
                    x_pos = new_x;
                    y_pos = new_y;
                }
            }
            else if(c == '\n'){
                // Attempt to bomb the ship
                if(ship_placement[1 - bigturn][x_pos][y_pos]==1){
                    ship_placement[1 - bigturn][x_pos][y_pos]++;
                    ship_bomb[bigturn][x_pos][y_pos]++;
                    ships_hit[bigturn]++;
                    printf(GREEN "You hit them!\n" RESET);
                    usleep(1000000);
                }
                else if(ship_bomb[bigturn][x_pos][y_pos]==-1 || ship_bomb[bigturn][x_pos][y_pos]==1){
                    printf(RED "You have already shot there!\n" RESET);
                    usleep(1000000);
                }
                else{
                    ship_bomb[bigturn][x_pos][y_pos]--;
                    printf(RED "You didn't hit them!\n" RESET);
                    usleep(1000000);
                    bigturn = 1 - bigturn;
                }
            }
        }

        if(ships_hit[bigturn]==17){
            display_board(ship_bomb, bigturn, x_pos, y_pos, 1, 0);
            usleep(1000000);
            disable_raw_mode(&orig_termios);
            if(bigturn==0){
                return 1;
            }
            else{
                return 2;
            }
        }
    }

    printf(CLEARSCREEN);
    return 0;
}