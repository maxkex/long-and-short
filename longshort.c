#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// convert a string to uppercase/lowercase
void stringUpper(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = toupper(str[i]);
        i++;
    }
}
void stringLower(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = tolower(str[i]);
        i++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Please enter a file to read from, and two files to write to.\n");
        exit(1);
    }

    // Open the source file for reading
    FILE *srcFile = fopen(argv[1], "r");
    if (!srcFile) {
        printf("Could not open %s for reading\n", argv[1]);
        exit(1);
    }

    // Open the short file for writing
    // short file will contain lines less then 20 characters, and will be upercase
    FILE *shortFile = fopen(argv[2], "w");
    if (!shortFile) {
        printf("Could not open %s for writing\n", argv[2]);
        exit(1);
    }

    // Open the long file for writing
    // long file will contain lines 20 or more characters, and will be lowercase
    FILE *longFile = fopen(argv[3], "w");
    if (!longFile) {
        printf("Could not open %s for writing\n", argv[3]);
        exit(1);
    }

    // count the number of lines writen to files
    int shortCount = 0;
    int longCount = 0;

    char line[1000]; // line maximum length is 999 chars, and 1 for null terminator 
    while (fgets(line, 1000, srcFile)) {

        // find the newline character and truncate the line
        char *newline = strchr(line, '\n');
        if (*newline) {
            *newline = '\0';
        }

        // if no newline is found, simply truncate the line
        if (!newline) {
            line[999] = '\0';
        }

        if(strlen(line) < 20) {
            // write to short file
            stringUpper(line);
            fprintf(shortFile, "%s\n", line);
            shortCount++;
        } else {
            // write to long file
            stringLower(line);
            fprintf(longFile, "%s\n", line);
            longCount++;
        }
    }
    
    printf("Wrote %d lines to %s\n", shortCount, argv[2]);
    printf("Wrote %d lines to %s\n", longCount, argv[3]);

    
    fclose(srcFile);
    fclose(shortFile);
    fclose(longFile);
    return 0;

}