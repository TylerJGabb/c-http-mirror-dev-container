#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument provided.\n");
        return 1;
    }

    // Get the length of the argument
    int length = strlen(argv[1]);

    // Allocate memory for the buffer
    char *buffer = (char *)malloc((length + 1) * sizeof(char));

    sscanf(argv[1], "%s", buffer);

    // Print the buffer
    printf("Argument: %s\n", buffer);

    // Free the buffer
    free(buffer);

    return 0;
}
