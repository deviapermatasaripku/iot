# Smart Home Security and Environment Monitoring System Based on Arduino v7

> Sistem monitoring lingkungan cerdas berbasis Arduino yang memantau kondisi suhu, kelembaban, kadar gas, dan jarak objek secara real-time — dilengkapi indikator LED, buzzer, LCD, dan dashboard web interaktif.

## Kenapa bikin alat ini?

Awalnya kepikiran karena banyak kejadian kecil di rumah/kos yang baru ketahuan setelah parah — kompor lupa dimatikan sampai bau gas, ruangan jadi lembab sampai berjamur, atau ada orang/barang yang mendekat ke area yang seharusnya dijaga (pintu, brankas, jendela) tanpa ada yang sadar. Kalau ngecek manual terus-terusan ya nggak mungkin, apalagi kalau lagi tidur atau keluar rumah.

Jadi alat ini dibuat untuk:

1. Memantau suhu, kelembaban, gas, dan jarak objek *otomatis*, tanpa perlu dicek manual.
2. Kasih peringatan **bertingkat** (AMAN → WASPADA → BAHAYA), jadi ada waktu buat bertindak sebelum kondisinya beneran parah — bukan alarm yang baru bunyi pas udah telat.
3. Bisa dipantau dari laptop/PC lewat dashboard web, jadi nggak harus selalu di depan alatnya.
4. Pakai komponen Arduino yang murah dan mudah dicari, jadi cocok buat proyek belajar IoT atau dipakai langsung di rumah.

## Buat siapa alat ini?

- Pemilik rumah/kos yang mau sistem peringatan dini sederhana buat gas bocor, suhu ruangan yang kelewat panas, atau deteksi sesuatu yang mendekat ke area tertentu.
- Mahasiswa/pelajar yang butuh contoh proyek IoT lengkap (sensor → Arduino → output ke LCD/LED/buzzer + dashboard web) buat tugas akhir atau praktikum.
- Yang hobi elektronika dan mau belajar komunikasi serial Arduino ke browser pakai Web Serial API, tanpa perlu software tambahan kayak Processing atau Python.

## Masalah apa yang diselesaikan?

Masalah:

- Nggak ada peringatan dini kalau suhu ruangan naik (risiko kebakaran/heatstroke)
- Kebocoran gas/asap baru ketahuan setelah baunya menyengat
- Kelembaban tinggi bikin jamur tanpa disadari
- Ada benda/orang mendekat ke area terlarang tapi nggak ketahuan
- Harus ada di dekat alat buat tau kondisi terkini
- Alarm biasa sering salah deteksi atau baru bunyi pas udah parah

Solusi dari sistem ini:

- DHT11 mantau suhu tiap 2 detik dengan 2 ambang batas
- MQ-2 mendeteksi gas dari awal, sebelum konsentrasinya bahaya
- DHT11 mantau kelembaban dengan peringatan bertingkat
- HC-SR04 deteksi jarak objek real-time
- Dashboard web nampilin status dari laptop via USB
- Logika 3 level (AMAN/WASPADA/BAHAYA) kasih waktu reaksi lebih awal

## Deskripsi

**Smart Home Security and Environment Monitoring System Based on Arduino** adalah alat pemantau lingkungan pakai Arduino yang mendeteksi kondisi berbahaya dan kasih peringatan dini. Alat ini baca data dari 4 sensor sekaligus, diproses langsung di Arduino, lalu hasilnya ditampilkan lewat **3 jalur output**:

- **LCD I2C 16×2** — tampilan langsung di alat
- **LED + Buzzer** — indikator visual dan suara
- **Dashboard Web** — monitoring lewat browser pakai Web Serial API

Logikanya pakai *worst-case* — status keseluruhan ditentukan dari sensor yang kondisinya paling parah. Jadi kalau cuma satu sensor aja yang BAHAYA, seluruh sistem (LED, buzzer, dashboard) langsung ikut BAHAYA, meskipun 3 sensor lain masih AMAN.


