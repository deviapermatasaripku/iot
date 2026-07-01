// ============================================================
//   SMART ENVIRONMENT MONITOR - v7 (SIMPLIFIED THRESHOLDS)
//   Sensors: DHT11, Ultrasonic, MQ2
//   Output: Serial (115200) + LCD I2C 16x2
// ============================================================

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- Pin ----------
#define DHTPIN 2
#define DHTTYPE DHT11
#define TRIG_PIN 9
#define ECHO_PIN 10

#define PIN_LED_HIJAU 3
#define PIN_LED_KUNING 4
#define PIN_LED_MERAH 5
#define PIN_BUZZER 8
#define PIN_MQ2 A0

// ---------- Objects ----------
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- Threshold Suhu & Kelembaban ----------
#define TEMP_WARN 30.0
#define TEMP_DANGER 38.0
#define HUM_WARN 70.0
#define HUM_DANGER 85.0

// ---------- Threshold Gas ----------
#define GAS_WARN 400
#define GAS_DANGER 700

// ---------- Threshold Jarak (SIMPLE FIXED VALUES) ----------
#define DIST_WARN 40.0    // cm — masuk WASPADA
#define DIST_DANGER 10.0  // cm — masuk BAHAYA

// ---------- Kode Status ----------
#define STATUS_AMAN 0
#define STATUS_WASPADA 1
#define STATUS_BAHAYA 2

// ---------- Variabel utama ----------
unsigned long previousMillis = 0;
const long SENSOR_INTERVAL = 2000;
int lcdPage = 0;
int currentStatus = STATUS_AMAN;

// ---------- Timer LED Kuning ----------
unsigned long tKuning = 0;
bool stateKuning = false;
#define KUNING_ON_MS 500
#define KUNING_OFF_MS 500

// ---------- Timer LED Merah ----------
unsigned long tMerah = 0;
bool stateMerah = false;
#define MERAH_ON_MS 150
#define MERAH_OFF_MS 150

// ---------- Timer Buzzer ----------
unsigned long tBuzzer = 0;
bool stateBuzzer = false;

// ============================================================
// HELPER
// ============================================================
void matikanSemua() {
  digitalWrite(PIN_LED_HIJAU, LOW);
  digitalWrite(PIN_LED_KUNING, LOW);
  digitalWrite(PIN_LED_MERAH, LOW);
  noTone(PIN_BUZZER);
  stateKuning = false;
  stateMerah = false;
  stateBuzzer = false;
}

