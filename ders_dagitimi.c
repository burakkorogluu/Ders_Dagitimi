#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HOCA_SAYI 10
#define DERS_SAYI 26  

typedef struct {
	char dersadi[30];
	int section;
	int zaman;    // 0 = Öğle, 1 = Sabah, 2 = Akşam
	int sure;     // Sınav süresi (dakika)
} Ders;

typedef struct {
	char isim[20];
	float toplamyuk;   
	Ders dersler[50];
	int derssayisi;
	float kidem;

} Hoca;

// DERS YÜK KATSAYISI

float dersYukKatsayisi(Ders d) {
	float zamanK = 1.0;

	// Zaman katsayısı
	if (d.zaman == 0) zamanK = 0.5;  // öğle
	else if (d.zaman == 1) zamanK = 1.0; // sabah
	else if (d.zaman == 2) zamanK = 1.0; // akşam
	else if (d.zaman == 3) zamanK = 1.5; // gece


	float sureK = 0.0;

	// Sınav süre katsayısı

	if (d.sure > 120)      sureK = 1.0;
	else if (d.sure > 90)  sureK = 0.6;
	else if (d.sure > 60)  sureK = 0.4;
	else if (d.sure > 30)  sureK = 0.2;
	else                   sureK = 0.1;

	return zamanK + sureK;
}

// EN AZ YÜKLÜ HOCAYI BUL

int enazyuklu(Hoca hocalar[]) {
	int i, min = 0;

	float minAdjusted = hocalar[0].toplamyuk * (1.0 + hocalar[0].kidem);

	for (i = 1; i < HOCA_SAYI; i++) {
		float adjusted = hocalar[i].toplamyuk * (1.0 + hocalar[i].kidem);
		if (adjusted < minAdjusted) {
			minAdjusted = adjusted;
			min = i;
		}
	}
	return min;
}


// DAĞITMA

void dagitma(Hoca hocalar[], Ders dersler[]) {
	for (int i = 0; i < DERS_SAYI; i++) {
		for (int s = 0; s < dersler[i].section; s++) {

			int index = enazyuklu(hocalar);

			int d = hocalar[index].derssayisi;
			hocalar[index].dersler[d] = dersler[i];
			hocalar[index].derssayisi++;

			float yuk = dersYukKatsayisi(dersler[i]);
			hocalar[index].toplamyuk += yuk;
		}
	}
}


// SHUFFLE

void shuffle(Ders dersler[]) {
	for (int i = DERS_SAYI - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		Ders temp = dersler[i];
		dersler[i] = dersler[j];
		dersler[j] = temp;
	}
}

void shuffleHoca(Hoca hocalar[]) {
	for (int i = HOCA_SAYI - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		Hoca temp = hocalar[i];
		hocalar[i] = hocalar[j];
		hocalar[j] = temp;
	}
}


int main() {
	srand(time(NULL));

	Hoca hocalar[HOCA_SAYI] = {
		{"UCO", 0, {}, 0, 1.0},
		{"YEG", 0, {}, 0, 1.0},
		{"ID", 0, {}, 0, 0.9},
		{"IMH", 0, {}, 0, 0.8},
		{"MBI", 0, {}, 0, 0.8},
		{"BK", 0, {}, 0, 0.8},
		{"UE", 0, {}, 0, 0.8},
		{"OCG", 0, {}, 0, 0.8},
		{"HC", 0, {}, 0, 0.7},
		{"TS", 0, {}, 0, 0.9}
	};

	
	Ders dersler[DERS_SAYI] = {
		{"A", 6, 1, 90}, {"A2", 4, 0, 60}, {"A3", 4, 2, 120},
		{"A4", 4, 1, 75}, {"A5", 4, 0, 50}, {"A6", 4, 1, 90},
		{"A7", 4, 2, 110}, {"A8", 3, 0, 45}, {"A9", 7, 1, 100},
		{"A10", 4, 2, 80}, {"A11", 2, 1, 60}, {"A12", 4, 0, 70},
		{"A13", 5, 1, 95}, {"A14", 6, 2, 120}, {"A15", 4, 1, 60},
		{"A16", 4, 0, 40}, {"A17", 4, 1, 85}, {"A18", 4, 2, 100},
		{"A19", 4, 0, 55}, {"A20", 4, 2, 150}, {"A21", 4, 1, 90},
		{"A22", 9, 0, 60}, {"A23", 11, 2, 120}, {"A24", 8, 1, 75},
		{"A25", 7, 0, 45}, {"A26", 9, 3, 130}
	};

	shuffle(dersler);
	shuffleHoca(hocalar);
	dagitma(hocalar, dersler);

	printf("===== HOCA YUKLERI VE DERSLER =====\n\n");

	for (int h = 0; h < HOCA_SAYI; h++) {
		printf("%s (Kidem: %.1f, Toplam Yuk: %.2f):\n",
			hocalar[h].isim, hocalar[h].kidem, hocalar[h].toplamyuk);

		for (int j = 0; j < hocalar[h].derssayisi; j++) {
			printf("  - %s\n", hocalar[h].dersler[j].dersadi);
		}
		printf("\n");
	}

	printf("===== DERS -> HOCA ESLEMESI =====\n\n");

	for (int d = 0; d < DERS_SAYI; d++) {
		printf("%s dersi: ", dersler[d].dersadi);
		for (int h = 0; h < HOCA_SAYI; h++) {
			for (int j = 0; j < hocalar[h].derssayisi; j++) {
				if (strcmp(hocalar[h].dersler[j].dersadi, dersler[d].dersadi) == 0) {
					printf("%s ", hocalar[h].isim);
				}
			}
		}
		printf("\n");
	}

	return 0;
}


