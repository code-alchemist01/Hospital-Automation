#include "auth.h"
#include <time.h>

// Global değişkenlerin tanımlanması
User users[MAX_USERS];
int userCount = 0;
int currentUserId = -1;

// Basit şifreleme fonksiyonu (gerçek uygulamada daha güvenli bir yöntem kullanılmalı)
void encryptPassword(char *password) {
    for(int i = 0; password[i] != '\0'; i++) {
        password[i] = password[i] + 1; // Basit bir Caesar cipher
    }
}

// Şifre çözme fonksiyonu
void decryptPassword(char *password) {
    for(int i = 0; password[i] != '\0'; i++) {
        password[i] = password[i] - 1;
    }
}

// Kullanıcı girişi
int loginUser(char *username, char *password) {
    char encryptedPass[MAX_PASSWORD];
    strcpy(encryptedPass, password);
    encryptPassword(encryptedPass);
    
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0 && 
           strcmp(users[i].password, encryptedPass) == 0 && 
           users[i].isActive) {
            currentUserId = users[i].id;
            printf("\nGiriş başarılı! Hoş geldiniz %s\n", username);
            return 1;
        }
    }
    
    printf("\nHatalı kullanıcı adı veya şifre!\n");
    return 0;
}

// Kullanıcı çıkışı
void logoutUser() {
    if(currentUserId != -1) {
        printf("\nÇıkış yapıldı.\n");
        currentUserId = -1;
    }
}

// Yeni kullanıcı kaydı
int registerUser(char *username, char *password, UserRole role) {
    if(userCount >= MAX_USERS) {
        printf("\nMaksimum kullanıcı sayısına ulaşıldı!\n");
        return 0;
    }
    
    // Kullanıcı adı kontrolü
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0) {
            printf("\nBu kullanıcı adı zaten kullanılıyor!\n");
            return 0;
        }
    }
    
    User newUser;
    newUser.id = userCount + 1;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    encryptPassword(newUser.password);
    newUser.role = role;
    newUser.isActive = 1;
    
    users[userCount++] = newUser;
    printf("\nKullanıcı başarıyla kaydedildi.\n");
    return 1;
}

// Şifre değiştirme
int changePassword(int userId, char *oldPassword, char *newPassword) {
    char encryptedOldPass[MAX_PASSWORD];
    strcpy(encryptedOldPass, oldPassword);
    encryptPassword(encryptedOldPass);
    
    for(int i = 0; i < userCount; i++) {
        if(users[i].id == userId && strcmp(users[i].password, encryptedOldPass) == 0) {
            strcpy(users[i].password, newPassword);
            encryptPassword(users[i].password);
            printf("\nŞifre başarıyla değiştirildi.\n");
            return 1;
        }
    }
    
    printf("\nGeçersiz eski şifre!\n");
    return 0;
}

// Yetki kontrolü
int hasPermission(int userId, UserRole requiredRole) {
    if(userId == -1) return 0;
    
    for(int i = 0; i < userCount; i++) {
        if(users[i].id == userId) {
            return users[i].role <= requiredRole && users[i].isActive;
        }
    }
    
    return 0;
}

// Kullanıcıları listeleme
void listUsers() {
    printf("\n=== KULLANICILAR ===\n");
    printf("ID\tKullanıcı Adı\tRol\tDurum\n");
    printf("----------------------------------------\n");
    
    for(int i = 0; i < userCount; i++) {
        const char *roleStr;
        switch(users[i].role) {
            case ROLE_ADMIN: roleStr = "Admin"; break;
            case ROLE_DOCTOR: roleStr = "Doktor"; break;
            case ROLE_NURSE: roleStr = "Hemşire"; break;
            case ROLE_RECEPTIONIST: roleStr = "Resepsiyon"; break;
            default: roleStr = "Bilinmiyor";
        }
        
        printf("%d\t%s\t%s\t%s\n",
               users[i].id,
               users[i].username,
               roleStr,
               users[i].isActive ? "Aktif" : "Pasif");
    }
}

// Kullanıcı deaktive etme
void deactivateUser(int userId) {
    for(int i = 0; i < userCount; i++) {
        if(users[i].id == userId) {
            users[i].isActive = 0;
            printf("\nKullanıcı deaktive edildi.\n");
            return;
        }
    }
    printf("\nKullanıcı bulunamadı!\n");
}

// Kullanıcı aktive etme
void activateUser(int userId) {
    for(int i = 0; i < userCount; i++) {
        if(users[i].id == userId) {
            users[i].isActive = 1;
            printf("\nKullanıcı aktive edildi.\n");
            return;
        }
    }
    printf("\nKullanıcı bulunamadı!\n");
}