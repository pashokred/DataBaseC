//
// Created by pashok on 31.01.21.
//

#ifndef TEST_STRUCTURES_H
#define TEST_STRUCTURES_H
#pragma once
#include "stdbool.h"

#define FILENAME_LEN 80
#define FULLNAME_LEN 60
typedef unsigned int uint;

///////  TEACHER   /////////

typedef struct tag_teacher {
    uint teacher_id;
    uint courses_numb;
    char name[FULLNAME_LEN];
} tteacher;

typedef struct tag_teacher_index {
    uint address;
    uint teacher_id;
    bool isDeleted;
} teacher_index;

typedef struct tag_teacher_garbage {
    uint tgarbage_id;
    uint teacher_id;
} teacher_garbage;


///////  COURSE   /////////

typedef struct tag_course {
    uint course_id;
    uint teacher_id;
    uint price;
    uint stud_amount;
} tcourse;

typedef struct tag_course_index {
    uint address;
    uint course_id;
    uint teacher_id;
    bool isDeleted;
} course_index;

typedef struct tag_course_garbage {
    uint cgarbage_id;
    uint course_id;
    uint teacher_id;
} course_garbage;


#endif //TEST_STRUCTURES_H
