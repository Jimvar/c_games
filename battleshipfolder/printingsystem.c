#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "printingsystem.h"

int startupscreen() {
    const int max_offset = 15; // Maximum horizontal movement for ships
    const int frame_delay = 150000; // Frame delay in microseconds (150ms)
    int direction = 1; // Direction of ship movement (1 = right, -1 = left)
    int offset = 0; // Offset for the first ship
    const int wave_width = 76; // Width matching the battleship logo
    int wave_cycle = 0; // Used to animate the wave movement
    int counter = 0; //For when the loop should stop

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

    return 0; // Exit the function
}