## Fitur Utama

Fitur dan Keterangan:

Monitoring Suhu (Membaca suhu ruangan via DHT11, threshold waspada 30°C dan bahaya 38°C )
Monitoring Kelembaban (Membaca kelembaban udara, threshold waspada 70% dan bahaya 85%)
Deteksi Gas & Asap (Membaca kadar gas via MQ-2, threshold waspada 400 dan bahaya 700)
Deteksi Jarak Objek (Mengukur jarak via ultrasonik HC-SR04, bahaya jika ≤ 10 cm )
Indikator 3 Level (Status AMAN / WASPADA / BAHAYA dengan LED dan buzzer berbeda)
Tampilan LCD (LCD 16×2 menampilkan data sensor bergantian setiap 2 detik)
Dashboard Web (Monitoring real-time via browser dengan grafik historis 10 data terakhir)
Web Serial API (Koneksi langsung Arduino ke browser tanpa software tambahan)
Mode Demo (Dashboard dapat berjalan tanpa Arduino dengan data simulasi)
Tes Startup Otomatis (Self-test LED dan buzzer setiap kali alat dinyalakan)


## Teknologi yang Digunakan

### Software

Teknologi:                    Versi                         Fungsi:
Arduino IDE                    2.x           Pemrograman dan upload kode ke board 
C++ (Arduino)                   —            Bahasa pemrograman firmware Arduino 
HTML5                           —            Struktur dashboard web 
CSS3                            —            Tampilan dan animasi dashboard 
JavaScript (Vanilla)           ES6+          Logika dashboard dan komunikasi serial 
Web Serial API                  —            Komunikasi browser ↔ Arduino via USB 
Google Fonts                    —            Font Orbitron, Share Tech Mono, Rajdhani
Canvas API                      —            Rendering grafik historis sensor

### Hardware

Komponen:                   Spesifikasi:                    Fungsi:
Arduino UNO / Nano          ATmega328P, 16 MHz        Mikrokontroler utama
Sensor DHT11                3.3–5V, akurasi ±2°C      Membaca suhu dan kelembaban 
Sensor HC-SR04              5V, range 2–400 cm        Mengukur jarak objek 
Sensor MQ-2                 5V, analog output         Mendeteksi gas LPG, asap, alkohol 
LCD 16×2 + I2C              5V, alamat 0x27           Menampilkan data sensor 
LED Hijau                   5mm, 20mA                 Indikator status AMAN 
LED Kuning                  5mm, 20mA                 Indikator status WASPADA 
LED Merah                   5mm, 20mA                 Indikator status BAHAYA 
Buzzer                      Pasif/Aktif, 5V           Indikator audio peringatan 
Kabel USB Tipe A–B              —                     Daya alat + komunikasi serial ke PC 
Kabel Jumper & Breadboard       —                     Merangkai seluruh komponen 
Resistor 220Ω (×3)              —                     Pembatas arus untuk LED 

### Library Arduino

Library:                      Author:                       Fungsi:

`DHT sensor library`         Adafruit                 Driver sensor DHT11 
`Adafruit Unified Sensor`    Adafruit                 Dependensi DHT library 
`LiquidCrystal I2C`          Frank de Brabander       Driver LCD I2C 
`Wire.h`                     Built-in                 Komunikasi I2C


## Arsitektur Sistem

┌─────────────────────────────────────────────────────────┐
│                     SENSOR LAYER                        │
│                                                         │
│  [DHT11]      [HC-SR04]      [MQ-2]                     │
│  Suhu &       Ultrasonik     Gas/Asap                   │
│  Kelembaban   Jarak          (Analog A0)                │
│    (D2)       (D9/D10)                                  │
└────────────────────┬────────────────────────────────────┘
                     │ Data Sensor (tiap 2 detik)
                     ▼
