#include "doctor_extended.h"

// Global değişkenlerin tanımlanması
Schedule schedules[MAX_SCHEDULES];
Shift shifts[MAX_SHIFTS];
Consultation consultations[MAX_CONSULTATIONS];
PerformanceRecord performanceRecords[MAX_PERFORMANCE_RECORDS];

int scheduleCount = 0;
int shiftCount = 0;
int consultationCount = 0;
int performanceRecordCount = 0;

// Çalışma takvimi işlemleri
void addSchedule(int doctorId) {
    if(scheduleCount >= MAX_SCHEDULES) {
        printf("\nMaksimum çalışma takvimi sayısına ulaşıldı!\n");
        return;
    }
    
    Schedule newSchedule;
    newSchedule.id = scheduleCount + 1;
    newSchedule.doctorId = doctorId;
    newSchedule.isAvailable = 1;
    
    printf("\nTarih (GG.AA.YYYY): ");
    scanf(" %[^\n]s", newSchedule.date);
    
    printf("Başlangıç Saati (SS:DD): ");
    scanf(" %[^\n]s", newSchedule.startTime);
    
    printf("Bitiş Saati (SS:DD): ");
    scanf(" %[^\n]s", newSchedule.endTime);
    
    if(!isTimeSlotAvailable(doctorId, newSchedule.date, newSchedule.startTime, newSchedule.endTime)) {
        printf("\nBu zaman diliminde çakışma var!\n");
        return;
    }
    
    printf("Notlar: ");
    scanf(" %[^\n]s", newSchedule.notes);
    
    schedules[scheduleCount++] = newSchedule;
    printf("\nÇalışma takvimi başarıyla eklendi.\n");
}

void viewSchedule(int doctorId) {
    int found = 0;
    printf("\n=== ÇALIŞMA TAKVİMİ ===\n");
    
    for(int i = 0; i < scheduleCount; i++) {
        if(schedules[i].doctorId == doctorId) {
            printf("\nID: %d\n", schedules[i].id);
            printf("Tarih: %s\n", schedules[i].date);
            printf("Saat: %s - %s\n", schedules[i].startTime, schedules[i].endTime);
            printf("Durum: %s\n", schedules[i].isAvailable ? "Müsait" : "Meşgul");
            printf("Notlar: %s\n", schedules[i].notes);
            printf("----------------------------------------\n");
            found++;
        }
    }
    
    if(!found) {
        printf("\nKayıtlı çalışma takvimi bulunamadı.\n");
    }
}

// Online konsültasyon işlemleri
void addConsultation(int doctorId, int patientId) {
    if(consultationCount >= MAX_CONSULTATIONS) {
        printf("\nMaksimum konsültasyon sayısına ulaşıldı!\n");
        return;
    }
    
    Consultation newConsultation;
    newConsultation.id = consultationCount + 1;
    newConsultation.doctorId = doctorId;
    newConsultation.patientId = patientId;
    
    printf("\nTarih (GG.AA.YYYY): ");
    scanf(" %[^\n]s", newConsultation.date);
    
    printf("Saat (SS:DD): ");
    scanf(" %[^\n]s", newConsultation.time);
    
    printf("Platform (Zoom/Teams): ");
    scanf(" %[^\n]s", newConsultation.platform);
    
    printf("Toplantı Linki: ");
    scanf(" %[^\n]s", newConsultation.meetingLink);
    
    printf("Notlar: ");
    scanf(" %[^\n]s", newConsultation.notes);
    
    strcpy(newConsultation.status, "Bekliyor");
    
    consultations[consultationCount++] = newConsultation;
    printf("\nOnline konsültasyon başarıyla oluşturuldu.\n");
}

void viewConsultations(int doctorId) {
    int found = 0;
    printf("\n=== ONLINE KONSÜLTASYONLAR ===\n");
    
    for(int i = 0; i < consultationCount; i++) {
        if(consultations[i].doctorId == doctorId) {
            int patientIndex = findPatientById(consultations[i].patientId);
            if(patientIndex != -1) {
                printf("\nID: %d\n", consultations[i].id);
                printf("Hasta: %s %s\n", 
                       patients[patientIndex].name,
                       patients[patientIndex].surname);
                printf("Tarih: %s\n", consultations[i].date);
                printf("Saat: %s\n", consultations[i].time);
                printf("Platform: %s\n", consultations[i].platform);
                printf("Link: %s\n", consultations[i].meetingLink);
                printf("Durum: %s\n", consultations[i].status);
                printf("Notlar: %s\n", consultations[i].notes);
                printf("----------------------------------------\n");
                found++;
            }
        }
    }
    
    if(!found) {
        printf("\nKayıtlı konsültasyon bulunamadı.\n");
    }
}

