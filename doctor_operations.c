#include "hospital.h"

// Doktor arama fonksiyonu
int searchDoctor(char *searchTerm) {
    printf("\n=== ARAMA SONUÇLARI ===\n");
    printf("ID\tAd\tSoyad\tUzmanlık\tTelefon\n");
    printf("------------------------------------------------\n");
    
    int found = 0;
    for(int i = 0; i < doctorCount; i++) {
        if(strstr(doctors[i].name, searchTerm) != NULL ||
           strstr(doctors[i].surname, searchTerm) != NULL ||
           strstr(doctors[i].specialization, searchTerm) != NULL) {
            printf("%d\t%s\t%s\t%s\t%s\n",
                   doctors[i].id,
                   doctors[i].name,
                   doctors[i].surname,
                   doctors[i].specialization,
                   doctors[i].phone);
            found++;
        }
    }
    
    if(!found) {
        printf("\nAranan kriterlere uygun doktor bulunamadı.\n");
    }
    
    return found;
}

// Doktor güncelleme fonksiyonu
void updateDoctor() {
    int id;
    printf("\nGüncellenecek doktor ID: ");
    scanf("%d", &id);
    
    int index = -1;
    for(int i = 0; i < doctorCount; i++) {
        if(doctors[i].id == id) {
            index = i;
            break;
        }
    }
    
    if(index == -1) {
        printf("\nBelirtilen ID'ye sahip doktor bulunamadı!\n");
        getchar();
        getchar();
        return;
    }
    
    printf("\nMevcut Bilgiler:\n");
    printf("Ad: %s\n", doctors[index].name);
    printf("Soyad: %s\n", doctors[index].surname);
    printf("Uzmanlık: %s\n", doctors[index].specialization);
    printf("Telefon: %s\n", doctors[index].phone);
    
    printf("\nYeni Bilgileri Girin:\n");
    printf("Yeni Ad (değiştirmemek için boş bırakın): ");
    char input[50];
    getchar();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strlen(input) > 0) strcpy(doctors[index].name, input);
    
    printf("Yeni Soyad: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strlen(input) > 0) strcpy(doctors[index].surname, input);
    
    printf("Yeni Uzmanlık Alanı: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strlen(input) > 0) strcpy(doctors[index].specialization, input);
    
    printf("Yeni Telefon: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strlen(input) > 0) strcpy(doctors[index].phone, input);
    
    printf("\nDoktor bilgileri başarıyla güncellendi.\n");
    getchar();
}

// Doktor silme fonksiyonu
void deleteDoctor() {
    int id;
    printf("\nSilinecek doktor ID: ");
    scanf("%d", &id);
    
    int index = -1;
    for(int i = 0; i < doctorCount; i++) {
        if(doctors[i].id == id) {
            index = i;
            break;
        }
    }
    
    if(index == -1) {
        printf("\nBelirtilen ID'ye sahip doktor bulunamadı!\n");
        getchar();
        getchar();
        return;
    }
    
    // Aktif randevuları kontrol et
    int hasActiveAppointments = 0;
    for(int i = 0; i < appointmentCount; i++) {
        if(appointments[i].doctorId == id && strcmp(appointments[i].status, "İptal") != 0) {
            hasActiveAppointments = 1;
            break;
        }
    }
    
    if(hasActiveAppointments) {
        printf("\nBu doktorun aktif randevuları bulunmaktadır. Önce randevuları iptal etmelisiniz.\n");
        getchar();
        getchar();
        return;
    }
    
    // Silme işlemi için onay al
    printf("\n%s %s isimli doktoru silmek istediğinize emin misiniz? (E/H): ",
           doctors[index].name, doctors[index].surname);
    char confirm;
    getchar();
    scanf("%c", &confirm);
    
    if(confirm == 'E' || confirm == 'e') {
        // Sonraki doktorları bir öne kaydır
        for(int i = index; i < doctorCount - 1; i++) {
            doctors[i] = doctors[i + 1];
        }
        doctorCount--;
        printf("\nDoktor başarıyla silindi.\n");
    } else {
        printf("\nSilme işlemi iptal edildi.\n");
    }
    
    getchar();
    getchar();
}

// Doktorun randevularını listele
void listDoctorAppointments(int doctorId) {
    int found = 0;
    printf("\n=== DOKTOR RANDEVULARI ===\n");
    printf("Randevu ID\tHasta\tTarih\tSaat\tDurum\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < appointmentCount; i++) {
        if(appointments[i].doctorId == doctorId) {
            int patientIndex = findPatientById(appointments[i].patientId);
            if(patientIndex != -1) {
                printf("%d\t%s %s\t%s\t%s\t%s\n",
                       appointments[i].id,
                       patients[patientIndex].name,
                       patients[patientIndex].surname,
                       appointments[i].date,
                       appointments[i].time,
                       appointments[i].status);
                found++;
            }
        }
    }
    
    if(!found) {
        printf("\nDoktora ait randevu bulunamadı.\n");
    }
    
    printf("\nDevam etmek için bir tuşa basın...");
    getchar();
    getchar();
}