#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "users.dat"
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

struct User {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
};

void registerUser();
void loginUser();
void viewUsers();

int main() {
    int choice;
    while (1) {
        printf("\nUser Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. View Users (Admin)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                viewUsers();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void registerUser() {
    struct User newUser;
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter username: ");
    fgets(newUser.username, MAX_USERNAME, stdin);
    strtok(newUser.username, "\n"); // Remove newline

    printf("Enter password: ");
    fgets(newUser.password, MAX_PASSWORD, stdin);
    strtok(newUser.password, "\n");

    fwrite(&newUser, sizeof(struct User), 1, file);
    fclose(file);

    printf("User registered successfully!\n");
}

void loginUser() {
    struct User user;
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    int found = 0;

    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("No users registered yet.\n");
        return;
    }

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    strtok(username, "\n");

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    strtok(password, "\n");

    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found)
        printf("Login successful!\n");
    else
        printf("Invalid username or password.\n");
}

void viewUsers() {
    struct User user;
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("No users registered yet.\n");
        return;
    }

    printf("\nRegistered Users:\n");
    while (fread(&user, sizeof(struct User), 1, file)) {
        printf("Username: %s\n", user.username);
    }
    fclose(file);
}
