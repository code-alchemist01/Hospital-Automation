#include "hospital.h"

// Randevu arama fonksiyonu
void searchAppointment() {
    int choice;
    printf("\nArama Kriteri Seçin:\n");
    printf("1. Tarihe Göre\n");
    printf("2. Hasta Adına Göre\n");
    printf("3. Doktor Adına Göre\n");
    printf("Seçiminiz: ");
    scanf("%d", &choice);
    
    char searchTerm[50];
    printf("\nArama terimi girin: ");
    scanf(" %[^\n]s", searchTerm);
    
    printf("\n=== ARAMA SONUÇLARI ===\n");
    printf("ID\tHasta\tDoktor\tTarih\tSaat\tDurum\n");
    printf("------------------------------------------------\n");
    
    int found = 0;
    for(int i = 0; i < appointmentCount; i++) {
        int patientIndex = findPatientById(appointments[i].patientId);
        int doctorIndex = findDoctorById(appointments[i].doctorId);
        
        if(patientIndex != -1 && doctorIndex != -1) {
            int match = 0;
            switch(choice) {
                case 1: // Tarih araması
                    match = (strstr(appointments[i].date, searchTerm) != NULL);
                    break;
                case 2: // Hasta adı araması
                    match = (strstr(patients[patientIndex].name, searchTerm) != NULL ||
                            strstr(patients[patientIndex].surname, searchTerm) != NULL);
                    break;
                case 3: // Doktor adı araması
                    match = (strstr(doctors[doctorIndex].name, searchTerm) != NULL ||
                            strstr(doctors[doctorIndex].surname, searchTerm) != NULL);
                    break;
            }
            
            if(match) {
                printf("%d\t%s %s\t%s %s\t%s\t%s\t%s\n",
                       appointments[i].id,
                       patients[patientIndex].name,
                       patients[patientIndex].surname,
                       doctors[doctorIndex].name,
                       doctors[doctorIndex].surname,
                       appointments[i].date,
                       appointments[i].time,
                       appointments[i].status);
                found++;
            }
        }
    }
    
    if(!found) {
        printf("\nAranan kriterlere uygun randevu bulunamadı.\n");
    }
    
    printf("\nDevam etmek için bir tuşa basın...");
    getchar();
    getchar();
}

// Randevu güncelleme fonksiyonu
void updateAppointment() {
    int id;
    printf("\nGüncellenecek randevu ID: ");
    scanf("%d", &id);
    
    int index = -1;
    for(int i = 0; i < appointmentCount; i++) {
        if(appointments[i].id == id) {
            index = i;
            break;
        }
    }
    
    if(index == -1) {
        printf("\nBelirtilen ID'ye sahip randevu bulunamadı!\n");
        getchar();
        getchar();
        return;
    }
    
    printf("\nMevcut Bilgiler:\n");
    int patientIndex = findPatientById(appointments[index].patientId);
    int doctorIndex = findDoctorById(appointments[index].doctorId);
    
    if(patientIndex != -1 && doctorIndex != -1) {
        printf("Hasta: %s %s\n", patients[patientIndex].name, patients[patientIndex].surname);
        printf("Doktor: %s %s\n", doctors[doctorIndex].name, doctors[doctorIndex].surname);
        printf("Tarih: %s\n", appointments[index].date);
        printf("Saat: %s\n", appointments[index].time);
        printf("Durum: %s\n", appointments[index].status);
        
        printf("\nYeni Bilgileri Girin:\n");
        printf("Yeni Tarih (GG.AA.YYYY) (değiştirmemek için boş bırakın): ");
        char input[50];
        getchar();
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if(strlen(input) > 0) strcpy(appointments[index].date, input);
        
        printf("Yeni Saat (SS:DD): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if(strlen(input) > 0) strcpy(appointments[index].time, input);
        
        printf("Yeni Durum (Aktif/İptal/Tamamlandı): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if(strlen(input) > 0) strcpy(appointments[index].status, input);
        
        printf("\nRandevu bilgileri başarıyla güncellendi.\n");
    }
    
    getchar();
}

// Randevu istatistikleri
void appointmentStatistics() {
    int totalActive = 0;
    int totalCancelled = 0;
    int totalCompleted = 0;
    
    for(int i = 0; i < appointmentCount; i++) {
        if(strcmp(appointments[i].status, "Aktif") == 0) totalActive++;
        else if(strcmp(appointments[i].status, "İptal") == 0) totalCancelled++;
        else if(strcmp(appointments[i].status, "Tamamlandı") == 0) totalCompleted++;
    }
    
    printf("\n=== RANDEVU İSTATİSTİKLERİ ===\n");
    printf("Toplam Randevu Sayısı: %d\n", appointmentCount);
    printf("Aktif Randevular: %d\n", totalActive);
    printf("İptal Edilen Randevular: %d\n", totalCancelled);
    printf("Tamamlanan Randevular: %d\n", totalCompleted);
    
    if(appointmentCount > 0) {
        printf("\nYüzdelik Dağılım:\n");
        printf("Aktif: %%%.2f\n", (float)totalActive/appointmentCount * 100);
        printf("İptal: %%%.2f\n", (float)totalCancelled/appointmentCount * 100);
        printf("Tamamlanan: %%%.2f\n", (float)totalCompleted/appointmentCount * 100);
    }
    
    printf("\nDevam etmek için bir tuşa basın...");
    getchar();
    getchar();
}