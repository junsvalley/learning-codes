#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 256

int main(int argc, char *args[])
{
    int floor_high_1   = 0;
    int floor_low_1    = 0;
    int ceiling_high_1 = 0;
    int ceiling_low_1  = 0;

    int floor_high_2   = 0;
    int floor_low_2    = 0;
    int ceiling_high_2 = 0;
    int ceiling_low_2  = 0;


    char line[MAXLINE] = {0};

    while (1) {
        fprintf(stderr, "Input floor 1 high   : ");
        if (read(STDIN_FILENO, line, MAXLINE) > 0) {
            floor_high_1 = atoi(line);
        }
        fprintf(stderr, "Input floor 1 low    : ");
        if (read(STDIN_FILENO, line, MAXLINE) > 0) {
            floor_low_1 = atoi(line);
        }
        fprintf(stderr, "Input ceiling 1 high : ");
        if (read(STDIN_FILENO, line, MAXLINE) > 0) {
            ceiling_high_1 = atoi(line);
        }
        fprintf(stderr, "Input ceiling 1 low  : ");
        if (read(STDIN_FILENO, line, MAXLINE) > 0) {
            ceiling_low_1 = atoi(line);
        }
        fprintf(stderr, "%02d %02d ~ %02d %02d\n", floor_high_1, floor_low_1, ceiling_high_1, ceiling_low_1);

        fprintf(stderr, "Input floor 2 high   : ");
        if (read(STDIN_FILENO, line, MAXLINE) > 0) {
            floor_high_2 = atoi(line);
        }
        fprintf(stderr, "Input floor 2 low    : ");
        if (read(STDIN_FILENO, line, MAXLINE) > 0) {
            floor_low_2 = atoi(line);
        }
        fprintf(stderr, "Input ceiling 2 high : ");
        if (read(STDIN_FILENO, line, MAXLINE) > 0) {
            ceiling_high_2 = atoi(line);
        }
        fprintf(stderr, "Input ceiling 2 low  : ");
        if (read(STDIN_FILENO, line, MAXLINE) > 0) {
            ceiling_low_2 = atoi(line);
        }
        fprintf(stderr, "%02d %02d ~ %02d %02d\n", floor_high_2, floor_low_2, ceiling_high_2, ceiling_low_2);

        //if ( ceiling_high_1 < floor_high_2 || ceiling_high_2 < floor_high_1 ) {
        //  fprintf(stderr, "NO OVERLAP AREA DEFINITELY\n");
        //  continue;
        //}

        if ( (floor_high_2 < ceiling_high_1 && ceiling_high_2 > floor_high_1) ||
             (floor_high_1 < ceiling_high_2 && ceiling_high_1 > floor_high_2) ) {
            fprintf(stderr, "OVERLAP AREA DEFINITELY\n");
            continue;
        }

        /* SIDE CASE */
        if (ceiling_high_1 == floor_high_2 && floor_high_1 == ceiling_high_2) {
            if ( (floor_low_2 <= ceiling_low_1 && ceiling_low_2 >= floor_low_1) ||
                 (floor_low_1 <= ceiling_low_2 && ceiling_low_1 >= floor_low_2) ) {
                fprintf(stderr, "OVERLAP AREA DEFINITELY ON SIDE-ALL\n");
                continue;
            }
        }

        if ( (ceiling_high_1 == floor_high_2 && floor_high_1 != ceiling_high_2 && ceiling_low_1 >= floor_low_2) ||
             (ceiling_high_2 == floor_high_1 && floor_high_2 != ceiling_high_1 && ceiling_low_2 >= floor_low_1) ) {
            fprintf(stderr, "OVERLAP AREA DEFINITELY ON SIDE\n");
            continue;
        }

        fprintf(stderr, "--- NO OVERLAP AREA ---\n");
    }
}
