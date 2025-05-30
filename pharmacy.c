#include "pharmacy.h"
#include "hospital.h"

// Global değişkenlerin tanımlanması
Medicine medicines[MAX_MEDICINES];
Supplier suppliers[MAX_SUPPLIERS];
Order orders[MAX_ORDERS];
StockTransaction stockTransactions[MAX_STOCK_TRANSACTIONS];

int medicineCount = 0;
int supplierCount = 0;
int orderCount = 0;
int stockTransactionCount = 0;

// İlaç işlemleri
void addMedicine() {
    if(medicineCount >= MAX_MEDICINES) {
        printf("\nMaksimum ilaç sayısına ulaşıldı!\n");
        return;
    }
    
    Medicine newMedicine;
    newMedicine.id = medicineCount + 1;
    
    printf("\nİlaç Adı: ");
    scanf(" %[^\n]s", newMedicine.name);
    
    printf("Jenerik Adı: ");
    scanf(" %[^\n]s", newMedicine.genericName);
    
    printf("Üretici: ");
    scanf(" %[^\n]s", newMedicine.manufacturer);
    
    printf("Kategori: ");
    scanf(" %[^\n]s", newMedicine.category);
    
    printf("Birim Fiyat: ");
    scanf("%f", &newMedicine.price);
    
    printf("Mevcut Stok: ");
    scanf("%d", &newMedicine.currentStock);
    
    printf("Minimum Stok: ");
    scanf("%d", &newMedicine.minimumStock);
    
    printf("Birim (Tablet/Şişe/Ampul): ");
    scanf(" %[^\n]s", newMedicine.unit);
    
    printf("Depo Konumu: ");
    scanf(" %[^\n]s", newMedicine.location);
    
    printf("Son Kullanma Tarihi (GG.AA.YYYY): ");
    scanf(" %[^\n]s", newMedicine.expiryDate);
    
    printf("Parti Numarası: ");
    scanf(" %[^\n]s", newMedicine.batchNumber);
    
    medicines[medicineCount++] = newMedicine;
    printf("\nİlaç başarıyla eklendi.\n");
}

void listMedicines() {
    printf("\n=== İLAÇ LİSTESİ ===\n");
    for(int i = 0; i < medicineCount; i++) {
        printf("\nID: %d\n", medicines[i].id);
        printf("Ad: %s\n", medicines[i].name);
        printf("Jenerik Ad: %s\n", medicines[i].genericName);
        printf("Üretici: %s\n", medicines[i].manufacturer);
        printf("Kategori: %s\n", medicines[i].category);
        printf("Fiyat: %.2f TL\n", medicines[i].price);
        printf("Mevcut Stok: %d %s\n", medicines[i].currentStock, medicines[i].unit);
        printf("Minimum Stok: %d %s\n", medicines[i].minimumStock, medicines[i].unit);
        printf("Konum: %s\n", medicines[i].location);
        printf("Son Kullanma: %s\n", medicines[i].expiryDate);
        printf("Parti No: %s\n", medicines[i].batchNumber);
        printf("----------------------------------------\n");
    }
}

void checkLowStock() {
    printf("\n=== DÜŞÜK STOK UYARISI ===\n");
    int found = 0;
    
    for(int i = 0; i < medicineCount; i++) {
        if(medicines[i].currentStock <= medicines[i].minimumStock) {
            printf("\nUYARI: Düşük stok seviyesi!\n");
            printf("İlaç: %s\n", medicines[i].name);
            printf("Mevcut Stok: %d %s\n", 
                   medicines[i].currentStock,
                   medicines[i].unit);
            printf("Minimum Stok: %d %s\n", 
                   medicines[i].minimumStock,
                   medicines[i].unit);
            printf("----------------------------------------\n");
            found++;
        }
    }
    
    if(!found) {
        printf("\nTüm ilaçlar yeterli stok seviyesinde.\n");
    }
}

