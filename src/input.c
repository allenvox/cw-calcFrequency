#include "input.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE_INCREMENT 10

void formatString(char *p)
{
    char *src = p, *dst = p;
    while (*src) {
        if (ispunct((unsigned char)*src)) {
          src++;
        } else if (src == dst) {
            src++;
            dst++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = 0;
}

void printHelp() {
    printf("\n Usage:\n");
    printf("\tcalcFrequency <in-file-name> <out-file-name>\n\n");
}

int isSuffix(char *substring, char *string) {
    int n1 = strlen(substring), n2 = strlen(string);
    if (n1 > n2) {
        return -1;
    }
    for (int i=0; i<n1; i++) {
        if (substring[n1 - i - 1] != string[n2 - i - 1]) {
            return -1;
        }
    }
    return 0;
}

int checkArgs(int argc, char **argv) {
    if(argc != 3 || isSuffix(".txt", argv[1]) != 0 || isSuffix(".txt", argv[2]) != 0) {
        printHelp();
        return -1;
    }
    return 0;
}

char **getInput(char *filename, int *wordCount) {
    *wordCount = 0;
    char buffer[64];
    int length;
    int size = SIZE_INCREMENT;

    char **words = (char **)malloc(size * sizeof(char*));
    FILE *input = fopen(filename, "r");

    while(fscanf(input, "%63s", buffer) != EOF) {
        buffer[strcspn(buffer, "\n")] = '\0';
        formatString(buffer);
        length = strlen(buffer);
        if(*wordCount >= size) {
            size += SIZE_INCREMENT;
            words = (char**) realloc(words, size * sizeof(char*));
        }
        words[*wordCount] = (char*) malloc(length + 1);
        strcpy(words[*wordCount], buffer);
        (*wordCount)++;
    }
    return words;
}