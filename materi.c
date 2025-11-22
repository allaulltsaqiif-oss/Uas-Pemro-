# Penjelasan Detail Setiap Baris Kode - Lab System

## 1. INCLUDE LIBRARIES (Baris 1-3)
```c
#include <stdio.h>      // Library untuk input/output (printf, scanf)
#include <stdlib.h>     // Library untuk alokasi memori dan fungsi umum
#include <string.h>     // Library untuk manipulasi string (strcmp, strcpy)
```

---

## 2. DEFINE CONSTANTS (Baris 5-6)
```c
#define MAX_STRING 50   // Konstanta untuk ukuran maksimal string (nama, merek, model)
#define MAX_TOOLS 100   // Konstanta untuk ukuran maksimal array alat
```

---

## 3. STRUKTUR DATA TOOL (Baris 8-14)
```c
typedef struct {        // Mendefinisikan struktur data bernama "Tool"
    unsigned int id;                    // ID alat (bilangan bulat positif)
    char name[MAX_STRING];              // Nama alat (string hingga 50 karakter)
    char brand[MAX_STRING];             // Merek alat (string hingga 50 karakter)
    char model[MAX_STRING];             // Model alat (string hingga 50 karakter)
    unsigned int year;                  // Tahun produksi (bilangan bulat positif)
    unsigned int quantity;              // Jumlah unit alat (bilangan bulat positif)
} Tool;                 // Nama tipe data yang didefinisikan
```

---

## 4. STRUKTUR DATA ACCOUNT (Baris 16-21)
```c
typedef struct {        // Mendefinisikan struktur data bernama "Account"
    char username[MAX_STRING];          // Username pengguna (string hingga 50 karakter)
    char password[MAX_STRING];          // Password pengguna (string hingga 50 karakter)
    char role[MAX_STRING];              // Role pengguna: "admin" atau "user"
} Account;              // Nama tipe data yang didefinisikan
```

---

## 5. GLOBAL VARIABLES (Baris 23-27)
```c
Tool tools[MAX_TOOLS];          // Array untuk menyimpan max 100 alat
int total_tools = 0;            // Counter untuk jumlah alat yang tersimpan (awalnya 0)
Account accounts[10];           // Array untuk menyimpan max 10 akun pengguna
int total_accounts = 0;         // Counter untuk jumlah akun yang tersimpan (awalnya 0)
```

---

## 6. FUNGSI LOAD_ACCOUNTS (Baris 29-42)
```c
void load_accounts() {          // Fungsi untuk membaca akun dari file (tidak return nilai)
    FILE *fp = fopen("accounts.txt", "r");  // Buka file accounts.txt mode baca
    if (!fp) {                  // Jika file tidak bisa dibuka (fp = NULL)
        printf("Gagal membuka file accounts.txt\n");  // Tampilkan pesan error
        return;                 // Keluar dari fungsi
    }
    total_accounts = 0;         // Reset counter akun ke 0
    // Loop membaca data dari file sampai EOF
    while (fscanf(fp, "%[^,],%[^,],%s\n",         // Format: username,password,role
                  accounts[total_accounts].username,   // Baca username (hingga koma)
                  accounts[total_accounts].password,   // Baca password (hingga koma)
                  accounts[total_accounts].role) == 3) { // Baca role (hingga newline)
        total_accounts++;       // Tambah counter jika membaca 3 field berhasil
    }
    fclose(fp);                 // Tutup file
}
```

---

## 7. FUNGSI SAVE_ACCOUNTS (Baris 44-54)
```c
void save_accounts() {          // Fungsi untuk menyimpan akun ke file
    FILE *fp = fopen("accounts.txt", "w");  // Buka file mode write (ganti isi)
    if (!fp) {                  // Jika file tidak bisa dibuka
        printf("Gagal menyimpan file accounts.txt\n");  // Tampilkan pesan error
        return;                 // Keluar dari fungsi
    }
    // Loop untuk menulis semua akun ke file
    for (int i = 0; i < total_accounts; i++) {
        fprintf(fp, "%s,%s,%s\n",       // Format: username,password,role
                accounts[i].username,    // Username
                accounts[i].password,    // Password
                accounts[i].role);       // Role
    }
    fclose(fp);                 // Tutup file
}
```

---