// Sipariş işlemleri
void createOrder(int supplierId) {
    if(orderCount >= MAX_ORDERS) {
        printf("\nMaksimum sipariş sayısına ulaşıldı!\n");
        return;
    }
    
    int supplierIndex = findSupplierById(supplierId);
    if(supplierIndex == -1) {
        printf("\nTedarikçi bulunamadı!\n");
        return;
    }
    
    Order newOrder;
    newOrder.id = orderCount + 1;
    newOrder.supplierId = supplierId;
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newOrder.orderDate, sizeof(newOrder.orderDate), "%d.%m.%Y", tm);
    
    printf("\nBeklenen Teslimat Tarihi (GG.AA.YYYY): ");
    scanf(" %[^\n]s", newOrder.expectedDelivery);
    
    printf("Notlar: ");
    scanf(" %[^\n]s", newOrder.notes);
    
    newOrder.totalAmount = 0;
    strcpy(newOrder.status, "Bekliyor");
    
    orders[orderCount++] = newOrder;
    printf("\nSipariş oluşturuldu. Şimdi ilaçları ekleyebilirsiniz.\n");
    
    char addMore;
    do {
        int medicineId;
        printf("\nİlaç ID: ");
        scanf("%d", &medicineId);
        addOrderDetail(newOrder.id, medicineId);
        
        printf("\nBaşka ilaç eklemek ister misiniz? (E/H): ");
        scanf(" %c", &addMore);
    } while(addMore == 'E' || addMore == 'e');
}

void addOrderDetail(int orderId, int medicineId) {
    int orderIndex = findOrderById(orderId);
    int medicineIndex = findMedicineById(medicineId);
    
    if(orderIndex == -1 || medicineIndex == -1) {
        printf("\nSipariş veya ilaç bulunamadı!\n");
        return;
    }
    
    int quantity;
    printf("Miktar: ");
    scanf("%d", &quantity);
    
    float totalPrice = quantity * medicines[medicineIndex].price;
    orders[orderIndex].totalAmount += totalPrice;
    
    printf("\nİlaç siparişe eklendi:\n");
    printf("İlaç: %s\n", medicines[medicineIndex].name);
    printf("Miktar: %d %s\n", quantity, medicines[medicineIndex].unit);
    printf("Toplam: %.2f TL\n", totalPrice);
}

// Stok işlemleri
void recordStockEntry(int medicineId, int quantity) {
    if(stockTransactionCount >= MAX_STOCK_TRANSACTIONS) {
        printf("\nMaksimum işlem sayısına ulaşıldı!\n");
        return;
    }
    
    int medicineIndex = findMedicineById(medicineId);
    if(medicineIndex == -1) {
        printf("\nİlaç bulunamadı!\n");
        return;
    }
    
    StockTransaction newTransaction;
    newTransaction.id = stockTransactionCount + 1;
    newTransaction.medicineId = medicineId;
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newTransaction.date, sizeof(newTransaction.date), "%d.%m.%Y", tm);
    
    strcpy(newTransaction.type, "Giriş");
    newTransaction.quantity = quantity;
    
    printf("\nGiriş Nedeni: ");
    scanf(" %[^\n]s", newTransaction.reason);
    
    printf("Notlar: ");
    scanf(" %[^\n]s", newTransaction.notes);
    
    medicines[medicineIndex].currentStock += quantity;
    stockTransactions[stockTransactionCount++] = newTransaction;
    
    printf("\nStok girişi başarıyla kaydedildi.\n");
    printf("Yeni stok seviyesi: %d %s\n", 
           medicines[medicineIndex].currentStock,
           medicines[medicineIndex].unit);
}

