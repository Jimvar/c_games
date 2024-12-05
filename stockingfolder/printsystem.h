#ifndef PRINTSYSTEM_H
#define PRINTSYSTEM_H

#define GREEN "\x1b[1;32m"
#define RED   "\x1b[1;31m"
#define RESET "\x1b[0m"
#define YELLOW "\x1b[1;93m"
#define CYAN "\x1b[1;38;5;123m"
#define BLUEISH "\x1b[1;38;5;37m"
#define SYSTEM "\x1b[0;38;5;69m"
#define PLAYER "\x1b[0;38;5;35m"

extern const char *colors[];

int startupscreen();

#endif 