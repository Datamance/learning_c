#include <stdio.h>
#include <ctype.h>


// Write functions in the order they are defined, or else you have to forward
// declare.

// Usually you write header files, so let's get used to forward declarations!

void print_letters(char word[]);
void print_arguments(int argc, char *argv[]);
int can_print_it(char ch);


void print_arguments(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        print_letters(argv[i]);
    }
};

void print_letters(char word[]) {
    // When they are arguments, arrays decay to pointers. This makes sizeof()
    // operate in a really shitty way.
    for (int i = 0; word[i] != '\0'; i++) {
        char ch = word[i];
        if (can_print_it(ch)) {
            printf("'%c' is represented as int %d.\n", ch, ch);
        }
    }
};

int can_print_it(char ch) {
    return isalpha(ch) || isblank(ch);
};



int main(int argc, char *argv[]) {
    print_arguments(argc, argv);
    return 0;
};
