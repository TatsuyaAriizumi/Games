//#define TETRIS_RUN
#ifdef TETRIS_RUN

#include "DxLib.h"
#include <time.h>

const int INIT = 0;
const int PLAY = 1;
const int OVER = 2;
int GameState = INIT;
const int BLOCKSIZE = 30;
const int ROWS = 20;
const int COLUMNS = 12;
const int WINDOW_WIDTH = BLOCKSIZE * COLUMNS;
const int WINDOW_HEIGHT = BLOCKSIZE * ROWS;
enum TYPE {
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	CYAN,
	BLUE,
	MAGENTA,
	WALL,
	BACK,
	BLACK
};
int Colors[10]{
	(int)GetColor(255,0,0),		// RED
	(int)GetColor(255,102,0),	// ORANGE
	(int)GetColor(255,255,0),	// YELLOW
	(int)GetColor(0,255,0),		// GREEN
	(int)GetColor(0,160,233),	// CYAN
	(int)GetColor(0,0,255),		// BLUE
	(int)GetColor(255,0,255),	// MAGENTA
	(int)GetColor(32,40,40),	// WALL
	(int)GetColor(16,16,16),	// BACK
	(int)GetColor(0,0,0)		// BLACK
};
int Stage[ROWS][COLUMNS];
int X, Y, R;
int PatternX[4], PatternY[4];
int PatternNum;
int Pattern[7][3][2] = {
	-1, 0,  1, 0,  2, 0,	//Å°Å†Å°Å°...RED

	-1, -1,					//Å°
	-1, 0,         1, 0,	//Å°Å†Å°...ORANGE

				   1, -1,	//Å@Å@Å°
	-1, 0,         1, 0,	//Å°Å†Å°...YELLOW

	-1, 0,					//Å°Å†
			0, 1,  1, 1,	//  Å°Å°...GREEN

				   1, 0,	//  Å†Å°
	-1, 1,  0, 1,			//Å°Å°...CYAN

			0, -1,			//  Å°
	- 1, 0,		   1, 0,	//Å°Å†Å°...BLUE

			1, 0,			//Å†Å°
	 0, 1,  1, 1			//Å°Å°...MAGENTA
};
int LoopCnt = 0;

void init() {
	for (int y = 0; y < ROWS; y++) {
		Stage[y][0] = WALL;
		Stage[y][COLUMNS - 1] = WALL;
		for (int x = 1; x < COLUMNS - 1; x++) {
			Stage[y][x] = BACK;
			if (y == ROWS - 1) Stage[y][x] = WALL;
		}
	}
	X = 5;
	Y = 1;
	R = 0;
	srand(time(NULL));
	PatternNum = rand() % 7;
	GameState = PLAY;
}

void drawStage() {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			DrawBox(BLOCKSIZE * x, BLOCKSIZE * y, BLOCKSIZE * (x + 1) + 1, BLOCKSIZE * (y + 1) + 1, Colors[Stage[y][x]], TRUE);
			DrawLine(BLOCKSIZE * x, BLOCKSIZE * y, BLOCKSIZE * (x + 1) + 1, BLOCKSIZE * y, Colors[BLACK]);
			DrawLine(BLOCKSIZE * (x + 1) + 1, BLOCKSIZE * y, BLOCKSIZE * (x + 1) + 1, BLOCKSIZE * (y + 1) + 1, Colors[BLACK]);
			DrawLine(BLOCKSIZE * (x + 1) + 1, BLOCKSIZE * (y + 1) + 1, BLOCKSIZE * x, BLOCKSIZE * (y + 1) + 1, Colors[BLACK]);
			DrawLine(BLOCKSIZE * x, BLOCKSIZE * (y + 1) + 1, BLOCKSIZE * x, BLOCKSIZE * y, Colors[BLACK]);
		}
	}
}

void setPosition() {
	PatternX[0] = X;
	PatternY[0] = Y;
	int r = R % 4;
	for (int i = 0; i < 3; i++) {
		int x = Pattern[PatternNum][i][0];
		int y = Pattern[PatternNum][i][1];
		for (int j = 0; j < r; j++) {
			int cmp = x;
			x = -y;
			y = cmp;
		}
		PatternX[i + 1] = X + x;
		PatternY[i + 1] = Y + y;
	}
}

void setPattern() {
	setPosition();
	for (int i = 0; i < 4; i++) {
		int x = PatternX[i];
		int y = PatternY[i];
		Stage[y][x] = PatternNum;
	}
}

void deletePattern() {
	setPosition();
	for (int i = 0; i < 4; i++) {
		int x = PatternX[i];
		int y = PatternY[i];
		Stage[y][x] = BACK;
	}
}

bool collision() {
	setPosition();
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		int x = PatternX[i];
		int y = PatternY[i];
		if(Stage[y][x] != BACK) flag = true;
	}
	return flag;
}

void complete() {
	for (int y = 1; y < ROWS - 1; y++) {
		bool flag = true;
		for (int x = 1; x < COLUMNS - 1; x++)
			if (Stage[y][x] == BACK) flag = false;
		if (flag) {
			for (int upy = y - 1; upy > 0; upy--)
				for (int x = 1; x < COLUMNS - 1; x++)
					Stage[upy + 1][x] = Stage[upy][x];
		}
	}
}

void play() {
	//Stage[Y][X] = BACK;
	deletePattern();

	int dy = 0, dx = 0, dr = 0;
	if ((++LoopCnt %= 10) == 0) dy = 1;
	if (CheckHitKey(KEY_INPUT_A)) dx = -1;
	if (CheckHitKey(KEY_INPUT_D)) dx = 1;
	if (CheckHitKey(KEY_INPUT_W)) dr = 1;
	if (CheckHitKey(KEY_INPUT_S)) dy = 1;
	Y += dy;
	X += dx;
	R += dr;
	//if (Stage[Y][X] != BACK) {
	if (collision()) {
		Y -= dy;
		X -= dx;
		R -= dr;
		if (dy == 1 && dx == 0 && dr == 0) {
			//Stage[Y][X] = PatternNum;
			setPattern();
			complete();
			// New Block
			Y = 1;
			X = 5;
			R = 0;
			PatternNum = rand() % 7;
			if (collision()) GameState = OVER;
		}
	}
	//Stage[Y][X] = PatternNum;
	setPattern();

	ClearDrawScreen();
	drawStage();
	ScreenFlip();
}

void over() {
	ClearDrawScreen();
	drawStage();
	DrawFormatString(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10, GetColor(255, 255, 255), "GAME OVER");
	ScreenFlip();
	if (CheckHitKey(KEY_INPUT_SPACE)) GameState = INIT;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		if (GameState == INIT) init();
		else if (GameState == PLAY) play();
		else if (GameState == OVER) over();
	}

	DxLib_End();
}


#endif 