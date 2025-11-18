#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 5000
#define MAX_WORD_LEN 100

// Membersihkan kata: hanya huruf, angka, dan apostrophe
void bersihkan_kata(char *src, char *dst) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (isalnum(src[i]) || src[i] == '\'') {
            dst[j++] = tolower(src[i]);
        }
    }
    dst[j] = '\0';
}

// Cek apakah kata sudah ada
int sudah_ada(char kata[][MAX_WORD_LEN], int count, char *baru) {
    for (int i = 0; i < count; i++) {
        if (strcmp(kata[i], baru) == 0) return 1;
    }
    return 0;
}

int main() {
    FILE *fin = fopen("lirik.txt", "r");
    FILE *fout = fopen("kosa-kata.word", "w");

    if (!fin || !fout) {
        printf("Gagal membuka file.\n");
        return 1;
    }

    char line[1000];
    char words[MAX_WORDS][MAX_WORD_LEN];
    int word_count = 0;

    // --- Ambil judul (baris pertama) ---
    fgets(line, sizeof(line), fin);
    fprintf(fout, "%s", line);   // tulis judul apa adanya

    // --- Proses sisa lirik ---
    while (fgets(line, sizeof(line), fin)) {
        char *token = strtok(line, " \n\t");

        while (token != NULL) {
            char cleaned[MAX_WORD_LEN] = "";
            bersihkan_kata(token, cleaned);

            if (strlen(cleaned) > 0 && !sudah_ada(words, word_count, cleaned)) {
                strcpy(words[word_count], cleaned);
                word_count++;
            }

            token = strtok(NULL, " \n\t");
        }
    }

    // --- Tulis ke file output ---
    for (int i = 0; i < word_count; i++) {
        fprintf(fout, "%s=\n", words[i]);
    }

    fclose(fin);
    fclose(fout);

    printf("File 'kosa-kata.word' berhasil dibuat!\n");
    return 0;
}

