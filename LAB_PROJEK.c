// Mengimpor library stdio.h untuk fungsi input/output seperti printf() dan scanf()
#include <stdio.h>
// Mengimpor library stdlib.h untuk fungsi umum seperti malloc() dan free()
#include <stdlib.h>
// Mengimpor library string.h untuk fungsi manipulasi string seperti strcmp()
#include <string.h>


#define MAX_STRING 50 // Mendefinisikan konstanta MAX_STRING dengan nilai 50 untuk ukuran maksimal string
#define MAX_TOOLS 100 // Mendefinisikan konstanta MAX_TOOLS dengan nilai 100 untuk ukuran maksimal array alat

// Struktur data untuk alat laboratorium
typedef struct {
    unsigned int id;
    char name[MAX_STRING]; // Nama alat
    char brand[MAX_STRING]; // Merek alat
    char model[MAX_STRING]; // Model alat
    unsigned int year; // Tahun produksi
    unsigned int quantity; // Jumlah unit tersedia
} Tool; // Struktur data untuk alat laboratorium

// Struktur data untuk akun pengguna
typedef struct {
    char username[MAX_STRING]; // Nama pengguna
    char password[MAX_STRING]; // Kata sandi pengguna
    char role[MAX_STRING]; // "admin" atau "user"
} Account;

// Global array alat dan akun
Tool tools[MAX_TOOLS]; // Array untuk menyimpan alat
int total_tools = 0; // Jumlah total alat
Account accounts[10]; // Array untuk menyimpan akun
int total_accounts = 0; // Jumlah total akun

// Fungsi untuk membaca data akun dari file
void load_accounts() {
    FILE *fp = fopen("accounts.txt", "r");// Membuka file accounts.txt untuk dibaca
    if (!fp) {// Jika file gagal dibuka
        printf("Gagal membuka file accounts.txt\n");// Menampilkan pesan kesalahan
        return;// Menghentikan eksekusi fungsi
    }
    total_accounts = 0; // Menginisialisasi jumlah akun menjadi 0
    while (fscanf(fp, "%[^,],%[^,],%s\n", accounts[total_accounts].username, // Membaca username 
                  accounts[total_accounts].password, // Membaca password
                  accounts[total_accounts].role) == 3) { // Membaca role
        total_accounts++;
    }  // Menambah jumlah akun
    fclose(fp); // Menutup file
}

// Fungsi untuk menyimpan data akun ke file
void save_accounts() { // Membuka file accounts.txt untuk ditulis
    FILE *fp = fopen("accounts.txt", "w"); // Membuka file accounts.txt untuk ditulis
    if (!fp) { // Jika file gagal dibuka
        printf("Gagal menyimpan file accounts.txt\n"); // Menampilkan pesan kesalahan
        return; // Menghentikan eksekusi fungsi
    }
    for (int i = 0; i < total_accounts; i++) { // Iterasi melalui semua akun
        fprintf(fp, "%s,%s,%s\n", accounts[i].username, accounts[i].password, accounts[i].role); // Menulis data akun ke file
    }
    fclose(fp); // Menutup file
}

// Fungsi untuk membaca data alat dari file
void load_tools() {
    FILE *fp = fopen("tools.txt", "r"); // Membuka file tools.txt untuk dibaca
    if (!fp) { // Jika file gagal dibuka
        printf("Gagal membuka file tools.txt\n");// Menampilkan pesan kesalahan
        return;// Menghentikan eksekusi fungsi
    }
    total_tools = 0;
    while (fscanf(fp, "%u,%[^,],%[^,],%[^,],%u,%u\n",// Membaca data alat dari file
                  &tools[total_tools].id, // Membaca ID alat
                  tools[total_tools].name, // Nama alat
                  tools[total_tools].brand,// Membaca merek alat
                  tools[total_tools].model, // Membaca model alat
                  &tools[total_tools].year,// Membaca tahun produksi
                  &tools[total_tools].quantity) == 6) { // Membaca jumlah unit
        total_tools++;// Menambah jumlah alat
    }
    fclose(fp);// Menutup file
}

