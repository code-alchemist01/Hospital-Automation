#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Kullanıcı rolleri
typedef enum {
    ROLE_ADMIN,
    ROLE_DOCTOR,
    ROLE_NURSE,
    ROLE_RECEPTIONIST
} UserRole;

// Kullanıcı yapısı
typedef struct {
    int id;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    UserRole role;
    int isActive;
} User;

// Fonksiyon prototipleri
int loginUser(char *username, char *password);
void logoutUser();
int registerUser(char *username, char *password, UserRole role);
int changePassword(int userId, char *oldPassword, char *newPassword);
int hasPermission(int userId, UserRole requiredRole);
void listUsers();
void deactivateUser(int userId);
void activateUser(int userId);

// Global değişkenler
extern User users[MAX_USERS];
extern int userCount;
extern int currentUserId;

#endif // AUTH_H