/* Auditorium Hall Booking - Phase 1
   1. Book hall: organiser name, event name, date, time slot (1-4)
   2. View all bookings
   3. Check a date and slot: show Free or Booked
   Slots: 1 = 9-11 AM, 2 = 11 AM-1 PM, 3 = 2-4 PM, 4 = 4-6 PM
*/
#include <stdio.h>
#include <string.h>

#define MAX 50

int main()
{
    char organiser[MAX][30];    /* organiser names */
    char event[MAX][30];        /* event names */
    char date[MAX][11];         /* dates as DD-MM-YYYY */
    int slot[MAX];              /* slot 1 to 4 */
    int count = 0;              /* number of bookings; S.No. = i + 1 */
    int choice = 0, i, found, s;
    char d[11];

    do {
        printf("\n===== AUDITORIUM HALL BOOKING =====\n");
        printf("1. Book Hall\n");
        printf("2. View All Bookings\n");
        printf("3. Check Date and Slot\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (count == MAX) {
                printf("Cannot book: storage full (%d bookings).\n", MAX);
                break;
            }
            printf("Enter organiser name: ");
            scanf(" %29[^\n]", organiser[count]);
            printf("Enter event name: ");
            scanf(" %29[^\n]", event[count]);
            printf("Enter date (DD-MM-YYYY): ");
            scanf("%10s", date[count]);
            printf("Slots: 1) 9-11 AM  2) 11 AM-1 PM  3) 2-4 PM  4) 4-6 PM\n");
            printf("Enter time slot (1-4): ");
            scanf("%d", &slot[count]);

            if (slot[count] < 1 || slot[count] > 4) {
                printf("Invalid slot. Booking not saved.\n");
                break;
            }
            /* check if this date and slot is already booked */
            found = 0;
            for (i = 0; i < count; i++) {
                if (strcmp(date[i], date[count]) == 0 && slot[i] == slot[count]) {
                    found = 1;
                }
            }
            if (found == 1) {
                printf("Hall already booked on that date and slot. Booking not saved.\n");
                break;
            }
            count++;
            printf("Hall booked with S.No. %d\n", count);
            break;

        case 2:
            if (count == 0) {
                printf("No bookings yet.\n");
                break;
            }
            printf("\n%-6s %-20s %-20s %-11s %-4s\n", "S.No.", "Organiser", "Event", "Date", "Slot");
            printf("-------------------------------------------------------------------\n");
            for (i = 0; i < count; i++) {
                printf("%-6d %-20s %-20s %-11s %-4d\n",
                       i + 1, organiser[i], event[i], date[i], slot[i]);
            }
            break;

        case 3:
            printf("Enter date (DD-MM-YYYY): ");
            scanf("%10s", d);
            printf("Enter time slot (1-4): ");
            scanf("%d", &s);
            if (s < 1 || s > 4) {
                printf("Invalid slot. Enter 1 to 4.\n");
                break;
            }
            found = 0;
            for (i = 0; i < count; i++) {
                if (strcmp(date[i], d) == 0 && slot[i] == s) {
                    printf("BOOKED: S.No. %d, %s by %s\n", i + 1, event[i], organiser[i]);
                    found = 1;
                }
            }
            if (found == 0)
                printf("FREE: The hall is available on %s, slot %d\n", d, s);
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