┌─────────────────────────────────────────────────────────┐
│                  PROCESSING LAYER                       │
│                                                         │
│               [ Arduino UNO/Nano ]                      │
│                                                         │
│  • Baca semua sensor                                    │
│  • Evaluasi status tiap sensor (AMAN/WASPADA/BAHAYA)    │
│  • Ambil status tertinggi (worst-case logic)            │
│  • Kirim data ke Serial (115200 baud)                   │
└──────────┬──────────────────────────┬───────────────────┘
           │                          │
           ▼                          ▼
┌──────────────────┐      ┌───────────────────────────────┐
│   OUTPUT LOKAL   │      │        OUTPUT SERIAL          │
│                  │      │                               │
│  [LCD I2C 16×2]  │      │  USB → PC → Chrome/Edge       │
│  Halaman 1:      │      │                               │
│  Suhu,Hum,Gas    │      │  [Dashboard Web HTML]         │
│                  │      │  • 4 kartu sensor real-time   │
│  Halaman 2:      │      │  • Grafik historis 10 data    │
│  Jarak, Status   │      │  • Panel kalibrasi            │
│                  │      │  • Status badge               │
│  [LED + Buzzer]  │      │                               │
│  Hijau/Kuning/   │      │                               │
│  Merah           │      │                               │
└──────────────────┘      └───────────────────────────────┘


## Cara Kerja Sistem

### 1. Inisialisasi (Setup)
Saat Arduino pertama dinyalakan, sistem melakukan:
- Inisialisasi semua pin (LED, buzzer, sensor)
- Inisialisasi LCD dan DHT11
- Tes self-check: LED hijau → kuning → merah → buzzer
- Menampilkan info threshold di LCD selama 2 detik

### 2. Loop Utama (setiap 2 detik)

Baca DHT11 → Baca MQ-2 → Baca HC-SR04 (rata-rata 3×)
       │
       ▼
Evaluasi status masing-masing sensor:
  • Suhu       : AMAN < 30 | WASPADA 30–38 | BAHAYA ≥ 38°C
  • Kelembaban : AMAN < 70 | WASPADA 70–85 | BAHAYA ≥ 85%
  • Gas        : AMAN < 400 | WASPADA 400–700 | BAHAYA ≥ 700
  • Jarak      : AMAN > 40cm | WASPADA 10–40cm | BAHAYA ≤ 10cm
       │
       ▼
Status Keseluruhan = MAX(statusSuhu, statusHum, statusGas, statusJarak)
       │
       ├──► Update LCD (berganti halaman tiap siklus)
       ├──► Kirim data via Serial ke dashboard web
       └──► Set status LED & buzzer


**Catatan soal sensor jarak:** kalau HC-SR04 nggak nangkap pantulan dari objek apapun (dalam 30.000 µs), Arduino bakal kirim nilai `999 cm`. Nilai ini **selalu dianggap AMAN**, bukan BAHAYA — soalnya 999 itu bukan jarak sungguhan, tapi cuma kode "nggak ada objek terdeteksi".

### 3. Kontrol LED & Buzzer (non-blocking, millis-based)

Status:                LED:                               Buzzer:

AMAN Hijau           ON steady                              OFF 
WASPADA       Kuning kedip 500ms on/off      Tone 1000Hz, 400ms on / 600ms off 
BAHAYA        Merah kedip 150ms on/off       Tone 2500Hz, 120ms on / 80ms off 

> Sistem menggunakan `millis()` bukan `delay()` agar LED dan buzzer bisa berkedip tanpa menghentikan pembacaan sensor.

### 4. Dashboard Web
- Baca data dari Serial port pakai **Web Serial API**
- Parse baris output Arduino: `Suhu:XX Hum:XX Gas:XX Jarak:XX`
- Update tampilan real-time: kartu sensor, grafik, status badge
- Status AMAN/WASPADA/BAHAYA di dashboard dihitung ulang sama JavaScript dari nilai sensor asli (bukan dicopy langsung dari teks status yang dikirim Arduino), pakai ambang batas yang sama kayak di firmware — jadi hasilnya selalu sama dengan LED/buzzer di alat aslinya
- Kalau nggak terkoneksi → otomatis jalan di **Mode Demo** dengan data simulasi


