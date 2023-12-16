#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument provided.\n");
        return 1;
    }

    // Get the length of the argument
    int length = strlen(argv[1]);

    // Allocate memory for the buffer
    char *buffer = (char *)malloc((length + 1) * sizeof(char));

    // Copy the argument into the buffer
    strcpy(buffer, argv[1]);

    // Print the buffer
    printf("Argument: %s\n", buffer);

    // Free the buffer
    free(buffer);

    return 0;
}
