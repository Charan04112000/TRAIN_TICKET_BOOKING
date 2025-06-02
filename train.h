#ifndef TRAIN_H
#define TRAIN_H

#define MAX_TRAINS 50

typedef struct {
    char train_no[10];
    char name[50];
    int total_seats;
    int available_seats;
} Train;

void init_trains();
void display_trains();
int get_available_seats(const char* train_no);
int update_seats(const char* train_no, int seats, int is_booking);

#endif
