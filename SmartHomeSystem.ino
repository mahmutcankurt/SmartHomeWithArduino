#include <SoftwareSerial.h> // Haberleşme için gerekli olan kütüphane.
#include <DHT.h>;           // DHT11 sensörü için gerekli olan kütüphane.

String flag;                // Bluetooth modülünden gelecek sinyalin dinlenmesi için değişken.

int relay1 = 4;             // 1 numaralı röleye ait pin.
int relay2 = 5;             // 2 numaralı röleye ait pin.
int relay3 = 6;             // 3 numaralı röleye ait pin.
float hum;                  // Nem değişkeni.
float temp;                 // Sıcaklık değişkeni.


SoftwareSerial blue(10,11); // Bluetooth modülünün TX / RX pinleri.
#define LDR 3               // LDR'nin kullanacağı pin.
#define DHTPIN 7            // DHT11'in kullanacağı pin.
#define DHTTYPE DHT11       // DHT sensörünün tanımlanması.
DHT dht(DHTPIN, DHTTYPE);   // DHT sensörünün nesne olarak oluşturulması.

void setup() {              // Kurulum fonksiyonu.
  Serial.begin(9600);       // Seri monitör baud rate tanımlaması.
  blue.begin(9600);         // Bluetooth modülü baud rate tanımlaması.
  dht.begin();              // DHT11 sensörü çalışma emri.
  pinMode(relay1, OUTPUT);  // 1 numaralı röle çalışma şekli tanımı.
  pinMode(relay2, OUTPUT);  // 2 numaralı röle çalışma şekli tanımı. 
  pinMode(relay3, OUTPUT);  // 3 numaralı röle çalışma şekli tanımı.
}

