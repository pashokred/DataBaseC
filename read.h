//
// Created by pashok on 31.01.21.
//

#ifndef TEST_READ_H
#define TEST_READ_H
#pragma once
#include <stdio.h>
#include "structures.h"
#include "interface.h"

void ReadMaster(){
    FILE *master = fopen("Teacher.fl", "r");
    if(master == NULL){
        perror("Error opening file Teacher.fl");
        return;
    }
    tteacher t;
    int n = 1;
    while (!feof(master)) {
        fread(&t, sizeof(tteacher), 1, master);
        if(!feof(master)){
            PrintTeacher(&t);
        }
    }
    fclose(master);
}

void ReadSlave(){
    FILE *slave = fopen("Course.fl", "r");
    if(slave == NULL){
        perror("Error opening file Course.fl");
        return;
    }
    tcourse course;
    while (!feof(slave)) {
        fread(&course, sizeof(tcourse), 1, slave);
        if(!feof(slave)){
            PrintCourse(&course);
        }
    }
    fclose(slave);
}

void ReadMasterIndex(){
    FILE *mind = fopen("Teacher.ind", "r");
    if(mind == NULL){
        perror("Error opening file Teacher.ind");
        return;
    }
    teacher_index teacherIndex;
    int n = 1;
    while (!feof(mind)) {
        fread(&teacherIndex, sizeof(teacher_index), 1, mind);
        if(!feof(mind)){
            printf("%d. Teacher index: %d\n   address: %d\n\n", n, teacherIndex.teacher_id, teacherIndex.address);
            ++n;
        }
    }
    fclose(mind);
}

void ReadSlaveIndex(){
    FILE *mind = fopen("Course.ind", "r");
    if(mind == NULL){
        perror("Error opening file Course.ind");
        return;
    }
    course_index courseIndex;
    int n = 1;
    while (!feof(mind)) {
        fread(&courseIndex, sizeof(courseIndex), 1, mind);
        if(!feof(mind)) {
            printf("%d. Course index: %d\n   address: %d\n\n", n, courseIndex.teacher_id, courseIndex.address);
            ++n;
        }
    }
    fclose(mind);
}

void ReadMasterGarbage(){
    FILE *mgarbage = fopen("TeacherGarbage.ind", "r");
    if(mgarbage == NULL){
        perror("Error opening file TeacherGarbage.ind");
        return;
    }
    teacher_garbage tgarbage;
    int n = 1;
    while (!feof(mgarbage)) {
        fread(&tgarbage, sizeof(tgarbage), 1, mgarbage);
        if(!feof(mgarbage)) {
            printf("%d. Teacher garbage index: %d\n   Teacher ID: %d\n\n", n, tgarbage.tgarbage_id,
                   tgarbage.teacher_id);
            ++n;
        }
    }
    fclose(mgarbage);
}

void ReadSlaveGarbage(){
    FILE *sgarbage = fopen("CourseGarbage.ind", "r");
    if(sgarbage == NULL){
        perror("Error opening file CourseGarbage.ind");
        return;
    }

    course_garbage cgarbage;
    int n = 1;
    while (!feof(sgarbage)) {
        fread(&cgarbage, sizeof(cgarbage), 1, sgarbage);
        if(!feof(sgarbage)) {
            printf("%d. Course garbage index: %d\n"
                   "   Teacher ID: %d\n"
                   "   Course ID: %d\n\n",
                   n, cgarbage.cgarbage_id, cgarbage.teacher_id, cgarbage.course_id);
            ++n;
        }
    }
    fclose(sgarbage);
}

#endif //TEST_READ_H
