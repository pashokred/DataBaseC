#include <stdio.h>
#include "read.h"
#include "interface.h"

void ClearAllFiles(){
    fclose(fopen("Teacher.fl", "w"));
    fclose(fopen("Teacher.ind", "w"));
    fclose(fopen("Course.fl", "w"));
    fclose(fopen("Course.ind", "w"));
    fclose(fopen("TeacherGarbage.ind", "w"));
    fclose(fopen("CourseGarbage.ind", "w"));
    printf("All files succesfully cleared!");
}

void Interface(){
    int option;
    SWITCH:
    printf("Enter command: ");
    scanf("%d", &option);
    switch (option) {
        case -1:
            printf("Exit");
            break;
        case 0:
            EnterTeacherInterface();
            goto SWITCH;
        case 1:
            EnterCourseInterface();
            goto SWITCH;
        case 2:
            PrintTeacherInterface();
            goto SWITCH;
        case 3:
            PrintCourseInterface();
            goto SWITCH;
        case 4:
            DeleteTeacherInterface();
            goto SWITCH;
        case 5:
            DeleteCourseInterface();
            goto SWITCH;
        case 6:
            UpdateTeacherInterface();
            goto SWITCH;
        case 7:
            UpdateCourseInterface();
            goto SWITCH;
        case 8:
            ClearAllFiles();
            goto SWITCH;
        case 9:
            ReadMaster();
            goto SWITCH;
        case 10:
            ReadSlave();
            goto SWITCH;
        case 11:
            ReadMasterIndex();
            goto SWITCH;
        case 12:
            ReadSlaveIndex();
            goto SWITCH;
        case 13:
            ReadMasterGarbage();
            goto SWITCH;
        case 14:
            ReadSlaveGarbage();
            goto SWITCH;

        default:
            printf("Unavailable command. You can write only 0-7. Try again");
            goto SWITCH;
    }
}

int main () {
    int option = 0;
    printf("Hello in C DataBase!\n"
           "The list of available commands:\n"
           "-1 - Exit\n"
           "0  - Enter teacher\n"
           "1  - Enter course\n"
           "2  - Print teacher\n"
           "3  - Print course\n"
           "4  - Delete teacher\n"
           "5  - Delete course\n"
           "6  - Update teacher\n"
           "7  - Update course\n"
           "8  - Clear all files\n\n"
           "9  - Read master FILE\n"
           "10 - Read slave FILE\n"
           "11 - Read master INDEX\n"
           "12 - Read slave INDEX\n"
           "13 - Read master GARBAGE\n"
           "14 - Read slave GARBAGE\n\n");
    Interface(option);
    return 0;
}