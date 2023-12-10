#include <ESP8266WiFi.h>
//Konfigurasi WiFi
const char *ssid = "Desember kita";
const char *password = "235689124";
//IP Address Server yang terpasang XAMPP
const char *host = "agusti-kalkulator.000webhostapp.com"; //sesuaikan
void setup() {
 Serial.begin(115200);
 pinMode(D0, OUTPUT);
 pinMode(D1, OUTPUT);
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 Serial.println("");
 Serial.print("Connecting");
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 //Jika koneksi berhasil, maka akan muncul address di serial monitor
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
}
int value = 0;
void loop() {
  String line;
 // Proses Pengiriman -----------------------------------------------------------
 delay(1000);
 value++;
 // Membaca Sensor Analog -------------------------------------------------------
//  int datasensor  = analogRead(A0);
//  int datasensor2  = analogRead(D0);
//  int maping = map(datasensor2,0,1023,0,1);
//  Serial.println(datasensor);
//  Serial.println(maping);
 Serial.print("connecting to ");
 Serial.println(host);
// Mengirimkan ke alamat host dengan port 80 -----------------------------------
 WiFiClient client1;
//  WiFiClient client2;
 const int httpPort = 80;
 if (!client1.connect(host, httpPort)) {
 Serial.println("connection to write-data failed");
  return;
 }
// Isi Konten yang dikirim adalah alamat ip si esp -----------------------------
  String url = "/kendali.php"; //write-data?data1=
  // url += datasensor;
  // url += "&data2=";
  // url += maping;
   Serial.print("Requesting URL (kendali.php): ");
    Serial.println(url);

    // Mengirimkan Request ke Server -----------------------------------------------
      client1.print(String("GET ") + url + " HTTP/1.1\r\n" +
      "Host: " + host + "\r\n" +
      "Connection: close\r\n\r\n");
                     

     unsigned long timeout = millis();
      while (client1.available() == 0) {
          if (millis() - timeout > 1000) {
          Serial.println(">>> Client Timeout !");
          client1.stop();
          return;
          }
      }
    String rServer;
    int hitung = 0;
    // Tunggu respons dari server dan cetak ke Serial Monitor
    while (client1.available()) {
         line = client1.readStringUntil('\r');
        line.trim();  // Menghapus spasi di awal dan akhir string

        
        // Serial.println(line);
        hitung++;
        if(hitung == 12){
          Serial.print("Received line: ");
          Serial.println(line);
          rServer = line;
        }
      
       
    }

   
    client1.stop();


    //  if (!client2.connect(host, httpPort)) {
    //     Serial.println("connection to write-data failed");
    //       return;
    //   }
    // // Isi Konten yang dikirim adalah alamat ip si esp -----------------------------
    //   String url2 = "/datasensor/write-data.php?data1="; //write-data?data1=
    //   url2 += datasensor;
    //   url2 += "&data2=";
    //   url2 += maping;
    //   Serial.print("Requesting URL (write-data.php): ");
    //   Serial.println(url2);

    // // Mengirimkan Request ke Server -----------------------------------------------
    //   client2.print(String("GET ") + url2 + " HTTP/1.1\r\n" +
    //   "Host: " + host + "\r\n" +
    //   "Connection: close\r\n\r\n");
                     

    //  unsigned long timeout2 = millis();
    //   while (client2.available() == 0) {
    //       if (millis() - timeout2 > 1000) {
    //       Serial.println(">>> Client Timeout !");
    //       client2.stop();
    //       return;
    //       }
    //   }


    // // Tunggu respons dari server dan cetak ke Serial Monitor
    // while (client2.available()) {
    //     String line2 = client2.readStringUntil('\r');
    //     Serial.print("Data dari server (kendali.php): " + line2);
    // }
    // client2.stop();
  int lampu1 = getValue(rServer, ';', 0).toInt();
  int lampu2 = getValue(rServer, ';', 1).toInt();

  if(lampu1 == 1){
    Serial.println("Lampu satu Nyala");
    digitalWrite(D0, HIGH);
  }else{
    Serial.println("Lampu satu Mati");
    digitalWrite(D0, LOW);
  }

  if(lampu2 == 1){
    Serial.println("Lampu dua Nyala");
    digitalWrite(D1, HIGH);

  }else{
    Serial.println("Lampu dua Mati");
    digitalWrite(D1, HIGH);
  }
   

 Serial.println();
 Serial.println("closing connection");
}

//parsing data
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}