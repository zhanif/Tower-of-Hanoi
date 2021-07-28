/**
 * Kelompok 6
 * 
 * Anggota:
 * 201524003 - Diana Fauziah
 * 201524011 - Ihsan Fauzan Hanif
 * 201524014 - Muhammad Aziz Taufiqurrahman
 * 
 * game.c
 * Implementasi kode program dari struktur data pada file game.h
 */

#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include <unistd.h>
#include "include/all.h"

#define ESC 27		// key ESC
#define ENTER 13	// key ENTER

/**
 * Membersihkan isi terminal
 * @author Ihsan Fauzan Hanif
 */
void cls()
{
	// hapus isi terminal dan set warna default menjadi bawaan
	// dari terminal (putih biasanya)
	system("cls");
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi = {0};
	GetConsoleScreenBufferInfo(hOutput, &csbi);
	SetConsoleTextAttribute(hOutput, csbi.wAttributes);
}
/**
 * Inisialisasi sistem Game, bertujuan untuk mengatur agar semua
 * informasi terkait dengan Game bernilai kosong
 * @author
 * Diana Fauziah
 * 07/21/21
 */
void createGame(Game *game)
{	
	//membuat semua game kosong/membentuk game baru
	memset(game, 0, sizeof(Game));
}
/**
 * Inisialisasi sistem game dan threading
 * @author Ihsan Fauzan Hanif
 */
void createRunner(Runner *runner)
{
	// mengisi blok memori yang digunakan Runner dengan nilai 0
	memset(runner, 0, sizeof(*runner));
}
/**
 * Menu utama dalam permainan
 * @author Ihsan Fauzan Hanif
 */
void menuMain(Game *game)
{
	bool showInvalidMsg = false;

	// pointer ke fungsi menu yang digunakan pada program
	void (*menuSelect[6])(Game*) = {
		menuPlayGame,
		menuLoadGame,
		menuPracticeGame,
		menuHighScore,
		menuCredits,
		menuExit
	};
	while (true)
	{
		cls();
		printf("-------------------------------------------------\n");
		printf("\t\tTower of Hanoi\n");
		printf("-------------------------------------------------\n");
		printf("\n[1]. Permainan Baru\n");
		printf("[2]. Lanjutkan Permainan\n");
		printf("[3]. Permainan Kustom\n");
		printf("[4]. Skor Tertinggi\n");
		printf("[5]. Tentang Permainan\n");
		printf("[6]. Keluar\n");

		// tampilkan pesan jika input tidak valid
		if (showInvalidMsg)
		{
			printf("\nInput tidak valid!\n");
			showInvalidMsg = false;
		}
		printf("\nInput: ");
		int input = 0;
		scanf("%d", &input);
		fflush(stdin);
		input--;
		if (input < 0 || input > 5) showInvalidMsg = true;
		else
		{
			// panggil fungsi via pointer
			menuSelect[input](game);
		}
	}
}
/**
 * Menu untuk memulai permainan baru
 * @author M Aziz Taufiqurrahman
 */
void menuPlayGame(Game *game)
{ 
	cls();
	createGame(game);
	printSaveGame(); 
	printf("\n0. Kembali\n");
	printf("masukkan posisi yang akan digunakan untuk menyimpan permainan: "); 
	scanf("%d", &game->index); 

	// set index atau posisi dari permainan pada data save game
	// (hitungan dimulai dari 0)
	if (game->index == 0) return;
	game->index--; 

	game->towerLevel = 1;
	fflush(stdin);
	printf ("Silakan, masukan nama anda : ");
	scanf("%[^\n]s", game->playerName); 
	fflush(stdin);
	saveGame(game, game->index);
	menuLobby(game);
}
/**
 * Menu untuk memuat permainan lama (yang telah tersimpan)
 * @author M Aziz Taufiqurrahman
 */
void menuLoadGame(Game *game) {
	int pilihan;
	cls();
	printSaveGame(); 
	printf("\n0. Kembali\n");
	printf("masukkan posisi dari game yang ingin dilanjutkan : ");  
	scanf ("%d", &pilihan); 
	if (pilihan == 0) return;
	fflush(stdin);

	// ambil data permainan berdasarkan index/pilihan (hitungan
	// dimulai dari 0)
	*game = loadGame(--pilihan);
	menuLobby(game);
}
/**
 * Menu untuk membuat permainan yang dikustomisasi oleh pemain
 * @author
 * Diana Fauziah
 * 07/21/21
 */
