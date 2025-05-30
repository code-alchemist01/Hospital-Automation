#include "finance.h"
#include "hospital.h"

// Global değişkenlerin tanımlanması
Invoice invoices[MAX_INVOICES];
Payment payments[MAX_PAYMENTS];
InsuranceClaim insuranceClaims[MAX_INSURANCE_CLAIMS];
SalaryRecord salaryRecords[MAX_SALARY_RECORDS];

int invoiceCount = 0;
int paymentCount = 0;
int insuranceClaimCount = 0;
int salaryRecordCount = 0;

// Fatura işlemleri
void createInvoice(int patientId) {
    if(invoiceCount >= MAX_INVOICES) {
        printf("\nMaksimum fatura sayısına ulaşıldı!\n");
        return;
    }
    
    int patientIndex = findPatientById(patientId);
    if(patientIndex == -1) {
        printf("\nHasta bulunamadı!\n");
        return;
    }
    
    Invoice newInvoice;
    newInvoice.id = invoiceCount + 1;
    newInvoice.patientId = patientId;
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newInvoice.date, sizeof(newInvoice.date), "%d.%m.%Y", tm);
    
    printf("\nFatura Tutarı: ");
    scanf("%f", &newInvoice.amount);
    
    printf("Açıklama: ");
    scanf(" %[^\n]s", newInvoice.description);
    
    printf("Ödeme Yöntemi: ");
    scanf(" %[^\n]s", newInvoice.paymentMethod);
    
    strcpy(newInvoice.status, "Bekliyor");
    
    invoices[invoiceCount++] = newInvoice;
    printf("\nFatura başarıyla oluşturuldu.\n");
}

void listInvoices() {
    printf("\n=== FATURALAR ===\n");
    for(int i = 0; i < invoiceCount; i++) {
        int patientIndex = findPatientById(invoices[i].patientId);
        if(patientIndex != -1) {
            printf("\nFatura ID: %d\n", invoices[i].id);
            printf("Hasta: %s %s\n", 
                   patients[patientIndex].name,
                   patients[patientIndex].surname);
            printf("Tarih: %s\n", invoices[i].date);
            printf("Tutar: %.2f TL\n", invoices[i].amount);
            printf("Açıklama: %s\n", invoices[i].description);
            printf("Durum: %s\n", invoices[i].status);
            printf("Ödeme Yöntemi: %s\n", invoices[i].paymentMethod);
            printf("----------------------------------------\n");
        }
    }
}

// Ödeme işlemleri
void recordPayment(int invoiceId) {
    if(paymentCount >= MAX_PAYMENTS) {
        printf("\nMaksimum ödeme sayısına ulaşıldı!\n");
        return;
    }
    
    int invoiceIndex = findInvoiceById(invoiceId);
    if(invoiceIndex == -1) {
        printf("\nFatura bulunamadı!\n");
        return;
    }
    
    Payment newPayment;
    newPayment.id = paymentCount + 1;
    newPayment.invoiceId = invoiceId;
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newPayment.date, sizeof(newPayment.date), "%d.%m.%Y", tm);
    
    printf("\nÖdeme Tutarı: ");
    scanf("%f", &newPayment.amount);
    
    printf("Ödeme Yöntemi: ");
    scanf(" %[^\n]s", newPayment.paymentMethod);
    
    printf("İşlem ID: ");
    scanf(" %[^\n]s", newPayment.transactionId);
    
    strcpy(newPayment.status, "Tamamlandı");
    strcpy(invoices[invoiceIndex].status, "Ödendi");
    
    payments[paymentCount++] = newPayment;
    printf("\nÖdeme başarıyla kaydedildi.\n");
}

// Sigorta işlemleri
void createInsuranceClaim(int patientId, int invoiceId) {
    if(insuranceClaimCount >= MAX_INSURANCE_CLAIMS) {
        printf("\nMaksimum sigorta talebi sayısına ulaşıldı!\n");
        return;
    }
    
    int patientIndex = findPatientById(patientId);
    int invoiceIndex = findInvoiceById(invoiceId);
    
    if(patientIndex == -1 || invoiceIndex == -1) {
        printf("\nHasta veya fatura bulunamadı!\n");
        return;
    }
    
    InsuranceClaim newClaim;
    newClaim.id = insuranceClaimCount + 1;
    newClaim.patientId = patientId;
    newClaim.invoiceId = invoiceId;
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newClaim.date, sizeof(newClaim.date), "%d.%m.%Y", tm);
    
    printf("\nSigorta Şirketi: ");
    scanf(" %[^\n]s", newClaim.insuranceCompany);
    
    printf("Poliçe Numarası: ");
    scanf(" %[^\n]s", newClaim.policyNumber);
    
    printf("Talep Tutarı: ");
    scanf("%f", &newClaim.claimAmount);
    
    printf("Notlar: ");
    scanf(" %[^\n]s", newClaim.notes);
    
    strcpy(newClaim.status, "Bekliyor");
    
    insuranceClaims[insuranceClaimCount++] = newClaim;
    printf("\nSigorta talebi başarıyla oluşturuldu.\n");
}

