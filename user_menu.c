#include "hospital.h"
#include "auth.h"

// Admin menüsü
void adminMenu() {
    int choice, userId;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    UserRole role;
    
    while(1) {
        system("cls");
        printf("\n=== YÖNETİCİ MENÜSÜ ===\n");
        printf("1. Kullanıcı Ekle\n");
        printf("2. Kullanıcıları Listele\n");
        printf("3. Kullanıcı Deaktive Et\n");
        printf("4. Kullanıcı Aktive Et\n");
        printf("5. Ana Menüye Dön\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\nKullanıcı Adı: ");
                scanf(" %[^\n]s", username);
                printf("Şifre: ");
                scanf(" %[^\n]s", password);
                printf("Rol (0:Admin, 1:Doktor, 2:Hemşire, 3:Resepsiyon): ");
                scanf("%d", (int*)&role);
                registerUser(username, password, role);
                break;
                
            case 2:
                listUsers();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
                
            case 3:
                printf("\nDeaktive edilecek kullanıcı ID: ");
                scanf("%d", &userId);
                deactivateUser(userId);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
                
            case 4:
                printf("\nAktive edilecek kullanıcı ID: ");
                scanf("%d", &userId);
                activateUser(userId);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
                
            case 5:
                return;
                
            default:
                printf("\nGeçersiz seçim!\n");
                getchar();
                getchar();
        }
    }
}

// Kullanıcı profil menüsü
void profileMenu() {
    int choice;
    char oldPassword[MAX_PASSWORD];
    char newPassword[MAX_PASSWORD];
    
    while(1) {
        system("cls");
        printf("\n=== PROFİL MENÜSÜ ===\n");
        printf("1. Şifre Değiştir\n");
        printf("2. Çıkış Yap\n");
        printf("3. Ana Menüye Dön\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\nEski Şifre: ");
                scanf(" %[^\n]s", oldPassword);
                printf("Yeni Şifre: ");
                scanf(" %[^\n]s", newPassword);
                changePassword(currentUserId, oldPassword, newPassword);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
                
            case 2:
                logoutUser();
                return;
                
            case 3:
                return;
                
            default:
                printf("\nGeçersiz seçim!\n");
                getchar();
                getchar();
        }
    }
}

// Giriş menüsü
int loginMenu() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    system("cls");
    printf("\n=== GİRİŞ EKRANI ===\n");
    printf("Kullanıcı Adı: ");
    scanf(" %[^\n]s", username);
    printf("Şifre: ");
    scanf(" %[^\n]s", password);
    
    return loginUser(username, password);
}