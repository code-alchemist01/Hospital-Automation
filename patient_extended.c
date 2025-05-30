#include "patient_extended.h"

// Global değişkenlerin tanımlanması
MedicalRecord medicalRecords[MAX_MEDICAL_RECORDS];
LabResult labResults[MAX_LAB_RESULTS];
Prescription prescriptions[MAX_PRESCRIPTIONS];
TreatmentPlan treatments[MAX_TREATMENTS];
PatientNote patientNotes[MAX_NOTES];

int medicalRecordCount = 0;
int labResultCount = 0;
int prescriptionCount = 0;
int treatmentCount = 0;
int noteCount = 0;

// Tıbbi kayıt işlemleri
void addMedicalRecord(int patientId) {
    if(medicalRecordCount >= MAX_MEDICAL_RECORDS) {
        printf("\nMaksimum tıbbi kayıt sayısına ulaşıldı!\n");
        return;
    }
    
    MedicalRecord newRecord;
    newRecord.id = medicalRecordCount + 1;
    newRecord.patientId = patientId;
    newRecord.doctorId = currentUserId;
    
    // Tarih otomatik olarak ayarlanır
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newRecord.date, sizeof(newRecord.date), "%d.%m.%Y", tm);
    
    printf("\nTanı: ");
    scanf(" %[^\n]s", newRecord.diagnosis);
    
    printf("Tedavi: ");
    scanf(" %[^\n]s", newRecord.treatment);
    
    printf("Notlar: ");
    scanf(" %[^\n]s", newRecord.notes);
    
    medicalRecords[medicalRecordCount++] = newRecord;
    printf("\nTıbbi kayıt başarıyla eklendi.\n");
}

void viewMedicalHistory(int patientId) {
    int found = 0;
    printf("\n=== HASTA TIBBİ GEÇMİŞİ ===\n");
    
    for(int i = 0; i < medicalRecordCount; i++) {
        if(medicalRecords[i].patientId == patientId) {
            printf("\nKayıt ID: %d\n", medicalRecords[i].id);
            printf("Tarih: %s\n", medicalRecords[i].date);
            printf("Tanı: %s\n", medicalRecords[i].diagnosis);
            printf("Tedavi: %s\n", medicalRecords[i].treatment);
            printf("Notlar: %s\n", medicalRecords[i].notes);
            printf("----------------------------------------\n");
            found++;
        }
    }
    
    if(!found) {
        printf("\nHastaya ait tıbbi kayıt bulunamadı.\n");
    }
}

// Laboratuvar sonuçları işlemleri
void addLabResult(int patientId) {
    if(labResultCount >= MAX_LAB_RESULTS) {
        printf("\nMaksimum laboratuvar sonucu sayısına ulaşıldı!\n");
        return;
    }
    
    LabResult newResult;
    newResult.id = labResultCount + 1;
    newResult.patientId = patientId;
    newResult.doctorId = currentUserId;
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newResult.date, sizeof(newResult.date), "%d.%m.%Y", tm);
    
    printf("\nTest Adı: ");
    scanf(" %[^\n]s", newResult.testName);
    
    printf("Sonuç: ");
    scanf(" %[^\n]s", newResult.result);
    
    printf("Normal Aralık: ");
    scanf(" %[^\n]s", newResult.normalRange);
    
    printf("Notlar: ");
    scanf(" %[^\n]s", newResult.notes);
    
    labResults[labResultCount++] = newResult;
    printf("\nLaboratuvar sonucu başarıyla eklendi.\n");
}

void viewLabResults(int patientId) {
    int found = 0;
    printf("\n=== LABORATUVAR SONUÇLARI ===\n");
    
    for(int i = 0; i < labResultCount; i++) {
        if(labResults[i].patientId == patientId) {
            printf("\nSonuç ID: %d\n", labResults[i].id);
            printf("Tarih: %s\n", labResults[i].date);
            printf("Test: %s\n", labResults[i].testName);
            printf("Sonuç: %s\n", labResults[i].result);
            printf("Normal Aralık: %s\n", labResults[i].normalRange);
            printf("Notlar: %s\n", labResults[i].notes);
            printf("----------------------------------------\n");
            found++;
        }
    }
    
    if(!found) {
        printf("\nHastaya ait laboratuvar sonucu bulunamadı.\n");
    }
}

// Reçete işlemleri
void addPrescription(int patientId) {
    if(prescriptionCount >= MAX_PRESCRIPTIONS) {
        printf("\nMaksimum reçete sayısına ulaşıldı!\n");
        return;
    }
    
    Prescription newPrescription;
    newPrescription.id = prescriptionCount + 1;
    newPrescription.patientId = patientId;
    newPrescription.doctorId = currentUserId;
    newPrescription.isActive = 1;
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newPrescription.date, sizeof(newPrescription.date), "%d.%m.%Y", tm);
    
    printf("\nİlaçlar: ");
    scanf(" %[^\n]s", newPrescription.medications);
    
    printf("Dozaj: ");
    scanf(" %[^\n]s", newPrescription.dosage);
    
    printf("Kullanım Talimatları: ");
    scanf(" %[^\n]s", newPrescription.instructions);
    
    printf("Son Kullanma Tarihi (GG.AA.YYYY): ");
    scanf(" %[^\n]s", newPrescription.validUntil);
    
    prescriptions[prescriptionCount++] = newPrescription;
    printf("\nReçete başarıyla oluşturuldu.\n");
}