void loop() {                         // Döngü ve çalışma fonksiyonu.
   int ldr = analogRead(A0);          // LDR sensörü pin tanımlaması.
   while (Serial.available()) {       // Bluetooth sensörü dinlenmesi.
    delay(3);  
    char c = Serial.read();
    flag += c; 
  }
  
  if (flag == "1 ON")                 // 1 numaralı rölenin çalışma koşulu.
  {
    digitalWrite(relay1, HIGH);       // 1 numaralı rölenin çalışma emri.
    Serial.println("\nRELAY 1 ON");   // Seri monitöre 1 numaralı rölenin açık olduğu bilgisinin yazılması. 
    delay(2000);
    hum = dht.readHumidity();         // Nem değerinin okunması.
    temp = dht.readTemperature();     // Sıcaklık değerinin okunması.
    Serial.print("Nem: ");            // Nem değerinin yazdırılması.
    Serial.print(hum);                // Nem değeri.
    Serial.print(" %, Sıcaklık: ");   // Sıcaklık değerinin yazdırılması.
    Serial.print(temp);               // Sıcaklık değeri.
    Serial.print(" Celsius");         // Sıcaklık birimi.
    blue.print("RELAY 1 ON ");        // Bluetooth adaptörüyle bağlanılan cihaza bilginin yazdırılması.
    blue.print("Nem: ");              // Nem değerinin yazdırılması.
    blue.print(hum);                  // Nem değeri.
    blue.print(" %, Sıcaklık: ");     // Sıcaklık değerinin yazdırılması.
    blue.print(temp);                 // Sıcaklık değeri.
    blue.println(" Celsius \n");      // Sıcaklık birimi.
  }
  
  if (ldr < 850)                  // LDR'den gelen veriye göre 1 numaralı rölenin çalışma koşulu.
  {                 
    digitalWrite(relay1, HIGH);
    Serial.println("\nRELAY 1 ON");
    delay(10000);
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    Serial.print("Nem: ");
    Serial.print(hum);
    Serial.print(" %, Sıcaklık: ");
    Serial.print(temp);
    Serial.print(" Celsius");
    Serial.print("Ortam Aydınlatması Yetersiz.");
    blue.print("RELAY 1 ON ");
    blue.print("Nem: ");
    blue.print(hum);
    blue.print(" %, Sıcaklık: ");
    blue.print(temp);
    blue.println(" Celsius \n");
    blue.print("Ortam Aydınlatması Yetersiz.");
  }
  
  if (flag == "1 OFF")                 // 1 numaralı rölenin kapanma koşulu.
  {
    digitalWrite(relay1, LOW);         // 1 numaralı rölenin kapanma emri.
    Serial.println("\nRELAY 1 OFF");   // Seri monitöre 1 numaralı rölenin açık olduğu bilgisinin yazılması. 
    delay(2000);
    hum = dht.readHumidity();         // Nem değerinin okunması.
    temp = dht.readTemperature();     // Sıcaklık değerinin okunması.
    Serial.print("Nem: ");            // Nem değerinin yazdırılması.
    Serial.print(hum);                // Nem değeri.
    Serial.print(" %, Sıcaklık: ");   // Sıcaklık değerinin yazdırılması.
    Serial.print(temp);               // Sıcaklık değeri.
    Serial.print(" Celsius");         // Sıcaklık birimi.
    blue.print("RELAY 1 OFF ");       // Bluetooth adaptörüyle bağlanılan cihaza bilginin yazdırılması.
    blue.print("Nem: ");              // Nem değerinin yazdırılması.
    blue.print(hum);                  // Nem değeri.
    blue.print(" %, Sıcaklık: ");     // Sıcaklık değerinin yazdırılması.
    blue.print(temp);                 // Sıcaklık değeri.
    blue.println(" Celsius \n");      // Sıcaklık birimi.
  }
  
    if (ldr > 900)        // LDR'den gelen veriye göre 1 numaralı rölenin kapanma koşulu.
    {                 
    digitalWrite(relay1, LOW);
    Serial.println("\nRELAY 1 OFF");
    delay(10000);
    hum = dht.readHumidity();                   // Nem değerinin okunması.
    temp = dht.readTemperature();               // Sıcaklık değerinin okunması.
    Serial.print("Nem: ");                      // Nem değerinin yazdırılması.
    Serial.print(hum);                          // Nem değeri.
    Serial.print(" %, Sıcaklık: ");             // Sıcaklık değerinin yazdırılması.
    Serial.print(temp);                         // Sıcaklık değeri.
    Serial.print(" Celsius");                   // Sıcaklık birimi.
    Serial.print("Ortam Aydınlatması Güzel.");  // Seri monitöre ortam aydınlatmasının yazılması.
    blue.print("RELAY 1 OFF ");                 // Bluetooth adaptörüyle bağlanılan cihaza bilginin yazdırılması.
    blue.print("Nem: ");                        // Nem değerinin yazdırılması.
    blue.print(hum);                            // Nem değeri.
    blue.print(" %, Sıcaklık: ");               // Sıcaklık değerinin yazdırılması.
    blue.print(temp);                           // Sıcaklık değeri.
    blue.println(" Celsius \n");                // Sıcaklık birimi.
    blue.print("Ortam Aydınlatması Güzel.");    // Bluetooth adaptörüyle bağlanılan cihaza ortam aydınlatmasının yazdırılması.
  }
  
  if (flag == "2 ON")                 // 2 numaralı rölenin çalışma koşulu.     
  {
    digitalWrite(relay2, HIGH);
    Serial.println("\nRELAY 2 ON");
    delay(2000);
    hum = dht.readHumidity();         // Nem değerinin okunması.
    temp = dht.readTemperature();     // Sıcaklık değerinin okunması.
    Serial.print("Nem: ");            // Nem değerinin yazdırılması.
    Serial.print(hum);                // Nem değeri.
    Serial.print(" %, Sıcaklık: ");   // Sıcaklık değerinin yazdırılması.
    Serial.print(temp);               // Sıcaklık değeri.
    Serial.print(" Celsius");         // Sıcaklık birimi.
    blue.print("RELAY 2 ON ");        // Bluetooth adaptörüyle bağlanılan cihaza bilginin yazdırılması.
    blue.print("Nem: ");              // Nem değerinin yazdırılması.
    blue.print(hum);                  // Nem değeri.
    blue.print(" %, Sıcaklık: ");     // Sıcaklık değerinin yazdırılması.
    blue.print(temp);                 // Sıcaklık değeri.
    blue.println(" Celsius \n");      // Sıcaklık birimi.
  }
  
  if (flag == "2 OFF")                 // 2 numaralı rölenin kapanma koşulu.
  {
    digitalWrite(relay2, LOW);
    Serial.println("\nRELAY 2 OFF");
    delay(2000);
    hum = dht.readHumidity();         // Nem değerinin okunması.
    temp = dht.readTemperature();     // Sıcaklık değerinin okunması.
    Serial.print("Nem: ");            // Nem değerinin yazdırılması.
    Serial.print(hum);                // Nem değeri.
    Serial.print(" %, Sıcaklık: ");   // Sıcaklık değerinin yazdırılması.
    Serial.print(temp);               // Sıcaklık değeri.
    Serial.print(" Celsius");         // Sıcaklık birimi.
    blue.print("RELAY 2 OFF ");        // Bluetooth adaptörüyle bağlanılan cihaza bilginin yazdırılması.
    blue.print("Nem: ");              // Nem değerinin yazdırılması.
    blue.print(hum);                  // Nem değeri.
    blue.print(" %, Sıcaklık: ");     // Sıcaklık değerinin yazdırılması.
    blue.print(temp);                 // Sıcaklık değeri.
    blue.println(" Celsius \n");      // Sıcaklık birimi.
  }
  
  if (flag == "3 ON")                 // 3 numaralı rölenin çalışma koşulu.     
  {
    digitalWrite(relay3, HIGH);
    Serial.println("\nRELAY 3 ON");
    delay(2000);
    hum = dht.readHumidity();         // Nem değerinin okunması.
    temp = dht.readTemperature();     // Sıcaklık değerinin okunması.
    Serial.print("Nem: ");            // Nem değerinin yazdırılması.
    Serial.print(hum);                // Nem değeri.
    Serial.print(" %, Sıcaklık: ");   // Sıcaklık değerinin yazdırılması.
    Serial.print(temp);               // Sıcaklık değeri.
    Serial.print(" Celsius");         // Sıcaklık birimi.
    blue.print("RELAY 3 ON ");        // Bluetooth adaptörüyle bağlanılan cihaza bilginin yazdırılması.
    blue.print("Nem: ");              // Nem değerinin yazdırılması.
    blue.print(hum);                  // Nem değeri.
    blue.print(" %, Sıcaklık: ");     // Sıcaklık değerinin yazdırılması.
    blue.print(temp);                 // Sıcaklık değeri.
    blue.println(" Celsius \n");      // Sıcaklık birimi.
  }
  
  if (flag == "3 OFF")                 // 3 numaralı rölenin kapanma koşulu.
  {
    digitalWrite(relay3, LOW);
    Serial.println("\nRELAY 3 OFF");
    delay(2000);
    hum = dht.readHumidity();         // Nem değerinin okunması.
    temp = dht.readTemperature();     // Sıcaklık değerinin okunması.
    Serial.print("Nem: ");            // Nem değerinin yazdırılması.
    Serial.print(hum);                // Nem değeri.
    Serial.print(" %, Sıcaklık: ");   // Sıcaklık değerinin yazdırılması.
    Serial.print(temp);               // Sıcaklık değeri.
    Serial.print(" Celsius");         // Sıcaklık birimi.
    blue.print("RELAY 3 OFF ");       // Bluetooth adaptörüyle bağlanılan cihaza bilginin yazdırılması.
    blue.print("Nem: ");              // Nem değerinin yazdırılması.
    blue.print(hum);                  // Nem değeri.
    blue.print(" %, Sıcaklık: ");     // Sıcaklık değerinin yazdırılması.
    blue.print(temp);                 // Sıcaklık değeri.
    blue.println(" Celsius \n");      // Sıcaklık birimi.
  }

  flag = "";
}
