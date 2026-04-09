# Posttest 2 Praktikum IoT - Sistem Kontrol dan Monitoring Smart House via Telegram Bot

Repositori ini dibuat untuk memenuhi tugas pengumpulan Posttest 2 Praktikum Internet of Things (IoT), Program Studi Informatika, Universitas Mulawarman (2026).

## Anggota Kelompok

| Nama                      | NIM        |
| :--                       | :--        |
| Christian Farrel A. P.    | 2309106032 |
| Zulfikar Heriansyah       | 2309106033 |
| Muhammad Rafly Pratama O. | 2309106043 |

---

## Judul Studi Kasus
**Smart House Berbasis Telegram Bot**

---

## Deskripsi Projek
Projek ini merupakan purwarupa sistem Internet of Things (IoT) yang mengintegrasikan sistem pencahayaan dan keamanan rumah (*smart house*) dengan kemampuan kontrol dan monitoring jarak jauh menggunakan platform Telegram Bot

Sistem ini bekerja dengan alur logika sebagai berikut:
1. **Kontrol LED Berbasis Hak Akses:** Setiap anggota memiliki LED pribadi yang hanya dapat dikontrol oleh pemiliknya melalui Telegram Bot. 
   - Jika pengguna mengakses LED miliknya sendiri, maka LED dapat dinyalakan atau dimatikan.
   - Jika pengguna mencoba mengontrol LED milik anggota lain, sistem akan menolak akses dan mengirimkan notifikasi peringatan.
   - Terdapat 1 LED utama (ruang tamu) yang dapat dikontrol oleh seluruh anggota.
2. **Monitoring Lingkungan (Suhu & Kelembapan):** Sensor DHT11 membaca suhu dan kelembapan secara *real-time*. 
   - Pengguna dapat mengecek kondisi suhu dan kelembapan kapan saja melalui Telegram Bot.
   - Sistem akan mengirimkan data kondisi ruangan secara langsung sesuai permintaan pengguna.
3. **Sistem Keamanan Gas (Otomatis):** Sensor MQ-2 digunakan untuk mendeteksi kebocoran gas di lingkungan rumah. 
   - Jika nilai gas melebihi ambang batas yang ditentukan, sistem akan secara otomatis mengirimkan peringatan darurat (*push notification*) ke grup Telegram.
   - Notifikasi berisi informasi kondisi berbahaya agar pengguna dapat segera melakukan tindakan.
4. Seluruh sistem terhubung ke internet melalui jaringan Wi-Fi untuk sinkronisasi data serta kontrol perangkat secara *real-time* melalui Telegram Bot.

---

## Pembagian Tugas

Agar pengerjaan projek berjalan efektif, berikut adalah pembagian tugas masing-masing anggota kelompok:

| Nama                      | Deskripsi Tugas                                                                        |
| :---                      | :---                                                                                   |
| Christian Farrel A. P     | Merancang skematik dan membangun perangkat IoT, pengujian fungsional dan dokumentasi   |
| Zulfikar Heriansyah       | Merekam serta mengedit video, pengujian fungsional, membantu membangun logic perangkat |
| Muhammad Rafly Pratama O. | Menyiapkan platform IoT, memrogram perangkat IoT, pengujian fungsional                 |

---

## Komponen yang Digunakan

Berikut adalah perangkat keras (*hardware*) yang digunakan dalam merangkai sistem ini:
* 1x Microcontroller Board (ESP32 / NodeMCU ESP8266)
* 1x Sensor DHT11 (Suhu & Kelembapan)
* 1x Sensor Gas MQ-2
* 4x LED (sesuai jumlah anggota + 1 LED utama)
* 1x Breadboard / Project Board
* Kabel Jumper Male-to-Male, Female-to-Female & Male-to-Female

**Platform IoT:** Telegram Bot

---

## Board Schematic

![Board Schematic](https://github.com/RaflyOlanda/posttest1-praktikum-iot-unmul-2026/blob/main/skematikIOT.png)

---

## Video Demo

Berikut adalah video demonstrasi yang menampilkan wajah anggota kelompok, bentuk fisik rangkaian serta pengujian *real-time* menggunakan platform IoT.

**Tonton Video Demo di YouTube:** [**[KLIK DI SINI UNTUK MENONTON]**](https://youtu.be/mVnffrpM51M?si=8B4oJmCmePdCa6vu)
