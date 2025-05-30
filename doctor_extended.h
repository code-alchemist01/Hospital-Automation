#ifndef DOCTOR_EXTENDED_H
#define DOCTOR_EXTENDED_H

#include "hospital.h"

#define MAX_SCHEDULES 1000
#define MAX_SHIFTS 500
#define MAX_CONSULTATIONS 200
#define MAX_PERFORMANCE_RECORDS 100

// Çalışma takvimi yapısı
typedef struct {
    int id;
    int doctorId;
    char date[20];
    char startTime[10];
    char endTime[10];
    int isAvailable;
    char notes[200];
} Schedule;

// Nöbet çizelgesi yapısı
typedef struct {
    int id;
    int doctorId;
    char date[20];
    char startTime[10];
    char endTime[10];
    char shiftType[50]; // Gündüz, Gece, Acil vs.
    char location[100];
    int isActive;
} Shift;

// Online konsültasyon yapısı
typedef struct {
    int id;
    int doctorId;
    int patientId;
    char date[20];
    char time[10];
    char platform[50]; // Zoom, Teams vs.
    char meetingLink[200];
    char notes[300];
    char status[20]; // Bekliyor, Tamamlandı, İptal
} Consultation;

// Performans kaydı yapısı
typedef struct {
    int id;
    int doctorId;
    char period[20]; // Ay/Yıl
    int patientCount;
    int consultationCount;
    int surgeryCount;
    float satisfactionRate;
    char evaluation[500];
} PerformanceRecord;

// Global değişkenler
extern Schedule schedules[MAX_SCHEDULES];
extern Shift shifts[MAX_SHIFTS];
extern Consultation consultations[MAX_CONSULTATIONS];
extern PerformanceRecord performanceRecords[MAX_PERFORMANCE_RECORDS];

extern int scheduleCount;
extern int shiftCount;
extern int consultationCount;
extern int performanceRecordCount;

// Fonksiyon prototipleri
// Çalışma takvimi işlemleri
void addSchedule(int doctorId);
void viewSchedule(int doctorId);
void updateSchedule(int scheduleId);
void cancelSchedule(int scheduleId);

// Nöbet çizelgesi işlemleri
void addShift(int doctorId);
void viewShifts(int doctorId);
void updateShift(int shiftId);
void cancelShift(int shiftId);

// Online konsültasyon işlemleri
void addConsultation(int doctorId, int patientId);
void viewConsultations(int doctorId);
void updateConsultation(int consultationId);
void cancelConsultation(int consultationId);

// Performans yönetimi işlemleri
void addPerformanceRecord(int doctorId);
void viewPerformanceHistory(int doctorId);
void updatePerformanceRecord(int recordId);
void generatePerformanceReport(int doctorId);

// Yardımcı fonksiyonlar
int findScheduleById(int id);
int findShiftById(int id);
int findConsultationById(int id);
int findPerformanceRecordById(int id);
int checkScheduleConflict(int doctorId, char *date, char *startTime, char *endTime);
int isTimeSlotAvailable(int doctorId, char *date, char *startTime, char *endTime);

#endif // DOCTOR_EXTENDED_H