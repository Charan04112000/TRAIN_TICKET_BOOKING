#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logger.h"

void init_logger() {
    FILE* fp = fopen("logs.txt", "a");
    if (fp) {
        time_t now = time(NULL);
        fprintf(fp, "=== Log Started: %s ===\n", ctime(&now));
        fclose(fp);
    }
}

void log_event(const char* username, const char* event_type, const char* details, const char* pnr, const char* train_no, int passengers, const char* quota, const char* status) {
    // Write to general logs.txt
    FILE* fp = fopen("logs.txt", "a");
    if (fp) {
        time_t now = time(NULL);
        fprintf(fp, "[%s] User: %s, Event: %s, Details: %s, PNR: %s\n", ctime(&now), username, event_type, details, pnr);
        fclose(fp);
    }
    // Write to PNR-specific log file
    char filename[20];
    snprintf(filename, sizeof(filename), "PNR%s.txt", pnr);
    fp = fopen(filename, "w");
    if (fp) {
        time_t now = time(NULL);
        fprintf(fp, "Booking Log for PNR: %s\n", pnr);
        fprintf(fp, "Timestamp: %s", ctime(&now));
        fprintf(fp, "User: %s\n", username);
        fprintf(fp, "Event: %s\n", event_type);
        fprintf(fp, "Train No: %s\n", train_no);
        fprintf(fp, "Passengers: %d\n", passengers);
        fprintf(fp, "Quota: %s\n", quota);
        fprintf(fp, "Status: %s\n", status);
        fprintf(fp, "Details: %s\n", details);
        fclose(fp);
    }
}