void menuPracticeGame(Game *game)
{
	while(true){
	cls();
	createGame(game);
	printf("-----------------MENU PRACTICE GAME---------------\n\n");
	printf("Masukan Banyaknya disk pada permainan : ");
	scanf("%d", &game->maxDisk);
	fflush(stdin);
		if(game->maxDisk == 1 || game->maxDisk== 2 || game->maxDisk == 3 ||game->maxDisk == 4 || game->maxDisk == 5){
			game->mode = PRACTICE;
			menuLobby(game);
			return;
		}	
	}
}
/**
 * Menu untuk menampilkan top 10 pemain dengan skor tertinggi
 * @author M Aziz Taufiqurrahman
 */
void menuHighScore(Game *game)
{
	char pilihan;
	cls();
	printf ("Berikut ini merupakan daftar 10 pemain dengan skor tertinggi : \n");
	printAllHighScore();
	printf ("Hapus High Score? y/n ");
	scanf ("%c", &pilihan);
	fflush(stdin);
	switch (pilihan) {
		case 'y' :
			deleteAllHighScore();
			return menuHighScore(game);
			break; 
		case 'n' : break;
		default : printf ("Anda memasukkan nilai yang salah :( ");
	}
	system("pause");
}
/**
 * Menu untuk menampilkan informasi mengenai game dan/atau developer
 * @author
 * Diana Fauziah
 * 07/21/21
 */
void menuCredits(Game *game)
{
	cls();
	printf("***********************************************************************************\n");
	printf("\t\t TOWER OF HANOI\n");
	printf("***********************************************************************************\n\n");
	printf("Permainan yang bertujuan untuk melatih kemampuan\n");
	printf("Matematis anda dalam memperhitungkan langkah untuk\n");
	printf("menyelesaikan permasalahan yang dilakukan dengan cara\n");
	printf("memindahkan seluruh disk pada tower yang ada di ujung\n");
	printf("===================================================================================\n\n");
	printf("--------------------------------------------------------\n");
	printf("|Tower of Hanoi dibuat oleh :							|\n");
	printf("|Diana Fauziah - Tunjukkan Versi Terbaik Anda!!!!   	|\n");
	printf("|Ihsan Fauzan Hanif - Orang yang menyukai pemrograman  	|\n");
	printf("|M Aziz Taufiqurrahman                                 	|\n");
	printf("--------------------------------------------------------\n");
	system("pause");
}
/**
 * Menu untuk keluar dari program
 * @author
 * Diana Fauziah
 * 07/21/21
 */
void menuExit(Game *game)
{
    char ch;
	cls();
    printf("-------------------------------------------------\n");
    printf("|Apakah Anda yakin ingin meninggalkan permainan? |\n");
    printf("\n|  Tekan [ESC] untuk keluar                    |\n");
    printf("=================================================\n");
    do {
		// jika tombol yang ditekan itu ESC, hentikan program
        ch = getch();
        if(ch == ESC){
        	exit(0);
        }
		else break;
    } while(ch != ESC);
}
/**
 * Menu sebagai tempat berhenti sesaat sebelum permainan dimulai
 * @author M Aziz Taufiqurrahman
 */
void menuLobby(Game *game) {
	int pilihan;
	cls();
	printf ("1. Mulai Permainan\n");
	printf ("2. Menu Utama\n");
	printf ("Masukkan pilihan Anda : ");
	scanf ("%d", &pilihan);
	fflush(stdin);
	switch (pilihan) {
		case 1 : gameEntry(game); break;
		case 2 : menuMain(game); break;
		default : printf ("Mohon maaf Anda salah dalam input nilai :( ");
	}
}
/**
 * Menu untuk memulai permainan baru
 * @author Ihsan Fauzan Hanif
 */
void menuPauseGame(Game *game)
{
	game->isPaused = true;
	cls();
	printf("-------------------------------------------------\n");
	printf("\t\tTower of Hanoi\n");
	printf("-------------------------------------------------\n\n\n");
	printTower(game);
	printf("\n[GAME DIJEDA]\n");
	if (game->mode == ORIGINAL) printf("\nWaktu tersisa: %d detik", game->timeLeft);	
	printf("\n[Enter] Lanjutkan Permainan\n[ESC] Menyerah\n\nInput: ");
	while (true)
	{
		// selagi dijeda, jika menerima key input ENTER lanjutkan permainan, jika ESC
		// permainan berakhir (kalah)
		fflush(stdin);
		char input = getch();
		if ((int)input == ENTER)
		{
			game->isPaused = false;
			break;
		}
		else if ((int)input == ESC)
		{
			game->state = LOSE;
			break;
		}
	}
}
/**
 * Menu untuk memulai permainan baru
 * @author Ihsan Fauzan Hanif
 */
