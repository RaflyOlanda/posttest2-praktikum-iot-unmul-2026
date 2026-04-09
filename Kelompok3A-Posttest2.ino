#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <DHT.h>


const char* ssid = "Universitas Mulawarman";
const char* password = "";
#define BOT_TOKEN "8750196555:AAHZ5roTffXUNRUK0BbmUd0ZYVfwtIa3kDU"


String USER_A_ID = "2088834262"; 
String USER_B_ID = "5882221433"; 
String USER_C_ID = "5253693868"; 
String GROUP_ID  = "-1003576559597"; 


#define LED_UTAMA 20
#define LED_A 8
#define LED_B 9
#define LED_C 21

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ2PIN 1 
int gasThreshold = 1500; 
bool gasWarningSent = false;


WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
unsigned long lastGasCheck;


void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id; 
    String from_id = bot.messages[i].from_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;

    if (from_name == "") from_name = "guest";

    
    if (text == "/start") {
      String welcome = "selamat datang di sistem smart house, " + from_name + ".\n";
      welcome += "silakan gunakan menu command untuk mengontrol perangkat atau mengecek status sensor\n";
      welcome += "/ledutama_on - Nyalakan LED Ruang Tamu\n";
      welcome += "/leda_on - Nyalakan Lampu di kamar A (khusus A)\n";
      welcome += "/leda_off - Matikan Lampu di kamar A (khusus A)\n";
      welcome += "/ledb_on - Nyalakan Lampu di kamar B (khusus B)\n";
      welcome += "/ledb_off - Matikan Lampu di kamar B (khusus B)\n";
      welcome += "/ledc_on - Nyalakan Lampu di kamar C (khusus C)\n";
      welcome += "/ledb_off - Matikan Lampu di kamar C (khusus C).";
      bot.sendMessage(chat_id, welcome, "");
    }

    
    else if (text == "/ledutama_on@posttest2AK3_bot") {
      digitalWrite(LED_UTAMA, HIGH);
      bot.sendMessage(chat_id, "lampu ruang tamu dinyalakan oleh " + from_name + ".", "");
    }
    else if (text == "/ledutama_off@posttest2AK3_bot") {
      digitalWrite(LED_UTAMA, LOW);
      bot.sendMessage(chat_id, "lampu ruang tamu dimatikan oleh " + from_name + ".", "");
    }

    // kontrol lampu kamar a, akses divalidasi khusus untuk anggota a
    else if (text == "/leda_on@posttest2AK3_bot") {
      if (from_id == USER_A_ID) {
        digitalWrite(LED_A, HIGH);
        bot.sendMessage(chat_id, "lampu kamar a menyala.", "");
      } else {
        bot.sendMessage(chat_id, "akses ditolak. " + from_name + " tidak memiliki izin untuk menyalakan lampu kamar a.", "");
      }
    }
    else if (text == "/leda_off@posttest2AK3_bot") {
      if (from_id == USER_A_ID) {
        digitalWrite(LED_A, LOW);
        bot.sendMessage(chat_id, "lampu kamar a mati.", "");
      } else {
        bot.sendMessage(chat_id, "akses ditolak. " + from_name + " tidak memiliki izin untuk mematikan lampu kamar a.", "");
      }
    }

    
    else if (text == "/ledb_on@posttest2AK3_bot") {
      if (from_id == USER_B_ID) {
        digitalWrite(LED_B, HIGH);
        bot.sendMessage(chat_id, "lampu kamar b menyala.", "");
      } else {
        bot.sendMessage(chat_id, "akses ditolak. " + from_name + " tidak memiliki izin untuk menyalakan lampu kamar b.", "");
      }
    }
    else if (text == "/ledb_off@posttest2AK3_bot") {
      if (from_id == USER_B_ID) {
        digitalWrite(LED_B, LOW);
        bot.sendMessage(chat_id, "lampu kamar b mati.", "");
      } else {
        bot.sendMessage(chat_id, "akses ditolak. " + from_name + " tidak memiliki izin untuk mematikan lampu kamar b.", "");
      }
    }

    
    else if (text == "/ledc_on@posttest2AK3_bot") {
      if (from_id == USER_C_ID) {
        digitalWrite(LED_C, HIGH);
        bot.sendMessage(chat_id, "lampu kamar c menyala.", "");
      } else {
        bot.sendMessage(chat_id, "akses ditolak. " + from_name + " tidak memiliki izin untuk menyalakan lampu kamar c.", "");
      }
    }
    else if (text == "/ledc_off@posttest2AK3_bot") {
      if (from_id == USER_C_ID) {
        digitalWrite(LED_C, LOW);
        bot.sendMessage(chat_id, "lampu kamar c mati.", "");
      } else {
        bot.sendMessage(chat_id, "akses ditolak. " + from_name + " tidak memiliki izin untuk mematikan lampu kamar c.", "");
      }
    }

    
    else if (text == "/status@posttest2AK3_bot") {
      float t = dht.readTemperature();
      float h = dht.readHumidity();
      int gasValue = analogRead(MQ2PIN);

      if (isnan(t) || isnan(h)) {
        bot.sendMessage(chat_id, "sistem gagal membaca data dari sensor suhu.", "");
        return;
      }

      String statusMsg = "status pemantauan smart house:\n\n";
      statusMsg += "suhu ruangan: " + String(t) + " derajat celcius\n";
      statusMsg += "kelembapan: " + String(h) + " %\n";
      statusMsg += "pembacaan sensor gas: " + String(gasValue) + " (ambang batas normal: " + String(gasThreshold) + ")\n";
      
      if(gasValue > gasThreshold) {
         statusMsg += "\nperingatan: terdeteksi indikasi kebocoran gas di atas ambang batas normal.";
      } else {
         statusMsg += "\nkondisi udara terpantau normal dan aman.";
      }

      bot.sendMessage(chat_id, statusMsg, "");
    }
  }
}

void setup() {
  Serial.begin(115200);

  
  pinMode(LED_UTAMA, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  
  
  digitalWrite(LED_UTAMA, LOW);
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_C, LOW);

  dht.begin();

  
  Serial.print("sedang menghubungkan ke jaringan wifi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nperangkat berhasil terhubung ke jaringan.");
}

void loop() {
  
  if (millis() > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("memproses pesan baru yang masuk.");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  
  if (millis() > lastGasCheck + 2000) {
    int gasValue = analogRead(MQ2PIN);
    
    
    if (gasValue > gasThreshold && !gasWarningSent) {
      String warningMsg = "peringatan darurat.\n\nsensor mendeteksi kadar gas atau asap yang tinggi di ruangan.\npembacaan saat ini: " + String(gasValue) + "\n\nharap segera melakukan pemeriksaan di lokasi.";
      bot.sendMessage(GROUP_ID, warningMsg, ""); 
      gasWarningSent = true; 
      Serial.println("pesan peringatan gas berhasil dikirim ke grup.");
    } 
    
    else if (gasValue < (gasThreshold - 300) && gasWarningSent) {
      bot.sendMessage(GROUP_ID, "informasi pembaruan: kadar gas terpantau sudah kembali normal di bawah ambang batas.", "");
      gasWarningSent = false;
    }
    
    lastGasCheck = millis();
  }
}