// Fungsi untuk menyimpan data alat ke file
void save_tools() { // Membuka file tools.txt untuk ditulis
    FILE *fp = fopen("tools.txt", "w");// Membuka file tools.txt untuk ditulis
    if (!fp) {// Jika file gagal dibuka
        printf("Gagal menyimpan file tools.txt\n");// Menampilkan pesan kesalahan
        return;   // Menghentikan eksekusi fungsi
    }
    for (int i = 0; i < total_tools; i++) {// Iterasi melalui semua alat
        fprintf(fp, "%u,%s,%s,%s,%u,%u\n", // Menulis data alat ke file
                tools[i].id, // ID alat
                tools[i].name, // Nama alat
                tools[i].brand, // Merek alat
                tools[i].model, // Model alat
                tools[i].year, // Tahun produksi
                tools[i].quantity); // Jumlah unit
    }
    fclose(fp); // Menutup file
}

// Fungsi login
Account* login(char *username, char *password) { // Iterasi melalui semua akun
    for (int i = 0; i < total_accounts; i++) { // Memeriksa kecocokan username dan password
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {// Jika ditemukan kecocokan
            return &accounts[i];// Mengembalikan pointer ke akun yang sesuai
        }
    }
    return NULL; // Mengembalikan NULL jika tidak ditemukan kecocokan
}

// Fungsi menampilkan daftar alat
void list_tools() {
    printf("Daftar Alat Laboratorium:\n");// Menampilkan header tabel
    printf("%-5s %-20s %-15s %-15s %-6s %-8s\n", "ID", "Nama", "Merek", "Model", "Tahun", "Jumlah");// Menampilkan judul kolom
    printf("-------------------------------------------------------------------------------\n"); // Garis pemisah
    for (int i = 0; i < total_tools; i++) { // Iterasi melalui semua alat
        printf("%-5u %-20s %-15s %-15s %-6u %-8u\n", // Menampilkan data alat
            tools[i].id, // ID alat
            tools[i].name, // Nama alat
            tools[i].brand, // Merek alat
            tools[i].model, // Model alat
            tools[i].year, // Tahun produksi
            tools[i].quantity); // Jumlah unit
    }
}

// Fitur admin: tambah alat
void add_tool() {// menambahkan alat baru
    Tool t;// Deklarasi variabel alat baru
    printf("Masukkan ID alat: ");// input ID alat
    scanf("%u", &t.id);// baca ID alat
    printf("Nama alat: "); // input nama alat
    scanf(" %[^\n]", t.name);// baca nama alat
    printf("Merek: ");// input merek alat
    scanf(" %[^\n]", t.brand); // baca merek alat
    printf("Model: ");// input model alat
    scanf(" %[^\n]", t.model);// baca model alat
    printf("Tahun produksi: "); // input tahun produksi
    scanf("%u", &t.year);// baca tahun produksi
    printf("Jumlah unit: ");// input jumlah unit
    scanf("%u", &t.quantity);// baca jumlah unit
    tools[total_tools++] = t;// menambahkan alat ke array
    save_tools();// menyimpan data alat ke file
    printf("Alat berhasil ditambahkan.\n"); /// Menampilkan pesan sukses
}

// Fitur admin: hapus alat
void delete_tool() {
    unsigned int id;// Deklarasi variabel ID alat
    printf("Masukkan ID alat yang ingin dihapus: ");// Input ID alat yang akan dihapus
    scanf("%u", &id);// Membaca ID alat
    for (int i = 0; i < total_tools; i++) {// Iterasi melalui semua alat
        if (tools[i].id == id) {// Jika ID alat ditemukan
            for (int j = i; j < total_tools - 1; j++) {// Menggeser alat setelah alat yang dihapus
                tools[j] = tools[j + 1];// Menggeser alat
            }
            total_tools--;// Mengurangi jumlah total alat
            save_tools();// Menyimpan perubahan ke file
            printf("Alat berhasil dihapus.\n");// Menampilkan pesan sukses
            return;// Menghentikan eksekusi fungsi
        }
    }
    printf("ID alat tidak ditemukan.\n");// Menampilkan pesan jika ID alat tidak ditemukan
}