## 8. FUNGSI LOAD_TOOLS (Baris 56-73)
```c
void load_tools() {             // Fungsi untuk membaca alat dari file
    FILE *fp = fopen("tools.txt", "r");  // Buka file tools.txt mode baca
    if (!fp) {                  // Jika file tidak bisa dibuka
        printf("Gagal membuka file tools.txt\n");  // Tampilkan pesan error
        return;                 // Keluar dari fungsi
    }
    total_tools = 0;            // Reset counter alat ke 0
    // Loop membaca data dari file sampai EOF
    while (fscanf(fp, "%u,%[^,],%[^,],%[^,],%u,%u\n",  // Format: id,name,brand,model,year,quantity
                  &tools[total_tools].id,      // Baca ID (unsigned int)
                  tools[total_tools].name,     // Baca nama (string)
                  tools[total_tools].brand,    // Baca merek (string)
                  tools[total_tools].model,    // Baca model (string)
                  &tools[total_tools].year,    // Baca tahun (unsigned int)
                  &tools[total_tools].quantity) == 6) {  // Baca jumlah, jika 6 field berhasil
        total_tools++;          // Tambah counter
    }
    fclose(fp);                 // Tutup file
}
```

---

## 9. FUNGSI SAVE_TOOLS (Baris 75-89)
```c
void save_tools() {             // Fungsi untuk menyimpan alat ke file
    FILE *fp = fopen("tools.txt", "w");  // Buka file mode write
    if (!fp) {                  // Jika file tidak bisa dibuka
        printf("Gagal menyimpan file tools.txt\n");  // Tampilkan pesan error
        return;                 // Keluar dari fungsi
    }
    // Loop untuk menulis semua alat ke file
    for (int i = 0; i < total_tools; i++) {
        fprintf(fp, "%u,%s,%s,%s,%u,%u\n",  // Format: id,name,brand,model,year,quantity
                tools[i].id,        // ID alat
                tools[i].name,      // Nama alat
                tools[i].brand,     // Merek alat
                tools[i].model,     // Model alat
                tools[i].year,      // Tahun produksi
                tools[i].quantity); // Jumlah unit
    }
    fclose(fp);                 // Tutup file
}
```

---

## 10. FUNGSI LOGIN (Baris 91-100)
```c
Account* login(char *username, char *password) {  // Fungsi verifikasi login, return pointer Account
    // Loop melalui semua akun yang tersimpan
    for (int i = 0; i < total_accounts; i++) {
        // Cek apakah username dan password cocok
        if (strcmp(accounts[i].username, username) == 0 && 
            strcmp(accounts[i].password, password) == 0) {
            return &accounts[i];        // Return alamat akun jika cocok
        }
    }
    return NULL;                        // Return NULL jika tidak ada yang cocok
}
```

---

## 11. FUNGSI LIST_TOOLS (Baris 102-109)
```c
void list_tools() {             // Fungsi menampilkan daftar semua alat
    printf("Daftar Alat Laboratorium:\n");  // Tampilkan judul
    printf("ID\tNama\tMerek\tModel\tTahun\tJumlah\n");  // Tampilkan header tabel
    // Loop untuk menampilkan setiap alat
    for (int i = 0; i < total_tools; i++) {
        printf("%u\t%s\t%s\t%s\t%u\t%u\n",  // Format: id nama merek model tahun jumlah
                tools[i].id,        // ID alat
                tools[i].name,      // Nama alat
                tools[i].brand,     // Merek alat
                tools[i].model,     // Model alat
                tools[i].year,      // Tahun produksi
                tools[i].quantity); // Jumlah unit
    }
}
```

---

## 12. FUNGSI ADD_TOOL (Baris 111-128)
```c
void add_tool() {               // Fungsi untuk menambah alat baru
    Tool t;                     // Variabel struct Tool untuk data baru
    printf("Masukkan ID alat: ");       // Minta input ID
    scanf("%u", &t.id);         // Baca ID (unsigned int)
    printf("Nama alat: ");              // Minta input nama
    scanf(" %[^\n]", t.name);   // Baca nama (string, bisa spasi, hingga Enter)
    printf("Merek: ");                  // Minta input merek
    scanf(" %[^\n]", t.brand);  // Baca merek (string, bisa spasi, hingga Enter)
    printf("Model: ");                  // Minta input model
    scanf(" %[^\n]", t.model);  // Baca model (string, bisa spasi, hingga Enter)
    printf("Tahun produksi: ");        // Minta input tahun
    scanf("%u", &t.year);       // Baca tahun (unsigned int)
    printf("Jumlah unit: ");           // Minta input jumlah
    scanf("%u", &t.quantity);   // Baca jumlah (unsigned int)
    tools[total_tools++] = t;   // Simpan data ke array dan tambah counter
    save_tools();               // Simpan data ke file
    printf("Alat berhasil ditambahkan.\n");  // Konfirmasi
}
```

---

