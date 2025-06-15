#include <Arduino.h>
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>

// ========== CONFIGURAÇÕES ========== //
const char* ssid = "rpi";
const char* password = "12345678";
const char* server = "192.168.10.148";  
const int port = 8000;

// Configuração da Matriz LED
#define MATRIX_PIN 5      
#define MATRIX_WIDTH 16   
#define MATRIX_HEIGHT 16  
#define BRIGHTNESS 50     
// ========== INICIALIZAÇÃO ========== //
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
  MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800);
void connectToWiFi();
void startupAnimation();
void fetchAndDisplayPattern();
void showErrorAnimation();
// ========== SETUP ========== //
void setup() {
  Serial.begin(115200);
  while (!Serial);  

  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  matrix.fillScreen(0);
  matrix.show();
 
  startupAnimation();
  
  connectToWiFi();
}

// ========== LOOP PRINCIPAL ========== //
void loop() {
  static unsigned long lastUpdate = 0;
  const unsigned long updateInterval = 10;  
  
  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();
    
    if (WiFi.status() == WL_CONNECTED) {
      fetchAndDisplayPattern();
    } else {
      Serial.println("WiFi desconectado. Reconectando...");
      connectToWiFi();
    }
  }
}

// ========== FUNÇÕES ========== //


void connectToWiFi() {
  Serial.print("Conectando a ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    matrix.drawPixel(random(MATRIX_WIDTH), random(MATRIX_HEIGHT), matrix.Color(0, 0, 50));
    matrix.show();
  }
  
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  matrix.fillScreen(0);
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    matrix.drawPixel(i, i, matrix.Color(0, 50, 0));
    matrix.show();
    delay(50);
  }
}

void fetchAndDisplayPattern() {
  WiFiClient client;
  Serial.println("Conectando ao servidor...");
  
  if (client.connect(server, port)) {
    Serial.println("Conectado! Enviando requisição...");

    client.println("GET /api/designs/current_display/ HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Connection: close");
    client.println();

    bool jsonStarted = false;
    String payload;
    
    while (client.connected() || client.available()) {
      String line = client.readStringUntil('\n');
      
      if (line.startsWith("{")) {
        jsonStarted = true;
      }
      
      if (jsonStarted) {
        payload += line;
      }
      
      if (line == "\r" && !jsonStarted) {
        jsonStarted = true; 
      }
      
      if (!client.available() && jsonStarted) {
        break;
      }
    }
    
    client.stop();
    Serial.println("Resposta recebida:");
    Serial.println(payload);

    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, payload);
    
    if (error) {
      Serial.print("Erro no JSON: ");
      Serial.println(error.c_str());
      showErrorAnimation();
      return;
    }

    if (!doc["status"].is<String>() || doc["status"] != "success") {
      Serial.println("Erro no servidor: " + doc["message"].as<String>());
      showErrorAnimation();
      return;
    }

    matrix.fillScreen(0);
    JsonArray pixels = doc["pixels"];
    
    for (JsonObject pixel : pixels) {
      int row = pixel["row"];
      int col = pixel["col"];
      String colorHex = pixel["color"];
 
      long color = strtol(colorHex.c_str(), NULL, 16);
      int r = (color >> 16) & 0xFF;
      int g = (color >> 8) & 0xFF;
      int b = color & 0xFF;
      
      matrix.drawPixel(col, row, matrix.Color(r, g, b));
    }
    
    matrix.show();
    Serial.println("Matriz atualizada com sucesso!");
    
  } else {
    Serial.println("Falha na conexão com o servidor");
    showErrorAnimation();
  }
}

void startupAnimation() {
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    matrix.drawPixel(i, 0, matrix.Color(50, 0, 0));
    matrix.drawPixel(0, i, matrix.Color(0, 50, 0));
    matrix.drawPixel(i, MATRIX_HEIGHT-1, matrix.Color(0, 0, 50));
    matrix.drawPixel(MATRIX_WIDTH-1, i, matrix.Color(50, 50, 0));
    matrix.show();
    delay(30);
  }
  matrix.fillScreen(0);
  matrix.show();
}

void showErrorAnimation() {
  for (int i = 0; i < 3; i++) {
    matrix.fillScreen(matrix.Color(50, 0, 0));
    matrix.show();
    delay(300);
    matrix.fillScreen(0);
    matrix.show();
    delay(300);
  }
}