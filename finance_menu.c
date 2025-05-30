#include "finance.h"
#include "hospital.h"

void financeMenu() {
    int choice, patientId, invoiceId, employeeId;
    char searchTerm[50];
    
    while(1) {
        system("cls");
        printf("\n=== FİNANS İŞLEMLERİ ===\n");
        printf("1. Yeni Fatura Oluştur\n");
        printf("2. Faturaları Listele\n");
        printf("3. Fatura Ara\n");
        printf("4. Ödeme Kaydet\n");
        printf("5. Ödemeleri Listele\n");
        printf("6. Sigorta Talebi Oluştur\n");
        printf("7. Sigorta Taleplerini Listele\n");
        printf("8. Maaş Kaydı Oluştur\n");
        printf("9. Maaş Kayıtlarını Listele\n");
        printf("10. Finansal Rapor Oluştur\n");
        printf("11. Ana Menüye Dön\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\nHasta ID: ");
                scanf("%d", &patientId);
                createInvoice(patientId);
                break;
            case 2:
                listInvoices();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 3:
                printf("\nArama terimi girin: ");
                scanf(" %[^\n]s", searchTerm);
                searchInvoice(searchTerm);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 4:
                printf("\nFatura ID: ");
                scanf("%d", &invoiceId);
                recordPayment(invoiceId);
                break;
            case 5:
                listPayments();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 6:
                printf("\nHasta ID: ");
                scanf("%d", &patientId);
                printf("Fatura ID: ");
                scanf("%d", &invoiceId);
                createInsuranceClaim(patientId, invoiceId);
                break;
            case 7:
                listInsuranceClaims();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 8:
                printf("\nÇalışan ID: ");
                scanf("%d", &employeeId);
                createSalaryRecord(employeeId);
                break;
            case 9:
                listSalaryRecords();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 10:
                generateFinancialReport();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 11:
                return;
            default:
                printf("\nGeçersiz seçim! Tekrar deneyin.\n");
                getchar();
        }
    }
}