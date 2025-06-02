#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ticket.h"
#include "train.h"
#include "logger.h"
#include "utils.h"

Ticket tickets[MAX_TICKETS];
int ticket_count = 0;

void init_tickets() {
    FILE* fp = fopen("tickets.txt", "r");
    if (fp) {
        while (fscanf(fp, "%s %s %s %d %s %s %d", tickets[ticket_count].pnr, tickets[ticket_count].username,
                      tickets[ticket_count].train_no, &tickets[ticket_count].passengers, tickets[ticket_count].quota,
                      tickets[ticket_count].status, &tickets[ticket_count].is_cancelled) == 7) {
            ticket_count++;
        }
        fclose(fp);
    }
}

void book_ticket(const char* username, const char* train_no, int passengers, const char* quota) {
    int available_seats = get_available_seats(train_no);
    if (available_seats == -1) {
        printf("Error: Invalid train number.\n");
        return;
    }
    if (passengers < 1 || (strcmp(quota, "Tatkal") == 0 && passengers > 4)) {
        printf("Error: Invalid number of passengers.\n");
        return;
    }
    char pnr[10];
    strcpy(pnr, generate_pnr());
    if (available_seats < passengers) {
        printf("Waitlisted: Not enough seats available.\n");
        log_event(username, "Booking", "Waitlisted", pnr, train_no, passengers, quota, "Waitlisted");
        strcpy(tickets[ticket_count].pnr, pnr);
        strcpy(tickets[ticket_count].username, username);
        strcpy(tickets[ticket_count].train_no, train_no);
        tickets[ticket_count].passengers = passengers;
        strcpy(tickets[ticket_count].quota, quota);
        strcpy(tickets[ticket_count].status, "Waitlisted");
        tickets[ticket_count].is_cancelled = 0;
    } else {
        if (update_seats(train_no, passengers, 1)) {
            printf("Booking confirmed! PNR: %s\n", pnr);
            log_event(username, "Booking", "Confirmed", pnr, train_no, passengers, quota, "Confirmed");
            strcpy(tickets[ticket_count].pnr, pnr);
            strcpy(tickets[ticket_count].username, username);
            strcpy(tickets[ticket_count].train_no, train_no);
            tickets[ticket_count].passengers = passengers;
            strcpy(tickets[ticket_count].quota, quota);
            strcpy(tickets[ticket_count].status, "Confirmed");
            tickets[ticket_count].is_cancelled = 0;
        } else {
            printf("Error: Booking failed.\n");
            return;
        }
    }
    FILE* fp = fopen("tickets.txt", "a");
    if (fp) {
        fprintf(fp, "%s %s %s %d %s %s %d\n", tickets[ticket_count].pnr, tickets[ticket_count].username,
                tickets[ticket_count].train_no, tickets[ticket_count].passengers, tickets[ticket_count].quota,
                tickets[ticket_count].status, tickets[ticket_count].is_cancelled);
        fclose(fp);
    }
    ticket_count++;
}

void cancel_ticket(const char* pnr, const char* username) {
    for (int i = 0; i < ticket_count; i++) {
        if (strcmp(tickets[i].pnr, pnr) == 0 && strcmp(tickets[i].username, username) == 0) {
            if (tickets[i].is_cancelled) {
                printf("Error: Ticket already cancelled.\n");
                return;
            }
            if (strcmp(tickets[i].status, "Confirmed") == 0) {
                update_seats(tickets[i].train_no, tickets[i].passengers, 0);
                printf("Ticket cancelled. Refund processed (less cancellation charges).\n");
                log_event(username, "Cancellation", "Confirmed ticket cancelled", pnr, tickets[i].train_no, tickets[i].passengers, tickets[i].quota, tickets[i].status);
            } else {
                printf("Waitlisted ticket cancelled. Full refund processed.\n");
                log_event(username, "Cancellation", "Waitlisted ticket cancelled", pnr, tickets[i].train_no, tickets[i].passengers, tickets[i].quota, tickets[i].status);
            }
            tickets[i].is_cancelled = 1;
            FILE* fp = fopen("tickets.txt", "w");
            for (int j = 0; j < ticket_count; j++) {
                fprintf(fp, "%s %s %s %d %s %s %d\n", tickets[j].pnr, tickets[j].username,
                        tickets[j].train_no, tickets[j].passengers, tickets[j].quota,
                        tickets[j].status, tickets[j].is_cancelled);
            }
            fclose(fp);
            return;
        }
    }
    printf("Error: Invalid PNR or unauthorized user.\n");
}

void check_pnr_status(const char* pnr) {
    for (int i = 0; i < ticket_count; i++) {
        if (strcmp(tickets[i].pnr, pnr) == 0) {
            printf("PNR: %s, Train: %s, Passengers: %d, Quota: %s, Status: %s, Cancelled: %s\n",
                   tickets[i].pnr, tickets[i].train_no, tickets[i].passengers, tickets[i].quota,
                   tickets[i].status, tickets[i].is_cancelled ? "Yes" : "No");
            if (strcmp(tickets[i].status, "Waitlisted") == 0) {
                int seats = get_available_seats(tickets[i].train_no);
                printf("Waitlist Prediction: %s\n", seats >= tickets[i].passengers ? "High chance of confirmation" : "Low chance of confirmation");
            }
            return;
        }
    }
    printf("Error: PNR not found.\n");
}

void display_passengers(const char* pnr) {
    for (int i = 0; i < ticket_count; i++) {
        if (strcmp(tickets[i].pnr, pnr) == 0) {
            printf("PNR: %s, Train: %s, Number of Passengers: %d, Quota: %s, Status: %s\n",
                   tickets[i].pnr, tickets[i].train_no, tickets[i].passengers, tickets[i].quota, tickets[i].status);
            printf("Passenger Details: [Simulated - %d passengers booked]\n", tickets[i].passengers);
            return;
        }
    }
    printf("Error: PNR not found.\n");
}
