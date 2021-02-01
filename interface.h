//
// Created by pashok on 31.01.21.
//

#ifndef TEST_INTERFACE_H
#define TEST_INTERFACE_H
#pragma once
#include "functions.h"

void PrintTeacher(tteacher *t){
    if(t == NULL){
        printf("Teacher is not exist");
        return;
    }
    if(TeacherInGarbage(t->teacher_id)){
        return;
    }
    printf("Teacher's full name: %s\n"
           "Number of courses: %d\n"
           "Teacher's id: %d\n\n",
           t->name, t->courses_numb, t->teacher_id);
}

void PrintCourse(tcourse *course){
    if(course == NULL){
        printf("Course is not exist");
        return;
    }
    if(CourseInGarbage(course->course_id)){
        return;
    }
    printf("Course price: %d\n"
           "Amount of students: %d\n"
           "Course's id: %d\n"
           "Teacher's id: %d\n\n",
           course->price, course->stud_amount, course->course_id, course->teacher_id);
}

void EnterTeacherInterface(){
    FILE *tind = fopen("Teacher.ind", "r");
    if(tind == NULL){
        perror("Error opening file Teacher.ind");
        return;
    }
    int ans, n = 0;
    do {
        tteacher teacher;
        printf("Enter teacher first name: ");
        scanf("%s", teacher.name);
        printf("Courses numb: ");
        scanf("%d", &(teacher.courses_numb));

        // Find last teacher index
        teacher_index teacherIndex;
        fseek(tind, 0L, SEEK_END);
        if(ftell(tind) == 0){
            teacher.teacher_id = 1;
        }
        else{
            fseek(tind, -sizeof(teacher_index), SEEK_END);
            fread(&teacherIndex, sizeof(teacher_index), 1, tind);
            // Incremented will be our index
            teacher.teacher_id = teacherIndex.teacher_id+1;
        }
        printf("New teacher id is: %d\n", teacher.teacher_id);
        insert_m(&teacher);
        ++n;
        printf("Continue (1 yes , 0 no)? ");
        scanf("%d", &ans);
    } while (ans);
    printf("In the file %d records\n", n);
    fclose(tind);
}

void EnterCourseInterface(){
    FILE *cind = fopen("Course.ind", "r");
    if(cind == NULL){
        perror("Error opening file Course.ind");
        return;
    }
    tcourse course;
    int ans, n = 0;
    do {
        printf("Enter teacher ID: ");
        scanf("%d", &(course.teacher_id));
        printf("Enter course price: ");
        scanf("%d", &(course.price));
        printf("Enter amount of students: ");
        scanf("%d", &(course.stud_amount));
        // Find course index
        course_index courseIndex;
        fseek(cind, 0L, SEEK_END);
        if(ftell(cind) == 0){
            course.course_id = 1;
        }
        else{
            fseek(cind, -sizeof(course_index), SEEK_END);
            fread(&courseIndex, sizeof(course_index), 1, cind);
            course.course_id = courseIndex.course_id+1;
        }
        printf("New course id is: %d\n", course.course_id);
        insert_s(&course);
        ++n;
        printf("Continue (1 yes , 0 no)? ");
        scanf("%d", &ans);
    } while (ans);
    printf("In the file %d records\n", n);
    fclose(cind);
}

void DeleteTeacherInterface(){
    uint teacherId;
    printf("Enter what you want delete teacher's ID: ");
    scanf("%d", &teacherId);
    del_m(teacherId);
    printf("Succesfully deleted teacher %d\n", teacherId);
}

void DeleteCourseInterface(){
    uint courseId, teacherId;
    printf("Enter what course you want delete teacher's ID: ");
    scanf("%d", &teacherId);
    printf("Enter what course you want delete course's ID: ");
    scanf("%d", &courseId);
    del_s(courseId, teacherId);
    printf("Succesfully deleted course %d\n", courseId);
}

void UpdateTeacherInterface(){
    uint teacherId, courses_numb;
    printf("Enter what teacher ID you want to update: ");
    scanf("%d", &teacherId);
    printf("Enter what courses number you want to update: ");
    scanf("%d", &courses_numb);
    update_m(teacherId, courses_numb);
    printf("Succesfully updated teacher %d\n", teacherId);
}

void UpdateCourseInterface(){
    uint teacherId, courseId, price, stud_amount;
    printf("Enter what teacher ID course you want to update: ");
    scanf("%d", &teacherId);
    printf("Enter what course ID you want to update: ");
    scanf("%d", &courseId);
    printf("Enter price: ");
    scanf("%d", &price);
    printf("Enter stud amount: ");
    scanf("%d", &stud_amount);
    update_s(courseId, teacherId, price, stud_amount);
    printf("Succesfully updated course %d\n", courseId);
}

void PrintTeacherInterface(){
    tteacher t;
    uint teacherId;
    printf("Enter teacher ID: ");
    scanf("%d", &teacherId);
    get_m(&t, teacherId);
    PrintTeacher(&t);
}

void PrintCourseInterface(){
    tcourse course;
    uint cteacherId, courseId;
    printf("Enter course's teacher ID: ");
    scanf("%d", &cteacherId);
    printf("Enter course ID: ");
    scanf("%d", &courseId);
    get_s(&course, cteacherId, courseId);
    PrintCourse(&course);
}

#endif //TEST_INTERFACE_H
