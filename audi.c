#include <stdio.h>
#include <string.h>

#define MAX 50
#define NAME_LENGTH 30
#define DATE_LENGTH 11

int readInt(const char *prompt, int *value)
{
    char line[100];
    char extra;

    printf("%s", prompt);

    if (fgets(line, sizeof(line), stdin) == NULL)
        return 0;

    /* Reject input that is not exactly one integer. */
    if (sscanf(line, " %d %c", value, &extra) != 1)
        return -1;

    return 1;
}

int isValidDate(const char date[])
{
    int day, month, year;
    char extra;

    if (strlen(date) != 10 || date[2] != '-' || date[5] != '-')
        return 0;

    if (sscanf(date, "%2d-%2d-%4d%c", &day, &month, &year, &extra) != 3)
        return 0;

    if (month < 1 || month > 12 || year < 1)
        return 0;

    if (day < 1 || day > 31)
        return 0;

    return 1;
}

void readLine(const char *prompt, char text[], int size)
{
    printf("%s", prompt);

    if (fgets(text, size, stdin) != NULL) {
        text[strcspn(text, "\n")] = '\0';
    }
}

int main(void)
{
    char organiser[MAX][NAME_LENGTH];
    char event[MAX][NAME_LENGTH];
    char date[MAX][DATE_LENGTH];
    int slot[MAX];
    int count = 0;
    int choice, result, i, found, selectedSlot;
    char checkedDate[DATE_LENGTH];

    do {
        printf("\n===== AUDITORIUM HALL BOOKING =====\n");
        printf("1. Book Hall\n");
        printf("2. View All Bookings\n");
        printf("3. Check Date and Slot\n");
        printf("4. Exit\n");

        result = readInt("Enter your choice: ", &choice);
        if (result == 0) {
            printf("\nInput ended. Exiting.\n");
            break;
        }
        if (result == -1) {
            printf("Invalid input. Enter a number from 1 to 4.\n");
            continue;
        }

        switch (choice) {
        case 1:
            if (count >= MAX) {
                printf("Cannot book: storage is full (%d bookings).\n", MAX);
                break;
            }

            readLine("Enter organiser name: ", organiser[count], NAME_LENGTH);
            readLine("Enter event name: ", event[count], NAME_LENGTH);
            readLine("Enter date (DD-MM-YYYY): ", date[count], DATE_LENGTH);

            if (!isValidDate(date[count])) {
                printf("Invalid date. Use DD-MM-YYYY.\n");
                break;
            }

            printf("Slots: 1) 9-11 AM  2) 11 AM-1 PM  "
                   "3) 2-4 PM  4) 4-6 PM\n");

            result = readInt("Enter time slot (1-4): ", &selectedSlot);
            if (result != 1 || selectedSlot < 1 || selectedSlot > 4) {
                printf("Invalid slot. Enter a number from 1 to 4.\n");
                break;
            }

            found = 0;
            for (i = 0; i < count; i++) {
                if (strcmp(date[i], date[count]) == 0 &&
                    slot[i] == selectedSlot) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("That date and slot are already booked. "
                       "Booking not saved.\n");
                break;
            }

            slot[count] = selectedSlot;
            count++;
            printf("Hall booked successfully. S.No. %d\n", count);
            break;

        case 2:
            if (count == 0) {
                printf("No bookings yet.\n");
                break;
            }

            printf("\n%-6s %-20s %-20s %-11s %-4s\n",
                   "S.No.", "Organiser", "Event", "Date", "Slot");
            printf("---------------------------------------------------------------\n");

            for (i = 0; i < count; i++) {
                printf("%-6d %-20s %-20s %-11s %-4d\n",
                       i + 1, organiser[i], event[i], date[i], slot[i]);
            }
            break;

        case 3:
            readLine("Enter date (DD-MM-YYYY): ",
                     checkedDate, DATE_LENGTH);

            if (!isValidDate(checkedDate)) {
                printf("Invalid date. Use DD-MM-YYYY.\n");
                break;
            }

            result = readInt("Enter time slot (1-4): ", &selectedSlot);
            if (result != 1 || selectedSlot < 1 || selectedSlot > 4) {
                printf("Invalid slot. Enter a number from 1 to 4.\n");
                break;
            }

            found = 0;
            for (i = 0; i < count; i++) {
                if (strcmp(date[i], checkedDate) == 0 &&
                    slot[i] == selectedSlot) {
                    printf("BOOKED: S.No. %d, %s by %s\n",
                           i + 1, event[i], organiser[i]);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("FREE: The hall is available on %s, slot %d.\n",
                       checkedDate, selectedSlot);
            }
            break;

        case 4:
            printf("Exiting. Goodbye!\n");
            break;

        default:
            printf("Invalid choice. Enter 1 to 4.\n");
        }
    } while (choice != 4);

    return 0;
}