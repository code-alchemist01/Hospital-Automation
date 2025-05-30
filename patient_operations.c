#include "hospital.h"

// Hasta arama fonksiyonu
int searchPatient(char *searchTerm) {
    printf("\n=== ARAMA SONUÇLARI ===\n");
    printf("ID\tAd\tSoyad\tTelefon\tYaş\tAdres\n");
    printf("------------------------------------------------\n");
    
    int found = 0;
    for(int i = 0; i < patientCount; i++) {
        if(strstr(patients[i].name, searchTerm) != NULL ||
           strstr(patients[i].surname, searchTerm) != NULL ||
           strstr(patients[i].phone, searchTerm) != NULL) {
            printf("%d\t%s\t%s\t%s\t%d\t%s\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].surname,
                   patients[i].phone,
                   patients[i].age,
                   patients[i].address);
            found++;
        }
    }
    
    if(!found) {
        printf("\nAranan kriterlere uygun hasta bulunamadı.\n");
    }
    
    return found;
}

// Hasta güncelleme fonksiyonu
void updatePatient() {
    int id;
    printf("\nGüncellenecek hasta ID: ");
    scanf("%d", &id);
    
    int index = -1;
    for(int i = 0; i < patientCount; i++) {
        if(patients[i].id == id) {
            index = i;
            break;
        }
    }
    
    if(index == -1) {
        printf("\nBelirtilen ID'ye sahip hasta bulunamadı!\n");
        getchar();
        getchar();
        return;
    }
    
    printf("\nMevcut Bilgiler:\n");
    printf("Ad: %s\n", patients[index].name);
    printf("Soyad: %s\n", patients[index].surname);
    printf("Telefon: %s\n", patients[index].phone);
    printf("Adres: %s\n", patients[index].address);
    printf("Yaş: %d\n", patients[index].age);
    
    printf("\nYeni Bilgileri Girin:\n");
    printf("Yeni Ad (değiştirmemek için boş bırakın): ");
    char input[50];
    getchar();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strlen(input) > 0) strcpy(patients[index].name, input);
    
    printf("Yeni Soyad: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strlen(input) > 0) strcpy(patients[index].surname, input);
    
    printf("Yeni Telefon: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strlen(input) > 0) strcpy(patients[index].phone, input);
    
    printf("Yeni Adres: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strlen(input) > 0) strcpy(patients[index].address, input);
    
    printf("Yeni Yaş: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strlen(input) > 0) patients[index].age = atoi(input);
    
    printf("\nHasta bilgileri başarıyla güncellendi.\n");
    getchar();
}

// Hasta silme fonksiyonu
void deletePatient() {
    int id;
    printf("\nSilinecek hasta ID: ");
    scanf("%d", &id);
    
    int index = -1;
    for(int i = 0; i < patientCount; i++) {
        if(patients[i].id == id) {
            index = i;
            break;
        }
    }
    
    if(index == -1) {
        printf("\nBelirtilen ID'ye sahip hasta bulunamadı!\n");
        getchar();
        getchar();
        return;
    }
    
    // Silme işlemi için onay al
    printf("\n%s %s isimli hastayı silmek istediğinize emin misiniz? (E/H): ",
           patients[index].name, patients[index].surname);
    char confirm;
    getchar();
    scanf("%c", &confirm);
    
    if(confirm == 'E' || confirm == 'e') {
        // Sonraki hastaları bir öne kaydır
        for(int i = index; i < patientCount - 1; i++) {
            patients[i] = patients[i + 1];
        }
        patientCount--;
        printf("\nHasta başarıyla silindi.\n");
    } else {
        printf("\nSilme işlemi iptal edildi.\n");
    }
    
    getchar();
    getchar();
}