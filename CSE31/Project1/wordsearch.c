#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int searchFrom(char** arr, char* word, int r, int c, int** path, int step, int dr, int dc);
static int pow10_of_digits(int x);
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

    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c", arr[i][j]);
            if (j != bSize - 1) printf(" "); 
        }
        printf("\n")
    }



}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    int **path = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++)
        path[i] = (int*)calloc(bSize, sizeof(int));

    int found = 0;

    int **path = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++)
        path [i] = (int*)calloc(bSize, sizeof(int));

    int found = 0;

    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            //temp stores one path per starting point + direction
            int **temp = (int**) malloc(bSize * sizeof(int*));
            for ( int r = 0; r < bSize; r++) 
                temp[r] = (int*) calloc(bSize, sizeof(int));

            for (int d = 0 ; d < 8; d++) {
                if (searchFrom(arr, word, i , j, temp, 0, dir[d][1])){
                    found = 1;
                }
            }

            for (int r = 0; r < bSize; r++) {
                for (int c = 0; c < bSize; c++) {
                    int tv = temp[r][c];
                    if (tv != 0) {
                        if (path[r][c] == 0)
                        path[r][c] = tv;
                        else {
                            int shift = pow10_of_digits(tv);
                            path[r][c] = path [r][c] * shift +tv;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            // temp stores one path per starting point + direction
            int **temp = (int**)malloc(bSize * sizeof(int*));
            for (int r = 0; r < bSize; r++)
                temp[r] = (int*)calloc(bSize, sizeof(int));

            for (int d = 0; d < 8; d++) {
                if (searchFrom(arr, word, i, j, temp, 0, dir[d][0], dir[d][1])) {
                    found = 1;

                    // merge temp into path
                    for (int r = 0; r < bSize; r++) {
                        for (int c = 0; c < bSize; c++) {
                            int tv = temp[r][c];
                            if (tv != 0) {
                                if (path[r][c] == 0)
                                    path[r][c] = tv;
                                else {
                                    int shift = pow10_of_digits(tv);
                                    path[r][c] = path[r][c] * shift + tv;
                                }
                            }
                        }
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
        for (int r = 0; r < bSize; r++) {
            for (int c = 0; c < bSize; c++) {
                printf("%d", path[r][c]);
                if (c != bSize - 1) printf(" ");
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
    if (r < 0 || r >= bSize || c < 0 || c >= bSize) return 0;

    char puzzleChar = arr[r][c];
    if (puzzleChar >= 'A' && puzzleChar <= 'Z') puzzleChar += 32;
    char wordChar = word[step];
    if (wordChar >= 'A' && wordChar <= 'Z') wordChar += 32;

    if (puzzleChar != wordChar) return 0;

    int old = path[r][c];
    if (old == 0) path[r][c] = step + 1;  // record this step once

    if (word[step + 1] == '\0') return 1; // last letter

    int found = 0;
    for (int d = 0; d < 8; d++) {
        int nr = r + dir[d][0];
        int nc = c + dir[d][1];
        if (searchFrom(arr, word, nr, nc, path, step + 1, dir[d][0], dir[d][1]))
            found = 1;
    }

    if (step > 0) path[r][c] = old; // backtrack

    return found;
}
static int pow10_of_digits(int x) {
    int p = 1;
    while (x > 0) {
        p *= 10;
        x /= 10;
    }
    return p;
}