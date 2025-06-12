# Tung Tung Turret - ESP32-CAM Firmware

ESP32-CAM Firmware für die automatisierte Nerf-Turret Anlage. Enthält Kamera-Streaming, Servo-Steuerung und Objekterkennung.

## Hardware-Anforderungen

- ESP32-CAM Board (AI-Thinker Modell)
- 2x SG90 Servo-Motoren
- Externes 5V Netzteil
- MicroSD-Karte (optional)

## Pin-Konfiguration

```
GPIO 12 - Pan Servo (Horizontal)
GPIO 13 - Tilt Servo (Vertikal)
GPIO 4  - LED Blitz
GPIO 33 - Rote LED
```

## Funktionen

### Kamera-Funktionen
- Live-Video-Streaming (MJPEG)
- Konfigurierbare Auflösung (VGA bis UXGA)
- Einstellbare Bildqualität
- Helligkeit/Kontrast-Steuerung
- Horizontal/Vertikal spiegeln

### Servo-Steuerung
- Pan/Tilt-Bewegungssteuerung
- Winkel-Begrenzungen konfigurierbar
- Geschwindigkeitsanpassung
- Auto-Zentrierung
- Kalibrierungs-Routinen

### Objekterkennung
- Bewegungserkennung
- Gesichtserkennung (basic)
- Farbbasierte Verfolgung
- Zielerkennung und -verfolgung

### Web-Interface
- Echtzeit-Kamera-Stream
- Manuelle Servo-Steuerung
- System-Status Überwachung
- Konfigurationsverwaltung

## Installation

### Voraussetzungen
```
Arduino IDE 1.8.x oder höher
ESP32 Board Package 2.0.x
ESP32Servo Library
WiFi Library
WebServer Library
```

### Einrichtung
1. Arduino IDE und ESP32 Board Package installieren
2. Repository klonen
3. `main.cpp` in Arduino IDE öffnen
4. WiFi-Zugangsdaten in `config.h` konfigurieren
5. "AI Thinker ESP32-CAM" Board auswählen
6. Firmware hochladen

### Konfiguration
`config.h` vor Kompilierung bearbeiten:
```cpp
#define WIFI_SSID "ihr_netzwerk"
#define WIFI_PASSWORD "ihr_passwort"
#define PAN_SERVO_PIN 12
#define TILT_SERVO_PIN 13
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180
```

## API-Endpunkte

### Kamera-Steuerung
```
GET /stream           - Live MJPEG Stream
GET /capture          - Einzelbild aufnehmen
POST /camera/settings - Kamera-Parameter aktualisieren
```

### Servo-Steuerung
```
POST /servo/move      - Servos zu Position bewegen
POST /servo/center    - Beide Servos zentrieren
GET /servo/status     - Aktuelle Positionen abrufen
POST /servo/calibrate - Kalibrierung ausführen
```

### System-Verwaltung
```
GET /status          - System-Status und Diagnose
GET /info            - Hardware-Informationen
POST /reboot         - ESP32 neustarten
GET /wifi/scan       - WiFi-Netzwerke scannen
```

## Kamera-Einstellungen

### Unterstützte Auflösungen
- QQVGA (160x120)
- QCIF (176x144)
- HQVGA (240x176)
- QVGA (320x240)
- CIF (400x296)
- VGA (640x480)
- SVGA (800x600)
- XGA (1024x768)
- SXGA (1280x1024)
- UXGA (1600x1200)

### Bildqualität
- Bereich: 4-63 (niedriger = bessere Qualität)
- Standard: 10
- Beeinflusst Kompression und Dateigröße

## Stromversorgung

### Spannungsspezifikationen
- ESP32-CAM: 5V (3.3V Logik)
- Servos: 5V
- Gesamtstrom: ~1.5A Spitze

### Netzteil-Hinweise
- USB-Stromversorgung unzureichend für Servos
- Externes 5V/2A Netzteil empfohlen
- Separate Servo-Stromschiene bevorzugt

## Fehlerbehebung

### Häufige Probleme

**Kamera initialisiert nicht:**
- Stromversorgung prüfen (5V/2A minimum)
- Kameramodul-Verbindung überprüfen
- Reset und niedrigere Auflösung versuchen

**WiFi-Verbindung fehlgeschlagen:**
- Zugangsdaten in config.h überprüfen
- Signalstärke kontrollieren
- Nur 2.4GHz Netzwerk verwenden

**Servo-Zittern:**
- Ausreichende Stromversorgung sicherstellen
- Servo-Verbindungen kontrollieren
- Servo-Geschwindigkeit im Code reduzieren

**Stream-Verzögerung:**
- Bildqualität-Einstellung verringern
- Bildrate reduzieren
- Netzwerk-Bandbreite prüfen

### Debug-Modus
Serielle Fehlersuche aktivieren:
```cpp
#define DEBUG_MODE 1
#define SERIAL_BAUD 115200
```

## Speicherverbrauch

### Flash-Speicher
- Firmware: ~1.2MB
- OTA-Updates: 1.5MB Partition
- Dateisystem: 1MB (optional)

### RAM-Verbrauch
- Kamera-Puffer: ~100KB
- WebServer: ~50KB
- Verfügbarer Heap: ~200KB

## Leistung

### Bildwiederholraten
- VGA (640x480): ~15 FPS
- SVGA (800x600): ~10 FPS
- XGA (1024x768): ~5 FPS
- UXGA (1600x1200): ~2 FPS

### Servo-Antwortzeit
- Positions-Update-Rate: 50Hz
- Bewegungsgenauigkeit: 1 Grad
- Maximale Geschwindigkeit: 180°/Sekunde

## Entwicklung

### Build-Befehle
```bash
# Kompilieren und hochladen
arduino-cli compile --upload -p /dev/ttyUSB0

# Serielle Ausgabe überwachen
arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=115200
```

### Dateistruktur
```
src/
├── main.cpp          - Hauptanwendung
├── config.h          - Konfigurationseinstellungen
├── camera.cpp        - Kamera-Funktionen
├── servo.cpp         - Servo-Steuerung
├── webserver.cpp     - HTTP-Server
├── detection.cpp     - Objekterkennung
└── utils.cpp         - Hilfsfunktionen
```

## Mitwirken

1. Arduino-Coding-Standards befolgen
2. Auf echter Hardware testen
3. Dokumentation aktualisieren
4. Pull-Requests an develop-Branch senden

## Lizenz

Nur für Bildungszwecke - HTL Mössingerstraße Projektlizenz.
