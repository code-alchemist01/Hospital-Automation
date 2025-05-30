#ifndef PATIENT_EXTENDED_H
#define PATIENT_EXTENDED_H

#include "hospital.h"

#define MAX_MEDICAL_RECORDS 1000
#define MAX_LAB_RESULTS 500
#define MAX_PRESCRIPTIONS 200
#define MAX_TREATMENTS 100
#define MAX_NOTES 500

// Tıbbi kayıt yapısı
typedef struct {
    int id;
    int patientId;
    char date[20];
    char diagnosis[200];
    char treatment[200];
    char notes[500];
    int doctorId;
} MedicalRecord;

// Laboratuvar sonucu yapısı
typedef struct {
    int id;
    int patientId;
    char date[20];
    char testName[100];
    char result[200];
    char normalRange[100];
    char notes[200];
    int doctorId;
} LabResult;

// Reçete yapısı
typedef struct {
    int id;
    int patientId;
    char date[20];
    char medications[500];
    char dosage[200];
    char instructions[300];
    char validUntil[20];
    int doctorId;
    int isActive;
} Prescription;

// Tedavi planı yapısı
typedef struct {
    int id;
    int patientId;
    char startDate[20];
    char endDate[20];
    char treatmentType[100];
    char description[300];
    char frequency[100];
    char progress[200];
    int doctorId;
    int isActive;
} TreatmentPlan;

// Hasta notu yapısı
typedef struct {
    int id;
    int patientId;
    char date[20];
    char note[500];
    int doctorId;
} PatientNote;

// Global değişkenler
extern MedicalRecord medicalRecords[MAX_MEDICAL_RECORDS];
extern LabResult labResults[MAX_LAB_RESULTS];
extern Prescription prescriptions[MAX_PRESCRIPTIONS];
extern TreatmentPlan treatments[MAX_TREATMENTS];
extern PatientNote patientNotes[MAX_NOTES];

extern int medicalRecordCount;
extern int labResultCount;
extern int prescriptionCount;
extern int treatmentCount;
extern int noteCount;

// Fonksiyon prototipleri
// Tıbbi kayıt işlemleri
void addMedicalRecord(int patientId);
void viewMedicalHistory(int patientId);
void updateMedicalRecord(int recordId);

// Laboratuvar sonuçları işlemleri
void addLabResult(int patientId);
void viewLabResults(int patientId);
void updateLabResult(int resultId);

// Reçete işlemleri
void addPrescription(int patientId);
void viewPrescriptions(int patientId);
void updatePrescription(int prescriptionId);
void deactivatePrescription(int prescriptionId);

// Tedavi planı işlemleri
void addTreatmentPlan(int patientId);
void viewTreatmentPlans(int patientId);
void updateTreatmentPlan(int planId);
void completeTreatmentPlan(int planId);

// Hasta notu işlemleri
void addPatientNote(int patientId);
void viewPatientNotes(int patientId);
void updatePatientNote(int noteId);

// Hasta dosyası işlemleri
void generatePatientReport(int patientId);
void exportPatientFile(int patientId);

// Yardımcı fonksiyonlar
int findMedicalRecordById(int id);
int findLabResultById(int id);
int findPrescriptionById(int id);
int findTreatmentPlanById(int id);
int findPatientNoteById(int id);

#endif // PATIENT_EXTENDED_H