// Maaş işlemleri
void createSalaryRecord(int employeeId) {
    if(salaryRecordCount >= MAX_SALARY_RECORDS) {
        printf("\nMaksimum maaş kaydı sayısına ulaşıldı!\n");
        return;
    }
    
    SalaryRecord newRecord;
    newRecord.id = salaryRecordCount + 1;
    newRecord.employeeId = employeeId;
    
    printf("\nDönem (AA/YYYY): ");
    scanf(" %[^\n]s", newRecord.period);
    
    printf("Temel Maaş: ");
    scanf("%f", &newRecord.baseSalary);
    
    printf("Mesai Ücreti: ");
    scanf("%f", &newRecord.overtime);
    
    printf("Bonus: ");
    scanf("%f", &newRecord.bonus);
    
    printf("Kesintiler: ");
    scanf("%f", &newRecord.deductions);
    
    newRecord.netSalary = newRecord.baseSalary + newRecord.overtime + 
                         newRecord.bonus - newRecord.deductions;
    
    strcpy(newRecord.paymentStatus, "Bekliyor");
    
    printf("Notlar: ");
    scanf(" %[^\n]s", newRecord.notes);
    
    salaryRecords[salaryRecordCount++] = newRecord;
    printf("\nMaaş kaydı başarıyla oluşturuldu.\n");
}

// Raporlama işlemleri
void generateFinancialReport() {
    float totalRevenue = calculateTotalRevenue();
    float totalExpenses = calculateTotalExpenses();
    float profit = totalRevenue - totalExpenses;
    
    char filename[] = "finansal_rapor.txt";
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("\nDosya oluşturulamadı!\n");
        return;
    }
    
    fprintf(fp, "=== FİNANSAL RAPOR ===\n\n");
    fprintf(fp, "Tarih: %s\n\n", __DATE__);
    
    fprintf(fp, "Gelir Özeti:\n");
    fprintf(fp, "Toplam Gelir: %.2f TL\n", totalRevenue);
    fprintf(fp, "Toplam Gider: %.2f TL\n", totalExpenses);
    fprintf(fp, "Net Kar/Zarar: %.2f TL\n\n", profit);
    
    fprintf(fp, "Fatura Durumu:\n");
    int pendingInvoices = 0;
    float pendingAmount = 0;
    for(int i = 0; i < invoiceCount; i++) {
        if(strcmp(invoices[i].status, "Bekliyor") == 0) {
            pendingInvoices++;
            pendingAmount += invoices[i].amount;
        }
    }
    fprintf(fp, "Bekleyen Fatura Sayısı: %d\n", pendingInvoices);
    fprintf(fp, "Bekleyen Fatura Tutarı: %.2f TL\n\n", pendingAmount);
    
    fprintf(fp, "Sigorta Talepleri:\n");
    int pendingClaims = 0;
    float claimAmount = 0;
    for(int i = 0; i < insuranceClaimCount; i++) {
        if(strcmp(insuranceClaims[i].status, "Bekliyor") == 0) {
            pendingClaims++;
            claimAmount += insuranceClaims[i].claimAmount;
        }
    }
    fprintf(fp, "Bekleyen Talep Sayısı: %d\n", pendingClaims);
    fprintf(fp, "Toplam Talep Tutarı: %.2f TL\n", claimAmount);
    
    fclose(fp);
    printf("\nFinansal rapor başarıyla oluşturuldu: %s\n", filename);
}

// Yardımcı fonksiyonlar
int findInvoiceById(int id) {
    for(int i = 0; i < invoiceCount; i++) {
        if(invoices[i].id == id) return i;
    }
    return -1;
}

int findPaymentById(int id) {
    for(int i = 0; i < paymentCount; i++) {
        if(payments[i].id == id) return i;
    }
    return -1;
}

int findInsuranceClaimById(int id) {
    for(int i = 0; i < insuranceClaimCount; i++) {
        if(insuranceClaims[i].id == id) return i;
    }
    return -1;
}

int findSalaryRecordById(int id) {
    for(int i = 0; i < salaryRecordCount; i++) {
        if(salaryRecords[i].id == id) return i;
    }
    return -1;
}

float calculateTotalRevenue() {
    float total = 0;
    for(int i = 0; i < paymentCount; i++) {
        if(strcmp(payments[i].status, "Tamamlandı") == 0) {
            total += payments[i].amount;
        }
    }
    return total;
}

