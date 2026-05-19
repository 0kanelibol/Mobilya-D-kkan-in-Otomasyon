#include <iostream>
#include <locale.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;



//-------------------------------------------------------------------------------------------------------------------------------------------

struct musteriBilgisi { 
    char adSoyAd[100]; // string kullanamıyoz cünkü binarry
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
    int satisAdet; // hesaplama kolaylığı için int yapıldı
    int total;
};

//-------------------------------------------------------------------------------------------------------------------------------------------

void mobilyaEkle(){
    mobilyaBilgisi a;
    ofstream mobilyaDosya;
    mobilyaDosya.open("mobilyalar.txt", ios::app | ios::binary); // dosyayı acar ve kaydeder 
    
    if (!mobilyaDosya){
        cout << "|| Dosya Acılamadı" << endl; // dosya acılmaz ise ekrana yazı cıkartır
        return;
    }
    
   	
    cout << "|| Lütfen mobilyanın adını giriniz: ";
	cin.getline(a.mobilyaAdi, 100);
    
    cout << "|| Lütfen mobilyanın id numarasını giriniz: ";
    cin.getline(a.id, 20);
    
    cout << "|| Lütfen mobilyanın stok bilgisini giriniz: ";
    cin >> a.stok;
    cin.ignore(); //cini temizler
    
    cout << "|| Lütfen mobilyanın fiyatını giriniz: ";
    cin >> a.fiyat;
    cin.ignore();
    
    mobilyaDosya.write((char*)&a, sizeof(mobilyaBilgisi));   // binary olarak structı tek seferde yazıyoruz yoksa sıkıntı oluyo
    
    cout << "|| ----------------------" << endl;
    cout << "|| Girdiğiniz Bilgiler" << endl;
    cout << "|| Mobilya ismi: " << a.mobilyaAdi << endl;
    cout << "|| Mobilya id: " << a.id << endl;
    cout << "|| Mobilya stok bilgisi: " << a.stok << endl;
    cout << "|| Mobilya fiyatı: " << a.fiyat << "TL" << endl;
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
        cout << "|| Dosya Acılmadı" << endl;
        return;
    }
    
    cout << "|| Lütfen silinecek olan id numarasini giriniz: ";
    cin.getline(silinecekId, 20); // id kontrol için id alır

    while (mobilyaDosya.read((char*)&a, sizeof(mobilyaBilgisi))){
        if (strcmp(a.id, silinecekId) == 0) { // dosyadaki id ile silinecek id kontolünü yapar ve eşit ise if calışır *
            bulundu = true; //kontol için
            cout << "|| ----------------------" << endl;
            cout << "|| Silinecek Mobilya Bilgileri" << endl;
            cout << "|| Mobilya ismi: " << a.mobilyaAdi << endl;
            cout << "|| Mobilya id: " << a.id << endl;
            cout << "|| Mobilya stok bilgisi: " << a.stok << endl;
            cout << "|| Mobilya fiyatı: " << a.fiyat << endl;
            cout << "|| ----------------------" << endl;
            cout << "|| İşleme devam etmek istermisiniz (E/e H/h): ";
            cin >> devam;
            cin.ignore();
            
            if (devam == 'e' || devam == 'E'){
                silindi = true;
                // temp dosyasına yazmıyoruz (böylece silinmiş oluyor)
            } else {
                temp.write((char*)&a, sizeof(mobilyaBilgisi)); //iptal edilirse tekrar yazılır
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
        cout << "|| İstenilen id bulunmuştur" << endl; //silineni göstermek için
        cout << "|| Silme islemi gerceklesmiştir" << endl;
        cout << "|| ----------------------" << endl;
    } else{
        remove("temp.txt");
        if (!bulundu) {
            cout << "|| Bu id mevcut değildir." << endl;
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
        cout << "|| Dosya Acılmadı" << endl;
        return;
    }
    
    cout << "|| Lütfen düzenlenecek olan id numarasını giriniz: ";
    cin.getline(duzenlenecekId, 20);

    while (mobilyaDosya.read((char*)&a, sizeof(mobilyaBilgisi))) {
        if (strcmp(a.id, duzenlenecekId) == 0) { //silme ile aynı mantıkta calışır 
            bulundu = true;
            cout << "|| ----------------------" << endl;
            cout << "|| Düzenlenecek Mobilya Bilgileri" << endl;
            cout << "|| Mobilya ismi: " << a.mobilyaAdi << endl;
            cout << "|| Mobilya id: " << a.id << endl;
            cout << "|| Mobilya stok bilgisi: " << a.stok << endl;
            cout << "|| Mobilya fiyatı: " << a.fiyat << endl;
            cout << "|| ----------------------" << endl;
            cout << "|| MOBİLYA BİLGİSİ GÜNCELLENMESİ " << endl;
            
            cout << "|| Lütfen mobilyanin ismini giriniz: ";
            cin.getline(a.mobilyaAdi, 100); //boşlukla beraber kullanmak için kullanılır yoksa boşluktan sonrakini almaz
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
        cout << "|| Girilen İD bulunamadı" << endl;
        remove("temp.txt");
        return;
    }
    
    cout << "|| Mobilya bilgileriniz güncellenmiştir. " << endl;
    remove("mobilyalar.txt");
    rename("temp.txt", "mobilyalar.txt");
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void mobilyaListele() {
    mobilyaBilgisi a;
    ifstream mobilyaDosya("mobilyalar.txt", ios::binary);
    
    if (!mobilyaDosya) {
        cout << "|| Dosya Acılmadı" << endl;
        return;
    }
    
    cout << "|| ----------------------" << endl;
    
    while (mobilyaDosya.read((char*)&a, sizeof(mobilyaBilgisi))) {
        cout << "|| Mobilya ismi: " << a.mobilyaAdi << endl;
        cout << "|| Mobilya id: " << a.id << endl;
        cout << "|| Mobilya stok bilgisi: " << a.stok << endl;
        cout << "|| Mobilya fiyatı: " << a.fiyat << endl;
        cout << "|| ----------------------" << endl;
    }
    
    mobilyaDosya.close();
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void musteriEkle() {
    musteriBilgisi a;
    ofstream musteriDosya("musteriler.txt", ios::app | ios::binary);
    
    if (!musteriDosya) {
        cout << "|| Dosya Acılmadı" << endl;
        return;
    }
    
    cout << "|| Lütfen müşterinin ismini ve soy ismini giriniz: ";
    cin.getline(a.adSoyAd, 100);
    cout << "|| Lütfen müşterinin id numarasını giriniz: ";
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
        cout << "|| Dosya Acılmadı" << endl;
        return;
    }
    
    cout << "|| ----------------------" << endl;
    while (musteriDosya.read((char*)&a, sizeof(musteriBilgisi))) { //char olarak yazması için
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
        cout << "|| Dosya Acılmadı" << endl;
        return;
    }
    
    cout << "|| Lütfen silinecek olan id numarasını giriniz: ";
    cin.getline(silinecekId, 20);

    while (musteriDosya.read((char*)&a, sizeof(musteriBilgisi))) {
        if (strcmp(a.id, silinecekId) == 0) {
            bulundu = true;
            cout << "|| ----------------------" << endl;
            cout << "|| Silinecek Müşterinin Bilgileri" << endl;
            cout << "|| Müsteri ismi: " << a.adSoyAd << endl;
            cout << "|| Müsteri id: " << a.id << endl;
            cout << "|| ----------------------" << endl;
            cout << "|| İşleme devam etmek istermisiniz (E/e H/h): ";
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
        cout << "|| İstenilen id bulunmuştur" << endl;
        cout << "|| Silme işlemi gercekleştirilmiştir" << endl;
        cout << "|| ----------------------" << endl;
    } else {
        remove("temp.txt");
        if (!bulundu) {
            cout << "|| Bu id mevcut değildir." << endl;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void satisYap() {
    musteriBilgisi m; //okunanı tutar
    mobilyaBilgisi mob;  //yazar
    satislar s;
    char musteriIdKontrol[20], mobilyaIdKontrol[20];
    bool mBulundu = false, mobBulundu = false;  //kontol etmek için
    int adet;
    
    
    cout << "|| Lütfen Müsterinin id numarasini giriniz: "; //müşteri id konturolü için yapılmıştır
    cin.getline(musteriIdKontrol, 20);
    
    ifstream mDosya("musteriler.txt", ios::binary);
    while (mDosya.read((char*)&m, sizeof(musteriBilgisi))) {
        if (strcmp(m.id, musteriIdKontrol) == 0) {
            mBulundu = true;
            break;
        }
    }
    mDosya.close(); //dosyamız kapanır
    
    if (!mBulundu) {
        cout << "|| Bu id numarasına sahip müşteri yoktur." << endl; //kontol için
        return;
    }

   
    cout << "|| Lütfen mobilyaniın id numarasını giriniz: "; //mobilya id kontorlu için
    cin.getline(mobilyaIdKontrol, 20);
    
    ifstream mobDosya("mobilyalar.txt", ios::binary);
    while (mobDosya.read((char*)&mob, sizeof(mobilyaBilgisi))) {
        if (strcmp(mob.id, mobilyaIdKontrol) == 0) {
            mobBulundu = true; //bulunursa ture olur ve ifi calıştırır
            break;
        }
    }
    mobDosya.close();
    
    if (!mobBulundu) {
        cout << "|| Bu id numarasına sahip mobilya yoktur." << endl;
        return;
    }

    cout << "|| Lütfen satiş adetini giriniz: ";
    cin >> adet;												// Satış İşlemi ve Stok Güncelleme
    cin.ignore();												

    ifstream mobOku("mobilyalar.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    bool stokYeterli = false;

    while (mobOku.read((char*)&mob, sizeof(mobilyaBilgisi))) {					
        if (strcmp(mob.id, mobilyaIdKontrol) == 0) {
            if (mob.stok >= adet) {					//stok kontol ve stok düşürmek ıcın				
                mob.stok -= adet;
                stokYeterli = true;
              																	
                strcpy(s.musteriId, musteriIdKontrol);
                strcpy(s.mobilyaId, mobilyaIdKontrol); //yeni bılgılerı kayıt alır
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
        cout << "|| Satiş başariyla yapıldı." << endl;
    } else {
        remove("temp.txt");
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void satisListele() {
    satislar s;
    ifstream satisDosya("satislar.txt", ios::binary);
    
    if (!satisDosya) {
        cout << "|| Dosya Acılmadı" << endl;
        return;
    }
    
    cout << "|| ----------------------" << endl;
    while (satisDosya.read((char*)&s, sizeof(satislar))) {
        cout << "|| Müsteri ID: " << s.musteriId << endl;
        cout << "|| Mobilya ID: " << s.mobilyaId << endl;
        cout << "|| Satiş adedi: " << s.satisAdet << endl;
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
        cout << "|| Dosya Acılmadı" << endl;
        return;
    }
    
    cout << "|| Lütfen aramak istediğiniz müşteri id numarasını girin: ";
    cin.getline(arananId, 20);
    
    while (musteriDosya.read((char*)&a, sizeof(musteriBilgisi))) {
        if (strcmp(a.id, arananId) == 0) {
            cout << "|| ----------------------" << endl;
            cout << "|| Aran id bulunmuştur" << endl;
            cout << "|| Müsteri ismi: " << a.adSoyAd << endl;
            cout << "|| Müsteri id: " << a.id << endl;
            cout << "|| ----------------------" << endl;
            bulundu = true;
            break;
        }
    }
    
    if (!bulundu) {
        cout << "|| Aranan id sistemde kayıtlı değildir " << endl;
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
        cout << "|| 1-Mobilya işlemleri           " << endl;
        cout << "|| 2-Müşteri işlemleri           " << endl;
        cout << "|| 3-Satiş işlemleri             " << endl;
        cout << "|| 4-Arama Yap                   " << endl;
        cout << "|| 0-Cikiş                       " << endl;
        cout << "||                               " << endl;
        cout << "|| Lütfen Yapmak İstediginiz İşlemi Seciniz: ";
        cin >> secim;
        cin.ignore();
        
        if (secim == 0) {
            cout << "|| ------------------------------------------" << endl;
            cout << "|| Bizi tercih ettiğiniz için teşekür ederiz." << endl;
            cout << "|| ------------------------------------------" << endl;
            return 0;
        }
        
        system("cls");
        
        if (secim == 1) {
            char mDevam;
            do {
                system("cls");
                cout << "|| MOBİLYA İŞLEMLERİ " << endl;
                cout << "|| 1-Mobilya Ekle" << endl;
                cout << "|| 2-Mobilya Sil" << endl;
                cout << "|| 3-Mobilya Düzenle" << endl;
                cout << "|| 4-Mobilyaları Listele" << endl;
                cout << "|| 0-Cikiş " << endl;
                cout << "|| Lütfen Yapmak İstediğiniz İşleimi Seciniz: ";
                cin >> secim_2;
                cin.ignore();
                
                switch (secim_2) {
                    case 1: mobilyaEkle(); break;
                    case 2: mobilyaSil(); break;
                    case 3: mobilyaDuzenle(); break;
                    case 4: mobilyaListele(); break;
                }
                if (secim_2 != 0) {
                    cout << "|| Bu menüde farklı bir işlem yapmak istermisiniz (E/e H/h): ";
                    cin >> mDevam;
                    cin.ignore();
                } else mDevam = 'h';
            } while (mDevam == 'e' || mDevam == 'E');
        }
        else if (secim == 2) {
            char mDevam;
            do {
                system("cls");
                cout << "|| MÜSTERİ İŞLEMLERİ " << endl;
                cout << "|| 1-Müşteri Ekle" << endl;
                cout << "|| 2-Muşterileri Listele" << endl;
                cout << "|| 3-Müşteri Sil" << endl;
                cout << "|| 0-Cikiş" << endl;
                cout << "|| Lütfen Yapmak İstediginiz İşleimi Seciniz: ";
                cin >> secim_2;
                cin.ignore();
                
                switch (secim_2) {
                    case 1: musteriEkle(); break;
                    case 2: musteriListele(); break;
                    case 3: musteriSil(); break;
                }
                if (secim_2 != 0) {
                    cout << "|| Bu menüde farklı bir işlem yapmak istermisiniz (E/e H/h): ";
                    cin >> mDevam;
                    cin.ignore();
                } else mDevam = 'h';
            } while (mDevam == 'e' || mDevam == 'E');
        }
        else if (secim == 3) {
            char mDevam;
            do {
                system("cls");
                cout << "|| SATIŞ İŞLEMLERİ " << endl;
                cout << "|| 1-Satış Yap" << endl;
                cout << "|| 2-Satışları Listele" << endl;
                cout << "|| 0-Cikiş" << endl;
                cout << "|| Lütfen Yapmak İstediginiz İşlemi Seciniz: ";
                cin >> secim_2;
                cin.ignore();
                
                switch (secim_2) {
                    case 1: satisYap(); break;
                    case 2: satisListele(); break;
                }
                if (secim_2 != 0) {
                    cout << "|| Bu menüde farklı bir işlemi yapmak istermisiniz (E/e H/h): ";
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