## Struktur Folder

Smart Home Security and Environment Monitoring System Based on Arduino/
│
├── sketch_jun5a.ino                       ← Firmware Arduino (upload ke board)
├── dashboard_environment_monitor.html     ← Dashboard Web (buka di Chrome/Edge)
└── README.md                              ← Dokumentasi lengkap proyek (file ini)


## Instalasi

### A. Persiapan Hardware

Rangkai semua komponen sesuai tabel wiring berikut:

Komponen:      Pin Komponen:      Pin Arduino:

DHT11            DATA                   D2 
HC-SR04          TRIG                   D9 
HC-SR04          ECHO                   D10 
LED Hijau        + Anoda          D3 (via resistor 220Ω)
LED Kuning       + Anoda          D4 (via resistor 220Ω)
LED Merah        + Anoda          D5 (via resistor 220Ω)
Buzzer            +                     D8 
MQ-2             AOUT                   A0 
LCD I2C          SDA                    A4
LCD I2C          SCL                    A5 
Semua            GND                   GND 
Semua            VCC                    5V 


> Tips: cek lagi semua sambungan GND sebelum nyalain alatnya — GND yang nggak nyambung bener itu penyebab paling sering sensor jadi baca nilai aneh (misal suhu 0°C atau gas selalu 0).

### B. Install Arduino IDE & Library