void menuShowStep(Game *game)
{
	cls();
	ShowStep(game, game->towerLevel);
	printf("\n");
	printf("\nTekan 'Enter' untuk melanjutkan");
	while (true)
	{
		// keluar dari menu ini jika input key-nya ENTER
		fflush(stdin);
		char input = getch();
		if ((int)input == ENTER) break;
	}
}
/**
 * Mendapatkan disk maksimal yang bisa dimasukkan berdasarkan level dari tower 
 * @author M Aziz Taufiqurrahman
 */
int getMaxDisk(int towerLevel) {
	switch (towerLevel) {
		case 1 : return 2; break;
		case 2 : return 3; break;
		case 3 : return 4; break;
		case 4 : return 5; break;
		case 5 : return 5; break;
	}
}
/**
 * Mendapatkan waktu maksimal yang bisa digunakan untuk bermain berdasarkan level
 * dari permainan
 * @author M Aziz Taufiqurrahman
 */
int getMaxTime(int towerLevel) {
	// mengembalikan nilai (waktu) yang tersedia untuk satu level dalam hitungan detik
	switch (towerLevel){
		case 1 : return 30; break; 
		case 2 : return 60; break; 
		case 3 : return 100; break; 
		case 4 : return 300; break; 
		case 5 : return 150; break;
	}
}
/**
 * Mendapatkan pergerakan minimal yang bisa dilakukan untuk menyelesaikan permainan
 * @author
 */
int getMinMoves(int towerLevel)
{
	// bit shifting kurangi satu
	// misal untuk 2 tower, seminimalnya ada 3 langkah,
	// satu pada blok memori dishift 2x kemudian dikurangi 1
	// -------------- 8 4 2 1
	// sebelum shift: 0 0 0 1 [1]
	// setelah shift: 0 1 0 0 [4]
	// setelah dikurangi 1: 0 0 1 1 [3]
	return 1 << towerLevel - 1;
}
/**
 * Memindahkan blok pada tower yang satu ke tower yang lain
 * @author
 * Diana Fauziah
 * 07/22/21
 */
void moveDisk(Tower* src, Tower* dest)
{
	// lepas disk dari tower satu, ambil datanya, kemudian tower tujuan diisi disk
	// dengan data (width) yang dilepas tadi
    int width = 0;
    pop(src, &width);
    push(dest, width);
}
/**
 * Menyimpan game dengan posisi penyimpanan berdasarkan index
 * @author Ihsan Fauzan Hanif
 */
bool saveGame(Game *game, int index)
{
    bool retVal = false;
    int maxSize = sizeof(*game) * MAX_SAVED_GAME;

	// alokasi memori dengan ukuran yang bisa menjangkau seluruh data save game
	// kemudian isi memori tersebut dengan data dari save game
    char *gameData = malloc(maxSize);
    memset(gameData, 0, maxSize);
    loadAllSaveGame(gameData, maxSize);
    
	// copy isi game ke save game (dengan posisi sesuai index (index perhitungan
	// data save game))
    memcpy(gameData + (index * sizeof(*game)), game, sizeof(*game));
    FILE *file = fopen("save.dat", "wb");
    if (!file)
    {
        printf("Error: Unable to create the file");
        system("pause");
        exit(EXIT_FAILURE);
    }
	// simpan data tersebut pada file save game
    if (fwrite(gameData, maxSize, 1, file) == 1) retVal = true;
    fclose(file);
    free(gameData);
    return retVal;
}
/**
 * Memuat seluruh data permainan tersimpan
 * @author Ihsan Fauzan Hanif
 */
void loadAllSaveGame(char* result, int memorySize)
{
	// masukkan semua data save game ke result
    FILE *file = fopen("save.dat", "rb");
    if (file) fread(result, memorySize, 1, file);
    fclose(file);
}
/**
 * Memuat game yang terdapat pada save game berdasarkan index
 * @author Ihsan Fauzan Hanif
 */
Game loadGame(int index)
{
    Game retVal;
    memset(&retVal, 0, sizeof(retVal));
    int maxSize = sizeof(retVal) * MAX_SAVED_GAME;
    char *gameData = malloc(maxSize);

	// ambil save game, copy isi save game dengan index yang diminta ke retVal
    loadAllSaveGame(gameData, maxSize);
    memcpy(&retVal, gameData + (index * sizeof(retVal)), sizeof(retVal));
    free(gameData);
    return retVal;
}
/**
 * Menghapus data game yang telah tersimpan
 * @author Ihsan Fauzan Hanif
 */