// ============================================================
// SETUP
// ============================================================
void setup() {
  Serial.begin(115200);
  delay(500);

  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(PIN_LED_HIJAU, OUTPUT);
  pinMode(PIN_LED_KUNING, OUTPUT);
  pinMode(PIN_LED_MERAH, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  matikanSemua();

  Serial.println(F("============================================================"));
  Serial.println(F("   SMART ENVIRONMENT MONITOR v7 | Threshold Sederhana"));
  Serial.println(F("   Jarak: AMAN >25cm | WASPADA 10-25cm | BAHAYA <=10cm"));
  Serial.println(F("============================================================"));

  // ===== TEST LED & BUZZER =====
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Test LED HIJAU  ");
  digitalWrite(PIN_LED_HIJAU, HIGH);
  delay(800);
  digitalWrite(PIN_LED_HIJAU, LOW);
  delay(200);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Test LED KUNING ");
  digitalWrite(PIN_LED_KUNING, HIGH);
  delay(800);
  digitalWrite(PIN_LED_KUNING, LOW);
  delay(200);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Test LED MERAH  ");
  digitalWrite(PIN_LED_MERAH, HIGH);
  delay(800);
  digitalWrite(PIN_LED_MERAH, LOW);
  delay(200);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Test BUZZER...  ");
  tone(PIN_BUZZER, 1000, 500);
  delay(700);
  noTone(PIN_BUZZER);

  matikanSemua();

  // ===== INFO THRESHOLD =====
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("W:>25cm B:<=10cm");
  lcd.setCursor(0, 1);
  lcd.print("Siap monitoring!");
  delay(2000);
  lcd.clear();

  Serial.println(F("[LOOP] Mulai monitoring..."));
}

// ============================================================
// LOOP
// ============================================================
void loop() {
  unsigned long now = millis();
  if (now - previousMillis >= SENSOR_INTERVAL) {
    previousMillis = now;
    readAndDisplay();
  }
  kontrolLED(now);
  kontrolBuzzer(now);
}

// ============================================================
// KONTROL LED
// ============================================================
void kontrolLED(unsigned long now) {
  if (currentStatus == STATUS_AMAN) {
    digitalWrite(PIN_LED_MERAH, LOW);
    digitalWrite(PIN_LED_KUNING, LOW);
    digitalWrite(PIN_LED_HIJAU, HIGH);
    stateKuning = false;
    stateMerah = false;
    return;
  }
  if (currentStatus == STATUS_WASPADA) {
    digitalWrite(PIN_LED_HIJAU, LOW);
    digitalWrite(PIN_LED_MERAH, LOW);
    stateMerah = false;
    unsigned long dur = stateKuning ? KUNING_ON_MS : KUNING_OFF_MS;
    if (now - tKuning >= dur) {
      stateKuning = !stateKuning;
      digitalWrite(PIN_LED_KUNING, stateKuning ? HIGH : LOW);
      tKuning = now;
    }
    return;
  }
  if (currentStatus == STATUS_BAHAYA) {
    digitalWrite(PIN_LED_HIJAU, LOW);
    digitalWrite(PIN_LED_KUNING, LOW);
    stateKuning = false;
    unsigned long dur = stateMerah ? MERAH_ON_MS : MERAH_OFF_MS;
    if (now - tMerah >= dur) {
      stateMerah = !stateMerah;
      digitalWrite(PIN_LED_MERAH, stateMerah ? HIGH : LOW);
      tMerah = now;
    }
  }
}

// ============================================================
// KONTROL BUZZER
// ============================================================
void kontrolBuzzer(unsigned long now) {
  if (currentStatus == STATUS_AMAN) {
    noTone(PIN_BUZZER);
    stateBuzzer = false;
    return;
  }
  unsigned long onDur, offDur;
  int freq;
  if (currentStatus == STATUS_WASPADA) {
    onDur = 400;
    offDur = 600;
    freq = 1000;
  } else {
    onDur = 120;
    offDur = 80;
    freq = 2500;
  }
  if (stateBuzzer) {
    if (now - tBuzzer >= onDur) {
      noTone(PIN_BUZZER);
      stateBuzzer = false;
      tBuzzer = now;
    }
  } else {
    if (now - tBuzzer >= offDur) {
      tone(PIN_BUZZER, freq);
      stateBuzzer = true;
      tBuzzer = now;
    }
  }
}

// ============================================================
// BACA SENSOR & TAMPILKAN
// ============================================================
void readAndDisplay() {
  float suhu = dht.readTemperature();
  float lembab = dht.readHumidity();
  int gasRaw = analogRead(PIN_MQ2);
  float jarak = readUltrasonic();

  bool dhtError = isnan(suhu) || isnan(lembab);
  if (dhtError) {
    suhu = 0;
    lembab = 0;
  }

  int statusSuhu = getStatusSuhu(suhu, dhtError);
  int statusHum = getStatusHum(lembab, dhtError);
  int statusGas = getStatusGas(gasRaw);
  int statusJarak = getStatusJarak(jarak);

  currentStatus = max(max(statusSuhu, statusGas), max(statusJarak, statusHum));

  // Serial output
  Serial.println(F("------------------------------------------------------------"));
  Serial.print(F("[Waktu] "));
  Serial.print(millis() / 1000);
  Serial.println(F("s"));
  Serial.print(F("Suhu:"));
  Serial.print(suhu, 1);
  Serial.print(F("C  Hum:"));
  Serial.print(lembab, 1);
  Serial.print(F("%  Gas:"));
  Serial.print(gasRaw);
  Serial.print(F("  Jarak:"));
  Serial.print(jarak, 1);
  Serial.println(F("cm"));

  Serial.print(F("Status => Suhu:"));
  Serial.print(labelStatus(statusSuhu));
  Serial.print(F(" Hum:"));
  Serial.print(labelStatus(statusHum));
  Serial.print(F(" Gas:"));
  Serial.print(labelStatus(statusGas));
  Serial.print(F(" Jarak:"));
  Serial.println(labelStatus(statusJarak));
  Serial.print(F("KESELURUHAN: "));
  switch (currentStatus) {
    case STATUS_AMAN: Serial.println(F("AMAN    -> LED Hijau")); break;
    case STATUS_WASPADA: Serial.println(F("WASPADA -> LED Kuning kedip")); break;
    case STATUS_BAHAYA: Serial.println(F("BAHAYA  -> LED Merah kedip")); break;
  }

  updateLCD(suhu, lembab, gasRaw, jarak, currentStatus, dhtError, lcdPage);
  lcdPage = (lcdPage + 1) % 2;
}

// ============================================================
// ULTRASONIC — rata-rata 3 pembacaan
// ============================================================
float readUltrasonic() {
  float total = 0;
  int valid = 0;
  for (int i = 0; i < 3; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    float hasil = (duration == 0) ? 999.0 : (duration * 0.034) / 2.0;
    if (hasil < 999) {
      total += hasil;
      valid++;
    }
    delay(30);
  }
  return (valid > 0) ? (total / valid) : 999.0;
}

// ============================================================
// STATUS EVALUATORS
// ============================================================
int getStatusSuhu(float t, bool err) {
  if (err) return STATUS_WASPADA;
  if (t >= TEMP_DANGER) return STATUS_BAHAYA;
  if (t >= TEMP_WARN) return STATUS_WASPADA;
  return STATUS_AMAN;
}

int getStatusHum(float h, bool err) {
  if (err) return STATUS_WASPADA;
  if (h >= HUM_DANGER) return STATUS_BAHAYA;
  if (h >= HUM_WARN) return STATUS_WASPADA;
  return STATUS_AMAN;
}

int getStatusGas(int g) {
  if (g >= GAS_DANGER) return STATUS_BAHAYA;
  if (g >= GAS_WARN) return STATUS_WASPADA;
  return STATUS_AMAN;
}

// SIMPLIFIED — just compare distance to fixed thresholds
int getStatusJarak(float d) {
  if (d >= 999) return STATUS_AMAN;            // tidak ada objek
  if (d <= DIST_DANGER) return STATUS_BAHAYA;  // <= 10 cm
  if (d <= DIST_WARN) return STATUS_WASPADA;   // <= 25 cm
  return STATUS_AMAN;
}

// ============================================================
// LCD UPDATE
// ============================================================
void updateLCD(float suhu, float lembab, int gasRaw, float jarak,
               int status, bool dhtError, int page) {
  lcd.clear();
  if (page == 0) {
    lcd.setCursor(0, 0);
    if (dhtError) lcd.print("DHT11 ERROR!    ");
    else {
      lcd.print("T:");
      lcd.print(suhu, 1);
      lcd.print((char)223);
      lcd.print("C H:");
      lcd.print(lembab, 0);
      lcd.print("%  ");
    }
    lcd.setCursor(0, 1);
    lcd.print("Gas:");
    lcd.print(gasRaw);
    lcd.print(" ");
    printLCDStatus(status);
  } else {
    lcd.setCursor(0, 0);
    if (jarak >= 999) lcd.print("Jarak: --.- cm  ");
    else {
      lcd.print("Jarak:");
      lcd.print(jarak, 1);
      lcd.print("cm   ");
    }
    lcd.setCursor(0, 1);
    printLCDStatus(status);
  }
}

void printLCDStatus(int status) {
  switch (status) {
    case STATUS_AMAN: lcd.print("[ AMAN ]"); break;
    case STATUS_WASPADA: lcd.print("[WASPDA]"); break;
    case STATUS_BAHAYA: lcd.print("[BAHAYA]"); break;
  }
}

String labelStatus(int s) {
  switch (s) {
    case STATUS_AMAN: return "AMAN";
    case STATUS_WASPADA: return "WSPT";
    case STATUS_BAHAYA: return "BAYA";
    default: return "????";
  }
}