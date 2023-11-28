
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Define data structures for bus schedules and bookings
struct BusSchedule {
    int busID;
    char source[50];
    char destination[50];
    char departureTime[10];
    int totalSeats;
    int availableSeats;
};

struct Booking {
    int bookingID;
    int busID;
    char customerName[50];
    char departureTime[10];
    int seatNumber;
};

// Function to load data from files
void loadBusSchedules(struct BusSchedule schedules[], int *numSchedules) {
    FILE *file = fopen("bus_schedules.txt", "r");
    if (file == NULL) {
        printf("No bus schedules found.\n");
        return;
    }

    while (fread(schedules, sizeof(struct BusSchedule), 1, file)) {
        (*numSchedules)++;
    }

    fclose(file);
}

void loadBookings(struct Booking bookings[], int *numBookings) {
    FILE *file = fopen("bookings.txt", "r");
    if (file == NULL) {
        printf("No bookings found.\n");
        return;
    }

    while (fread(bookings, sizeof(struct Booking), 1, file)) {
        (*numBookings)++;
    }

    fclose(file);
}

// Function to save data to files
void saveBusSchedules(const struct BusSchedule schedules[], int numSchedules) {
    FILE *file = fopen("bus_schedules.txt", "w");
    if (file == NULL) {
        printf("Error saving bus schedules.\n");
        return;
    }

    fwrite(schedules, sizeof(struct BusSchedule), numSchedules, file);

    fclose(file);
}

void saveBookings(const struct Booking bookings[], int numBookings) {
    FILE *file = fopen("bookings.txt", "w");
    if (file == NULL) {
        printf("Error saving bookings.\n");
        return;
    }

    fwrite(bookings, sizeof(struct Booking), numBookings, file);

    fclose(file);
}

// Employee login system (simplified for this example)
bool employeeLogin() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // Replace with actual authentication logic
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        return true;
    }

    return false;
}

// Function to add a new bus schedule
void addBusSchedule(struct BusSchedule schedules[], int *numSchedules) {
    // Prompt for schedule details and add it to the array
    struct BusSchedule newSchedule;
    printf("Enter source: ");
    scanf("%s", newSchedule.source);
    printf("Enter destination: ");
    scanf("%s", newSchedule.destination);
    printf("Enter departure time: ");
    scanf("%s", newSchedule.departureTime);
    printf("Enter total seats: ");
    scanf("%d", &newSchedule.totalSeats);
    newSchedule.availableSeats = newSchedule.totalSeats;

    // Assign a unique bus ID
    newSchedule.busID = (*numSchedules) + 1;

    schedules[*numSchedules] = newSchedule;
    (*numSchedules)++;
}

// Function to display available seats for a specific bus
void displayAvailableSeats(struct BusSchedule schedules[], int numSchedules, int busID) {
    for (int i = 0; i < numSchedules; i++) {
        if (schedules[i].busID == busID) {
            printf("Bus ID: %d\n", schedules[i].busID);
            printf("Source: %s\n", schedules[i].source);
            printf("Destination: %s\n", schedules[i].destination);
            printf("Departure Time: %s\n", schedules[i].departureTime);
            printf("Available Seats: %d\n", schedules[i].availableSeats);
            return;
        }
    }
    printf("Bus ID %d not found.\n", busID);
}

// Function to book a seat
void bookSeat(struct BusSchedule schedules[], int numSchedules, struct Booking bookings[], int *numBookings) {
    // Prompt for booking details
    struct Booking newBooking;
    printf("Enter your name: ");
    scanf("%s", newBooking.customerName);
    printf("Enter bus ID: ");
    scanf("%d", &newBooking.busID);
    printf("Enter seat number: ");
    scanf("%d", &newBooking.seatNumber);

    // Check if the seat is available
    for (int i = 0; i < numSchedules; i++) {
        if (schedules[i].busID == newBooking.busID) {
            if (schedules[i].availableSeats > 0) {
                schedules[i].availableSeats--;
                newBooking.bookingID = (*numBookings) + 1;
                strcpy(newBooking.departureTime, schedules[i].departureTime);
                bookings[*numBookings] = newBooking;
                (*numBookings)++;
                printf("Booking successful. Your booking ID is %d.\n", newBooking.bookingID);
                return;
            } else {
                printf("Sorry, the bus is fully booked.\n");
                return;
            }
        }
    }
    printf("Bus ID %d not found.\n", newBooking.busID);
}

// Function to view booking history
void viewBookingHistory(struct Booking bookings[], int numBookings) {
    for (int i = 0; i < numBookings; i++) {
        printf("Booking ID: %d\n", bookings[i].bookingID);
        printf("Customer Name: %s\n", bookings[i].customerName);
        printf("Bus ID: %d\n", bookings[i].busID);
        printf("Seat Number: %d\n", bookings[i].seatNumber);
        printf("Departure Time: %s\n", bookings[i].departureTime);
        printf("------------------------------\n");
    }
}

int main() {
    struct BusSchedule schedules[100];
    struct Booking bookings[100];
    int numSchedules = 0;
    int numBookings = 0;

    // Load data from files
    loadBusSchedules(schedules, &numSchedules);
    loadBookings(bookings, &numBookings);

    int choice;

    while (1) {
        printf("Bus Reservation and Booking System\n");
        printf("1. Add Bus Schedule\n");
        printf("2. Display Available Seats\n");
        printf("3. Book a Seat\n");
        printf("4. View Booking History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

         switch (choice) {
            case 1:
                if (employeeLogin()) {
                    addBusSchedule(schedules, &numSchedules);
                    saveBusSchedules(schedules, numSchedules);
                } else {
                    printf("Employee login failed. Please try again.\n");
                }
                break;
            case 2:
                {
                int busID;  // Declare variables within a block
                    printf("Enter the Bus ID: ");
                    scanf("%d", &busID);
                    displayAvailableSeats(schedules, numSchedules, busID);
                }
                break;
            case 3:
                bookSeat(schedules, numSchedules, bookings, &numBookings);
                saveBookings(bookings, numBookings);
                break;
            case 4:
                viewBookingHistory(bookings, numBookings);
                break;
            case 5:
                // Exit the program
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }


    return 0;
}
