#include <stdio.h>
#include <stdbool.h>

#include "os.h"

#define LIB1_PATH "../lib/libimpl1.so"
#define LIB2_PATH "../lib/libimpl2.so"

void clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    const char* libs[] = { LIB1_PATH, LIB2_PATH };
    int current_lib = 0;
    LibHandle handle = NULL;
    int (*gcf_func)(int, int) = NULL;
    float (*e_func)(int) = NULL;
    handle = LibLoad(libs[current_lib]);
    if (!handle) {
        return 1;
    }
    *(void**)(&gcf_func) = LibGetSymbol(handle, "GCF");
    *(void**)(&e_func) = LibGetSymbol(handle, "E");
    if (!gcf_func || !e_func) {
        LibClose(handle);
        return 1;
    }
    printf("Loaded: %s\n", libs[current_lib]);
    
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
        if (command == 0) {
            LibClose(handle);
            current_lib = 1 - current_lib;
            handle = LibLoad(libs[current_lib]);
            if (!handle) return 1;
            *(void**)(&gcf_func) = LibGetSymbol(handle, "GCF");
            *(void**)(&e_func) = LibGetSymbol(handle, "E");
            if (!gcf_func || !e_func) {
                LibClose(handle);
                return 1;
            }
            printf("Switched to: %s\n", libs[current_lib]);
        } else if (command == 1) {
            int a, b;
            if (scanf("%d %d", &a, &b) != 2) {
                fprintf(stderr, "Error: Invalid arguments for GCF. Expected two integers.\n");
                clear();
            } else {
                int res = gcf_func(a, b);
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
                printf("%f\n", e_func(x));
            }
        } else {
            fprintf(stderr, "Error: Unknown command. Use 0, 1 or 2.\n");
            clear();
        }
    }
    LibClose(handle);
    return 0;
}