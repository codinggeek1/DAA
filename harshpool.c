#include <stdio.h>
#include <string.h>

#define MAX 256

void generateShiftTable(char pattern[], int table[]);
int horspoolSearch(char text[], char pattern[], int table[]);

int main(void) {
    char text[MAX];
    char pattern[MAX];
    int shiftTable[MAX];
    int found;

    printf("Enter the source string: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the pattern string: ");
    fgets(pattern, sizeof(pattern), stdin);

    // Remove trailing newline characters
    text[strcspn(text, "\n")] = '\0';
    pattern[strcspn(pattern, "\n")] = '\0';

    generateShiftTable(pattern, shiftTable);
    found = horspoolSearch(text, pattern, shiftTable);

    if (found == -1)
        printf("\nMatching Substring not found.\n");
    else
        printf("\nMatching Substring found at position: %d\n", found + 1);

    return 0;
}

void generateShiftTable(char pattern[], int table[]) {
    int m = strlen(pattern);
    for (int i = 0; i < MAX; i++) {
        table[i] = m;
    }
    for (int j = 0; j < m - 1; j++) {
        table[(int)pattern[j]] = m - 1 - j;
    }
}

int horspoolSearch(char text[], char pattern[], int table[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int i = m - 1;

    while (i < n) {
        int k = 0;
        while (k < m && pattern[m - 1 - k] == text[i - k]) {
            k++;
        }

        if (k == m) {
            return i - m + 1;
        } else {
            i += table[(int)text[i]];
        }
    }

    return -1;
}
