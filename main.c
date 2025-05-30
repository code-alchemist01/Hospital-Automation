#include "hospital.h"



int main() {
    system("chcp 65001"); // Türkçe karakter desteği
    
    // Admin hesabını oluştur
    if(userCount == 0) {
        registerUser("admin", "admin123", ROLE_ADMIN);
        printf("\nAdmin hesabı oluşturuldu.\n");
        printf("Kullanıcı adı: admin\n");
        printf("Şifre: admin123\n");
        printf("\nDevam etmek için bir tuşa basın...");
        getchar();
        getchar();
    }
    
    while(1) {
        if(currentUserId == -1) {
            if(!loginMenu()) {
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                continue;
            }
        }
        mainMenu();
    }
    
    return 0;
}

void mainMenu() {
    int choice;
    
    while(1) {
        system("cls");
        printf("\n=== HASTANE YÖNETİM SİSTEMİ ===\n");
        printf("Giriş yapan kullanıcı: %s\n\n", users[currentUserId-1].username);
        
        if(hasPermission(currentUserId, ROLE_ADMIN)) {
            printf("1. Hasta İşlemleri\n");
            printf("2. Doktor İşlemleri\n");
            printf("3. Randevu İşlemleri\n");
            printf("4. Finans İşlemleri\n");
            printf("5. Eczane ve Stok Yönetimi\n");
            printf("6. Kullanıcı Yönetimi\n");
            printf("7. Profil İşlemleri\n");
            printf("8. Çıkış\n");
        }
        else if(hasPermission(currentUserId, ROLE_DOCTOR)) {
            printf("1. Hasta İşlemleri\n");
            printf("2. Randevu İşlemleri\n");
            printf("3. Profil İşlemleri\n");
            printf("4. Çıkış\n");
        }
        else if(hasPermission(currentUserId, ROLE_NURSE)) {
            printf("1. Hasta İşlemleri\n");
            printf("2. Randevu İşlemleri\n");
            printf("3. Eczane ve Stok Yönetimi\n");
            printf("4. Profil İşlemleri\n");
            printf("5. Çıkış\n");
        }
        else {
            printf("1. Hasta İşlemleri\n");
            printf("2. Randevu İşlemleri\n");
            printf("3. Finans İşlemleri\n");
            printf("4. Profil İşlemleri\n");
            printf("5. Çıkış\n");
        }
        
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        
        if(hasPermission(currentUserId, ROLE_ADMIN)) {
            switch(choice) {
                case 1:
                    patientMenu();
                    break;
                case 2:
                    doctorMenu();
                    break;
                case 3:
                    appointmentMenu();
                    break;
                case 4:
                    adminMenu();
                    break;
                case 5:
                    profileMenu();
                    break;
                case 6:
                    logoutUser();
                    return;
                default:
                    printf("\nGeçersiz seçim! Tekrar deneyin.\n");
                    getchar();
            }
        } else {
            switch(choice) {
                case 1:
                    patientMenu();
                    break;
                case 2:
                    appointmentMenu();
                    break;
                case 3:
                    profileMenu();
                    break;
                case 4:
                    logoutUser();
                    return;
                default:
                    printf("\nGeçersiz seçim! Tekrar deneyin.\n");
                    getchar();
            }
        }
    }
}

void patientMenu() {
    int choice, patientId;
    char searchTerm[50];
    
    while(1) {
        system("cls");
        printf("\n=== HASTA İŞLEMLERİ ===\n");
        printf("1. Yeni Hasta Kaydı\n");
        printf("2. Hastaları Listele\n");
        printf("3. Hasta Ara\n");
        printf("4. Hasta Bilgilerini Güncelle\n");
        printf("5. Hasta Sil\n");
        printf("6. Tıbbi Kayıt Ekle\n");
        printf("7. Tıbbi Geçmişi Görüntüle\n");
        printf("8. Laboratuvar Sonucu Ekle\n");
        printf("9. Laboratuvar Sonuçlarını Görüntüle\n");
        printf("10. Reçete Yaz\n");
        printf("11. Reçeteleri Görüntüle\n");
        printf("12. Hasta Raporu Oluştur\n");
        printf("13. Ana Menüye Dön\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addPatient();
                break;
            case 2:
                listPatients();
                break;
            case 3:
                printf("\nArama terimi girin: ");
                scanf(" %[^\n]s", searchTerm);
                searchPatient(searchTerm);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 4:
                updatePatient();
                break;
            case 5:
                deletePatient();
                break;
            case 6:
                printf("\nHasta ID: ");
                scanf("%d", &patientId);
                addMedicalRecord(patientId);
                break;
            case 7:
                printf("\nHasta ID: ");
                scanf("%d", &patientId);
                viewMedicalHistory(patientId);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 8:
                printf("\nHasta ID: ");
                scanf("%d", &patientId);
                addLabResult(patientId);
                break;
            case 9:
                printf("\nHasta ID: ");
                scanf("%d", &patientId);
                viewLabResults(patientId);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 10:
                printf("\nHasta ID: ");
                scanf("%d", &patientId);
                addPrescription(patientId);
                break;
            case 11:
                printf("\nHasta ID: ");
                scanf("%d", &patientId);
                viewPrescriptions(patientId);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 12:
                printf("\nHasta ID: ");
                scanf("%d", &patientId);
                generatePatientReport(patientId);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 13:
                return;
            default:
                printf("\nGeçersiz seçim! Tekrar deneyin.\n");
                getchar();
        }
    }
}

void addPatient() {
    if(patientCount >= MAX_PATIENTS) {
        printf("\nMaksimum hasta sayısına ulaşıldı!\n");
        getchar();
        return;
    }
    
    Patient newPatient;
    newPatient.id = patientCount + 1;
    
    printf("\nHasta Adı: ");
    scanf(" %[^\n]s", newPatient.name);
    
    printf("Hasta Soyadı: ");
    scanf(" %[^\n]s", newPatient.surname);
    
    printf("Telefon: ");
    scanf(" %[^\n]s", newPatient.phone);
    
    printf("Adres: ");
    scanf(" %[^\n]s", newPatient.address);
    
    printf("Yaş: ");
    scanf("%d", &newPatient.age);
    
    patients[patientCount++] = newPatient;
    printf("\nHasta kaydı başarıyla oluşturuldu.\n");
    getchar();
    getchar();
}

void listPatients() {
    if(patientCount == 0) {
        printf("\nKayıtlı hasta bulunmamaktadır.\n");
        getchar();
        getchar();
        return;
    }
    
    printf("\n=== HASTA LİSTESİ ===\n");
    printf("ID\tAd\tSoyad\tTelefon\tYaş\tAdres\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < patientCount; i++) {
        printf("%d\t%s\t%s\t%s\t%d\t%s\n",
               patients[i].id,
               patients[i].name,
               patients[i].surname,
               patients[i].phone,
               patients[i].age,
               patients[i].address);
    }
    
    printf("\nDevam etmek için bir tuşa basın...");
    getchar();
    getchar();
}

// Diğer fonksiyonlar benzer şekilde implement edilecek