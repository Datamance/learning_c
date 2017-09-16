#include <stdio.h>
#include <string.h>

/*
A typedef, in spite of the name, does not define a new type;
it merely creates a new name for an existing type.

You could also do this:

struct Student {
    int id;
    char name[256];
    int age;
    float weight;
}

typedef struct Student StudentStruct;

Both the collapsed version below and the more "explicit" version above do
the same thing, which is to let you forgo "struct StudentStruct stud" in
your variable definitions.
*/

typedef struct Student {
    int id;
    char name[300];
    int age;
    float weight;
} StudentStruct;


void display(char introString[], StudentStruct stud) {
    printf("%s\nStudent: %s\nID: %d\nAge: %d\nWeight: %.2f\n", introString, stud.name, stud.id, stud.age, stud.weight);
    // *char studName = &stud.name
    // printf("Student name dereferenced: %s", *studName)
};


int main(int argc, char *argv[]) {
    printf("Arg Count #: %d\n", argc);

    char myString[] = "Let's do a string.";

    StudentStruct rico = {1, "Rico Rodriguez", 30, 150};

    StudentStruct *ricoPtr;

    ricoPtr = &rico;

    display(myString, rico);

    return 0;
};
