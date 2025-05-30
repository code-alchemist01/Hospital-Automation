#include "pharmacy.h"
#include "hospital.h"

void pharmacyMenu() {
    int choice, medicineId, supplierId, orderId, quantity;
    char searchTerm[50];
    
    while(1) {
        system("cls");
        printf("\n=== ECZANE VE STOK YÖNETİMİ ===\n");
        printf("1. Yeni İlaç Ekle\n");
        printf("2. İlaçları Listele\n");
        printf("3. İlaç Ara\n");
        printf("4. İlaç Bilgilerini Güncelle\n");
        printf("5. İlaç Sil\n");
        printf("6. Düşük Stok Kontrolü\n");
        printf("7. Son Kullanma Tarihi Kontrolü\n");
        printf("8. Yeni Tedarikçi Ekle\n");
        printf("9. Tedarikçileri Listele\n");
        printf("10. Yeni Sipariş Oluştur\n");
        printf("11. Siparişleri Listele\n");
        printf("12. Stok Girişi Yap\n");
        printf("13. Stok Çıkışı Yap\n");
        printf("14. Stok Hareketlerini Listele\n");
        printf("15. Stok Raporu Oluştur\n");
        printf("16. Ana Menüye Dön\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addMedicine();
                break;
            case 2:
                listMedicines();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 3:
                printf("\nArama terimi girin: ");
                scanf(" %[^\n]s", searchTerm);
                searchMedicine(searchTerm);
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 4:
                printf("\nİlaç ID: ");
                scanf("%d", &medicineId);
                updateMedicine(medicineId);
                break;
            case 5:
                printf("\nİlaç ID: ");
                scanf("%d", &medicineId);
                deleteMedicine(medicineId);
                break;
            case 6:
                checkLowStock();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 7:
                checkExpiryDates();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 8:
                addSupplier();
                break;
            case 9:
                listSuppliers();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 10:
                printf("\nTedarikçi ID: ");
                scanf("%d", &supplierId);
                createOrder(supplierId);
                break;
            case 11:
                listOrders();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 12:
                printf("\nİlaç ID: ");
                scanf("%d", &medicineId);
                printf("Miktar: ");
                scanf("%d", &quantity);
                recordStockEntry(medicineId, quantity);
                break;
            case 13:
                printf("\nİlaç ID: ");
                scanf("%d", &medicineId);
                printf("Miktar: ");
                scanf("%d", &quantity);
                recordStockExit(medicineId, quantity);
                break;
            case 14:
                listStockTransactions();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 15:
                generateInventoryReport();
                printf("\nDevam etmek için bir tuşa basın...");
                getchar();
                getchar();
                break;
            case 16:
                return;
            default:
                printf("\nGeçersiz seçim! Tekrar deneyin.\n");
                getchar();
        }
    }
}