// Fitur admin: edit alat
void edit_tool() {// Mengedit data alat
    unsigned int id;// Deklarasi variabel ID alat
    printf("Masukkan ID alat yang ingin diedit: ");// Input ID alat yang akan diedit
    scanf("%u", &id);// Membaca ID alat
    for (int i = 0; i < total_tools; i++) {// Iterasi melalui semua alat
        if (tools[i].id == id) {// Jika ID alat ditemukan
            printf("Edit Nama (current: %s): ", tools[i].name);// Menampilkan nama alat saat ini
            scanf(" %[^\n]", tools[i].name);// Membaca nama alat baru
            printf("Edit Merek (current: %s): ", tools[i].brand);// Menampilkan merek alat saat ini
            scanf(" %[^\n]", tools[i].brand);// Membaca merek alat baru
            printf("Edit Model (current: %s): ", tools[i].model);// Menampilkan model alat saat ini
            scanf(" %[^\n]", tools[i].model);// Membaca model alat baru
            printf("Edit Tahun (current: %u): ", tools[i].year);// Menampilkan tahun produksi saat ini
            scanf("%u", &tools[i].year);// Membaca tahun produksi baru
            printf("Edit Jumlah (current: %u): ", tools[i].quantity);// Menampilkan jumlah unit saat ini
            scanf("%u", &tools[i].quantity);// Membaca jumlah unit baru
            save_tools();// Menyimpan perubahan ke file
            printf("Data alat berhasil diubah.\n");// Menampilkan pesan sukses
            return;// Menghentikan eksekusi fungsi
        }
    }
    printf("ID alat tidak ditemukan.\n");// Menampilkan pesan jika ID alat tidak ditemukan
}

// Fungsi user: lihat alat tersedia
void user_view_tools() {// Menampilkan daftar alat
    list_tools();// Memanggil fungsi list_tools untuk menampilkan alat
}

// Fungsi user: pinjam alat
void borrow_tool() {// Meminjam alat
    unsigned int id, jumlah;// Deklarasi variabel ID alat dan jumlah yang dipinjam
    printf("Masukkan ID alat yang ingin dipinjam: ");// Input ID alat yang akan dipinjam
    scanf("%u", &id);// Membaca ID alat
    printf("Jumlah yang ingin dipinjam: ");// Input jumlah yang akan dipinjam
    scanf("%u", &jumlah);// Membaca jumlah yang akan dipinjam
    for (int i = 0; i < total_tools; i++) {// Iterasi melalui semua alat
        if (tools[i].id == id) {// Jika ID alat ditemukan
            if (tools[i].quantity >= jumlah) {// Jika jumlah alat cukup
                tools[i].quantity -= jumlah;// Mengurangi jumlah alat yang tersedia
                save_tools();// Menyimpan perubahan ke file
                printf("Alat berhasil dipinjam.\n");// Menampilkan pesan sukses
                return; // Menghentikan eksekusi fungsi
            } else {// Jika jumlah alat tidak cukup
                printf("Jumlah alat tidak cukup.\n");// Menampilkan pesan kesalahan
                return;// Menghentikan eksekusi fungsi
            }
        }
    }
    printf("ID alat tidak ditemukan.\n"); // Menampilkan pesan jika ID alat tidak ditemukan
}

// Fungsi user: kembalikan alat
void return_tool() {// Mengembalikan alat
    unsigned int id, jumlah;// Deklarasi variabel ID alat dan jumlah yang dikembalikan
    printf("Masukkan ID alat yang dikembalikan: ");//  input ID alat yang akan dikembalikan
    scanf("%u", &id);// Membaca ID alat/
    printf("Jumlah yang dikembalikan: ");// Input jumlah yang dikembalikan
    scanf("%u", &jumlah); // Membaca jumlah yang dikembalikan
    for (int i = 0; i < total_tools; i++) {// Iterasi melalui semua alat
        if (tools[i].id == id) {// Jika ID alat ditemukan
            tools[i].quantity += jumlah;// Menambahkan jumlah alat yang dikembalikan
            save_tools();// Menyimpan perubahan ke file
            printf("Alat berhasil dikembalikan.\n");// Menampilkan pesan sukses
            return;// Menghentikan eksekusi fungsi
        }
    }
    printf("ID alat tidak ditemukan.\n");// Menampilkan pesan jika ID alat tidak ditemukan
}