bool deleteGame(int index)
{
	// set blok memori menjadi nol dan simpan hasil perubahan tersebut
    Game g;
    memset(&g, 0, sizeof(Game));
    return saveGame(&g, index);
}
/**
 * Menampilkan daftar permainan tersimpan
 * @author Ihsan Fauzan Hanif
 */
void printSaveGame()
{
	Game sgData[MAX_SAVED_GAME] = {0};
	Game game;

	int maxSize = sizeof(Game) * MAX_SAVED_GAME;
    char *gameData = malloc(maxSize);
	memset(gameData, 0, maxSize);
	loadAllSaveGame(gameData, maxSize);
	memcpy(sgData, gameData, maxSize);
	free(gameData);

	int i;
	for (i = 0; i < MAX_SAVED_GAME; i++)
	{
		game = sgData[i];
		if (game.index == 0 && strlen(game.playerName) == 0) printf("%02d. [Kosong]\n", i + 1);
		else printf("%02d. %s - Level: %d - Skor: %d %s\n", i + 1, game.playerName, game.towerLevel, game.score, game.isLevelMax? " [TAMAT]" : "");
	}
}
/**
 * Titik masuk dari permainan
 * @author Ihsan Fauzan Hanif
 */
void gameEntry(Game *game)
{
    game->isLevelMax = false;
    game->isPaused = false;

	// pengaturan untuk setiap mode permainan
	if (game->mode == ORIGINAL)
	{
		game->maxDisk = getMaxDisk(game->towerLevel);
		game->timeLeft = getMaxTime(game->towerLevel);
	}
	else game->towerLevel = game->maxDisk;

	// isi tower kiri dengan disk (terurut, 3 --> 2 --> 1)
	int i;
	for (i = game->maxDisk; i > 0; i--) push(&game->left, i);

	// sistem multi threading (menjalankan sistem dalam waktu yang bersamaan)
	// pertama sistem ketika permainan itu sendiri dijalankan
	// kedua sistem untuk mengurus waktu dari permainan
    pthread_t thGameRun, thGameTimer;
	Runner runner;
	createRunner(&runner);
	runner.game = &game;
	runner.threadGame = &thGameRun;
	runner.threadTimer = &thGameTimer;
    pthread_create(&thGameRun, NULL, gameRun, &runner);
    pthread_create(&thGameTimer, NULL, gameTimer, &runner);

	// gabungkan thread agar berjalan bersamaan
    pthread_join(thGameRun, NULL);
    pthread_join(thGameTimer, NULL);

	// setelah thread berakhir, hapus semua isi tower, dan masuk ke pengkondisian keadaan
	// dari permainan (menang/kalahnya)
	printf("\n[Permainan Berakhir]\n\n");
	Tower* tempAddr = &game->left;
	int x;
	while (!isEmpty(*tempAddr)) pop(tempAddr, &x);
	tempAddr = &game->middle;
	while (!isEmpty(*tempAddr)) pop(tempAddr, &x);
	tempAddr = &game->right;
	while (!isEmpty(*tempAddr)) pop(tempAddr, &x);
	printf(game->state == WIN? "Anda Menang!\n" : "Anda Kalah!\n");
	switch(game->state)
	{
		case WIN:
			if (game->mode == ORIGINAL)
			{
				// update skor jika menang
				game->score += (game->towerLevel * 100) + game->timeLeft - game->moveCount;
				if (game->towerLevel == 5) game->score += game->score * 2 / 10;
				printf("Skor Anda: %d\n", game->score);
				if (game->towerLevel < 5)
				{
					game->towerLevel++;
					saveGame(game, game->index);
					printf("Anda telah naik level! Lanjutkan sekarang? [Y/N] ");
					char input = (char)0;
					scanf("%c", &input);
					fflush(stdin);
					if (input == 'Y' || input == 'y') return menuLobby(game);
				}
				else
				{
					// hanya simpan skor dan data bahwa level sudah max kalau sudah mencapai
					// level 5
					game->isLevelMax = true;
					saveGame(game, game->index);
					printf("Selamat! Anda telah menyelesaikan semua level.\n");
					printf("Untuk mendapatkan skor lagi, anda bisa mengulangi level ini.\n\n");
					printf("Tekan tombol apapun untuk melanjutkan");
					getch();
					fflush(stdin);
				}
			}
			else
			{
				// hanya bisa mengulangi atau keluar dari permainan jika modenya PRACTICE
				printf("Ulangi permainan? [Y/N] ");
				char input = (char)0;
				scanf("%c", &input);
				fflush(stdin);
				if (input == 'Y' || input == 'y') return menuLobby(game);
			}
			return menuMain(game);
		case LOSE:
			if (game->mode == ORIGINAL)
			{
				// simpan skor hasil permainan jika kalah dalam permainan, juga hapus data
				// permainannya karena dilarang untuk mengulangi permainan ketika sudah kalah
				saveHighScore(*game);
				deleteGame(game->index);
				printf("Skor Anda: %d\n", game->score);
				printf("Permainan tidak dapat diulangi.\n");
				printf("Tekan tombol apapun untuk melanjutkan");
				getch();
				fflush(stdin);
			}
			else
			{
				// hanya bisa mengulangi atau keluar dari permainan jika modenya PRACTICE
				printf("Ulangi permainan? [Y/N] ");
				char input = (char)0;
				scanf("%c", &input);
				fflush(stdin);

				if (input == 'Y' || input == 'y') return menuLobby(game);
			}
			return menuMain(game);
	}
}
/**
 * Menampilkan output isi dari tower berdasarkan string.
 * @author Ihsan Fauzan Hanif
 */
