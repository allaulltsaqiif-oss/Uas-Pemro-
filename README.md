# 📘 FINAL PROJECT LAB PEMROGRAMAN
---

👥 Anggota Kelompok
anggota:
    - nama: "Nama 1"
      npm: "NPM"
    - nama: "Nama 2"
      npm: "NPM"
    - nama: "Nama 3"
      npm: "NPM"
      
---

# 🧪 PROBLEM 1 — Sistem Peminjaman Alat Laboratorium (Bahasa C)
 Program ini adalah implementasi sistem peminjaman alat laboratorium berbasis CLI (Command Line Interface) menggunakan bahasa C dengan penyimpanan data melalui file .txt. Sistem mendukung dua peran utama: Admin dan User, masing-masing dengan hak akses berbeda.

🔐 Fitur Login

    akun:
      - Admin 👨‍💼
      - User 👤
      Semua akun disimpan di file .txt.
      User harus login terlebih dahulu untuk bisa mengakses sistem.

🧾 Kesimpulan Project
    Sistem Peminjaman Alat Laboratorium ini menawarkan solusi sederhana dan efektif untuk mengelola alat lab dalam bentuk aplikasi CLI menggunakan bahasa C. Dengan memanfaatkan file .txt sebagai penyimpanan data, sistem dapat tetap  berjalan tanpa database. Proyek ini memperkuat pemahaman mahasiswa mengenai file handling, struktur data, logika program, dan implementasi CRUD pada bahasa C.
 
---

# 📘 Bonus Project — Daftar Kosa-Kata dari Lirik Lagu

Program ini dibuat untuk membantu Bang Isra, seorang pecinta musik yang ingin mempelajari arti lirik lagu bahasa Inggris. Ia ingin mengekstrak semua kosa-kata unik dari sebuah file lirik lagu tanpa duplikasi, menuliskannya dalam huruf kecil, serta menampilkan dalam format yang rapi.
Program membaca file lirik.txt, kemudian menghasilkan kosa-kata.word berisi daftar kata unik dalam urutan kemunculannya.

📥 Input
Program menerima sebuah file bernama 
```bash
lirik.txt
```

📤 Output
Program menghasilkan file 
```bash
kosa-kata.word
```

🛠️ Cara Kerja Program (Ringkasan)
- Membaca judul dari baris pertama file.
- Membaca seluruh lirik.
- Membersihkan tanda baca, mempertahankan tanda apostrof.
- Memecah lirik menjadi kata-kata.
- Mengubah seluruh kata menjadi huruf kecil.

📂 Struktur File
```bash
📁 Soal bonus
├── lirik.c
├── lirik.txt
└── kosa-kata.word   ← hasil output
```

📝 Kesimpulan
Program ini berhasil membantu menghasilkan daftar kosa-kata unik dari sebuah lirik lagu dengan format yang rapi dan mudah dipelajari. Dengan membaca file lirik.txt, program mengekstrak setiap kata, mengubahnya ke huruf kecil, menghapus tanda baca yang tidak diperlukan, dan menyimpannya tanpa duplikasi dalam urutan kemunculannya. Hasil akhirnya ditulis ke dalam file kosa-kata.word dengan format kata= sehingga memudahkan pengguna seperti Bang Isra untuk menghafal dan memahami arti kata-kata dalam lirik lagu favoritnya. Program ini sederhana namun efektif untuk keperluan pembelajaran bahasa dan analisis teks.
Menyimpan kata unik dalam urutan kemunculan.
Menuliskannya ke file kosa-kata.word dengan format kata=.