void viewPrescriptions(int patientId) {
    int found = 0;
    printf("\n=== REÇETELER ===\n");
    
    for(int i = 0; i < prescriptionCount; i++) {
        if(prescriptions[i].patientId == patientId) {
            printf("\nReçete ID: %d\n", prescriptions[i].id);
            printf("Tarih: %s\n", prescriptions[i].date);
            printf("İlaçlar: %s\n", prescriptions[i].medications);
            printf("Dozaj: %s\n", prescriptions[i].dosage);
            printf("Kullanım Talimatları: %s\n", prescriptions[i].instructions);
            printf("Son Kullanma Tarihi: %s\n", prescriptions[i].validUntil);
            printf("Durum: %s\n", prescriptions[i].isActive ? "Aktif" : "Pasif");
            printf("----------------------------------------\n");
            found++;
        }
    }
    
    if(!found) {
        printf("\nHastaya ait reçete bulunamadı.\n");
    }
}

// Hasta dosyası işlemleri
void generatePatientReport(int patientId) {
    int patientIndex = findPatientById(patientId);
    if(patientIndex == -1) {
        printf("\nHasta bulunamadı!\n");
        return;
    }
    
    char filename[100];
    sprintf(filename, "hasta_rapor_%d.txt", patientId);
    
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("\nDosya oluşturulamadı!\n");
        return;
    }
    
    // Hasta bilgileri
    fprintf(fp, "=== HASTA RAPORU ===\n\n");
    fprintf(fp, "Hasta Bilgileri:\n");
    fprintf(fp, "ID: %d\n", patients[patientIndex].id);
    fprintf(fp, "Ad Soyad: %s %s\n", patients[patientIndex].name, patients[patientIndex].surname);
    fprintf(fp, "Yaş: %d\n", patients[patientIndex].age);
    fprintf(fp, "Telefon: %s\n", patients[patientIndex].phone);
    fprintf(fp, "Adres: %s\n\n", patients[patientIndex].address);
    
    // Tıbbi kayıtlar
    fprintf(fp, "Tıbbi Kayıtlar:\n");
    for(int i = 0; i < medicalRecordCount; i++) {
        if(medicalRecords[i].patientId == patientId) {
            fprintf(fp, "\nTarih: %s\n", medicalRecords[i].date);
            fprintf(fp, "Tanı: %s\n", medicalRecords[i].diagnosis);
            fprintf(fp, "Tedavi: %s\n", medicalRecords[i].treatment);
            fprintf(fp, "Notlar: %s\n", medicalRecords[i].notes);
            fprintf(fp, "----------------------------------------\n");
        }
    }
    
    // Laboratuvar sonuçları
    fprintf(fp, "\nLaboratuvar Sonuçları:\n");
    for(int i = 0; i < labResultCount; i++) {
        if(labResults[i].patientId == patientId) {
            fprintf(fp, "\nTarih: %s\n", labResults[i].date);
            fprintf(fp, "Test: %s\n", labResults[i].testName);
            fprintf(fp, "Sonuç: %s\n", labResults[i].result);
            fprintf(fp, "Normal Aralık: %s\n", labResults[i].normalRange);
            fprintf(fp, "----------------------------------------\n");
        }
    }
    
    // Aktif reçeteler
    fprintf(fp, "\nAktif Reçeteler:\n");
    for(int i = 0; i < prescriptionCount; i++) {
        if(prescriptions[i].patientId == patientId && prescriptions[i].isActive) {
            fprintf(fp, "\nTarih: %s\n", prescriptions[i].date);
            fprintf(fp, "İlaçlar: %s\n", prescriptions[i].medications);
            fprintf(fp, "Dozaj: %s\n", prescriptions[i].dosage);
            fprintf(fp, "Kullanım Talimatları: %s\n", prescriptions[i].instructions);
            fprintf(fp, "Son Kullanma Tarihi: %s\n", prescriptions[i].validUntil);
            fprintf(fp, "----------------------------------------\n");
        }
    }
    
    fclose(fp);
    printf("\nHasta raporu başarıyla oluşturuldu: %s\n", filename);
}

// Yardımcı fonksiyonlar
int findMedicalRecordById(int id) {
    for(int i = 0; i < medicalRecordCount; i++) {
        if(medicalRecords[i].id == id) return i;
    }
    return -1;
}

int findLabResultById(int id) {
    for(int i = 0; i < labResultCount; i++) {
        if(labResults[i].id == id) return i;
    }
    return -1;
}

int findPrescriptionById(int id) {
    for(int i = 0; i < prescriptionCount; i++) {
        if(prescriptions[i].id == id) return i;
    }
    return -1;
}