void printTowerStr(char *str, int width)
{
	// inisialisasi handler standar output
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cInfo;

	// dapatkan informasi dari terminal
	GetConsoleScreenBufferInfo(hConsole, &cInfo);
	WORD consoleAttr = cInfo.wAttributes;
	int i, j;
	for (i = 0; i < strlen(str); i++)
	{
		// jika char posisi ke i (atau sama saja dengan str[i]) tidak berisi UI_BLOCK, skip
		if (*(str + i) != -37)
		{
			printf("%c", *(str + i));
			continue;
		}
		
		// jika charnya UI_BLOCK, loop sampai ujung dari char (spasi)
		int diskWidth = 0;
		int lastIndex = 0;
		for (j = i; j < strlen(str); j++)
		{
			diskWidth++;
			if (*(str + j) == ' ') break;
		}

		// kalkulasi panjang UI_BLOCK terhadap width dari disk
		lastIndex = diskWidth;
		diskWidth = (diskWidth - 1) / width / 2;
		int color = consoleAttr;

		// atur warna berdasarkan width dari disk
		switch (diskWidth)
		{
			case 1: color = 12; break; // merah
			case 2: color = 14; break; // kuning
			case 3: color = 10; break; // hijau
			case 4: color = 9; break; // biru
			case 5: color = 13; break; // ungu
		}
		SetConsoleTextAttribute(hConsole, color);
		int k;
		for (k = 0, j = i; k < lastIndex; k++, j++)
		{
			printf("%c", *(str + j));
		}
		SetConsoleTextAttribute(hConsole, consoleAttr);

		// loop kata berikutnya dimulai dengan posisi setelah spasi ditemukan
		i += lastIndex - 1;
	}
	printf("\n");
}
/**
 * Menampilkan tampilan dari tower
 * @author Ihsan Fauzan Hanif
 */
