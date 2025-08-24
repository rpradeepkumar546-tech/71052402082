#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Attendance {
    char rollNo[15];
    char name[50];
    char date[15];
    char status[10];
    struct Attendance* next;
} Attendance;

Attendance* head = NULL;

// 1. Add Record
void addRecord(char rollNo[], char name[], char date[], char status[]) {
    Attendance* newNode = (Attendance*)malloc(sizeof(Attendance));
    strcpy(newNode->rollNo, rollNo);
    strcpy(newNode->name, name);
    strcpy(newNode->date, date);
    strcpy(newNode->status, status);
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Attendance* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    printf("Record added successfully!\n");
}

// 2. Delete Record
void deleteRecord(char rollNo[], char date[]) {
    Attendance *temp = head, *prev = NULL;

    while (temp != NULL && !(strcmp(temp->rollNo, rollNo) == 0 && strcmp(temp->date, date) == 0)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Record not found!\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Record deleted successfully!\n");
}

// 3. Search Record
void searchRecord(char rollNo[], char date[]) {
    Attendance* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->rollNo, rollNo) == 0 && strcmp(temp->date, date) == 0) {
            printf("Record Found -> Roll No: %s, Name: %s, Date: %s, Status: %s\n",
                   temp->rollNo, temp->name, temp->date, temp->status);
            return;
        }
        temp = temp->next;
    }
    printf("Record not found!\n");
}

// 4. Display Records by Date
void displayByDate(char date[]) {
    Attendance* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->date, date) == 0) {
            printf("Roll No: %s, Name: %s, Date: %s, Status: %s\n",
                   temp->rollNo, temp->name, temp->date, temp->status);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) printf("No records for this date!\n");
}

// 5. Reverse Display
void reverseDisplay(Attendance* node) {
    if (node == NULL) return;
    reverseDisplay(node->next);
    printf("Roll No: %s, Name: %s, Date: %s, Status: %s\n",
           node->rollNo, node->name, node->date, node->status);
}

// 6. Clone Attendance List
Attendance* cloneList() {
    if (head == NULL) return NULL;
    Attendance *cloneHead = NULL, *cloneTail = NULL, *temp = head;

    while (temp != NULL) {
        Attendance* newNode = (Attendance*)malloc(sizeof(Attendance));
        strcpy(newNode->rollNo, temp->rollNo);
        strcpy(newNode->name, temp->name);
        strcpy(newNode->date, temp->date);
        strcpy(newNode->status, temp->status);
        newNode->next = NULL;

        if (cloneHead == NULL) {
            cloneHead = newNode;
            cloneTail = newNode;
        } else {
            cloneTail->next = newNode;
            cloneTail = newNode;
        }
        temp = temp->next;
    }
    printf("List cloned successfully!\n");
    return cloneHead;
}

int main() {
    int choice;
    char rollNo[15], name[50], date[15], status[10];
    Attendance* clonedList = NULL;

    do {
        printf("\n--- Student Attendance Monitoring System ---\n");
        printf("1. Add Record\n");
        printf("2. Delete Record\n");
        printf("3. Search Record\n");
        printf("4. Display Records by Date\n");
        printf("5. Reverse Display\n");
        printf("6. Clone Attendance List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch(choice) {
            case 1:
                printf("Enter Roll No, Name, Date (dd-mm-yyyy), Status (Present/Absent):\n");
                scanf("%s %[^\n] %s %s", rollNo, name, date, status);
                addRecord(rollNo, name, date, status);
                break;
            case 2:
                printf("Enter Roll No and Date to delete: ");
                scanf("%s %s", rollNo, date);
                deleteRecord(rollNo, date);
                break;
            case 3:
                printf("Enter Roll No and Date to search: ");
                scanf("%s %s", rollNo, date);
                searchRecord(rollNo, date);
                break;
            case 4:
                printf("Enter Date to display records: ");
                scanf("%s", date);
                displayByDate(date);
                break;
            case 5:
                printf("Attendance in Reverse Order:\n");
                reverseDisplay(head);
                break;
            case 6:
                clonedList = cloneList();
                break;
            case 7:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 7);

    return 0;
}
