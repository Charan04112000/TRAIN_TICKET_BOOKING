#ifndef USER_H
#define USER_H

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

void init_users();
int register_user(const char* username, const char* password);
int login_user(const char* username, const char* password);

#endif