void printTower(Game* g)
{
	// Karakter yang ditampilkan pada terminal (berdasarkan kode ASCII)
	#define UI_BLOCK 219 // kotak
	#define UI_GROUND 196 // garis horizontal panjang
	#define UI_POLE 179 // garis vertikal panjang

	// size kotak yang di-print
	int sizeEach = 2;
	// panjang output: tower + spasi + panjang disk terhadap size kotak
	// (2 = tambahan kiri-kanan, 3 = banyak tower)
	int width = 3 + 3 + (g->maxDisk * (2 * sizeEach) * 3);

	// posisi tengah dari hasil print disk (3 disk):
	// lebar: 1
	// ---|--- ---|--- ---|---
	// 4 - 12 - 20
	// lebar: 2
	// ------|------ ------|------ ------|------
	// 7 - 21 - 35
	// lebar: 3
	// ---------|--------- ---------|--------- ---------|---------
	// 10 - 30 - 50
	// lebar: 4
	// ------------|------------
	// 13 - ? - ?
	// didapat rumus: sizeEach * maxDisk + 1

	// posisi tengah dari satu disk
	int midPos = sizeEach * g->maxDisk + 1;

	// posisi tengah dari disk terhadap tower (sesuai kalkulasi diatas)
	int middlePos[3] = {
		midPos - 1,
		midPos * 3 - 1,
		midPos * 5 - 1
	};

	char* output = malloc(width + 1);
	int height = g->maxDisk + 1;

	Address* diskLeft = &(g->left).top;
	Address* diskMiddle = &(g->middle).top;
	Address* diskRight = &(g->right).top;

	int heightDiskLeft = getDiskCount(&(g->left));
	int heightDiskMiddle = getDiskCount(&(g->middle));
	int heightDiskRight = getDiskCount(&(g->right));
	printf("\n");

	// loop setiap baris output
	int i, j;
	for (i = height + 1; i > 0; i--)
	{
		// set blok memori dengan spasi
		*(output + width) = (char)0;
		memset(output, ' ', width);

		// jika i = baris terakhir, set posisi tengah dengan nomor dari tower-nya
		if (i == 0 + 1)
		{
			memset(output, UI_GROUND, width);
			*(output + middlePos[0]) = '1';
			*(output + middlePos[1]) = '2';
			*(output + middlePos[2]) = '3';
		}
		else if (i > 0)
		{
			// nilai tengahnya pasti tiang dari tower
			*(output + middlePos[0]) = *(output + middlePos[1]) = *(output + middlePos[2]) = UI_POLE;

			// loop untuk setiap disk
			for (j = 0; j < 3; j++)
			{
				Address **diskPtr = (j == 0)? &diskLeft : (j == 1)? &diskMiddle : &diskRight;
				int *heightDisk = (j == 0)? &heightDiskLeft : (j == 1)? &heightDiskMiddle : &heightDiskRight;

				if (!(*diskPtr) || !(**diskPtr)) continue;
				if (i - 1 <= *heightDisk)
				{
					// copy nilai UI_BLOCK ke output
					int blockLen = ((**diskPtr)->width * 2) + 1;
					int pos = middlePos[j] - (**diskPtr)->width * sizeEach;
					memset(output + pos, UI_BLOCK, ((**diskPtr)->width * sizeEach) * 2 + 1);
					*diskPtr = &(**diskPtr)->next;
				}
			}
		}
		// print hasil dari proses pembuatan output menara (per baris)
		printTowerStr(output, sizeEach);
	}
	free(output);

	// lupakan pendefinisian tadi
	#undef UI_BLOCK
	#undef UI_POLE
	#undef UI_GROUND
}
/**
 * Menjalankan lojik dari permainan
 * @author Ihsan Fauzan Hanif
 */
void *gameRun(void *argsData)
{
	bool showInvalidMsg = false;
	Runner* runner = (Runner*)argsData;
	pthread_t* thTimer = runner->threadTimer;
    Game* game = *(runner->game);
	game->state = NONE;
    while (true)
    {
		cls();
		printf("-------------------------------------------------\n");
		printf("\t\tTower of Hanoi\n");
		printf("-------------------------------------------------\n");
        if (game->timeLeft <= 0 && game->mode == ORIGINAL)
		{
			// permainan kalah jika waktu habis pada mode original
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO csbi = {};
			
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			SetConsoleTextAttribute(hConsole, 12);
			printf("\nWaktu Habis! Tekan apapun untuk melanjutkan\n\n");
			SetConsoleTextAttribute(hConsole, csbi.wAttributes);

			// hentikan timer
			pthread_cancel(*thTimer);
			game->state = LOSE;
		}
		else printf("\n\n");
		printTower(game);
		
		if (game->state != NONE) break;
        if (game->isPaused) menuPauseGame(game);
        else
        {
			// terima input dari pemain
			printf("\n[P] Pause Game\n");
			if (game->mode == PRACTICE)
			{
				printf("[H] Show hint\n");
				printf("[Q] Menyerah\n");
			}
			printf("Masukkan nomor menara asal dan tujuan yang dipisahkan spasi untuk memindahkan disk.\n");
			printf("\nTotal langkah: %d\n", game->moveCount);
			if (showInvalidMsg)
			{
				printf("\nInput tidak valid!\n");
				showInvalidMsg = false;
			}
			printf("\nInput: ");
			char input[10] = {'\000'};
			fgets(input, 10, stdin);
			fflush(stdin);

			// pengkondisian input pemain
			input[strlen(input) - 1] = (char)0;
			if (game->mode == PRACTICE)
			{
				if (strcmp(input, "H") == 0 || strcmp(input, "h") == 0)
				{
					menuShowStep(game);
					continue;
				}
				if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
				{
					game->state = LOSE;
					continue;
				}
			}
			if (strcmp(input, "P") == 0 || strcmp(input, "p") == 0)
			{
				game->isPaused = true;
				continue;
			}

			// input char array ke angka (input tidak langsung angka karena input bisa
			// berupa char array)
			char *pSrc = strtok(input, " ");
			char *pDest = strtok(NULL, " ");

			int src = atoi(pSrc);
			int dest = atoi(pDest);
			if (src < 1 || src > 3 || dest < 1 || dest > 3)
			{
				showInvalidMsg = true;
				continue;
			}

			Tower *from = src == 1? &game->left : src == 2? &game->middle : &game->right;
			Tower *to = dest == 1? &game->left : dest == 2? &game->middle : &game->right;

			int topSrc = from->top? from->top->width : 0;
			int topDest = to->top? to->top->width : 0;

			// pindahkan disk jika disk asal lebih kecil dari tujuan, atau tujuannya kosong
			// dan juga posisinya harus berbeda
			if (
				(topSrc > 0 && topSrc < topDest) ||
				(topDest == 0 && topSrc != topDest)
			)
			{
				moveDisk(from, to);
				game->moveCount++;
				// jika total disk di tower kanan sama dengan jumlah maksimum maka pemain menang
				if (getDiskCount(&game->right) == game->maxDisk) game->state = WIN;
			}
			else showInvalidMsg = true;
        }
    }
    return NULL;
}
/**
 * Menjalankan timer dari permainan
 * @author Ihsan Fauzan Hanif
 */
