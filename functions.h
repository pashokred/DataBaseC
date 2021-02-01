//
// Created by pashok on 31.01.21.
//

#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H
#define COURSES_COUNT 50
#pragma once

bool IsEmpty(FILE *file){
    if(NULL != file){
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        if(size != 0){
            return false;
        }
    }
    return true;
}

bool TeacherInGarbage(uint teacherId){
    FILE *mgarbage = fopen("TeacherGarbage.ind", "r");
    bool ingarbage = false;
    if(mgarbage == NULL){
        perror("Error opening file TeacherGarbage.ind");
        fclose(mgarbage);
        return true;
    }
    if(!IsEmpty(mgarbage)){
        // Find teacher in garbage
        teacher_garbage last, curr;
        fseek(mgarbage, -sizeof(teacher_garbage), SEEK_END);
        fread(&last, sizeof(teacher_garbage), 1, mgarbage);

        for(int i = 0; i < last.tgarbage_id; ++i){
            fseek(mgarbage, i * sizeof(teacher_garbage), SEEK_SET);
            fread(&curr, sizeof(teacher_garbage), 1, mgarbage);
            if(curr.teacher_id == teacherId){
                // Teacher in garbage, not exist
                ingarbage = true;
            }
        }
    }
    fclose(mgarbage);
    return ingarbage;
}

bool CourseInGarbage(uint courseId){
    FILE *cgarbage = fopen("CourseGarbage.ind", "r");
    bool ingarbage = false;
    if(cgarbage == NULL){
        perror("Error opening file TeacherGarbage.ind");
        fclose(cgarbage);
        return true;
    }
    if(!IsEmpty(cgarbage)){
        // Find teacher in garbage
        course_garbage last, curr;
        fseek(cgarbage, -sizeof(course_garbage), SEEK_END);
        fread(&last, sizeof(course_garbage), 1, cgarbage);

        for(int i = 0; i < last.cgarbage_id; ++i){
            fseek(cgarbage, i * sizeof(course_garbage), SEEK_SET);
            fread(&curr, sizeof(course_garbage), 1, cgarbage);
            if(curr.course_id == courseId){
                // Course in garbage, not exist
                ingarbage = true;
            }
        }
    }
    fclose(cgarbage);
    return ingarbage;
}

void get_m(tteacher *t, int teacherId){
    teacher_index ti;
    tteacher teacher;
    FILE *master = fopen("Teacher.fl", "r");
    if(master == NULL){
        perror("Error opening file Teacher.fl");
        return;
    }
    FILE *mind = fopen("Teacher.ind", "r");
    if(mind == NULL){
        perror("Error opening file Teacher.ind");
        return;
    }

    if(TeacherInGarbage(teacherId)){
        t = NULL;
        return;
    }

    // Find teacher index in index file
    fseek(mind, (teacherId-1) * sizeof(teacher_index), SEEK_SET);
    fread(&ti, sizeof(teacher_index), 1, mind);

    // Find teacher by record in teacher index
    fseek(master, ti.address, SEEK_SET);
    fread(&teacher, sizeof(tteacher), 1, master);

    *t = teacher;
    fclose(mind);
    fclose(master);
}



void get_s(tcourse *course, uint teacherId, uint courseId){
    tteacher t;
    get_m(&t, teacherId);
    FILE *slave = fopen("Course.fl", "r");
    if(slave == NULL){
        perror("Error opening file Course.fl");
        return;
    }

    if(CourseInGarbage(courseId)){
        course = NULL;
        return;
    }
    fseek(slave, (courseId-1) * sizeof(tcourse), SEEK_SET);
    fread(course, sizeof(tcourse), 1, slave);
    fclose(slave);
}

course_index* getCoursesByTeacher(uint teacherId) {
    static course_index courses[COURSES_COUNT];
    int j = 0;
    FILE *sind = fopen("Course.ind", "r");
    if(sind == NULL){
        perror("Error opening file Course.ind");
        return NULL;
    }
    course_index last, curr;
    fseek(sind, -sizeof(course_index), SEEK_END);
    fread(&last, sizeof(course_index), 1, sind);

    for(int i = 0; i < last.course_id; ++i){
        fseek(sind, i * sizeof(course_index), SEEK_SET);
        fread(&curr, sizeof(course_index), 1, sind);
        if(curr.teacher_id == teacherId){
            courses[j++] = curr;
        }
    }
    fclose(sind);
    return courses;
}

