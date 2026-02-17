#include <stdio.h>
int main(int argc, char*argv[])
{
int repetitionCount;
int typoLine;

printf("Enter the repetition count for the punishment phrase: ");
scanf("%d" , &repetitionCount);

while ( repetitionCount <= 0 ){
    printf("You entered an invalid value for the repetition count! Please re-enter: ");
    scanf("%d" , &repetitionCount);
}

printf("Enter the line where you want to insert the typo: ");
scanf("%d" , &typoLine);

while (typoLine <=0 || typoLine > repetitionCount) {
    printf("You entered an invalid value for the typo placement! Please re-enter: ");
    scanf( "%d" , &typoLine);
}

for (int i = 1; i <=repetitionCount; i++) {
    if ( i==typoLine) {
        printf("Cading wiht is C avesone!\n");
    }
    else{
        printf("Coding with C is awesome!\n");
    }
}

return 0;
}
