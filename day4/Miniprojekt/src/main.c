#include <stdio.h>

#include "../include/student_tracker.h"

int main(void)
{
    StudentRecord records[MAX_STUDENTS];
    int recordCount = 0;
    int isRunning = 1;
    MenuOption selectedOption;

    initializeRecords(records, MAX_STUDENTS);

    while (isRunning) {
        showMenu(recordCount, MAX_STUDENTS);
        selectedOption = readMenuChoice();
        if (selectedOption == 0) {
            continue;
        }

        switch (selectedOption) {
            case MENU_ADD_RECORD:
                addStudentRecord(records, MAX_STUDENTS, &recordCount);
                break;
            case MENU_SHOW_RECORDS:
                displayStudentRecords(records, recordCount);
                break;
            case MENU_SHOW_REPORT:
                generateAnalyticalReport(records, recordCount);
                break;
            case MENU_SEARCH_RECORDS:
                searchStudentRecords(records, recordCount);
                break;
            case MENU_UPDATE_RECORD:
                updateStudentRecord(records, recordCount);
                break;
            case MENU_SHOW_RANKING:
                showProgressRanking(records, recordCount);
                break;
            case MENU_EDIT_RECORD:
                editStudentRecord(records, recordCount);
                break;
            case MENU_DELETE_RECORD:
                deleteStudentRecord(records, &recordCount);
                break;
            case MENU_EXIT:
                printf("Programi po mbyllet.\n");
                isRunning = 0;
                break;
            default:
                printf("Ndodhi nje gabim ne menu. Provo perseri.\n");
                break;
        }
    }

    return 0;
}
