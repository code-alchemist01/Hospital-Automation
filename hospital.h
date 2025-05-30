#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auth.h"
#include "patient_extended.h"
#include "doctor_extended.h"

// Sabitler
#define MAX_PATIENTS 1000
#define MAX_DOCTORS 100
#define MAX_APPOINTMENTS 2000

// Yapılar
typedef struct {
    int id;
    char name[50];
    char surname[50];
    char phone[15];
    char address[100];
    int age;
} Patient;

typedef struct {
    int id;
    char name[50];
    char surname[50];
    char specialization[50];
    char phone[15];
} Doctor;

typedef struct {
    int id;
    int patientId;
    int doctorId;
    char date[20];
    char time[10];
    char status[20];
} Appointment;

// Global değişkenler
extern Patient patients[MAX_PATIENTS];
extern Doctor doctors[MAX_DOCTORS];
extern Appointment appointments[MAX_APPOINTMENTS];
extern int patientCount;
extern int doctorCount;
extern int appointmentCount;

// Fonksiyon prototipleri
// Ana menü fonksiyonları
void mainMenu();
void patientMenu();
void doctorMenu();
void appointmentMenu();

// Hasta işlemleri
void addPatient();
void listPatients();
int searchPatient(char *searchTerm);
void updatePatient();
void deletePatient();

// Doktor işlemleri
void addDoctor();
void listDoctors();
int searchDoctor(char *searchTerm);
void updateDoctor();
void deleteDoctor();
void listDoctorAppointments(int doctorId);

// Randevu işlemleri
void makeAppointment();
void listAppointments();
void searchAppointment();
void updateAppointment();
void cancelAppointment();
void appointmentStatistics();
int findPatientById(int id);
int findDoctorById(int id);

// Kullanıcı yönetimi
void adminMenu();
void profileMenu();
int loginMenu();

// Finans işlemleri
void financeMenu();

// Eczane ve stok yönetimi
void pharmacyMenu();

#endif // HOSPITAL_H