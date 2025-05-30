#ifndef FINANCE_H
#define FINANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INVOICES 1000
#define MAX_PAYMENTS 2000
#define MAX_INSURANCE_CLAIMS 500
#define MAX_SALARY_RECORDS 200

// Fatura yapısı
typedef struct {
    int id;
    int patientId;
    char date[20];
    float amount;
    char description[200];
    char status[20]; // Ödendi, Bekliyor, İptal
    char paymentMethod[50];
} Invoice;

// Ödeme yapısı
typedef struct {
    int id;
    int invoiceId;
    char date[20];
    float amount;
    char paymentMethod[50];
    char transactionId[100];
    char status[20];
} Payment;

// Sigorta talebi yapısı
typedef struct {
    int id;
    int patientId;
    int invoiceId;
    char date[20];
    char insuranceCompany[100];
    char policyNumber[50];
    float claimAmount;
    char status[20]; // Onaylandı, Bekliyor, Reddedildi
    char notes[200];
} InsuranceClaim;

// Maaş kaydı yapısı
typedef struct {
    int id;
    int employeeId;
    char period[20]; // Ay/Yıl
    float baseSalary;
    float overtime;
    float bonus;
    float deductions;
    float netSalary;
    char paymentStatus[20];
    char notes[200];
} SalaryRecord;

// Global değişkenler
extern Invoice invoices[MAX_INVOICES];
extern Payment payments[MAX_PAYMENTS];
extern InsuranceClaim insuranceClaims[MAX_INSURANCE_CLAIMS];
extern SalaryRecord salaryRecords[MAX_SALARY_RECORDS];

extern int invoiceCount;
extern int paymentCount;
extern int insuranceClaimCount;
extern int salaryRecordCount;

// Fonksiyon prototipleri
// Fatura işlemleri
void createInvoice(int patientId);
void listInvoices();
void searchInvoice(char *searchTerm);
void updateInvoice(int invoiceId);
void cancelInvoice(int invoiceId);

// Ödeme işlemleri
void recordPayment(int invoiceId);
void listPayments();
void searchPayment(char *searchTerm);
void updatePayment(int paymentId);
void generatePaymentReport();

// Sigorta işlemleri
void createInsuranceClaim(int patientId, int invoiceId);
void listInsuranceClaims();
void updateInsuranceClaim(int claimId);
void generateInsuranceReport();

// Maaş işlemleri
void createSalaryRecord(int employeeId);
void listSalaryRecords();
void updateSalaryRecord(int recordId);
void generatePayrollReport();

// Raporlama işlemleri
void generateFinancialReport();
void generateRevenueReport();
void generateExpenseReport();

// Yardımcı fonksiyonlar
int findInvoiceById(int id);
int findPaymentById(int id);
int findInsuranceClaimById(int id);
int findSalaryRecordById(int id);
float calculateTotalRevenue();
float calculateTotalExpenses();

#endif // FINANCE_H