float calculateTotalExpenses() {
    float total = 0;
    for(int i = 0; i < salaryRecordCount; i++) {
        if(strcmp(salaryRecords[i].paymentStatus, "Ödendi") == 0) {
            total += salaryRecords[i].netSalary;
        }
    }
    // Diğer giderler buraya eklenebilir
    return total;
}

void listInsuranceClaims() {
    printf("\n=== SİGORTA TALEPLERİ ===\n");
    for(int i = 0; i < insuranceClaimCount; i++) {
        int patientIndex = findPatientById(insuranceClaims[i].patientId);
        int invoiceIndex = findInvoiceById(insuranceClaims[i].invoiceId);
        
        if(patientIndex != -1 && invoiceIndex != -1) {
            printf("\nTalep ID: %d\n", insuranceClaims[i].id);
            printf("Hasta: %s %s\n", 
                   patients[patientIndex].name,
                   patients[patientIndex].surname);
            printf("Tarih: %s\n", insuranceClaims[i].date);
            printf("Sigorta Şirketi: %s\n", insuranceClaims[i].insuranceCompany);
            printf("Poliçe No: %s\n", insuranceClaims[i].policyNumber);
            printf("Talep Tutarı: %.2f TL\n", insuranceClaims[i].claimAmount);
            printf("Durum: %s\n", insuranceClaims[i].status);
            printf("Notlar: %s\n", insuranceClaims[i].notes);
            printf("----------------------------------------\n");
        }
    }
}

void listSalaryRecords() {
    printf("\n=== MAAŞ KAYITLARI ===\n");
    for(int i = 0; i < salaryRecordCount; i++) {
        printf("\nKayıt ID: %d\n", salaryRecords[i].id);
        printf("Çalışan ID: %d\n", salaryRecords[i].employeeId);
        printf("Dönem: %s\n", salaryRecords[i].period);
        printf("Temel Maaş: %.2f TL\n", salaryRecords[i].baseSalary);
        printf("Mesai Ücreti: %.2f TL\n", salaryRecords[i].overtime);
        printf("Bonus: %.2f TL\n", salaryRecords[i].bonus);
        printf("Kesintiler: %.2f TL\n", salaryRecords[i].deductions);
        printf("Net Maaş: %.2f TL\n", salaryRecords[i].netSalary);
        printf("Ödeme Durumu: %s\n", salaryRecords[i].paymentStatus);
        printf("Notlar: %s\n", salaryRecords[i].notes);
        printf("----------------------------------------\n");
    }
}

void searchInvoice(char *searchTerm) {
    printf("\n=== FATURA ARAMA SONUÇLARI ===\n");
    int found = 0;
    
    for(int i = 0; i < invoiceCount; i++) {
        int patientIndex = findPatientById(invoices[i].patientId);
        if(patientIndex != -1) {
            char fullName[100];
            sprintf(fullName, "%s %s", patients[patientIndex].name, patients[patientIndex].surname);
            
            if(strstr(fullName, searchTerm) != NULL ||
               strstr(invoices[i].description, searchTerm) != NULL ||
               strstr(invoices[i].status, searchTerm) != NULL ||
               strstr(invoices[i].paymentMethod, searchTerm) != NULL) {
                
                printf("\nFatura ID: %d\n", invoices[i].id);
                printf("Hasta: %s\n", fullName);
                printf("Tarih: %s\n", invoices[i].date);
                printf("Tutar: %.2f TL\n", invoices[i].amount);
                printf("Açıklama: %s\n", invoices[i].description);
                printf("Durum: %s\n", invoices[i].status);
                printf("Ödeme Yöntemi: %s\n", invoices[i].paymentMethod);
                printf("----------------------------------------\n");
                found++;
            }
        }
    }
    
    if(!found) {
        printf("\nAranan kriterlere uygun fatura bulunamadı.\n");
    }
}

void listPayments() {
    printf("\n=== ÖDEME LİSTESİ ===\n");
    for(int i = 0; i < paymentCount; i++) {
        int invoiceIndex = findInvoiceById(payments[i].invoiceId);
        if(invoiceIndex != -1) {
            int patientIndex = findPatientById(invoices[invoiceIndex].patientId);
            if(patientIndex != -1) {
                printf("\nÖdeme ID: %d\n", payments[i].id);
                printf("Fatura ID: %d\n", payments[i].invoiceId);
                printf("Hasta: %s %s\n", 
                       patients[patientIndex].name,
                       patients[patientIndex].surname);
                printf("Tarih: %s\n", payments[i].date);
                printf("Tutar: %.2f TL\n", payments[i].amount);
                printf("Ödeme Yöntemi: %s\n", payments[i].paymentMethod);
                printf("İşlem ID: %s\n", payments[i].transactionId);
                printf("Durum: %s\n", payments[i].status);
                printf("----------------------------------------\n");
            }
        }
    }
}