#include <stdio.h>
#include <stdbool.h>

#include "interface.h"

void clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int command;
    while (true) {
        printf("> ");
        int scan_result = scanf("%d", &command);
        if (scan_result == EOF) {
            printf("\nExiting.\n");
            break;
        }
        if (scan_result == 0) {
            fprintf(stderr, "Error: Invalid command. Please enter a number.\n");
            clear();
            continue;
        }
        if (command == 1) {
            int a, b;
            if (scanf("%d %d", &a, &b) != 2) {
                fprintf(stderr, "Error: Invalid arguments for GCF. Expected two integers.\n");
                clear();
            } else {
                int res = GCF(a, b);
                if (res != -1) {
                    printf("%d\n", res);
                }
            }
        } else if (command == 2) {
            int x;
            if (scanf("%d", &x) != 1) {
                fprintf(stderr, "Error: Invalid argument for E. Expected one integer.\n");
                clear();
            } else {
                printf("%f\n", E(x));
            }
        } else {
            fprintf(stderr, "Error: Unknown command. Use 1 or 2.\n");
            clear();
        }
    }
    return 0;
}