// Raporlama işlemleri
void generateInventoryReport() {
    char filename[] = "stok_raporu.txt";
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("\nDosya oluşturulamadı!\n");
        return;
    }
    
    fprintf(fp, "=== STOK DURUM RAPORU ===\n\n");
    fprintf(fp, "Tarih: %s\n\n", __DATE__);
    
    float totalValue = 0;
    int lowStockCount = 0;
    
    for(int i = 0; i < medicineCount; i++) {
        float itemValue = medicines[i].currentStock * medicines[i].price;
        totalValue += itemValue;
        
        if(medicines[i].currentStock <= medicines[i].minimumStock) {
            lowStockCount++;
        }
        
        fprintf(fp, "\nİlaç: %s\n", medicines[i].name);
        fprintf(fp, "Stok: %d %s\n", 
                medicines[i].currentStock,
                medicines[i].unit);
        fprintf(fp, "Birim Fiyat: %.2f TL\n", medicines[i].price);
        fprintf(fp, "Toplam Değer: %.2f TL\n", itemValue);
        fprintf(fp, "Son Kullanma: %s\n", medicines[i].expiryDate);
        fprintf(fp, "----------------------------------------\n");
    }
    
    fprintf(fp, "\nÖZET:\n");
    fprintf(fp, "Toplam İlaç Çeşidi: %d\n", medicineCount);
    fprintf(fp, "Düşük Stok Sayısı: %d\n", lowStockCount);
    fprintf(fp, "Toplam Stok Değeri: %.2f TL\n", totalValue);
    
    fclose(fp);
    printf("\nStok raporu başarıyla oluşturuldu: %s\n", filename);
}

// Yardımcı fonksiyonlar
int findMedicineById(int id) {
    for(int i = 0; i < medicineCount; i++) {
        if(medicines[i].id == id) return i;
    }
    return -1;
}

int findSupplierById(int id) {
    for(int i = 0; i < supplierCount; i++) {
        if(suppliers[i].id == id) return i;
    }
    return -1;
}

int findOrderById(int id) {
    for(int i = 0; i < orderCount; i++) {
        if(orders[i].id == id) return i;
    }
    return -1;
}

int findStockTransactionById(int id) {
    for(int i = 0; i < stockTransactionCount; i++) {
        if(stockTransactions[i].id == id) return i;
    }
    return -1;
}

void updateMedicineStock(int medicineId, int quantity, char *type) {
    int index = findMedicineById(medicineId);
    if(index != -1) {
        if(strcmp(type, "Giriş") == 0) {
            medicines[index].currentStock += quantity;
        } else if(strcmp(type, "Çıkış") == 0) {
            medicines[index].currentStock -= quantity;
        }
    }
}

void recordStockExit(int medicineId, int quantity) {
    if(stockTransactionCount >= MAX_STOCK_TRANSACTIONS) {
        printf("\nMaksimum işlem sayısına ulaşıldı!\n");
        return;
    }
    
    int medicineIndex = findMedicineById(medicineId);
    if(medicineIndex == -1) {
        printf("\nİlaç bulunamadı!\n");
        return;
    }
    
    if(medicines[medicineIndex].currentStock < quantity) {
        printf("\nYetersiz stok! Mevcut stok: %d %s\n", 
               medicines[medicineIndex].currentStock,
               medicines[medicineIndex].unit);
        return;
    }
    
    StockTransaction newTransaction;
    newTransaction.id = stockTransactionCount + 1;
    newTransaction.medicineId = medicineId;
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newTransaction.date, sizeof(newTransaction.date), "%d.%m.%Y", tm);
    
    strcpy(newTransaction.type, "Çıkış");
    newTransaction.quantity = quantity;
    
    printf("\nÇıkış Nedeni: ");
    scanf(" %[^\n]s", newTransaction.reason);
    
    printf("Notlar: ");
    scanf(" %[^\n]s", newTransaction.notes);
    
    medicines[medicineIndex].currentStock -= quantity;
    stockTransactions[stockTransactionCount++] = newTransaction;
    
    printf("\nStok çıkışı başarıyla kaydedildi.\n");
    printf("Yeni stok seviyesi: %d %s\n", 
           medicines[medicineIndex].currentStock,
           medicines[medicineIndex].unit);
}

void listStockTransactions() {
    printf("\n=== STOK HAREKETLERİ ===\n");
    for(int i = 0; i < stockTransactionCount; i++) {
        int medicineIndex = findMedicineById(stockTransactions[i].medicineId);
        if(medicineIndex != -1) {
            printf("\nİşlem ID: %d\n", stockTransactions[i].id);
            printf("İlaç: %s\n", medicines[medicineIndex].name);
            printf("Tarih: %s\n", stockTransactions[i].date);
            printf("İşlem: %s\n", stockTransactions[i].type);
            printf("Miktar: %d %s\n", 
                   stockTransactions[i].quantity,
                   medicines[medicineIndex].unit);
            printf("Neden: %s\n", stockTransactions[i].reason);
            printf("Notlar: %s\n", stockTransactions[i].notes);
            printf("----------------------------------------\n");
        }
    }
}

