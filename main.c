#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "ticket.h"
#include "train.h"
#include "logger.h"

void display_menu() {
    printf("\n=== Train Ticket Booking System ===\n");
    printf("1. Register\n2. Login\n3. Book Ticket\n4. Cancel Ticket\n5. Check PNR Status\n6. View Train Schedule\n7. Railway Employee Login\n8. Exit\n");
    printf("Enter choice: ");
}

int main() {
    init_users();
    init_trains();
    init_tickets();
    init_logger();

    int choice;
    char username[50], password[50];
    int logged_in = 0;
    int employee_logged_in = 0;

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1: // Register
                printf("Enter username: ");
                fgets(username, 50, stdin);
                username[strcspn(username, "\n")] = 0;
                printf("Enter password: ");
                fgets(password, 50, stdin);
                password[strcspn(password, "\n")] = 0;
                if (register_user(username, password)) {
                    printf("Registration successful!\n");
                } else {
                    printf("Registration failed: Username exists or error occurred.\n");
                }
                break;

            case 2: // Login
                printf("Enter username: ");
                fgets(username, 50, stdin);
                username[strcspn(username, "\n")] = 0;
                printf("Enter password: ");
                fgets(password, 50, stdin);
                password[strcspn(password, "\n")] = 0;
                if (login_user(username, password)) {
                    printf("Login successful!\n");
                    logged_in = 1;
                } else {
                    printf("Login failed: Invalid credentials.\n");
                }
                break;

            case 3: // Book Ticket
                if (!logged_in) {
                    printf("Please login first.\n");
                    break;
                }
                printf("Enter train number: ");
                char train_no[10];
                fgets(train_no, 10, stdin);
                train_no[strcspn(train_no, "\n")] = 0;
                printf("Enter number of passengers (max 4 for Tatkal): ");
                int passengers;
                scanf("%d", &passengers);
                getchar();
                printf("Enter quota (General/Tatkal): ");
                char quota[10];
                fgets(quota, 10, stdin);
                quota[strcspn(quota, "\n")] = 0;
                if (passengers > 4 && strcmp(quota, "Tatkal") == 0) {
                    printf("Error: Max 4 passengers allowed for Tatkal.\n");
                    break;
                }
                book_ticket(username, train_no, passengers, quota);
                break;

            case 4: // Cancel Ticket
                if (!logged_in) {
                    printf("Please login first.\n");
                    break;
                }
                printf("Enter PNR number: ");
                char pnr[10];
                fgets(pnr, 10, stdin);
                pnr[strcspn(pnr, "\n")] = 0;
                cancel_ticket(pnr, username);
                break;

            case 5: // Check PNR Status
                printf("Enter PNR number: ");
                fgets(pnr, 10, stdin);
                pnr[strcspn(pnr, "\n")] = 0;
                check_pnr_status(pnr);
                break;

            case 6: // View Train Schedule
                display_trains();
                break;

            case 7: // Railway Employee Login
                printf("Enter employee username: ");
                fgets(username, 50, stdin);
                username[strcspn(username, "\n")] = 0;
                printf("Enter employee password: ");
                fgets(password, 50, stdin);
                password[strcspn(password, "\n")] = 0;
                if (strcmp(username, "railway") == 0 && strcmp(password, "admin123") == 0) {
                    printf("Employee login successful!\n");
                    employee_logged_in = 1;
                    printf("Enter PNR number to view passengers: ");
                    fgets(pnr, 10, stdin);
                    pnr[strcspn(pnr, "\n")] = 0;
                    display_passengers(pnr);
                } else {
                    printf("Employee login failed: Invalid credentials.\n");
                }
                break;

            case 8: // Exit
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
