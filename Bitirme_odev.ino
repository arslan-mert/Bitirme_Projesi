#include<LiquidCrystal.h>                // 2 x 16 lcd ekran kütüphanesi eklenmesi.
LiquidCrystal lcd(12 , 11, 2, 3, 4, 10); // RS = 12 nolu pin ,  E = 11 nolu pin ,  d4 = 2 nolu pin , d5 = 3 nolu pin , d6 = 4 nolu pin , d7 = 10 nolu pine Arduino'nun baglandı.
int lm35Pin_Esanjor = A0;                // LM35 Esanjor sıcaklık sensörünün çıkışını Arduino'nun analog A0 pinine bagladık.
int lm35Pin_Panel = A1;                  // LM35 Panel sıcaklık sensörünün çıkışını Arduino'nun analog A1 pinine bagladık.
int relay = 8 ;                          //  Arduino'nun 8 nolu bacagını led adlı degişkene atadık.
int zaman = 1000 ;                       // 1s bekle
int okunan_deger_Esanjor = 0;            // Esanjör'ün sıcaklık sensörünün çıkış degişkenini tanımladık.(0-1023 arasında)
float sicaklik_gerilim_Esanjor = 0;      // Esanjör'ün Analog degerinin gerilim cinsinden tanımlama degişkeni 
float sicaklik_Esanjor = 0;              // Esanjör 'ün sıcaklık degeri degişkenin tanımlanması
int okunan_deger_Panel = 0;              // Panel'in sıcaklık sensörünün çıkış degişkenini tanımladık.(0-1023 arasında)
float sicaklik_gerilim_Panel = 0;        // Esanjör'ün Analog degerinin gerilim cinsinden tanımlama degişkeni 
float sicaklik_Panel = 0;                // Panel'in sıcaklık degeri degişkenin tanımlanması.
float sicaklik_Fark ;                    // Sıcaklık farkının tanımlanması (Panel-Esanjör) 
#define arttir 6                         // Sıcaklık ayar arttırma butonu 6 numaralı pin tanımlandı
#define azalt 7                          // Sıcaklık ayar azaltma butonu 7 numaralı pin tanımlandı 
float ayar = 4;                          // Sıcaklık ayarı  4 dereceye ayarlandı (Başlangıç)
void setup()
{
pinMode(relay,OUTPUT);                   // 8 nolu bacak çıkış oluyor 
pinMode(lm35Pin_Esanjor, INPUT);         // AO nolu bacak giriş Esanjör sıcaklık girişi (0 -1023 arasında)
pinMode(lm35Pin_Panel, INPUT);           // A1 nolu bacak giriş Panel  sıcaklık girişi   (0 -1023 arasında)
pinMode(arttir,INPUT_PULLUP);            // Arduino'unun 6 numaralı pini sıcaklık arttır ayar butonu
pinMode(azalt,INPUT_PULLUP);             // Arduino'nun  7 numaralı pini  sıcaklık azaltma ayar butonu
Serial.begin(9600);                      // seri haberleşme ve hızı
lcd.begin(16, 2);                        // 16 sütün ve 2 satırdan oluştugu fonksiyonla yazıldı.
}

