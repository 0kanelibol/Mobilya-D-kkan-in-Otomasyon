#include <iostream>
#include <locale.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;



//-------------------------------------------------------------------------------------------------------------------------------------------

struct musteriBilgisi { 
    char adSoyAd[100]; // string kullanamýyoz cünkü binarry
    char id[20];
};

//-------------------------------------------------------------------------------------------------------------------------------------------

struct mobilyaBilgisi { 
    char mobilyaAdi[100];
    char id[20];
    int stok;
    int fiyat;
};

//-------------------------------------------------------------------------------------------------------------------------------------------

struct satislar {
    char musteriId[20];
    char mobilyaId[20];
    int satisAdet; // hesaplama kolaylýðý için int yapýldý
    int total;
};

//-------------------------------------------------------------------------------------------------------------------------------------------

void mobilyaEkle(){
    mobilyaBilgisi a;
    ofstream mobilyaDosya;
    mobilyaDosya.open("mobilyalar.txt", ios::app | ios::binary); // dosyayý acar ve kaydeder 
    
    if (!mobilyaDosya){
        cout << "|| Dosya Acýlamadý" << endl; // dosya acýlmaz ise ekrana yazý cýkartýr
        return;
    }
    
   	
    cout << "|| Lütfen mobilyanýn adýný giriniz: ";
	cin.getline(a.mobilyaAdi, 100);
    
    cout << "|| Lütfen mobilyanýn id numarasýný giriniz: ";
    cin.getline(a.id, 20);
    
    cout << "|| Lütfen mobilyanýn stok bilgisini giriniz: ";
    cin >> a.stok;
    cin.ignore(); //cini temizler
    
    cout << "|| Lütfen mobilyanýn fiyatýný giriniz: ";
    cin >> a.fiyat;
    cin.ignore();
    
    mobilyaDosya.write((char*)&a, sizeof(mobilyaBilgisi));   // binary olarak structý tek seferde yazýyoruz yoksa sýkýntý oluyo
    
    cout << "|| ----------------------" << endl;
    cout << "|| Girdiðiniz Bilgiler" << endl;
    cout << "|| Mobilya ismi: " << a.mobilyaAdi << endl;
    cout << "|| Mobilya id: " << a.id << endl;
    cout << "|| Mobilya stok bilgisi: " << a.stok << endl;
    cout << "|| Mobilya fiyatý: " << a.fiyat << "TL" << endl;
    cout << "|| ----------------------" << endl;
    
    mobilyaDosya.close();
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void mobilyaSil(){
    mobilyaBilgisi a;
    char silinecekId[20];
    char devam;
    bool bulundu = false;//kontol için
    bool silindi = false;// kontrol için
    
    ifstream mobilyaDosya("mobilyalar.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    
    if (!mobilyaDosya || !temp){
        cout << "|| Dosya Acýlmadý" << endl;
        return;
    }
    
    cout << "|| Lütfen silinecek olan id numarasini giriniz: ";
    cin.getline(silinecekId, 20); // id kontrol için id alýr

    while (mobilyaDosya.read((char*)&a, sizeof(mobilyaBilgisi))){
        if (strcmp(a.id, silinecekId) == 0) { // dosyadaki id ile silinecek id kontolünü yapar ve eþit ise if calýþýr *
            bulundu = true; //kontol için
            cout << "|| ----------------------" << endl;
            cout << "|| Silinecek Mobilya Bilgileri" << endl;
            cout << "|| Mobilya ismi: " << a.mobilyaAdi << endl;
            cout << "|| Mobilya id: " << a.id << endl;
            cout << "|| Mobilya stok bilgisi: " << a.stok << endl;
            cout << "|| Mobilya fiyatý: " << a.fiyat << endl;
            cout << "|| ----------------------" << endl;
            cout << "|| Ýþleme devam etmek istermisiniz (E/e H/h): ";
            cin >> devam;
            cin.ignore();
            
            if (devam == 'e' || devam == 'E'){
                silindi = true;
                // temp dosyasýna yazmýyoruz (böylece silinmiþ oluyor)
            } else {
                temp.write((char*)&a, sizeof(mobilyaBilgisi)); //iptal edilirse tekrar yazýlýr
            }
        } else{
            temp.write((char*)&a, sizeof(mobilyaBilgisi));  //tekrar yazar
        }
    }
    
    mobilyaDosya.close();
    temp.close();
    
    if (silindi){
        remove("mobilyalar.txt");
        rename("temp.txt", "mobilyalar.txt");
        cout << "|| ----------------------" << endl;
        cout << "|| Ýstenilen id bulunmuþtur" << endl; //silineni göstermek için
        cout << "|| Silme islemi gerceklesmiþtir" << endl;
        cout << "|| ----------------------" << endl;
    } else{
        remove("temp.txt");
        if (!bulundu) {
            cout << "|| Bu id mevcut deðildir." << endl;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void mobilyaDuzenle(){
    mobilyaBilgisi a;
    char duzenlenecekId[20];
    bool bulundu = false; //kontol için
    
    ifstream mobilyaDosya("mobilyalar.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    
    if (!mobilyaDosya){
        cout << "|| Dosya Acýlmadý" << endl;
        return;
    }
    
    cout << "|| Lütfen düzenlenecek olan id numarasýný giriniz: ";
    cin.getline(duzenlenecekId, 20);

    while (mobilyaDosya.read((char*)&a, sizeof(mobilyaBilgisi))) {
        if (strcmp(a.id, duzenlenecekId) == 0) { //silme ile ayný mantýkta calýþýr 
            bulundu = true;
            cout << "|| ----------------------" << endl;
            cout << "|| Düzenlenecek Mobilya Bilgileri" << endl;
            cout << "|| Mobilya ismi: " << a.mobilyaAdi << endl;
            cout << "|| Mobilya id: " << a.id << endl;
            cout << "|| Mobilya stok bilgisi: " << a.stok << endl;
            cout << "|| Mobilya fiyatý: " << a.fiyat << endl;
            cout << "|| ----------------------" << endl;
            cout << "|| MOBÝLYA BÝLGÝSÝ GÜNCELLENMESÝ " << endl;
            
            cout << "|| Lütfen mobilyanin ismini giriniz: ";
            cin.getline(a.mobilyaAdi, 100); //boþlukla beraber kullanmak için kullanýlýr yoksa boþluktan sonrakini almaz
            cout << "|| Lütfen mobilyanin id numarasini giriniz: ";
            cin.getline(a.id, 20);
            cout << "|| Lütfen mobilyanin stok bilgisini giriniz: ";
            cin >> a.stok;
            cin.ignore();
            cout << "|| Lütfen mobilyanin fiyatini giriniz: ";
            cin >> a.fiyat;
            cin.ignore();
            
            temp.write((char*)&a, sizeof(mobilyaBilgisi)); //yazar
        } else {
            temp.write((char*)&a, sizeof(mobilyaBilgisi)); //yazar
        }
    }
    
    mobilyaDosya.close();
    temp.close();
    
    if (!bulundu) {
        cout << "|| Girilen ÝD bulunamadý" << endl;
        remove("temp.txt");
        return;
    }
    
    cout << "|| Mobilya bilgileriniz güncellenmiþtir. " << endl;
    remove("mobilyalar.txt");
    rename("temp.txt", "mobilyalar.txt");
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void mobilyaListele() {
    mobilyaBilgisi a;
    ifstream mobilyaDosya("mobilyalar.txt", ios::binary);
    
    if (!mobilyaDosya) {
        cout << "|| Dosya Acýlmadý" << endl;
        return;
    }
    
    cout << "|| ----------------------" << endl;
    
    while (mobilyaDosya.read((char*)&a, sizeof(mobilyaBilgisi))) {
        cout << "|| Mobilya ismi: " << a.mobilyaAdi << endl;
        cout << "|| Mobilya id: " << a.id << endl;
        cout << "|| Mobilya stok bilgisi: " << a.stok << endl;
        cout << "|| Mobilya fiyatý: " << a.fiyat << endl;
        cout << "|| ----------------------" << endl;
    }
    
    mobilyaDosya.close();
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void musteriEkle() {
    musteriBilgisi a;
    ofstream musteriDosya("musteriler.txt", ios::app | ios::binary);
    
    if (!musteriDosya) {
        cout << "|| Dosya Acýlmadý" << endl;
        return;
    }
    
    cout << "|| Lütfen müþterinin ismini ve soy ismini giriniz: ";
    cin.getline(a.adSoyAd, 100);
    cout << "|| Lütfen müþterinin id numarasýný giriniz: ";
    cin.getline(a.id, 20);
    
    musteriDosya.write((char*)&a, sizeof(musteriBilgisi));
    
    cout << "|| ----------------------" << endl;
    cout << "|| Girdiginiz Bilgiler" << endl;
    cout << "|| Müsteri ismi: " << a.adSoyAd << endl;
    cout << "|| Müsteri id: " << a.id << endl;
    cout << "|| ----------------------" << endl;
    
    musteriDosya.close();
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void musteriListele() {
    musteriBilgisi a;
    ifstream musteriDosya("musteriler.txt", ios::binary); //binary olarak acar
    
    if (!musteriDosya) {
        cout << "|| Dosya Acýlmadý" << endl;
        return;
    }
    
    cout << "|| ----------------------" << endl;
    while (musteriDosya.read((char*)&a, sizeof(musteriBilgisi))) { //char olarak yazmasý için
        cout << "|| Müsteri ismi: " << a.adSoyAd << endl;
        cout << "|| Müsteri id: " << a.id << endl;
        cout << "|| ----------------------" << endl;
    }
    musteriDosya.close();
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void musteriSil() {
    musteriBilgisi a;
    char silinecekId[20];
    char devam;
    bool bulundu = false;
    bool silindi = false;
    
    ifstream musteriDosya("musteriler.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    
    if (!musteriDosya || !temp) {
        cout << "|| Dosya Acýlmadý" << endl;
        return;
    }
    
    cout << "|| Lütfen silinecek olan id numarasýný giriniz: ";
    cin.getline(silinecekId, 20);

    while (musteriDosya.read((char*)&a, sizeof(musteriBilgisi))) {
        if (strcmp(a.id, silinecekId) == 0) {
            bulundu = true;
            cout << "|| ----------------------" << endl;
            cout << "|| Silinecek Müþterinin Bilgileri" << endl;
            cout << "|| Müsteri ismi: " << a.adSoyAd << endl;
            cout << "|| Müsteri id: " << a.id << endl;
            cout << "|| ----------------------" << endl;
            cout << "|| Ýþleme devam etmek istermisiniz (E/e H/h): ";
            cin >> devam;
            cin.ignore();
            
            if (devam == 'e' || devam == 'E') {
                silindi = true;
            } else {
                temp.write((char*)&a, sizeof(musteriBilgisi));
            }
        } else {
            temp.write((char*)&a, sizeof(musteriBilgisi));
        }
    }
    
    musteriDosya.close();
    temp.close();
    
    if (silindi) {
        remove("musteriler.txt");
        rename("temp.txt", "musteriler.txt");
        cout << "|| ----------------------" << endl;
        cout << "|| Ýstenilen id bulunmuþtur" << endl;
        cout << "|| Silme iþlemi gercekleþtirilmiþtir" << endl;
        cout << "|| ----------------------" << endl;
    } else {
        remove("temp.txt");
        if (!bulundu) {
            cout << "|| Bu id mevcut deðildir." << endl;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void satisYap() {
    musteriBilgisi m; //okunaný tutar
    mobilyaBilgisi mob;  //yazar
    satislar s;
    char musteriIdKontrol[20], mobilyaIdKontrol[20];
    bool mBulundu = false, mobBulundu = false;  //kontol etmek için
    int adet;
    
    
    cout << "|| Lütfen Müsterinin id numarasini giriniz: "; //müþteri id konturolü için yapýlmýþtýr
    cin.getline(musteriIdKontrol, 20);
    
    ifstream mDosya("musteriler.txt", ios::binary);
    while (mDosya.read((char*)&m, sizeof(musteriBilgisi))) {
        if (strcmp(m.id, musteriIdKontrol) == 0) {
            mBulundu = true;
            break;
        }
    }
    mDosya.close(); //dosyamýz kapanýr
    
    if (!mBulundu) {
        cout << "|| Bu id numarasýna sahip müþteri yoktur." << endl; //kontol için
        return;
    }

   
    cout << "|| Lütfen mobilyaniýn id numarasýný giriniz: "; //mobilya id kontorlu için
    cin.getline(mobilyaIdKontrol, 20);
    
    ifstream mobDosya("mobilyalar.txt", ios::binary);
    while (mobDosya.read((char*)&mob, sizeof(mobilyaBilgisi))) {
        if (strcmp(mob.id, mobilyaIdKontrol) == 0) {
            mobBulundu = true; //bulunursa ture olur ve ifi calýþtýrýr
            break;
        }
    }
    mobDosya.close();
    
    if (!mobBulundu) {
        cout << "|| Bu id numarasýna sahip mobilya yoktur." << endl;
        return;
    }

    cout << "|| Lütfen satiþ adetini giriniz: ";
    cin >> adet;												// Satýþ Ýþlemi ve Stok Güncelleme
    cin.ignore();												

    ifstream mobOku("mobilyalar.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    bool stokYeterli = false;

    while (mobOku.read((char*)&mob, sizeof(mobilyaBilgisi))) {					
        if (strcmp(mob.id, mobilyaIdKontrol) == 0) {
            if (mob.stok >= adet) {					//stok kontol ve stok düþürmek ýcýn				
                mob.stok -= adet;
                stokYeterli = true;
              																	
                strcpy(s.musteriId, musteriIdKontrol);
                strcpy(s.mobilyaId, mobilyaIdKontrol); //yeni býlgýlerý kayýt alýr
                s.satisAdet = adet;
                s.total = adet * mob.fiyat;
                																
                ofstream sDosya("satislar.txt", ios::app | ios::binary);
                sDosya.write((char*)&s, sizeof(satislar));
                sDosya.close();
            } else {
                cout << "|| Yetersiz stok! Mevcut: " << mob.stok << endl;
            }
        }
        temp.write((char*)&mob, sizeof(mobilyaBilgisi));
    }
    
    mobOku.close();
    temp.close();
    
    if (stokYeterli) {
        remove("mobilyalar.txt");
        rename("temp.txt", "mobilyalar.txt");
        cout << "|| Satiþ baþariyla yapýldý." << endl;
    } else {
        remove("temp.txt");
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void satisListele() {
    satislar s;
    ifstream satisDosya("satislar.txt", ios::binary);
    
    if (!satisDosya) {
        cout << "|| Dosya Acýlmadý" << endl;
        return;
    }
    
    cout << "|| ----------------------" << endl;
    while (satisDosya.read((char*)&s, sizeof(satislar))) {
        cout << "|| Müsteri ID: " << s.musteriId << endl;
        cout << "|| Mobilya ID: " << s.mobilyaId << endl;
        cout << "|| Satiþ adedi: " << s.satisAdet << endl;
        cout << "|| Toplam tutar: " << s.total << "TL" << endl;
        cout << "|| ----------------------" << endl;
    }
    satisDosya.close();
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void aramaYap() {
    musteriBilgisi a;
    char arananId[20];
    bool bulundu = false;
    
    ifstream musteriDosya("musteriler.txt", ios::binary);
    if (!musteriDosya) {
        cout << "|| Dosya Acýlmadý" << endl;
        return;
    }
    
    cout << "|| Lütfen aramak istediðiniz müþteri id numarasýný girin: ";
    cin.getline(arananId, 20);
    
    while (musteriDosya.read((char*)&a, sizeof(musteriBilgisi))) {
        if (strcmp(a.id, arananId) == 0) {
            cout << "|| ----------------------" << endl;
            cout << "|| Aran id bulunmuþtur" << endl;
            cout << "|| Müsteri ismi: " << a.adSoyAd << endl;
            cout << "|| Müsteri id: " << a.id << endl;
            cout << "|| ----------------------" << endl;
            bulundu = true;
            break;
        }
    }
    
    if (!bulundu) {
        cout << "|| Aranan id sistemde kayýtlý deðildir " << endl;
    }
    musteriDosya.close();
}

//-------------------------------------------------------------------------------------------------------------------------------------------

int main() {
    setlocale(LC_ALL, "Turkish");
    char devam;
    
    do {
        system("cls");
        int secim, secim_2;
        
        cout << "|| MENÜ " << endl;
        cout << "||                               " << endl;
        cout << "|| 1-Mobilya iþlemleri           " << endl;
        cout << "|| 2-Müþteri iþlemleri           " << endl;
        cout << "|| 3-Satiþ iþlemleri             " << endl;
        cout << "|| 4-Arama Yap                   " << endl;
        cout << "|| 0-Cikiþ                       " << endl;
        cout << "||                               " << endl;
        cout << "|| Lütfen Yapmak Ýstediginiz Ýþlemi Seciniz: ";
        cin >> secim;
        cin.ignore();
        
        if (secim == 0) {
            cout << "|| ------------------------------------------" << endl;
            cout << "|| Bizi tercih ettiðiniz için teþekür ederiz." << endl;
            cout << "|| ------------------------------------------" << endl;
            return 0;
        }
        
        system("cls");
        
        if (secim == 1) {
            char mDevam;
            do {
                system("cls");
                cout << "|| MOBÝLYA ÝÞLEMLERÝ " << endl;
                cout << "|| 1-Mobilya Ekle" << endl;
                cout << "|| 2-Mobilya Sil" << endl;
                cout << "|| 3-Mobilya Düzenle" << endl;
                cout << "|| 4-Mobilyalarý Listele" << endl;
                cout << "|| 0-Cikiþ " << endl;
                cout << "|| Lütfen Yapmak Ýstediðiniz Ýþleimi Seciniz: ";
                cin >> secim_2;
                cin.ignore();
                
                switch (secim_2) {
                    case 1: mobilyaEkle(); break;
                    case 2: mobilyaSil(); break;
                    case 3: mobilyaDuzenle(); break;
                    case 4: mobilyaListele(); break;
                }
                if (secim_2 != 0) {
                    cout << "|| Bu menüde farklý bir iþlem yapmak istermisiniz (E/e H/h): ";
                    cin >> mDevam;
                    cin.ignore();
                } else mDevam = 'h';
            } while (mDevam == 'e' || mDevam == 'E');
        }
        else if (secim == 2) {
            char mDevam;
            do {
                system("cls");
                cout << "|| MÜSTERÝ ÝÞLEMLERÝ " << endl;
                cout << "|| 1-Müþteri Ekle" << endl;
                cout << "|| 2-Muþterileri Listele" << endl;
                cout << "|| 3-Müþteri Sil" << endl;
                cout << "|| 0-Cikiþ" << endl;
                cout << "|| Lütfen Yapmak Ýstediginiz Ýþleimi Seciniz: ";
                cin >> secim_2;
                cin.ignore();
                
                switch (secim_2) {
                    case 1: musteriEkle(); break;
                    case 2: musteriListele(); break;
                    case 3: musteriSil(); break;
                }
                if (secim_2 != 0) {
                    cout << "|| Bu menüde farklý bir iþlem yapmak istermisiniz (E/e H/h): ";
                    cin >> mDevam;
                    cin.ignore();
                } else mDevam = 'h';
            } while (mDevam == 'e' || mDevam == 'E');
        }
        else if (secim == 3) {
            char mDevam;
            do {
                system("cls");
                cout << "|| SATIÞ ÝÞLEMLERÝ " << endl;
                cout << "|| 1-Satýþ Yap" << endl;
                cout << "|| 2-Satýþlarý Listele" << endl;
                cout << "|| 0-Cikiþ" << endl;
                cout << "|| Lütfen Yapmak Ýstediginiz Ýþlemi Seciniz: ";
                cin >> secim_2;
                cin.ignore();
                
                switch (secim_2) {
                    case 1: satisYap(); break;
                    case 2: satisListele(); break;
                }
                if (secim_2 != 0) {
                    cout << "|| Bu menüde farklý bir iþlemi yapmak istermisiniz (E/e H/h): ";
                    cin >> mDevam;
                    cin.ignore();
                } else mDevam = 'h';
            } while (mDevam == 'e' || mDevam == 'E');
        }
        else if (secim == 4) {
            aramaYap();
        }

        cout << "|| Menüye dönmek istermisiniz(E/e H/h): ";
        cin >> devam;
        cin.ignore();
        
    } while (devam == 'e' || devam == 'E');
    
    return 0;
}


