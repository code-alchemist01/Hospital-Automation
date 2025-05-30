#include "hospital.h"

// Randevu işlemleri için yardımcı fonksiyonlar
int findPatientById(int id) {
    for(int i = 0; i < patientCount; i++) {
        if(patients[i].id == id) return i;
    }
    return -1;
}

int findDoctorById(int id) {
    for(int i = 0; i < doctorCount; i++) {
        if(doctors[i].id == id) return i;
    }
    return -1;
}

// Randevu oluşturma fonksiyonu
void makeAppointment() {
    if(appointmentCount >= MAX_APPOINTMENTS) {
        printf("\nMaksimum randevu sayısına ulaşıldı!\n");
        getchar();
        return;
    }
    
    Appointment newAppointment;
    newAppointment.id = appointmentCount + 1;
    
    // Hasta seçimi
    listPatients();
    printf("\nHasta ID: ");
    scanf("%d", &newAppointment.patientId);
    
    if(findPatientById(newAppointment.patientId) == -1) {
        printf("\nGeçersiz hasta ID!\n");
        getchar();
        getchar();
        return;
    }
    
    // Doktor seçimi
    listDoctors();
    printf("\nDoktor ID: ");
    scanf("%d", &newAppointment.doctorId);
    
    if(findDoctorById(newAppointment.doctorId) == -1) {
        printf("\nGeçersiz doktor ID!\n");
        getchar();
        getchar();
        return;
    }
    
    printf("Randevu Tarihi (GG.AA.YYYY): ");
    scanf(" %[^\n]s", newAppointment.date);
    
    printf("Randevu Saati (SS:DD): ");
    scanf(" %[^\n]s", newAppointment.time);
    
    strcpy(newAppointment.status, "Aktif");
    
    appointments[appointmentCount++] = newAppointment;
    printf("\nRandevu başarıyla oluşturuldu.\n");
    getchar();
    getchar();
}

// Randevuları listeleme fonksiyonu
void listAppointments() {
    if(appointmentCount == 0) {
        printf("\nKayıtlı randevu bulunmamaktadır.\n");
        getchar();
        getchar();
        return;
    }
    
    printf("\n=== RANDEVU LİSTESİ ===\n");
    printf("ID\tHasta\tDoktor\tTarih\tSaat\tDurum\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < appointmentCount; i++) {
        int patientIndex = findPatientById(appointments[i].patientId);
        int doctorIndex = findDoctorById(appointments[i].doctorId);
        
        if(patientIndex != -1 && doctorIndex != -1) {
            printf("%d\t%s %s\t%s %s\t%s\t%s\t%s\n",
                   appointments[i].id,
                   patients[patientIndex].name,
                   patients[patientIndex].surname,
                   doctors[doctorIndex].name,
                   doctors[doctorIndex].surname,
                   appointments[i].date,
                   appointments[i].time,
                   appointments[i].status);
        }
    }
    
    printf("\nDevam etmek için bir tuşa basın...");
    getchar();
    getchar();
}

// Randevu iptal etme fonksiyonu
void cancelAppointment() {
    int appointmentId;
    
    listAppointments();
    printf("\nİptal edilecek randevu ID: ");
    scanf("%d", &appointmentId);
    
    for(int i = 0; i < appointmentCount; i++) {
        if(appointments[i].id == appointmentId) {
            strcpy(appointments[i].status, "İptal");
            printf("\nRandevu başarıyla iptal edildi.\n");
            getchar();
            getchar();
            return;
        }
    }
    
    printf("\nGeçersiz randevu ID!\n");
    getchar();
    getchar();
}

// Randevu menüsü
void appointmentMenu() {
    int choice;
    
    while(1) {
        system("cls");
        printf("\n=== RANDEVU İŞLEMLERİ ===\n");
        printf("1. Yeni Randevu\n");
        printf("2. Randevuları Listele\n");
        printf("3. Randevu Ara\n");
        printf("4. Randevu Güncelle\n");
        printf("5. Randevu İptal\n");
        printf("6. Randevu İstatistikleri\n");
        printf("7. Ana Menüye Dön\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                makeAppointment();
                break;
            case 2:
                listAppointments();
                break;
            case 3:
                searchAppointment();
                break;
            case 4:
                updateAppointment();
                break;
            case 5:
                cancelAppointment();
                break;
            case 6:
                appointmentStatistics();
                break;
            case 7:
                return;
            default:
                printf("\nGeçersiz seçim! Tekrar deneyin.\n");
                getchar();
        }
    }
}