void checkExpiryDates() {
    printf("\n=== SON KULLANMA TARİHİ KONTROLÜ ===\n");
    int found = 0;
    
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    char currentDate[20];
    strftime(currentDate, sizeof(currentDate), "%d.%m.%Y", tm);
    
    for(int i = 0; i < medicineCount; i++) {
        // Basit tarih karşılaştırması
        if(strcmp(medicines[i].expiryDate, currentDate) <= 0) {
            printf("\nUYARI: Son kullanma tarihi geçmiş veya yaklaşıyor!\n");
            printf("İlaç: %s\n", medicines[i].name);
            printf("Son Kullanma: %s\n", medicines[i].expiryDate);
            printf("Mevcut Stok: %d %s\n", 
                   medicines[i].currentStock,
                   medicines[i].unit);
            printf("----------------------------------------\n");
            found++;
        }
    }
    
    if(!found) {
        printf("\nSon kullanma tarihi yaklaşan ilaç bulunmadı.\n");
    }
}

void addSupplier() {
    if(supplierCount >= MAX_SUPPLIERS) {
        printf("\nMaksimum tedarikçi sayısına ulaşıldı!\n");
        return;
    }
    
    Supplier newSupplier;
    newSupplier.id = supplierCount + 1;
    
    printf("\nTedarikçi Adı: ");
    scanf(" %[^\n]s", newSupplier.name);
    
    printf("İletişim Kişisi: ");
    scanf(" %[^\n]s", newSupplier.contactPerson);
    
    printf("Telefon: ");
    scanf(" %[^\n]s", newSupplier.phone);
    
    printf("E-posta: ");
    scanf(" %[^\n]s", newSupplier.email);
    
    printf("Adres: ");
    scanf(" %[^\n]s", newSupplier.address);
    
    strcpy(newSupplier.status, "Aktif");
    
    suppliers[supplierCount++] = newSupplier;
    printf("\nTedarikçi başarıyla eklendi.\n");
}

void listSuppliers() {
    printf("\n=== TEDARİKÇİ LİSTESİ ===\n");
    for(int i = 0; i < supplierCount; i++) {
        printf("\nID: %d\n", suppliers[i].id);
        printf("Ad: %s\n", suppliers[i].name);
        printf("İletişim Kişisi: %s\n", suppliers[i].contactPerson);
        printf("Telefon: %s\n", suppliers[i].phone);
        printf("E-posta: %s\n", suppliers[i].email);
        printf("Adres: %s\n", suppliers[i].address);
        printf("Durum: %s\n", suppliers[i].status);
        printf("----------------------------------------\n");
    }
}

void listOrders() {
    printf("\n=== SİPARİŞ LİSTESİ ===\n");
    for(int i = 0; i < orderCount; i++) {
        int supplierIndex = findSupplierById(orders[i].supplierId);
        if(supplierIndex != -1) {
            printf("\nSipariş ID: %d\n", orders[i].id);
            printf("Tedarikçi: %s\n", suppliers[supplierIndex].name);
            printf("Sipariş Tarihi: %s\n", orders[i].orderDate);
            printf("Beklenen Teslimat: %s\n", orders[i].expectedDelivery);
            printf("Toplam Tutar: %.2f TL\n", orders[i].totalAmount);
            printf("Durum: %s\n", orders[i].status);
            printf("Notlar: %s\n", orders[i].notes);
            printf("----------------------------------------\n");
        }
    }
}

