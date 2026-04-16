#include <stdio.h>
#include <conio.h>
#include <string.h>
#define MAX_ROOMS 100
struct Room {
    int number;
    char type[20];       
    char acType[10];     
    int price;          
    int booked;         
    char customer[50];  
    int daysBooked;      
};

struct Room rooms[MAX_ROOMS];
int roomCount = 0;


void clrscr_safe();
void addRoom();
void displayRooms();
void displayAvailableRooms();
void bookRoom();
void cancelBooking();
void searchRoom();
int findRoomIndexByNumber(int rno);
void waitForEnter();

void clrscr_safe() {
        clrscr();

}

void waitForEnter() {
    int c;
    /* consume leftover characters until newline */
    while ((c = getchar()) != '\n' && c != EOF) ;
    printf("Press Enter to continue...");
    getchar(); /* wait for Enter */
}

void addRoom() {
    int rno;
    /* local declarations first for Turbo C compatibility */
    clrscr_safe();
    if (roomCount >= MAX_ROOMS) {
        printf("Room capacity reached. Cannot add more rooms.\n");
        waitForEnter();
        return;
    }
    printf("Add Room\n");
    printf("Enter room number: ");
    scanf("%d", &rno);
    if (findRoomIndexByNumber(rno) != -1) {
        printf("Room with number %d already exists.\n", rno);
        waitForEnter();
        return;
    }
    rooms[roomCount].number = rno;
    /* consume newline */
    getchar();
    printf("Enter room type (Single/Double/Suite): ");
    gets(rooms[roomCount].type); /* Turbo C supports gets */
    printf("Enter AC type (AC/Non-AC): ");
    gets(rooms[roomCount].acType);
    printf("Enter price per day: ");
    scanf("%d", &rooms[roomCount].price);
    rooms[roomCount].booked = 0;
    rooms[roomCount].customer[0] = '\0';
    rooms[roomCount].daysBooked = 0;
    roomCount++;
    printf("Room added successfully.\n");
    waitForEnter();
}

void displayRooms() {
    int i;
    clrscr_safe();
    printf("All Rooms\n");
    if (roomCount == 0) {
        printf("No rooms available.\n");
    } else {
        printf("No.  Type       AC-Type   Price/day  Status    Customer    Days\n");
        printf("---- ---------- --------- ---------- --------- ----------- ----\n");
        for (i = 0; i < roomCount; i++) {
            printf("%-4d %-10s %-9s %-10d %-9s %-11s %-4d\n",
                   rooms[i].number,
                   rooms[i].type,
                   rooms[i].acType,
                   rooms[i].price,
                   rooms[i].booked ? "Booked" : "Available",
                   rooms[i].booked ? rooms[i].customer : "-",
                   rooms[i].booked ? rooms[i].daysBooked : 0);
        }
    }
    waitForEnter();
}

/* Show only available rooms with price/day (helpful before booking) */
void displayAvailableRooms() {
    int i;
    int any = 0;
    printf("Available Rooms (showing price per day):\n");
    printf("No.  Type       AC-Type   Price/day\n");
    printf("---- ---------- --------- ----------\n");
    for (i = 0; i < roomCount; i++) {
        if (!rooms[i].booked) {
            any = 1;
            printf("%-4d %-10s %-9s %-10d\n",
                   rooms[i].number,
                   rooms[i].type,
                   rooms[i].acType,
                   rooms[i].price);
        }
    }
    if (!any) printf("No available rooms right now.\n");
}

void bookRoom() {
    int rno, i, idx;
    int days;
    clrscr_safe();
    printf("Book Room\n");
    if (roomCount == 0) {
        printf("No rooms in system. Add rooms first.\n");
        waitForEnter();
        return;
    }
    /* show available rooms first */
    displayAvailableRooms();
    /* ask which room to book */
    printf("\nEnter room number to book (choose from available list): ");
    scanf("%d", &rno);
    idx = findRoomIndexByNumber(rno);
    if (idx == -1) {
        printf("Room %d not found.\n", rno);
        waitForEnter();
        return;
    }
    if (rooms[idx].booked) {
        printf("Room %d already booked by %s.\n", rno, rooms[idx].customer);
        waitForEnter();
        return;
    }
    /* show price per day */
    printf("Price per day for room %d is: %d\n", rno, rooms[idx].price);
    /* consume newline before gets */
    getchar();
    printf("Enter customer name: ");
    gets(rooms[idx].customer);
    printf("Enter number of days to book: ");
    scanf("%d", &days);
    if (days <= 0) days = 1; /* default to 1 if invalid */
    rooms[idx].booked = 1;
    rooms[idx].daysBooked = days;
    /* compute total cost */
    {
        long total = (long) rooms[idx].price * days;
        printf("Room %d successfully booked for %s for %d day(s).\n", rno, rooms[idx].customer, days);
        printf("Total amount = %ld\n", total);
    }
    waitForEnter();
}

void cancelBooking() {
    int rno, idx;
    clrscr_safe();
    printf("Cancel Booking\n");
    if (roomCount == 0) {
        printf("No rooms in system.\n");
        waitForEnter();
        return;
    }
    printf("Enter room number to cancel booking: ");
    scanf("%d", &rno);
    idx = findRoomIndexByNumber(rno);
    if (idx == -1) {
        printf("Room %d not found.\n", rno);
        waitForEnter();
        return;
    }
    if (!rooms[idx].booked) {
        printf("Room %d is not currently booked.\n", rno);
        waitForEnter();
        return;
    }
    rooms[idx].booked = 0;
    rooms[idx].customer[0] = '\0';
    rooms[idx].daysBooked = 0;
    printf("Booking for room %d cancelled.\n", rno);
    waitForEnter();
}

void searchRoom() {
    int rno, idx;
    clrscr_safe();
    printf("Search Room by Number\n");
    printf("Enter room number: ");
    scanf("%d", &rno);
    idx = findRoomIndexByNumber(rno);
    if (idx == -1) {
        printf("Room %d not found.\n", rno);
    } else {
        printf("Room Details:\n");
        printf("Number: %d\n", rooms[idx].number);
        printf("Type: %s\n", rooms[idx].type);
        printf("AC Type: %s\n", rooms[idx].acType);
        printf("Price per day: %d\n", rooms[idx].price);
        printf("Status: %s\n", rooms[idx].booked ? "Booked" : "Available");
        if (rooms[idx].booked) {
            printf("Customer: %s\n", rooms[idx].customer);
            printf("Days booked: %d\n", rooms[idx].daysBooked);
            printf("Total cost: %ld\n", (long)rooms[idx].price * rooms[idx].daysBooked);
        }
    }
    waitForEnter();
}

int findRoomIndexByNumber(int rno) {
    int i;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i].number == rno) return i;
    }
    return -1;
}

int main() {
    int choice;
    clrscr_safe();
    while (1) {
        clrscr_safe();
        printf("=== Hotel Room Reservation System ===\n");
        printf("1. Add Room\n");
        printf("2. Display Rooms\n");
        printf("3. Book Room\n");
        printf("4. Cancel Booking\n");
        printf("5. Search Room\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addRoom(); break;
            case 2: displayRooms(); break;
            case 3: bookRoom(); break;
            case 4: cancelBooking(); break;
            case 5: searchRoom(); break;
            case 6:
                clrscr_safe();
                printf("Exiting... Press Enter.\n");
                waitForEnter();
                return 0;
            default:
                printf("Invalid choice.\n");
                waitForEnter();
        }
    }
    return 0;
}