void loop()
{
if(digitalRead(arttir)== 0){             // eger 6 nolu terminalden pull_up baglı butonu basılırsa lojik 0 okunursa ayar derecesini 1 arttır.
  ayar = ayar + 1;                       // ayar derecesinin 1 derece arttırılması.
  delay(250);                            // 250 ms gecikme.
}
else if(digitalRead(azalt)== 0){         // eger 7 nolu terminelden azalt butonuna basıldıgında lojik 0 okunursa ayar derecesini 1 azalt.
  ayar = ayar - 1 ;                      // ayar derecesinin 1 azaltılması.
  delay (250);                           // 250 ms gecikme.
} 


okunan_deger_Esanjor = analogRead(lm35Pin_Esanjor);              // Esanjör'e ait lm35 sıcaklık sensörünün okunması  A0 okunuyor.
sicaklik_gerilim_Esanjor = (okunan_deger_Esanjor / 1023.0)*5000; // Esanjör'e ait lm35 sıcaklık sensöründen okunan verinin gerilime dönüştürülmesi
sicaklik_Esanjor = sicaklik_gerilim_Esanjor /10.0;               // Gerilime dönüştürülen verinin 10mV cinsinden sıcaklık karşılığı.(Esanjor'ün)
delay(zaman);                                                    // 1sn bekle sonra panel'in sıcaklığını oku.
okunan_deger_Panel = analogRead(lm35Pin_Panel);                  // Panel'e ait lm35 sıcaklık sensörünün okunması  A1 okunuyor. 
sicaklik_gerilim_Panel = (okunan_deger_Panel / 1023.0)*5000;     // Panel'e ait lm35 sıcaklık sensöründen okunan verinin gerilime dönüştürülmesi 
sicaklik_Panel = sicaklik_gerilim_Panel / 10.0 ;                 // Gerilime dönüştürülen verinin 10mV cinsinden sıcaklık karşılığı. (Panel'in)

sicaklik_Fark = sicaklik_Panel-sicaklik_Esanjor;                 // panel sıcaklıgından Esanjordeki sıcaklığın çıkarılması.

Serial.print("panel'in sıcaklık degeri : ");                     // panel sıcaklıgının serial port ekranına  gönderilmesi(bilgisayar ekranında gözükmesi)
Serial.println(sicaklik_Panel);                                  // panel sıcaklıgının ekrana bastırılması.
Serial.print("Eşanjörün sıcaklık degeri : ");                    // eşenjör sıcaklıgının serial port ekranına  gönderilmesi.
Serial.println(sicaklik_Esanjor);                                // eşenjör sıcaklıgının bilgisayar ekranına bastırılması.
Serial.print("Sıcaklık farkı : ");                               // sıcaklık farkının serial port ekranına gönderilmesi
Serial.println(sicaklik_Fark);                                   // sıcaklık farkının bilgisayar ekranında gözükmesi  
Serial.print("sıcaklık ayarı : ");                               // sıcaklık ayarının serial port ekranına  bastırılması.
Serial.println(ayar);                                            // sıcaklık ayar 'ın bilgisayarda gözükmesi.

lcd.clear();                                                     // LCD ekran temizlendi.
lcd.home();                                                      // LCD ekran'daki imlec sol üst köşeye taşındı (0 0 boyut olarak)
lcd.print("Fark:");                                              // panel sıcaklıgından eşenjor sıcaklıgının farkının lcd bastırılması
lcd.setCursor(5 , 0 );                                           // yazı yazmak istedigimizde imleci istedigimiz yere koyan komut o.sütün 1. satıra imlec yerleştirildi.
lcd.print(sicaklik_Fark);                                        // LCD ekrana farkın sayısal olarak bastırılması .
lcd.print("  C ");                                               // LCD ekrana C(cantigrat yazılması).
lcd.setCursor(0 , 2);                                            // LCD ekranın imleci 0.satır 2.sütüna getirildi.
lcd.print("Ayar: ");                                             // Derece ile sıcaklık farkının ayarlanması yazıldı LCD 'ye.
lcd.print(ayar);                                                 // Ayar degişkeninin bastırılması.
lcd.print("  C");                                                // C ekrana basıldı.
delay(1000);                                                     // 1 sn bekle ekran titremesin.

if(sicaklik_Fark > ayar  ){                                      // Sıcaklık farkı ayar 'dan büyük ise röle çıkış versin.
digitalWrite(relay,HIGH);
}
else{                                                            // Sıcaklık farkı ayar'dan küçük veya eşit ise röle çıkış vermesin.
digitalWrite(relay, LOW);

}
delay(500);

}
