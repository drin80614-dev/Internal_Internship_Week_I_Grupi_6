#ifndef STUDENT_TRACKER_H
#define STUDENT_TRACKER_H

#define MAX_STUDENTS 10
#define NAME_LENGTH 50

typedef enum {
    MENU_ADD_RECORD = 1,
    MENU_SHOW_RECORDS,
    MENU_SHOW_REPORT,
    MENU_SEARCH_RECORDS,
    MENU_UPDATE_RECORD,
    MENU_SHOW_RANKING,
    MENU_EDIT_RECORD,
    MENU_DELETE_RECORD,
    MENU_EXIT
} MenuOption;

typedef enum {
    STATUS_BELOW_TARGET = 1,
    STATUS_ON_TRACK,
    STATUS_COMPLETED
} ProgressStatus;

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float progressScore;
    ProgressStatus status;
} StudentRecord;

void initializeRecords(StudentRecord records[], int size);
void showMenu(int recordCount, int maxStudents);
MenuOption readMenuChoice(void);
void addStudentRecord(StudentRecord records[], int size, int *recordCount);
void displayStudentRecords(const StudentRecord records[], int recordCount);
void generateAnalyticalReport(const StudentRecord records[], int recordCount);
void searchStudentRecords(const StudentRecord records[], int recordCount);
void updateStudentRecord(StudentRecord records[], int recordCount);
void showProgressRanking(const StudentRecord records[], int recordCount);
void editStudentRecord(StudentRecord records[], int recordCount);
void deleteStudentRecord(StudentRecord records[], int *recordCount);
const char *getStatusText(ProgressStatus status);

#endif
