#include "hospital.h"

// Doktor işlemleri için fonksiyonlar
void addDoctor() {
    if(doctorCount >= MAX_DOCTORS) {
        printf("\nMaksimum doktor sayısına ulaşıldı!\n");
        getchar();
        return;
    }
    
    Doctor newDoctor;
    newDoctor.id = doctorCount + 1;
    
    printf("\nDoktor Adı: ");
    scanf(" %[^\n]s", newDoctor.name);
    
    printf("Doktor Soyadı: ");
    scanf(" %[^\n]s", newDoctor.surname);
    
    printf("Uzmanlık Alanı: ");
    scanf(" %[^\n]s", newDoctor.specialization);
    
    printf("Telefon: ");
    scanf(" %[^\n]s", newDoctor.phone);
    
    doctors[doctorCount++] = newDoctor;
    printf("\nDoktor kaydı başarıyla oluşturuldu.\n");
    getchar();
    getchar();
}

void listDoctors() {
    if(doctorCount == 0) {
        printf("\nKayıtlı doktor bulunmamaktadır.\n");
        getchar();
        getchar();
        return;
    }
    
    printf("\n=== DOKTOR LİSTESİ ===\n");
    printf("ID\tAd\tSoyad\tUzmanlık\tTelefon\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < doctorCount; i++) {
        printf("%d\t%s\t%s\t%s\t%s\n",
               doctors[i].id,
               doctors[i].name,
               doctors[i].surname,
               doctors[i].specialization,
               doctors[i].phone);
    }
    
    printf("\nDevam etmek için bir tuşa basın...");
    getchar();
    getchar();
}

void doctorMenu() {
    int choice, doctorId, patientId;
    char searchTerm[50];
    
    while(1) {
        system("cls");
        printf("\n=== DOKTOR İŞLEMLERİ ===\n");
        printf("1. Yeni Doktor Kaydı\n");
        printf("2. Doktorları Listele\n");
        printf("3. Doktor Ara\n");
        printf("4. Doktor Bilgilerini Güncelle\n");
        printf("5. Doktor Sil\n");
        printf("6. Doktor Randevularını Görüntüle\n");
        printf("7. Çalışma Takvimi Ekle\n");
        printf("8. Çalışma Takvimini Görüntüle\n");
        printf("9. Online Konsültasyon Ekle\n");
        printf("10. Konsültasyonları Görüntüle\n");
        printf("11. Performans Kaydı Ekle\n");
        printf("12. Performans Raporu Oluştur\n");
        printf("13. Ana Menüye Dön\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addDoctor();
                break;
            case 2:
                listDoctors();
                break;
            case 3:
                printf("\nArama terimi girin: ");
                scanf(" %[^\n]s", searchTerm);
                searchDoctor(searchTerm);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 4:
                updateDoctor();
                break;
            case 5:
                deleteDoctor();
                break;
            case 6:
                printf("\nDoktor ID: ");
                scanf("%d", &doctorId);
                listDoctorAppointments(doctorId);
                break;
            case 7:
                printf("\nDoktor ID: ");
                scanf("%d", &doctorId);
                addSchedule(doctorId);
                break;
            case 8:
                printf("\nDoktor ID: ");
                scanf("%d", &doctorId);
                viewSchedule(doctorId);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 9:
                printf("\nDoktor ID: ");
                scanf("%d", &doctorId);
                printf("Hasta ID: ");
                scanf("%d", &patientId);
                addConsultation(doctorId, patientId);
                break;
            case 10:
                printf("\nDoktor ID: ");
                scanf("%d", &doctorId);
                viewConsultations(doctorId);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 11:
                printf("\nDoktor ID: ");
                scanf("%d", &doctorId);
                addPerformanceRecord(doctorId);
                break;
            case 12:
                printf("\nDoktor ID: ");
                scanf("%d", &doctorId);
                generatePerformanceReport(doctorId);
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