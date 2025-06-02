#ifndef TICKET_H
#define TICKET_H

#define MAX_TICKETS 1000

typedef struct {
    char pnr[10];
    char username[50];
    char train_no[10];
    int passengers;
    char quota[10];
    char status[20];
    int is_cancelled;
} Ticket;

void init_tickets();
void book_ticket(const char* username, const char* train_no, int passengers, const char* quota);
void cancel_ticket(const char* pnr, const char* username);
void check_pnr_status(const char* pnr);
void display_passengers(const char* pnr);

#endif
