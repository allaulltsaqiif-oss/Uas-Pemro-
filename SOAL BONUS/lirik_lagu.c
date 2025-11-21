#include <stdio.h>  //standar Input dan Output
#include <ctype.h>  //fungsi digunakan untuk memeriksa dan memanipulasi karakter
#include <string.h> //fungsi untuk memproses string dan array karakter

#define MAX_WORDS 5000  //define digunakan utk membuat konstanta MAX_WORDS yg bernilai 5000
#define MAX_WORD_LEN 100    //menentukan panjang maksimal sebuah kata

// Membersihkan kata: hanya huruf, angka, dan apostrophe
void bersihkan_kata(char *src, char *dst) {
    int j = 0;      //variabel utk menyimpan angka input
    for (int i = 0; src[i] != '\0'; i++) {   //perulangan dari huruf pertama di src sampai '\0'(END)
        if (isalnum(src[i]) || src[i] == '\'') {    //isalnum = utk mengecek karakter adalah huruf/angka, tanda kutip (')
            dst[j++] = tolower(src[i]);     //tolower = utk mengubah huruf menjadi huruf kecil
        }
    }
    dst[j] = '\0';      //tempat kumpul karakter -sampai stop
}

// Cek apakah kata sudah pernah muncul / belum 
int sudah_ada(char kata[][MAX_WORD_LEN], int count, char *baru) {
    for (int i = 0; i < count; i++) {
        if (strcmp(kata[i], baru) == 0) return 1;   //membandingkan kata ke-i dengan kata baru
    }
    return 0;       //kata belum ada
}

int main() {
    FILE *fin = fopen("lirik.txt", "r");        //membuka file lirik.txt, read
    FILE *fout = fopen("kosa-kata.word", "w");  //membuka/membuat file kosa-kata.word, write

    if (!fin || !fout) {        //kosong/NULL, file tidak terbuka
        printf("Gagal membuka file.\n");
        return 1;       //program berhenti karena error
    }

    char line[1000];        //tempat penyimpanan utk 1 baris teks, max 1000 karakter
    char words[MAX_WORDS][MAX_WORD_LEN];    //menyimpan semua kata yg ditemukan
    int word_count = 0;     //penghitung jumlah angka yg masuk ke array
    
    // --- Ambil judul (baris pertama) ---
   fgets(line, sizeof(line), fin);                               // Membaca baris pertama dari file input (judul lagu)
fprintf(fout, "%s", line);                                    // Menulis judul lagu ke file output tanpa perubahan

// --- Proses sisa lirik ---
while (fgets(line, sizeof(line), fin)) {                      // Loop membaca setiap baris lirik dari file input
    char *token = strtok(line, " \n\t");                      // Memecah baris menjadi token menggunakan spasi, newline, tab sebagai delimiter

    while (token != NULL) {                                   // Loop memproses setiap token dalam baris
        char cleaned[MAX_WORD_LEN] = "";                      // Deklarasi array untuk menyimpan kata yang sudah dibersihkan
        bersihkan_kata(token, cleaned);                       // Memanggil fungsi untuk membersihkan kata dari karakter khusus

        if (strlen(cleaned) > 0 && !sudah_ada(words, word_count, cleaned)) {  // Cek jika kata tidak kosong dan belum ada di array
            strcpy(words[word_count], cleaned);               // Menyalin kata yang sudah dibersihkan ke array words
            word_count++;                                      // Menambah counter jumlah kata unik
        }

        token = strtok(NULL, " \n\t");                        // Mengambil token berikutnya dari baris yang sama
    }
}

// --- Tulis ke file output ---
for (int i = 0; i < word_count; i++) {                       // Loop melalui semua kata unik yang telah dikumpulkan
    fprintf(fout, "%s=\n", words[i]);                        // Menulis setiap kata ke file output dengan format "kata="
}

fclose(fin);                                                  // Menutup file input
fclose(fout);                                                 // Menutup file output

printf("File 'kosa-kata.word' berhasil dibuat!\n");          // Menampilkan pesan sukses ke user

return 0;                                                     // Mengembalikan nilai 0 menandakan program berakhir dengan sukses