int main(int argc, char *argv[]) {// Fungsi utama program
    if (argc != 3) {// Memeriksa argumen baris perintah
        printf("Usage: %s <username> <password>\n", argv[0]);// Menampilkan cara penggunaan program
        return 1;// Menghentikan eksekusi program
    }

    load_accounts();// Memuat data akun dari file
    load_tools();// Memuat data alat dari file

    Account *current_user = login(argv[1], argv[2]);// Melakukan login dengan username dan password dari argumen
    if (!current_user) {// Jika login gagal
        printf("Login gagal!\n");// Menampilkan pesan gagal
        return 1;// Menghentikan eksekusi program
    }

    printf("Selamat datang, %s (%s)\n", current_user->username, current_user->role);// Menampilkan pesan selamat datang

    int exit = 0;// Variabel untuk mengontrol keluar dari menu
    int choice;// Variabel untuk menyimpan pilihan menu

    while (!exit) {// Loop utama menu
        if (strcmp(current_user->role, "admin") == 0) {// admin
            printf("\n=== Menu Admin ===\n");// Menampilkan menu admin
            printf("1. Lihat alat\n");// Opsi lihat alat
            printf("2. Tambah alat\n");// Opsi tambah alat
            printf("3. Hapus alat\n");// Opsi hapus alat
            printf("4. Ubah alat\n");// Opsi ubah alat
            printf("5. Keluar\n");// Opsi keluar
            printf("Pilih: ");// Meminta input pilihan
            scanf("%d", &choice);// Membaca pilihan
            switch (choice) {// Menangani pilihan menu
                case 1:// Lihat alat
                    list_tools();// Memanggil fungsi list_tools
                    break;
                case 2:// Tambah alat
                    add_tool();// Memanggil fungsi tambah alat
                    break;
                case 3:// Hapus alat
                    delete_tool();// Memanggil fungsi hapus alat
                    break;
                case 4:// Ubah alat
                    edit_tool();// Memanggil fungsi ubah alat
                    break;// Menangani pilihan menu
                case 5:// Keluar
                    exit = 1;// Mengatur variabel exit untuk keluar dari menu
                    break;// Menangani pilihan menu
                default://
                    printf("Pilihan tidak valid.\n");// Menampilkan pesan jika pilihan tidak valid
            }
} else { // user
            printf("\n=== Menu User ===\n");// Menampilkan menu user
            printf("1. Lihat alat\n");// Opsi lihat alat
            printf("2. Pinjam alat\n");// Opsi pinjam alat
            printf("3. Kembalikan alat\n");// 
            printf("4. Keluar\n");// Opsi keluar
            printf("Pilih: ");// Meminta input pilihan
            scanf("%d", &choice);// Membaca pilihan
            switch (choice) {// Menangani pilihan menu
                case 1://   Lihat alat
                    list_tools();// Memanggil fungsi list_tools
                    break;// Menangani pilihan menu/
                case 2:// Pinjam alat
                    borrow_tool();// Memanggil fungsi pinjam alat
                    break;// Menangani pilihan menu/
                case 3:// Kembalikan alat
                    return_tool();// Memanggil fungsi kembalikan alat
                    break;// Menangani pilihan menu
                case 4:// Keluar
                    exit = 1;// Mengatur variabel exit untuk keluar dari menu
                    break;// Menangani pilihan menu
                default:// Jika pilihan tidak valid
                    printf("Pilihan tidak valid.\n");// Menampilkan pesan jika pilihan tidak valid
            }
        }
    }

    printf("Terima kasih telah menggunakan sistem.\n"); // Menampilkan pesan terima kasih
    return 0;// Menghentikan eksekusi program
}
