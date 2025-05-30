# Hospital Automation

Bu proje, hastane içi iş süreçlerinin otomasyonunu sağlamak amacıyla geliştirilmiş kapsamlı bir C programıdır. Hasta, doktor, randevu, eczane ve finans gibi temel hastane işlevlerini modüler şekilde yönetir.

## Özellikler

- **Hasta Kayıt Yönetimi:** Yeni hasta ekleme, hasta bilgilerini güncelleme ve hasta arama.
- **Doktor Yönetimi:** Doktor ekleme, doktor listesi ve doktor bilgilerini düzenleme.
- **Randevu Sistemi:** Hasta ve doktorlar arasında randevu oluşturma ve yönetme.
- **Eczane Modülü:** İlaç yönetimi ve eczane işlemleri.
- **Finans Yönetimi:** Hastane gelir ve gider işlemleri.
- **Kullanıcı Girişi & Yetkilendirme:** Farklı kullanıcı rolleri için giriş ve yetki sistemi.

## Dosya Yapısı (İlk 20 Dosya)
- `main.c`: Uygulamanın ana dosyası.
- `appointment.c`, `appointment_operations.c`: Randevu işlemleri.
- `auth.c`, `auth.h`: Giriş ve yetkilendirme mekanizması.
- `doctor.c`, `doctor_operations.c`, `doctor_extended.c`, `doctor_extended.h`: Doktor yönetimi ve işlemleri.
- `patient_operations.c`, `patient_extended.c`, `patient_extended.h`: Hasta ile ilgili işlemler ve ek özellikler.
- `pharmacy.c`, `pharmacy.h`, `pharmacy_menu.c`: Eczane yönetimi.
- `finance.c`, `finance.h`, `finance_menu.c`: Finansal işlemler.
- `user_menu.c`: Kullanıcı arayüzü menüsü.
- `hospital.h`: Genel tanımlar ve yapılar.
- `globals.c`: Global değişkenler.
- `Makefile`: Derleme betiği.
- `hospital.exe`: Derlenmiş uygulama.

> Not: Burada listelenenler yalnızca ilk 20 dosyadır, tüm dosyaları görmek için [GitHub dosya listesine bakınız](https://github.com/code-alchemist01/Hospital-Automation/tree/master).

## Kurulum

1. Projeyi klonlayın:
   ```bash
   git clone https://github.com/code-alchemist01/Hospital-Automation.git
   cd Hospital-Automation
   ```
2. Derleyin:
   ```bash
   make
   ```
3. Uygulamayı çalıştırın:
   ```bash
   ./hospital.exe
   ```

## Katkıda Bulunma

Katkıda bulunmak için lütfen fork'layın ve pull request gönderin.

## Lisans

Bu projede açık bir lisans belirtilmemiştir.

---

Daha fazla bilgi ve tüm dosyaları görmek için: [GitHub Repository](https://github.com/code-alchemist01/Hospital-Automation)