## 13. FUNGSI DELETE_TOOL (Baris 130-146)
```c
void delete_tool() {            // Fungsi untuk menghapus alat
    unsigned int id;            // Variabel untuk menyimpan ID yang dicari
    printf("Masukkan ID alat yang ingin dihapus: ");  // Minta input
    scanf("%u", &id);           // Baca ID
    // Loop mencari alat dengan ID tertentu
    for (int i = 0; i < total_tools; i++) {
        if (tools[i].id == id) {        // Jika ID ketemu
            // Geser semua alat setelah posisi i ke posisi sebelumnya
            for (int j = i; j < total_tools - 1; j++) {
                tools[j] = tools[j + 1];
            }
            total_tools--;      // Kurangi counter alat
            save_tools();       // Simpan ke file
            printf("Alat berhasil dihapus.\n");  // Konfirmasi
            return;             // Keluar dari fungsi
        }
    }
    printf("ID alat tidak ditemukan.\n");  // Pesan jika ID tidak ketemu
}
```

---

## 14. FUNGSI EDIT_TOOL (Baris 148-173)
```c
void edit_tool() {              // Fungsi untuk mengubah data alat
    unsigned int id;            // Variabel untuk menyimpan ID yang dicari
    printf("Masukkan ID alat yang ingin diedit: ");  // Minta input
    scanf("%u", &id);           // Baca ID
    // Loop mencari alat dengan ID tertentu
    for (int i = 0; i < total_tools; i++) {
        if (tools[i].id == id) {        // Jika ID ketemu
            printf("Edit Nama (current: %s): ", tools[i].name);  // Tampilkan nama sekarang
            scanf(" %[^\n]", tools[i].name);  // Baca nama baru
            printf("Edit Merek (current: %s): ", tools[i].brand);  // Tampilkan merek sekarang
            scanf(" %[^\n]", tools[i].brand);  // Baca merek baru
            printf("Edit Model (current: %s): ", tools[i].model);  // Tampilkan model sekarang
            scanf(" %[^\n]", tools[i].model);  // Baca model baru
            printf("Edit Tahun (current: %u): ", tools[i].year);  // Tampilkan tahun sekarang
            scanf("%u", &tools[i].year);  // Baca tahun baru
            printf("Edit Jumlah (current: %u): ", tools[i].quantity);  // Tampilkan jumlah sekarang
            scanf("%u", &tools[i].quantity);  // Baca jumlah baru
            save_tools();       // Simpan ke file
            printf("Data alat berhasil diubah.\n");  // Konfirmasi
            return;             // Keluar dari fungsi
        }
    }
    printf("ID alat tidak ditemukan.\n");  // Pesan jika ID tidak ketemu
}
```

---

## 15. FUNGSI USER_VIEW_TOOLS (Baris 175-177)
```c
void user_view_tools() {        // Fungsi wrapper untuk user melihat alat
    list_tools();               // Panggil fungsi list_tools()
}
```

---

## 16. FUNGSI BORROW_TOOL (Baris 179-199)
```c
void borrow_tool() {            // Fungsi untuk meminjam alat
    unsigned int id, jumlah;    // Variabel untuk ID alat dan jumlah pinjam
    printf("Masukkan ID alat yang ingin dipinjam: ");  // Minta input
    scanf("%u", &id);           // Baca ID alat
    printf("Jumlah yang ingin dipinjam: ");  // Minta input
    scanf("%u", &jumlah);       // Baca jumlah pinjam
    // Loop mencari alat dengan ID tertentu
    for (int i = 0; i < total_tools; i++) {
        if (tools[i].id == id) {        // Jika ID ketemu
            // Cek apakah stok cukup
            if (tools[i].quantity >= jumlah) {
                tools[i].quantity -= jumlah;  // Kurangi stok
                save_tools();   // Simpan ke file
                printf("Alat berhasil dipinjam.\n");  // Konfirmasi
                return;         // Keluar dari fungsi
            } else {
                printf("Jumlah alat tidak cukup.\n");  // Pesan stok kurang
                return;         // Keluar dari fungsi
            }
        }
    }
    printf("ID alat tidak ditemukan.\n");  // Pesan jika ID tidak ketemu
}
```

---

## 17. FUNGSI RETURN_TOOL (Baris 201-218)
```c
void return_tool() {            // Fungsi untuk mengembalikan alat
    unsigned int id, jumlah;    // Variabel untuk ID alat dan jumlah kembalian
    printf("Masukkan ID alat yang dikembalikan: ");  // Minta input
    scanf("%u", &id);           // Baca ID alat
    printf("Jumlah yang dikembalikan: ");  // Minta input
    scanf("%u", &jumlah);       // Baca jumlah kembalian
    // Loop mencari alat dengan ID tertentu
    for (int i = 0; i < total_tools; i++) {
        if (tools[i].id == id) {        // Jika ID ketemu
            tools[i].quantity += jumlah;  // Tambah stok
            save_tools();       // Simpan ke file
            printf("Alat berhasil dikembalikan.\n");  // Konfirmasi
            return;             // Keluar dari fungsi
        }
    }
    printf("ID alat tidak ditemukan.\n");  // Pesan jika ID tidak ketemu
}
```

---