void *gameTimer(void *argsData)
{
	Runner *runner = (Runner*) argsData;
	Game* game = *(runner->game);

	// toleransi waktu satu detik untuk bermain
	sleep(1);

	// inisialisasi koordinat untuk mengupdate timer
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	COORD timerCoord;
	timerCoord.X = 0;
	timerCoord.Y = 4;

    while (game->timeLeft > -1 && game->state == NONE)
    {
        if (!game->isPaused && game->mode == ORIGINAL)
		{
			// jika game tidak dijeda dan modenya original, maka timer setiap satu detik
			// mengupdate tampilan terminal
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			SetConsoleCursorPosition(hConsole, timerCoord);
			printf("                         ");
			SetConsoleCursorPosition(hConsole, timerCoord);

			// warnanya merah ketika timer tinggal 4 detik lagi
			if (game->timeLeft < 5) SetConsoleTextAttribute(hConsole, 12);
			if (game->timeLeft == 0)
			{
				// pemain kalah jika waktu habis
				printf("Waktu Habis! Tekan apapun untuk melanjutkan");
				game->state = LOSE;
			}
			else printf("Waktu Tersisa: %d detik", game->timeLeft);

			// kembali ke koordinat untuk memasukkan input
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			SetConsoleTextAttribute(hConsole, csbi.wAttributes);
			game->timeLeft--;
		}
        sleep(1);
    }
    return NULL;
}
/**
 * Menyimpan skor dari permainan
 * @author Ihsan Fauzan Hanif
 */
void saveHighScore(Game game)
{
	// alokasi blok memori untuk menyimpan seluruh data highscore
    int maxSize = sizeof(game) * MAX_SAVED_SCORE;
    Game HSdata[MAX_SAVED_SCORE];
    memset(&HSdata, 0, sizeof(HSdata));
    
    FILE *file = fopen("score.dat", "rb");
    if (file) fread(HSdata, maxSize, 1, file);
    fclose(file);

    // ambil data highscore yang dulu, kemudian data baru dimasukkan ke dalam highscore
	// apabila record terakhir pada highscore lebih dari data baru, kemudian sortir isinya
	if (game.score < HSdata[MAX_SAVED_SCORE - 1].score) return;
    memset(&HSdata[MAX_SAVED_SCORE - 1], 0, sizeof(HSdata[MAX_SAVED_SCORE - 1]));
    memcpy(&HSdata[MAX_SAVED_SCORE - 1], &game, sizeof(game));
    sortHighScore(HSdata);

	// simpan kembali ke file save highscore
    file = fopen("score.dat", "wb");
    if (!file) return;
    int code = fwrite(HSdata, sizeof(HSdata), 1, file);
    fclose(file);
}
/**
 * Menyortir isi dari file highscore
 * @author Ihsan Fauzan Hanif
 */
void sortHighScore(Game *game)
{
    Game temp;
    int i, j;
    for (i = 0; i < MAX_SAVED_SCORE; i++)
    {
        for (j = MAX_SAVED_SCORE - 1; j > i; j--)
        {
            if (game[j].score > game[j - 1].score)
            {
                memset(&temp, 0, sizeof(Game));
                memcpy(&temp, &game[j], sizeof(Game));

                memset(&game[j], 0, sizeof(Game));
                memcpy(&game[j], &game[j - 1], sizeof(Game));
                
                memset(&game[j - 1], 0, sizeof(Game));
                memcpy(&game[j - 1], &temp, sizeof(Game));
            }
        }
    }
}
/**
 * Menghapus semua skor yang tersimpan
 * @author Ihsan Fauzan Hanif
 */
