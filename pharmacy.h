#ifndef PHARMACY_H
#define PHARMACY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEDICINES 1000
#define MAX_SUPPLIERS 100
#define MAX_ORDERS 500
#define MAX_STOCK_TRANSACTIONS 2000

// İlaç yapısı
typedef struct {
    int id;
    char name[100];
    char genericName[100];
    char manufacturer[100];
    char category[50];
    float price;
    int currentStock;
    int minimumStock;
    char unit[20]; // Tablet, Şişe, Ampul vs.
    char location[50]; // Depo konumu
    char expiryDate[20];
    char batchNumber[50];
} Medicine;

// Tedarikçi yapısı
typedef struct {
    int id;
    char name[100];
    char contactPerson[100];
    char phone[15];
    char email[100];
    char address[200];
    char status[20]; // Aktif, Pasif
} Supplier;

// Sipariş yapısı
typedef struct {
    int id;
    int supplierId;
    char orderDate[20];
    char expectedDelivery[20];
    float totalAmount;
    char status[20]; // Bekliyor, Onaylandı, Tamamlandı, İptal
    char notes[200];
} Order;

// Sipariş detay yapısı
typedef struct {
    int orderId;
    int medicineId;
    int quantity;
    float unitPrice;
    float totalPrice;
} OrderDetail;

// Stok işlem yapısı
typedef struct {
    int id;
    int medicineId;
    char date[20];
    char type[20]; // Giriş, Çıkış
    int quantity;
    char reason[100]; // Satış, Sipariş, Fire vs.
    char notes[200];
} StockTransaction;

// Global değişkenler
extern Medicine medicines[MAX_MEDICINES];
extern Supplier suppliers[MAX_SUPPLIERS];
extern Order orders[MAX_ORDERS];
extern StockTransaction stockTransactions[MAX_STOCK_TRANSACTIONS];

extern int medicineCount;
extern int supplierCount;
extern int orderCount;
extern int stockTransactionCount;

// Fonksiyon prototipleri
// İlaç işlemleri
void addMedicine();
void listMedicines();
void searchMedicine(char *searchTerm);
void updateMedicine(int medicineId);
void deleteMedicine(int medicineId);
void checkExpiryDates();
void checkLowStock();

// Tedarikçi işlemleri
void addSupplier();
void listSuppliers();
void searchSupplier(char *searchTerm);
void updateSupplier(int supplierId);
void deleteSupplier(int supplierId);

// Sipariş işlemleri
void createOrder(int supplierId);
void addOrderDetail(int orderId, int medicineId);
void listOrders();
void updateOrderStatus(int orderId);
void cancelOrder(int orderId);

// Stok işlemleri
void recordStockEntry(int medicineId, int quantity);
void recordStockExit(int medicineId, int quantity);
void listStockTransactions();
void generateStockReport();

// Raporlama işlemleri
void generateInventoryReport();
void generateExpiryReport();
void generateOrderReport();

// Yardımcı fonksiyonlar
int findMedicineById(int id);
int findSupplierById(int id);
int findOrderById(int id);
int findStockTransactionById(int id);
void updateMedicineStock(int medicineId, int quantity, char *type);

#endif // PHARMACY_H