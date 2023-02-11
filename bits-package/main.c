
/*
    main.c
    Jeff Ondich, 19 January 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bits.h"
// #include "bits.c"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s action [arguments...]\n", argv[0]);
        fprintf(stderr, "  where action can be to_upper, to_lower,...\n");
        fprintf(stderr, "  and arguments are appropriate to the specific action.\n");
        return 1;
    }

    if (strcmp(argv[1], "to_upper") == 0) {
        char *buffer = malloc(strlen(argv[2]) + 1);
        if (buffer != NULL) {
            strcpy(buffer, argv[2]);
            to_upper(buffer);
            printf("%s\n", buffer);
            free(buffer);
        }
    }

    else if (strcmp(argv[1], "to_lower") == 0) {
        char *buffer = malloc(strlen(argv[2]) + 1);
        if (buffer != NULL) {
            strcpy(buffer, argv[2]);
            to_lower(buffer);
            printf("%s\n", buffer);
            free(buffer);
        }
    }

    else if (strcmp(argv[1], "middle_bits") == 0) {
        char *buffer = malloc(strlen(argv[2]) + 1);
        if (buffer != NULL) {
            strcpy(buffer, argv[2]);
            to_lower(buffer);
            printf("%s\n", buffer);
            free(buffer);
        }
    }

    else if (strcmp(argv[1], "to_utf8") == 0) {
        char *buffer = malloc(5);
        if (buffer != NULL) {
            // strcpy(buffer, argv[2]);
            // to_lower(buffer);
            // printf("%s\n", buffer);
            to_utf8(233, buffer);
            for (int i = 0; i > 4; i++){
                printf("%X\n", buffer[i]);
                printf("loop\n");
            }
            free(buffer);
        }
        else {
        }
    }
    // etc.

    return 0;
}
