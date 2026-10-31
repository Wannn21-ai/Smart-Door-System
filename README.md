# Smart Door System

Sistem pintu otomatis berbasis ESP32 yang menggunakan keypad 4x4, LCD I2C, servo, LED, dan buzzer untuk membuka pintu dengan password 4 digit.

Proyek ini dibuat berdasarkan kode firmware `sketch.ino` dan dirancang untuk simulasi hardware di Wokwi maupun implementasi nyata pada perangkat ESP32.

## Fitur

- Input password melalui keypad 4x4
- Tampilan status akses di LCD 16x2 I2C
- Servo motor untuk mengunci dan membuka pintu
- Indikator LED hijau untuk akses diterima
- Indikator LED merah dan buzzer untuk akses ditolak
- Reset input password dengan tombol `*`
- Verifikasi PIN saat tombol `#` ditekan

## Komponen yang Digunakan

- ESP32 Dev Module
- Keypad 4x4
- LCD 16x2 I2C
- Servo motor
- LED hijau
- LED merah
- Buzzer
- Kabel jumper dan breadboard

## Konfigurasi Pin

Berikut konfigurasi pin yang dipakai pada kode:

| Komponen | Pin |
| --- | --- |
| Keypad Row 1 | 13 |
| Keypad Row 2 | 12 |
| Keypad Row 3 | 14 |
| Keypad Row 4 | 27 |
| Keypad Col 1 | 26 |
| Keypad Col 2 | 25 |
| Keypad Col 3 | 33 |
| Keypad Col 4 | 32 |
| Servo | 4 |
| LED Hijau | 18 |
| LED Merah | 5 |
| Buzzer | 15 |
| LCD I2C | 0x27 |

## Password Default

Password yang digunakan pada sistem adalah:

```text
2121
```

Cara penggunaan:

1. Masukkan 4 digit password
2. Tekan `#` untuk memvalidasi
3. Jika benar, pintu terbuka dan LED hijau menyala
4. Jika salah, buzzer berbunyi dan LED merah menyala
5. Tekan `*` untuk menghapus input dan mulai lagi

## Cara Kerja Sistem

Pada `setup()`:

- LCD diinisialisasi dan menampilkan teks `ETT PINNYA DULU:`
- Servo diarahkan ke posisi terkunci (`0°`)
- Pin LED dan buzzer diatur sebagai output

Pada `loop()`:

- Program membaca tombol yang ditekan pada keypad
- Jika tombol `#` ditekan, maka fungsi `checkPassword()` dipanggil
- Jika tombol `*` ditekan, input dibersihkan
- Jika tombol lain ditekan, karakter ditambahkan ke `input` dan ditampilkan di LCD

Pada `checkPassword()`:

- Jika `input == "2121"`, jalankan `accessGranted()`
- Jika tidak, jalankan `accessDenied()`
- Setelah itu, input dikosongkan dan LCD dikembalikan ke tampilan awal

Pada `accessGranted()`:

- LCD menampilkan `Siap Boss Dibuka`
- Servo berputar ke posisi `90°` untuk membuka
- LED hijau menyala selama beberapa detik
- Setelah itu servo kembali terkunci dan LED dimatikan

Pada `accessDenied()`:

- LCD menampilkan `Lu Siapa??`
- LED merah menyala
- Buzzer berbunyi selama 1 detik
- Setelah itu LED dimatikan

## Library yang Diperlukan

Library yang dibutuhkan berdasarkan `libraries.txt`:

- `Keypad`
- `LiquidCrystal I2C`
- `Adafruit Keypad`
- `ESP32Servo`

## Persiapan Pengembangan

Buka proyek di Arduino IDE atau platform pengembangan berbasis ESP32, lalu:

1. Pilih board ESP32
2. Tambahkan library yang diperlukan
3. Buka file `sketch.ino`
4. Upload ke ESP32
5. Hubungkan komponen sesuai pin di atas

## Simulasi Wokwi

Proyek ini juga disiapkan untuk simulasi pada Wokwi. Informasi simulasi dapat dilihat pada file `wokwi-project.txt`.

## Struktur File

```text
Smart-Door-System/
├── sketch.ino
├── libraries.txt
├── wokwi-project.txt
├── diagram.json
├── LICENSE
└── README.md
```

## Lisensi

Proyek ini dilisensikan di bawah MIT License. Silakan lihat file `LICENSE` untuk detail lebih lanjut.

## Catatan

Kode saat ini memakai password yang bersifat hardcoded (`"2121"`). Untuk penggunaan nyata, disarankan untuk menambahkan:

- fitur perubahan password
- penyimpanan password di EEPROM
- sistem log akses
- autentikasi lebih aman
- kontrol door lock yang lebih kompleks

## Referensi

- Wokwi Project: `Downloaded from https://wokwi.com/projects/434304740489802753`
- Library: `https://docs.wokwi.com/guides/libraries`
