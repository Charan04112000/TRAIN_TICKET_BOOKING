#ifndef LOGGER_H
#define LOGGER_H

void init_logger();
void log_event(const char* username, const char* event_type, const char* details, const char* pnr, const char* train_no, int passengers, const char* quota, const char* status);

#endif