void searchMedicine(char *searchTerm) {
    printf("\n=== İLAÇ ARAMA SONUÇLARI ===\n");
    int found = 0;
    
    for(int i = 0; i < medicineCount; i++) {
        if(strstr(medicines[i].name, searchTerm) != NULL ||
           strstr(medicines[i].genericName, searchTerm) != NULL ||
           strstr(medicines[i].manufacturer, searchTerm) != NULL ||
           strstr(medicines[i].category, searchTerm) != NULL) {
            
            printf("\nID: %d\n", medicines[i].id);
            printf("Ad: %s\n", medicines[i].name);
            printf("Jenerik Ad: %s\n", medicines[i].genericName);
            printf("Üretici: %s\n", medicines[i].manufacturer);
            printf("Kategori: %s\n", medicines[i].category);
            printf("Fiyat: %.2f TL\n", medicines[i].price);
            printf("Mevcut Stok: %d %s\n", medicines[i].currentStock, medicines[i].unit);
            printf("----------------------------------------\n");
            found++;
        }
    }
    
    if(!found) {
        printf("\nAranan kriterlere uygun ilaç bulunamadı.\n");
    }
}

void updateMedicine(int medicineId) {
    int index = findMedicineById(medicineId);
    if(index == -1) {
        printf("\nİlaç bulunamadı!\n");
        return;
    }
    
    printf("\n=== İLAÇ BİLGİLERİNİ GÜNCELLE ===\n");
    printf("Mevcut Bilgiler:\n");
    printf("Ad: %s\n", medicines[index].name);
    printf("Jenerik Ad: %s\n", medicines[index].genericName);
    printf("Üretici: %s\n", medicines[index].manufacturer);
    printf("Kategori: %s\n", medicines[index].category);
    printf("Fiyat: %.2f TL\n", medicines[index].price);
    printf("Minimum Stok: %d\n", medicines[index].minimumStock);
    
    printf("\nYeni bilgileri girin (değiştirmek istemediğiniz alanları boş bırakın):\n");
    char input[100];
    
    printf("Yeni Ad: ");
    getchar();
    fgets(input, sizeof(input), stdin);
    if(input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(medicines[index].name, input);
    }
    
    printf("Yeni Jenerik Ad: ");
    fgets(input, sizeof(input), stdin);
    if(input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(medicines[index].genericName, input);
    }
    
    printf("Yeni Üretici: ");
    fgets(input, sizeof(input), stdin);
    if(input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(medicines[index].manufacturer, input);
    }
    
    printf("Yeni Kategori: ");
    fgets(input, sizeof(input), stdin);
    if(input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(medicines[index].category, input);
    }
    
    printf("Yeni Fiyat (TL): ");
    fgets(input, sizeof(input), stdin);
    if(input[0] != '\n') {
        medicines[index].price = atof(input);
    }
    
    printf("Yeni Minimum Stok: ");
    fgets(input, sizeof(input), stdin);
    if(input[0] != '\n') {
        medicines[index].minimumStock = atoi(input);
    }
    
    printf("\nİlaç bilgileri başarıyla güncellendi.\n");
}

void deleteMedicine(int medicineId) {
    int index = findMedicineById(medicineId);
    if(index == -1) {
        printf("\nİlaç bulunamadı!\n");
        return;
    }
    
    printf("\n=== İLAÇ SİLME ===\n");
    printf("Silinecek İlaç:\n");
    printf("Ad: %s\n", medicines[index].name);
    printf("Jenerik Ad: %s\n", medicines[index].genericName);
    printf("Üretici: %s\n", medicines[index].manufacturer);
    printf("Mevcut Stok: %d %s\n", medicines[index].currentStock, medicines[index].unit);
    
    char confirm;
    printf("\nBu ilacı silmek istediğinizden emin misiniz? (E/H): ");
    scanf(" %c", &confirm);
    
    if(confirm == 'E' || confirm == 'e') {
        // Son ilaç değilse, diğer ilaçları kaydır
        if(index < medicineCount - 1) {
            for(int i = index; i < medicineCount - 1; i++) {
                medicines[i] = medicines[i + 1];
            }
        }
        medicineCount--;
        printf("\nİlaç başarıyla silindi.\n");
    } else {
        printf("\nSilme işlemi iptal edildi.\n");
    }
}