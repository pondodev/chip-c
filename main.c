#include <stdio.h>

#include "main.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        error_code = 5;
    } else {
        error_code = init(argv[1], &core);
    }

    while (error_code == 0) {
        error_code = cycle(&core);
    }

    handle_error_code();

    return error_code;
}

void handle_error_code() {
    switch (error_code) {
        case 3:
            printf("ERROR: out of memory bounds\n");
            break;

        case 4:
            printf("ERROR: failed to read rom\n");
            break;

        default:
            printf("unrecognised exit code\n");
            break;
    }
}
