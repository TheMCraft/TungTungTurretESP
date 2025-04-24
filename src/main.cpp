#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "htl-IoT";
const char* password = "PASSWORD";

WebServer server(80);

void startCameraServer() {
  server.on("/stream", HTTP_GET, []() {
    WiFiClient client = server.client();
    String response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
    client.print(response);

    while (1) {
      camera_fb_t *fb = esp_camera_fb_get();
      if (!fb) continue;

      client.printf("--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n", fb->len);
      client.write(fb->buf, fb->len);
      client.print("\r\n");
      esp_camera_fb_return(fb);

      if (!client.connected()) break;
      delay(50);
    }
  });
  server.begin();
}

/*
OV2640-Pin | ESP32 GPIO
D0 | 5
D1 | 18
D2 | 19
D3 | 21
D4 | 36
D5 | 39
D6 | 34
D7 | 35
XCLK | 0
PCLK | 22
VSYNC | 25
HREF | 23
SDA | 26
SCL | 27
PWDN | 32
RESET | -1
VCC | 3.3 V
GND | GND
*/

void setup() {
  Serial.begin(115200);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Kamerainit fehlgeschlagen: 0x%x\n", err);
    return;
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WLAN verbunden. IP-Adresse: " + WiFi.localIP().toString());

  startCameraServer();
}

void loop() {
  server.handleClient();
}