## 18. FUNGSI MAIN (Baris 220-228)
```c
int main(int argc, char *argv[]) {      // Fungsi utama program
    // argc = jumlah argumen (program name + 2 argumen), argv = array argumen
    if (argc != 3) {            // Cek apakah argumen tepat 3 (program, username, password)
        printf("Usage: %s <username> <password>\n", argv[0]);  // Tampilkan cara pakai
        return 1;               // Return 1 (error)
    }

    load_accounts();            // Muat data akun dari file
    load_tools();               // Muat data alat dari file

    Account *current_user = login(argv[1], argv[2]);  // Verifikasi login
    if (!current_user) {        // Jika login gagal (NULL)
        printf("Login gagal!\n");      // Tampilkan pesan error
        return 1;               // Return 1 (error)
    }

    printf("Selamat datang, %s (%s)\n", current_user->username, current_user->role);  // Sambutan

    int exit = 0;               // Flag untuk keluar dari program (0 = belum keluar)
    int choice;                 // Variabel untuk menyimpan pilihan menu
```

---

## 19. MAIN LOOP - ADMIN MENU (Baris 230-265)
```c
    while (!exit) {             // Loop selama exit = 0 (user belum keluar)
        // Cek role pengguna
        if (strcmp(current_user->role, "admin") == 0) {  // Jika role adalah "admin"
            printf("\n=== Menu Admin ===\n");  // Tampilkan judul menu
            printf("1. Lihat alat\n");   // Opsi 1
            printf("2. Tambah alat\n");  // Opsi 2
            printf("3. Hapus alat\n");   // Opsi 3
            printf("4. Ubah alat\n");    // Opsi 4
            printf("5. Keluar\n");       // Opsi 5
            printf("Pilih: ");           // Minta input
            scanf("%d", &choice);        // Baca pilihan

            switch (choice) {            // Switch berdasarkan pilihan
                case 1:
                    list_tools();        // Panggil fungsi lihat alat
                    break;               // Keluar dari switch
                case 2:
                    add_tool();          // Panggil fungsi tambah alat
                    break;               // Keluar dari switch
                case 3:
                    delete_tool();       // Panggil fungsi hapus alat
                    break;               // Keluar dari switch
                case 4:
                    edit_tool();         // Panggil fungsi edit alat
                    break;               // Keluar dari switch
                case 5:
                    exit = 1;            // Set exit = 1 (keluar dari loop)
                    break;               // Keluar dari switch
                default:
                    printf("Pilihan tidak valid.\n");  // Pesan pilihan salah
            }
```

---

## 20. MAIN LOOP - USER MENU (Baris 266-287)
```c
        } else {                 // Jika role bukan "admin" (adalah "user")
            printf("\n=== Menu User ===\n");  // Tampilkan judul menu
            printf("1. Lihat alat\n");   // Opsi 1
            printf("2. Pinjam alat\n");  // Opsi 2
            printf("3. Kembalikan alat\n");  // Opsi 3
            printf("4. Keluar\n");       // Opsi 4
            printf("Pilih: ");           // Minta input
            scanf("%d", &choice);        // Baca pilihan

            switch (choice) {            // Switch berdasarkan pilihan
                case 1:
                    list_tools();        // Panggil fungsi lihat alat
                    break;               // Keluar dari switch
                case 2:
                    borrow_tool();       // Panggil fungsi pinjam alat
                    break;               // Keluar dari switch
                case 3:
                    return_tool();       // Panggil fungsi kembalikan alat
                    break;               // Keluar dari switch
                case 4:
                    exit = 1;            // Set exit = 1 (keluar dari loop)
                    break;               // Keluar dari switch
                default:
                    printf("Pilihan tidak valid.\n");  // Pesan pilihan salah
            }
        }
    }

    printf("Terima kasih telah menggunakan sistem.\n");  // Pesan terakhir
    return 0;                   // Return 0 (program sukses)
}
```

---

## RINGKASAN ALUR PROGRAM

1. **Inisialisasi**: Load akun dan alat dari file
2. **Login**: Verifikasi username dan password
3. **Menu**: Tampilkan menu sesuai role (admin/user)
4. **Admin dapat**:
   - Lihat semua alat
   - Tambah alat baru
   - Hapus alat
   - Edit data alat
5. **User dapat**:
   - Lihat alat tersedia
   - Pinjam alat (kurangi stok)
   - Kembalikan alat (tambah stok)
6. **Simpan**: Setiap perubahan disimpan ke file

---

## FORMAT FILE

### `accounts.txt`
```
username,password,role
admin,admin123,admin
user1,pass123,user
```

### `tools.txt`
```
id,name,brand,model,year,quantity
1,Mikroskop,Zeiss,XY-100,2020,5
2,Beaker,Pyrex,500ml,2019,10
```