1. Download dan install [Arduino IDE 2.x](https://www.arduino.cc/en/software)
2. Buka Arduino IDE → **Sketch → Include Library → Manage Libraries**
3. Cari dan install ketiga library berikut:
   - `DHT sensor library` by Adafruit
   - `Adafruit Unified Sensor` by Adafruit
   - `LiquidCrystal I2C` by Frank de Brabander

### C. Upload Firmware ke Arduino

1. Buka file `sketch_jun5a.ino` di Arduino IDE
2. Pilih **Tools → Board → Arduino UNO**
3. Pilih **Tools → Port → COM_** (port Arduino yang terdeteksi)
4. Klik tombol **Upload ▶**
5. Tunggu hingga muncul pesan **"Done uploading"**

### D. Buka Dashboard Web

1. Pastikan Arduino masih tersambung ke PC via USB
2. Double-click file `dashboard_environment_monitor.html`
3. Buka dengan **Google Chrome** atau **Microsoft Edge**
4. Klik **CONNECT ARDUINO** → pilih port COM → **Connect**

> Penting: buka file HTML-nya langsung pakai double-click (protokol `file://`), **jangan** lewat Live Server/Live Preview di VS Code. Soalnya Web Serial API kebanyakan diblokir di mode preview kayak gitu.


## Cara Menyalakan & Mematikan Alat

### Cara nyalain

1. **Colok kabel USB** dari Arduino ke laptop/PC, atau ke adaptor power 5V kalau cuma butuh LED/LCD/buzzer-nya aja tanpa dashboard.
2. Alatnya **langsung nyala** begitu dapat daya — nggak ada tombol power.
3. Arduino otomatis jalankan **self-test** selama ±3 detik:
   - LED Hijau nyala 0.8 detik
   - LED Kuning nyala 0.8 detik
   - LED Merah nyala 0.8 detik
   - Buzzer bunyi singkat 0.5 detik
   - LCD nampilin pesan "Test LED..." lalu info threshold
4. Setelah self-test kelar, LCD bakal nampilin **"Siap monitoring!"**, dan sistem mulai baca sensor tiap 2 detik.
5. **Tunggu ±60 detik** dulu sebelum percaya pembacaan sensor gas (MQ-2) — sensor ini butuh waktu pemanasan biar hasilnya stabil. Selama warm-up ini, nilai gas yang muncul belum bisa dijadikan acuan.
6. Kalau mau dipantau dari laptop, lanjut ke bagian **Buka Dashboard Web** di atas.

### Cara matiin

- **Cabut kabel USB / adaptor power** dari Arduino — alatnya langsung mati.
- **Nggak ada prosedur shutdown khusus**, soalnya sistem ini nggak nyimpen data ke storage permanen, jadi nggak ada risiko data korup.
- Kalau dashboard web masih kebuka pas alatnya dicabut, dashboard otomatis pindah ke **Mode Demo** begitu koneksi serial-nya putus.

### Restart

- Cabut lalu colok lagi kabel USB-nya, **atau**
- Pencet tombol **Reset** kecil di board Arduino (kalau ada).
- Sistemnya bakal ngulang lagi semua proses self-test dari awal kayak pas pertama nyala.


## Cara Penggunaan Dashboard Web

### Baca status

🟢 LED Hijau nyala         →  AMAN     — kondisi normal
🟡 LED Kuning kedip        →  WASPADA  — mendekati batas bahaya
🔴 LED Merah kedip cepat   →  BAHAYA   — udah lewat batas aman


### LCD Ganti Halaman Tiap 2 Detik

┌────────────────┐       ┌────────────────┐
│T:27.5°C H:62%  │  ───► │Jarak:35.2cm    │
│Gas:310  [ AMAN]│       │[ AMAN ]        │
└────────────────┘       └────────────────┘
  Halaman 1                 Halaman 2


### Panel-Panel di Dashboard

Panel dan Fungsi:

**Indikator Status Serial** (atas) -> Nunjukin dashboard sedang konek ke Arduino asli atau lagi di Mode Demo 
**Log Serial** -> Nampilin baris mentah data yang diterima dari Arduino, buat keperluan debug 
**Status Badge Utama** -> Status keseluruhan sistem (AMAN/WASPADA/BAHAYA), ngikutin logika worst-case sama kayak firmware
**4 Kartu Sensor** -> Nilai real-time Suhu, Kelembaban, Gas, dan Jarak beserta status masing-masing 
**Simulasi Kondisi** -> Tombol AMAN/WASPADA/BAHAYA buat manggil data simulasi manual (cuma jalan di Mode Demo, nggak ngaruh kalau Arduino udah konek) 
**LED & Buzzer** -> Replika visual dari LED dan buzzer yang ada di alat aslinya 
**Threshold Sensor** -> Nampilin ambang batas WASPADA/BAHAYA tiap sensor, harus sama dengan nilai `#define` di firmware 
**Kalibrasi** -> Nampilin nilai ambang gas dan jarak yang dipakai dashboard 
**Grafik Riwayat** -> Grafik garis dari 10 pembacaan terakhir buat keempat sensor 

### Mode Demo vs Mode Terhubung

- **Mode Demo** jalan otomatis kalau dashboard dibuka tanpa konek Arduino. Data sensornya disimulasikan random sesuai tombol AMAN/WASPADA/BAHAYA yang dipilih — cocok buat demo fitur tanpa harus pakai alat asli.
- **Mode Terhubung** jalan setelah klik **CONNECT ARDUINO** dan pilih port yang bener. Semua data berasal dari pembacaan sensor real-time.
- Tombol simulasi (AMAN/WASPADA/BAHAYA) **nggak ngaruh apa-apa** kalau lagi Mode Terhubung — dashboard tetap nampilin data asli dari Arduino.


## Troubleshooting

Masalah:

- Tombol **CONNECT ARDUINO** nggak muncul / browser bilang Web Serial nggak didukung 
- Dashboard tetap nunjukin **AMAN** padahal alat aslinya udah BAHAYA 
- LCD blank / nggak nyala sama sekali
- Sensor suhu/kelembaban selalu error
- Nilai gas (MQ-2) selalu tinggi padahal udaranya bersih 
- Jarak kebaca **999 cm** terus 
- Status di web beda sama status di alat fisik
- Port Arduino nggak muncul pas klik Connect | Driver USB belum keinstall, atau port-nya lagi dipakai Serial Monitor di Arduino IDE |

Kemungkinan Sebab:
- Browsernya bukan Chrome/Edge, atau filenya dibuka via Live Server
- Belum klik CONNECT, salah pilih port, atau dashboard masih versi lama
- Alamat I2C salah, atau SDA/SCL ketuker
- Pin data DHT11 nggak nyambung bener, atau sensornya rusak
- Sensor belum kelar warm-up (±60 detik)
- Memang nggak ada objek di depan sensor (ini normal), atau TRIG/ECHO ketuker
- Dashboard masih nyimpen data lama / belum baca baris serial terbaru
- Driver USB belum keinstall, atau port-nya lagi dipakai Serial Monitor di Arduino IDE

Solusi:
- Pakai Google Chrome/Microsoft Edge versi terbaru, buka file HTML-nya langsung pakai double-click
- Cek status di pojok kiri atas dashboard udah "Arduino terhubung" belum (bukan Mode Demo); pakai dashboard versi terbaru
- Cek alamat I2C pakai I2C scanner sketch; pastikan alamatnya `0x27`; cek lagi SDA→A4, SCL→A5
- Cek sambungan ke D2; coba ganti sensor DHT11 kalau ada
- Tunggu warm-up-nya selesai dulu sebelum jadiin nilai gas sebagai acuan
- Kalau memang nggak ada benda di depan, 999 cm + status AMAN itu wajar; kalau ada benda tapi tetap 999, cek sambungan D9 (TRIG) dan D10 (ECHO)
- Klik **DISCONNECT** lalu **CONNECT ARDUINO** lagi; cek log serial-nya update tiap 2 detik
- Tutup Serial Monitor di Arduino IDE dulu sebelum buka dashboard web; cek driver CH340/FTDI udah keinstall (kalau pakai board clone)


## FAQ

**Dashboard web-nya wajib dipakai?**
Nggak. Alatnya tetap berfungsi penuh sendiri (LCD + LED + buzzer) tanpa harus konek ke komputer. Dashboard cuma fitur tambahan buat monitoring dari laptop.

**Bisa dipantau dari internet/jarak jauh?**
Belum, di versi ini nggak bisa. Web Serial API yang dipakai cuma kerja lewat USB langsung antara Arduino dan komputer yang sama, bukan lewat internet atau Wi-Fi.

**Kenapa harus Chrome/Edge, kok nggak bisa Firefox?**
Soalnya Web Serial API baru didukung browser yang basisnya Chromium (Chrome, Edge, Opera). Firefox dan Safari belum support API ini.

**Kalau dua sensor statusnya beda, misal suhu AMAN tapi gas BAHAYA, gimana?**
Sistemnya bakal ngikutin status yang **paling parah** dari keempat sensor. Jadi kalau salah satu BAHAYA, semuanya (LED, buzzer, dashboard) ikut nunjukin BAHAYA, walau tiga sensor lain AMAN.

**Ambang batasnya bisa diubah-ubah?**
Bisa. Semua threshold-nya didefinisikan sebagai `#define` di awal file `.ino` (kayak `TEMP_WARN`, `GAS_DANGER`, `DIST_WARN`, dll). Tinggal ubah nilainya, upload ulang. Tapi kalau diubah di firmware, jangan lupa ubah juga nilai yang sama di file dashboard HTML-nya biar tetap sinkron.

**Bisa ganti pakai DHT22 daripada DHT11?**
Bisa, tinggal ubah baris `#define DHTTYPE DHT11` jadi `#define DHTTYPE DHT22` di kode `.ino`. DHT22 akurasinya lebih bagus dan rentang suhunya lebih luas.

**Alatnya bisa nyala terus berapa lama?**
Nggak ada batasan dari software. Selama daya USB/adaptornya stabil, alatnya bisa jalan 24/7. Yang penting jangan sampai sirkulasi udara di sekitar MQ-2 dan DHT11 terhalang, biar pembacaannya tetap akurat.


## Hasil Pengujian

### Pengujian Sensor DHT11

Kondisi Uji:               Suhu Terbaca:          Kelembaban:           Status:            Hasil:
Suhu ruangan normal            27°C                   60%                AMAN              Sesuai
Dekatkan sumber panas          32°C                   65%               WASPADA            Sesuai
Suhu ekstrem tinggi            39°C                   70%               BAHAYA             Sesuai 
DHT11 tidak terhubung         ERROR                  ERROR              WASPADA        Failsafe aktif

### Pengujian Sensor HC-SR04

Kondisi Uji:         Jarak Terbaca:        Status:          Hasil:
Tidak ada objek        999 cm (∞)           AMAN            Sesuai
Objek jarak 50 cm       ~50 cm              AMAN            Sesuai 
Objek jarak 25 cm       ~25 cm             WASPADA          Sesuai 
Objek jarak 8 cm        ~8 cm              BAHAYA           Sesuai 

### Pengujian Sensor MQ-2

Kondisi Uji:                        Nilai Gas (raw):       Status:      Hasil:
Udara bersih (setelah warm-up)          < 300               AMAN        Sesuai 
Dekatkan korek api                      450–600            WASPADA      Sesuai 
Asap pekat / gas dekat                  > 700              BAHAYA       Sesuai

### Pengujian Dashboard Web

Skenario dan Hasil:
Buka tanpa Arduino (Mode Demo) -> Data simulasi berjalan otomatis
Connect ke Arduino via Chrome -> Data real-time tampil dalam < 1 detik 
Disconnect dan reconnect -> Berfungsi normal, kembali ke Mode Demo 
Buka di Firefox -> Web Serial API tidak didukung 
Buka via VS Code Live Preview -> Web Serial API diblokir 
Objek mendekat ≤10cm pas Arduino udah konek -> Dashboard nunjukin BAHAYA real-time, sinkron sama LED merah di alat fisik 
Nggak ada objek terdeteksi (999cm) pas Arduino udah konek -> Dashboard nunjukin AMAN, sinkron sama LED hijau di alat fisik 

### Pengujian Respons Sistem

Parameter:                                   Nilai:

Interval baca sensor                         2000 ms 
Waktu respons LED/buzzer                   < 10 ms (non-blocking) 
Delay startup self-test                    ± 3 detik 
Warm-up MQ-2                               ± 60 detik 
Akurasi jarak ultrasonik (rata-rata 3×)    ± 1–2 cm 


## Lisensi

Proyek ini dibuat untuk keperluan **edukasi dan pembelajaran**.

MIT License

Proyek ini bebas digunakan, dimodifikasi, dan didistribusikan
untuk keperluan pendidikan dengan tetap mencantumkan kredit
kepada pengembang asli.

Penggunaan untuk keperluan komersial memerlukan izin tertulis
dari pengembang.

## Konfigurasi Teknis

Parameter:                                              Nilai:
Baud Rate Serial                                       `115200`
Interval Baca Sensor                                   `2000 ms`
Alamat LCD I2C                                         `0x27` 
Rata-rata pembacaan ultrasonik                         `3×` per siklus 
Timeout ultrasonik                                     `30.000 µs` 
Kedip LED Kuning                                       `500ms ON / 500ms OFF` 
Kedip LED Merah                                        `150ms ON / 150ms OFF`
Frekuensi buzzer WASPADA                               `1000 Hz`
Frekuensi buzzer BAHAYA                                `2500 Hz`
Nilai khusus "tidak ada objek" (ultrasonik)            `999 cm` → selalu dianggap AMAN 


*Smart Home Security and Environment Monitoring System Based on Arduino v7 · Arduino + Web Serial API*  
*Sensor: DHT11 · HC-SR04 · MQ-2 · LCD I2C 16×2*