// Performans yönetimi işlemleri
void addPerformanceRecord(int doctorId) {
    if(performanceRecordCount >= MAX_PERFORMANCE_RECORDS) {
        printf("\nMaksimum performans kaydı sayısına ulaşıldı!\n");
        return;
    }
    
    PerformanceRecord newRecord;
    newRecord.id = performanceRecordCount + 1;
    newRecord.doctorId = doctorId;
    
    printf("\nDönem (AA/YYYY): ");
    scanf(" %[^\n]s", newRecord.period);
    
    printf("Hasta Sayısı: ");
    scanf("%d", &newRecord.patientCount);
    
    printf("Konsültasyon Sayısı: ");
    scanf("%d", &newRecord.consultationCount);
    
    printf("Ameliyat Sayısı: ");
    scanf("%d", &newRecord.surgeryCount);
    
    printf("Hasta Memnuniyet Oranı (0-100): ");
    scanf("%f", &newRecord.satisfactionRate);
    
    printf("Değerlendirme: ");
    scanf(" %[^\n]s", newRecord.evaluation);
    
    performanceRecords[performanceRecordCount++] = newRecord;
    printf("\nPerformans kaydı başarıyla eklendi.\n");
}

void generatePerformanceReport(int doctorId) {
    int doctorIndex = findDoctorById(doctorId);
    if(doctorIndex == -1) {
        printf("\nDoktor bulunamadı!\n");
        return;
    }
    
    char filename[100];
    sprintf(filename, "doktor_performans_%d.txt", doctorId);
    
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("\nDosya oluşturulamadı!\n");
        return;
    }
    
    fprintf(fp, "=== DOKTOR PERFORMANS RAPORU ===\n\n");
    fprintf(fp, "Doktor Bilgileri:\n");
    fprintf(fp, "Ad Soyad: %s %s\n", doctors[doctorIndex].name, doctors[doctorIndex].surname);
    fprintf(fp, "Uzmanlık: %s\n\n", doctors[doctorIndex].specialization);
    
    fprintf(fp, "Performans Kayıtları:\n");
    for(int i = 0; i < performanceRecordCount; i++) {
        if(performanceRecords[i].doctorId == doctorId) {
            fprintf(fp, "\nDönem: %s\n", performanceRecords[i].period);
            fprintf(fp, "Hasta Sayısı: %d\n", performanceRecords[i].patientCount);
            fprintf(fp, "Konsültasyon Sayısı: %d\n", performanceRecords[i].consultationCount);
            fprintf(fp, "Ameliyat Sayısı: %d\n", performanceRecords[i].surgeryCount);
            fprintf(fp, "Hasta Memnuniyet Oranı: %.2f%%\n", performanceRecords[i].satisfactionRate);
            fprintf(fp, "Değerlendirme: %s\n", performanceRecords[i].evaluation);
            fprintf(fp, "----------------------------------------\n");
        }
    }
    
    fclose(fp);
    printf("\nPerformans raporu başarıyla oluşturuldu: %s\n", filename);
}

// Yardımcı fonksiyonlar
int isTimeSlotAvailable(int doctorId, char *date, char *startTime, char *endTime) {
    for(int i = 0; i < scheduleCount; i++) {
        if(schedules[i].doctorId == doctorId && 
           strcmp(schedules[i].date, date) == 0) {
            // Basit çakışma kontrolü
            if(strcmp(startTime, schedules[i].endTime) < 0 && 
               strcmp(endTime, schedules[i].startTime) > 0) {
                return 0; // Çakışma var
            }
        }
    }
    return 1; // Çakışma yok
}

int findScheduleById(int id) {
    for(int i = 0; i < scheduleCount; i++) {
        if(schedules[i].id == id) return i;
    }
    return -1;
}

int findConsultationById(int id) {
    for(int i = 0; i < consultationCount; i++) {
        if(consultations[i].id == id) return i;
    }
    return -1;
}

int findPerformanceRecordById(int id) {
    for(int i = 0; i < performanceRecordCount; i++) {
        if(performanceRecords[i].id == id) return i;
    }
    return -1;
}