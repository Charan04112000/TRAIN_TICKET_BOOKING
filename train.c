#include <stdio.h>
#include <string.h>
#include "train.h"

Train trains[MAX_TRAINS];
int train_count = 0;

void init_trains() {
    FILE* fp = fopen("trains.txt", "r");
    if (fp) {
        while (fscanf(fp, "%s %s %d %d", trains[train_count].train_no, trains[train_count].name, 
                      &trains[train_count].total_seats, &trains[train_count].available_seats) == 4) {
            train_count++;
        }
        fclose(fp);
    } else {
        // Initialize sample trains
        strcpy(trains[0].train_no, "12345");
        strcpy(trains[0].name, "Express");
        trains[0].total_seats = 100;
        trains[0].available_seats = 100;
        train_count = 1;

        FILE* fp = fopen("trains.txt", "w");
        for (int i = 0; i < train_count; i++) {
            fprintf(fp, "%s %s %d %d\n", trains[i].train_no, trains[i].name, 
                    trains[i].total_seats, trains[i].available_seats);
        }
        fclose(fp);
    }
}

void display_trains() {
    printf("\n=== Train Schedule ===\n");
    for (int i = 0; i < train_count; i++) {
        printf("Train No: %s, Name: %s, Available Seats: %d/%d\n", 
               trains[i].train_no, trains[i].name, trains[i].available_seats, trains[i].total_seats);
    }
}

int get_available_seats(const char* train_no) {
    for (int i = 0; i < train_count; i++) {
        if (strcmp(trains[i].train_no, train_no) == 0) {
            return trains[i].available_seats;
        }
    }
    return -1;
}

int update_seats(const char* train_no, int seats, int is_booking) {
    for (int i = 0; i < train_count; i++) {
        if (strcmp(trains[i].train_no, train_no) == 0) {
            if (is_booking && trains[i].available_seats >= seats) {
                trains[i].available_seats -= seats;
            } else if (!is_booking) {
                trains[i].available_seats += seats;
            } else {
                return 0; // Not enough seats
            }
            FILE* fp = fopen("trains.txt", "w");
            for (int j = 0; j < train_count; j++) {
                fprintf(fp, "%s %s %d %d\n", trains[j].train_no, trains[j].name, 
                        trains[j].total_seats, trains[j].available_seats);
            }
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
