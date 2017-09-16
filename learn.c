#include <stdio.h>
#include <string.h>

/*
A typedef, in spite of the name, does not define a new type;
it merely creates a new name for an existing type. For example, given:
*/

typedef struct Student {
    int id;
    char name[256];
    int age;
    float weight;
} StudentStruct;


void display(StudentStruct stud) {
    printf("Student: %s\nID: %d\nAge: %d\nWeight: %.2f\n", stud.name, stud.id, stud.age, stud.weight);
    // *char studName = &stud.name
    // printf("Student name dereferenced: %s", *studName)
};


int main(int argc, char *argv[]) {
    printf("Process #: %d\n", argc);

    StudentStruct rico = {1, "Rico Rodriguez", 30, 150};

    StudentStruct *ricoPtr;

    ricoPtr = &rico;

    printf("%s is his name.\n", ricoPtr->name);

    display(rico);

    return 0;
};
