#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int searchFrom(char** arr, char* word, int r, int c, int** path, int step, int dr, int dc);
// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

int dir[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},   // up, down, left, right
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}  // diagonals
};

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c", arr[i][j]);
            if (j != bSize - 1) printf(" ");
        }
        printf("\n");
    }

}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    int **path = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++) {
        path[i] = (int*)malloc(bSize * sizeof(int));
        for (int j = 0; j < bSize; j++)
            path[i][j] = 0;
    }

    int found = 0;

    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            // temporary array to backtrack a single attempt
            int **temp = (int**)malloc(bSize * sizeof(int*));
            for (int r = 0; r < bSize; r++) {
                temp[r] = (int*)malloc(bSize * sizeof(int));
                for (int c = 0; c < bSize; c++) temp[r][c] = 0;
            }

            for (int d = 0; d < 8; d++) {
                if (searchFrom(arr, word, i, j, temp, 0, dir[d][0], dir[d][1])) {
                    found = 1;
                    // merge temp into path only if first letter is free
                    if (path[i][j] == 0) {
                        for (int r = 0; r < bSize; r++)
                            for (int c = 0; c < bSize; c++)
                                if (temp[r][c] != 0)
                                    path[r][c] = temp[r][c];
                    }
                }
            }

            for (int r = 0; r < bSize; r++) free(temp[r]);
            free(temp);
        }
    }

    if (found) {
        printf("Word found!\n");
        printf("Printing the search path:\n");
        for (int i = 0; i < bSize; i++) {
            for (int j = 0; j < bSize; j++) {
                printf("%d", path[i][j]);
                if (j != bSize - 1) printf(" ");
            }
            printf("\n");
        }
    } else {
        printf("Word not found!\n");
    }

    for (int i = 0; i < bSize; i++) free(path[i]);
    free(path);

}
int searchFrom(char** arr, char* word, int r, int c, int** path, int step, int dr, int dc) {
    if (word[step] == '\0') return 1; // full word found
    if (r < 0 || r >= bSize || c < 0 || c >= bSize) return 0;

    char puzzleChar = arr[r][c];
    if (puzzleChar >= 'A' && puzzleChar <= 'Z') puzzleChar += 32;
    char wordChar = word[step];
    if (wordChar >= 'A' && wordChar <= 'Z') wordChar += 32;

    if (puzzleChar != wordChar) return 0;

    int oldValue = path[r][c];

    // Append step to cell
    if (oldValue == 0)
        path[r][c] = step + 1;
    else
        path[r][c] = oldValue * 10 + (step + 1);

    // If last character, word is found
    if (word[step + 1] == '\0') return 1;

    // Explore all 8 directions
    for (int d = 0; d < 8; d++) {
        int nr = r + dir[d][0];
        int nc = c + dir[d][1];
        if (searchFrom(arr, word, nr, nc, path, step + 1, dir[d][0], dir[d][1])) {
            return 1; // Keep this path in path array
        }
    }

    // No valid path found from this cell, backtrack
    path[r][c] = oldValue;
    return 0;
}