bool deleteAllHighScore()
{
    return remove("score.dat") == 0? true : false;
}
/**
 * Menampilkan taktik bermain Tower of hanoi@author 
 * Diana Fauziah
 * 07/22/21
 */
void ShowStep(Game *game, int choose){
	cls();
	printf("===============================================================\n");
	printf("\t\t\t\t TAKTIK PERMAINAN TOWER OF HANOI\n");
	printf("===============================================================\n\n");
	
	if (choose == 1){
		printf("Level 1\n");
		printf("-------------------------------------------\n");
		printf("1. Gunakan rumus f(n) = 2^n-1), untuk menghitung jumlah minimal langkah\n");
		printf("2. untuk kasus ini terdapat 2 piringan berarti -> 2^2 - 1 = 3 (langkah)\n");
		printf("3. disk 1 -> tower C\n");
		printf("4. disk 2 -> tower B\n");
		printf("5. disk 1 -> tower B\n");
	}else if (choose == 2){
		printf("Level 2\n");
		printf("-------------------------------------------\n");
		printf("1. Gunakan rumus f(n) = 2^n-1), untuk menghitung jumlah minimal langkah\n");
		printf("2. untuk kasus ini terdapat 3 piringan berarti -> 2^3 - 1 = 7 (langkah)\n");
		printf("3. disk 1 -> tower C\n");
		printf("4. disk 2 -> tower B\n");
		printf("5. disk 1 -> tower B\n");
		printf("6. disk 3 -> tower C\n");
		printf("7. disk 1 -> tower A\n");
		printf("8. disk 2 -> tower C\n");
		printf("9. disk 1 -> tower C\n");
	}else if (choose == 3){
		printf("Level 3\n");
		printf("-------------------------------------------\n");
		printf("1. Gunakan rumus f(n) = 2^n-1), untuk menghitung jumlah minimal langkah\n");
		printf("2. untuk kasus ini terdapat 4 piringan berarti -> 2^4 - 1 = 15 (langkah)\n");
		printf("3. disk 1 -> tower C\n");
		printf("....................\n");
		printf("15. disk 1 -> tower B\n");
	}else if (choose == 4){
		printf("Level 4\n");
		printf("-------------------------------------------\n");
		printf("1. Gunakan rumus f(n) = 2^n-1), untuk menghitung jumlah minimal langkah\n");
		printf("2. untuk kasus ini terdapat 5 piringan berarti -> 2^5 - 1 = 31 (langkah)\n");
		printf("3. disk 1 -> tower C\n");
		printf("....................\n");
		printf("31. disk 1 -> tower B\n");
	}else if (choose == 5){
		printf("Level 5\n");
		printf("-------------------------------------------\n");
		printf("1. Gunakan rumus f(n) = 2^n-1), untuk menghitung jumlah minimal langkah\n");
		printf("2. untuk kasus ini terdapat 5 piringan berarti -> 2^5 - 1 = 31 (langkah)\n");
		printf("3. disk 1 -> tower C\n");
		printf("....................\n");
		printf("15. disk 1 -> tower B\n");
	}
}
/**
 * Menampilkan seluruh daftar high score
 * @author Ihsan Fauzan Hanif
 */
void printAllHighScore()
{
	int maxSize = sizeof(Game) * MAX_SAVED_SCORE;
    Game HSdata[MAX_SAVED_SCORE] = {0};
	Game game;

	// baca semua isi file dan masukkan pada array highscore
    FILE *file = fopen("score.dat", "rb");
    if (file) fread(HSdata, maxSize, 1, file);
    fclose(file);
	int i;
	for (i = 0; i < MAX_SAVED_SCORE; i++)
	{
		game = HSdata[i];
		if (game.index == 0 && strlen(game.playerName) == 0) printf("%02d. [Kosong]\n", i + 1);
		else printf("%02d. %s - Skor: %d - Total Langkah: %d\n", i + 1, game.playerName, game.score, game.moveCount);
	}
}
/**
 * Inisialisasi pengaturan sistem pada game
 * @author Ihsan Fauzan Hanif
 */
void initializeGameSystem(Game* game)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // set agar pthread bisa dicancel
	createGame(game); // inisialisasi game
}
