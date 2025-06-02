#include <stdio.h>
#include <string.h>
#include "user.h"

User users[MAX_USERS];
int user_count = 0;

void init_users() {
    FILE* fp = fopen("users.txt", "r");
    if (fp) {
        while (fscanf(fp, "%s %s", users[user_count].username, users[user_count].password) == 2) {
            user_count++;
        }
        fclose(fp);
    }
}

int register_user(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 0; // Username exists
        }
    }
    if (user_count >= MAX_USERS) {
        return 0; // Max users reached
    }
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    user_count++;

    FILE* fp = fopen("users.txt", "a");
    if (!fp) return 0;
    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);
    return 1;
}

int login_user(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}
