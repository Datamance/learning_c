#include <stdio.h>

int main(int argc, char *argv[]) {
    int numbers[4] = { 0 };
    char name[5] = { 'a' };

    // first, print em out raw
    printf("numbers: %d %d %d %d\n",
           numbers[0], numbers[1], numbers[2], numbers[3]);

    printf("name each: %c, %c, %c, %c\n",
           name[0], name[1], name[2], name[3]);

    printf("Full name: %s\n", name);

    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    name[0] = 'R';
    name[1] = 'i';
    name[2] = 'c';
    name[3] = 'o';
    name[4] = '\0';

    // Now, see what they look like filled out
    printf("numbers: %d %d %d %d\n",
           numbers[0], numbers[1], numbers[2], numbers[3]);

    printf("name each: %c, %c, %c, %c\n",
           name[0], name[1], name[2], name[3]);

    printf("Full name: %s\n", name);

    // Another way to do strings - don't have to terminate with null byte, as
    // with a buffered array.
    char *love = "love";

    printf("%s\n", love);

    int i = 0;
    while (i < 4) {
        printf("%i: %c\n", i, love[i]);
        i++;
    };

    // For strings, we must account for the null byte. So to go backwards, one
    // must start at an index that is not just one less than the length, but
    // also one less than the null byte.
    for (i = sizeof(name) - 2; i >= 0; i--) {
        printf("%i: %c\n", i, name[i]);
    };


    for (i = 1; i < argc; i++) {
        printf("argument #%d: %s\n", i, argv[i]);
    }

    return 0;
}