void del_s(uint courseId, uint teacherId){
    tcourse course;
    get_s(&course, teacherId, courseId);

    FILE *sgarbage = fopen("CourseGarbage.ind", "a+");
    if(sgarbage == NULL){
        perror("Error opening file CourseGarbage.ind");
        return;
    }
    course_garbage cgarbage;
    cgarbage.teacher_id = teacherId;
    cgarbage.course_id = courseId;
    if(IsEmpty(sgarbage)){
        cgarbage.cgarbage_id = 1;
    } else {
        course_garbage prev;
        fseek(sgarbage, -sizeof(course_garbage), SEEK_END);
        fread(&prev, sizeof(course_garbage), 1, sgarbage);
        cgarbage.cgarbage_id = prev.cgarbage_id+1;
    }
    fwrite(&cgarbage, sizeof(course_garbage), 1, sgarbage);
    fclose(sgarbage);
}

void del_m(uint teacherId){
    FILE *mgarbage = fopen("TeacherGarbage.ind", "a+");
    if(mgarbage == NULL){
        perror("Error opening file TeacherGarbage.ind");
        return;
    }
    teacher_garbage tgarbage;
    tgarbage.teacher_id = teacherId;
    if(IsEmpty(mgarbage)){
        tgarbage.tgarbage_id = 1;
    } else {
        teacher_garbage prev;
        fseek(mgarbage, -sizeof(teacher_garbage), SEEK_END);
        fread(&prev, sizeof(teacher_garbage), 1, mgarbage);
        tgarbage.tgarbage_id = prev.tgarbage_id+1;
    }
    fwrite(&tgarbage, sizeof(teacher_garbage), 1, mgarbage);

    course_index *courses;
    courses = getCoursesByTeacher(teacherId);
    for(int i = 0; i < COURSES_COUNT; ++i){
        if(&courses[i] == NULL){
            break;
        }
        del_s(courses[i].course_id, teacherId);
    }
    fclose(mgarbage);
}

void update_m(uint teacherId, const uint courses_numb){
    FILE *master = fopen("Teacher.fl", "r+");
    if(master == NULL){
        perror("Error opening file Teacher.fl");
        return;
    }
    FILE *mind = fopen("Teacher.ind", "r+");
    if(mind == NULL){
        perror("Error opening file Teacher.ind");
        return;
    }
    teacher_index ti;
    tteacher t;
    get_m(&t, teacherId);
    t.courses_numb = courses_numb;

    // Find teacher index in index file
    fseek(mind, (teacherId-1) * sizeof(teacher_index), SEEK_SET);
    fread(&ti, sizeof(teacher_index), 1, mind);

    // Find teacher by record in teacher index
    fseek(master, ti.address, SEEK_SET);
    fwrite(&t, sizeof(tteacher), 1, master);
    fclose(master);
    fclose(mind);
}

void update_s(uint courseId, uint teacherId, uint price, uint stud_amount){
    tteacher t;
    tcourse course;
    course.course_id = courseId;
    course.teacher_id = teacherId;
    course.price = price;
    course.stud_amount = stud_amount;
    get_m(&t, teacherId);
    FILE *slave = fopen("Course.fl", "r+");
    if(slave == NULL){
        perror("Error opening file Course.fl");
        return;
    }
    fseek(slave, (courseId-1) * sizeof(tcourse), SEEK_SET);
    fwrite(&course, sizeof(tcourse), 1, slave);
}

void insert_m(tteacher *t){
    FILE *master = fopen("Teacher.fl", "a+");
    if(master == NULL){
        perror("Error opening file Teacher.fl");
        return;
    }
    FILE *mind = fopen("Teacher.ind", "a+");
    if(mind == NULL){
        perror("Error opening file Teacher.ind");
        return;
    }

    teacher_index ti;
    ti.teacher_id = t->teacher_id;
    ti.address = (t->teacher_id-1) * sizeof(teacher_index);

    fwrite(t, sizeof(tteacher), 1, master);
    fwrite(&ti, sizeof(teacher_index), 1, mind);

    fclose(mind);
    fclose(master);
}

void insert_s(tcourse *course){
    FILE *slave = fopen("Course.fl", "a+");
    if(slave == NULL){
        perror("Error opening file Course.fl");
        return;
    }
    FILE *sind = fopen("Course.ind", "a+");
    if(sind == NULL){
        perror("Error opening file Course.ind");
        return;
    }

    course_index courseIndex;
    courseIndex.course_id = course->course_id;
    courseIndex.teacher_id = course->teacher_id;
    courseIndex.address = (course->course_id-1) * sizeof(course_index);

    fwrite(course, sizeof(tcourse), 1, slave);
    fwrite(&courseIndex, sizeof(course_index), 1, sind);

    fclose(sind);
    fclose(slave);
}

#endif //TEST_FUNCTIONS_H
