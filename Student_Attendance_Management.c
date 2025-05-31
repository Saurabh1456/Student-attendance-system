#include <stdio.h>
#include <string.h>
#include <time.h>

struct Student{

    char name[100];
    int rollNo;
    char batch[20];

};
void addStudent() {
    struct Student s;
    FILE *ptr;

    printf("Enter name: ");
    getchar();
    scanf("%[^\n]", s.name);
    
    printf("Enter Roll no: ");
    scanf("%d", &s.rollNo);
    
    getchar();
    printf("Enter Batch name: ");
    scanf("%[^\n]", s.batch);

    ptr = fopen("students_db.txt", "a"); 
    
    if (ptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(ptr, "%d,%s,%s\n", s.rollNo, s.name, s.batch);
    fclose(ptr);

    printf("Student added successfully!\n");
}
void updateStudent() {
    printf("Enter student roll number to update: ");
    int rollNo;
    scanf("%d", &rollNo);

    FILE *ptr = fopen("students_db.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (ptr == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[200];
    int found = 0;
    while (fgets(line, sizeof(line), ptr) != NULL) {
        int r;
        char name[100], subject[100];

        sscanf(line, "%d,%[^,],%[^\n]", &r, name, subject);

        if (r == rollNo) {
            found = 1;
            printf("Enter new name: ");
            getchar();
            scanf("%[^\n]", name);
            printf("Enter new batch: ");
            getchar();
            scanf("%[^\n]", subject);
            fprintf(temp, "%d,%s,%s\n", rollNo, name, subject);
        } else {
            fprintf(temp, "%s", line);
        }
    }

    fclose(ptr);
    fclose(temp);
    remove("students_db.txt");
    rename("temp.txt", "students_db.txt");

    if (found)
        printf("Student record updated successfully!\n");
    else
        printf("Student not found!\n");
}
void markAttendance() {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char timeStr[100];

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", local);

    FILE *students = fopen("students_db.txt", "r");
    FILE *attendanceLog = fopen("attendancelog.txt", "a");

    char line[200];
    printf("Enter subject: ");
    char sub[50];
    getchar();
    fgets(sub, sizeof(sub), stdin);
    sub[strcspn(sub, "\n")] = '\0';

    char attendance;
    
    printf("Enter attendance status (P/A):\n");

    while (fgets(line, sizeof(line), students) != NULL) {
        int rollNo;
        char name[100], subject[100];

        sscanf(line, "%d,%[^,],%[^\n]", &rollNo, name, subject);
        
        printf("Roll No %d (%s): ", rollNo, name);
        scanf(" %c", &attendance);

        fprintf(attendanceLog, "%02d-%02d-%04d %02d:%02d:%02d\t%-20s\t%-10c\t%-10s\n",
                local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
                local->tm_hour, local->tm_min, local->tm_sec, name, attendance, sub);
    }

    fclose(students);
    fclose(attendanceLog);

    printf("Attendance marked successfully!\n");
}
void viewAttendance()
{
    FILE* ptr;
    char line[100];
    ptr=fopen("attendancelog.txt","r");

    while (fgets(line, sizeof(line), ptr) != NULL) {
        printf("%s\n", line);
    }

    fclose(ptr);

}
void search()
{

    FILE *ptr;
    char line[200];
    char searchName[50], searchSubject[50], searchDate[15];

    ptr = fopen("attendancelog.txt", "r");
    

    int choice;
    printf("Search by:\n");
    printf("1. Student Name\n");
    printf("2. Subject\n");
    printf("3. Date (DD-MM-YYYY)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter student name: ");
        scanf("%s", searchName);
    } else if (choice == 2) {
        printf("Enter subject name: ");
        scanf("%s", searchSubject);
    } else if (choice == 3) {
        printf("Enter date (DD-MM-YYYY): ");
        scanf("%s", searchDate);
    } else {
        printf("Invalid choice!\n");
        fclose(ptr);
    }

    printf("\nSearching...\n");

    int found = 0;
    while (fgets(line, sizeof(line), ptr) != NULL) {
        if ((choice == 1 && strstr(line, searchName)) ||
            (choice == 2 && strstr(line, searchSubject)) ||
            (choice == 3 && strstr(line, searchDate))) {
            printf("Record Found: %s", line);
            found = 1;
        }
    }

    fclose(ptr);

    if (!found) {
        printf("No matching records found.\n");
    }
}
void deleteStudent() {
    printf("Enter student roll number to delete: ");
    int rollNo;
    scanf("%d", &rollNo);

    FILE *ptr = fopen("students_db.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (ptr == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[200];
    int found = 0;
    while (fgets(line, sizeof(line), ptr) != NULL) {
        int r;
        sscanf(line, "%d,", &r);

        if (r != rollNo) {
            fprintf(temp, "%s", line);
        } else {
            found = 1;
        }
    }

    fclose(ptr);
    fclose(temp);
    remove("students_db.txt");
    rename("temp.txt", "students_db.txt");

    if (found)
        printf("Student deleted successfully!\n");
    else
        printf("Student not found!\n");
}
int main()
{
    int n;
    do
    {
        printf("Enter 1 to add students\n");
        printf("Enter 2 to update student details\n");
        printf("Enter 3 to mark attendance\n");
        printf("Enter 4 to view attendance log\n");
        printf("Enter 5 to search\n");
        printf("Enter 6 to delete student record\n");
        printf("Enter 7 to EXIT\n");
        printf("Enter your choice:");
        scanf("%d",&n);

        switch (n)
        {
            case 1:
            addStudent();
            break;

            case 2:
            updateStudent();
            break;

            case 3:
            markAttendance();
            break;

            case 4:
            viewAttendance();
            break;

            case 5:
            search();
            break;

            case 6:
            deleteStudent();
            break;

            case 7:
            printf("Exiting........");
            break;

        default:
            break;
         }
    } while (n!=7);
      
}
