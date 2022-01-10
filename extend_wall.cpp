//#define EXTEND_WALL_RUN
#ifdef EXTEND_WALL_RUN

#include "DxLib.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

#define WHITE (GetColor(255,255,255))
#define BLACK (GetColor(0,0,0))
#define GREY (GetColor(128,128,128))
#define RED (GetColor(255,0,0))

enum MODE {
	INIT,
	CREATE,
	OVER,
	STATE_MAX
};

enum TYPE {
	PATH,
	WALL,
	CREATING
};

enum DIRECTION {
	EAST,
	NORTH,
	WEST,
	SOUTH,
	DIRECTION_MAX
};

typedef struct {
	int x, y;
} POSITION;

typedef struct {
	int x, y;
} DIR;

DIR Dir[DIRECTION_MAX] = {
	 1,  0,		// EAST
	 0, -1,		// NORTH
	-1,  0,		// WEST
	 0,  1		// SOUTH
};

int ModeState = INIT;
const int CELL_SIZE = 30;
const int BLANK = 50;
const int MAZE_SIZE = 15;			// MazeSize must be odd.
TYPE Maze[MAZE_SIZE][MAZE_SIZE];
vector<POSITION> Candidate;

void PrintMode() {
	switch (ModeState) {
	case INIT:		DrawFormatString(0, 0, WHITE, "INIT");		break;
	case CREATE:	DrawFormatString(0, 0, WHITE, "CREATE");	break;
	case OVER:		DrawFormatString(0, 0, WHITE, "OVER");		break;
	default:													break;
	}
}

void DrawMaze() {
	for (int y = 0; y < MAZE_SIZE; y++) {
		for (int x = 0; x < MAZE_SIZE; x++) {
			if (Maze[y][x] == WALL)
				DrawBox(CELL_SIZE * x, CELL_SIZE * y + BLANK, CELL_SIZE * (x + 1) + 1, CELL_SIZE * (y + 1) + 1 + BLANK, GREY, TRUE);
			else if (Maze[y][x] == CREATING)
				DrawBox(CELL_SIZE * x, CELL_SIZE * y + BLANK, CELL_SIZE * (x + 1) + 1, CELL_SIZE * (y + 1) + 1 + BLANK, RED, TRUE);

			DrawLine(CELL_SIZE * x, CELL_SIZE * y + BLANK, CELL_SIZE * (x + 1), CELL_SIZE * y + BLANK, WHITE);
			DrawLine(CELL_SIZE * (x + 1), CELL_SIZE * y + BLANK, CELL_SIZE * (x + 1), CELL_SIZE * (y + 1) + BLANK, WHITE);
			DrawLine(CELL_SIZE * (x + 1), CELL_SIZE * (y + 1) + BLANK, CELL_SIZE * x, CELL_SIZE * (y + 1) + BLANK, WHITE);
			DrawLine(CELL_SIZE * x, CELL_SIZE * (y + 1) + BLANK, CELL_SIZE * x, CELL_SIZE * y + BLANK, WHITE);
		}
	}
}

POSITION GetPosition(int x, int y) {
	POSITION p;
	p.x = x;
	p.y = y;
	return p;
}

/*
bool IsAllWall() {
	bool flag = true;
	for (auto p : Candidate)
		if (Maze[p.y][p.x] != WALL)
			flag = false;
}
*/

void Init() {
	if (MAZE_SIZE % 2 == 0) ModeState = OVER;
	for (int y = 0; y < MAZE_SIZE; y++) {
		for (int x = 0; x < MAZE_SIZE; x++) {
			if (y == 0 || y == MAZE_SIZE - 1 || x == 0 || x == MAZE_SIZE - 1)
				Maze[y][x] = WALL;
			else Maze[y][x] = PATH;
			if (x % 2 == 0 && y % 2 == 0)
				Candidate.push_back(GetPosition(x, y));
		}
	}
	srand(time(NULL));
	PrintMode();
	DrawMaze();
	WaitKey();
	ModeState = CREATE;
}

void Create() {
	while (Candidate.size()) {
		int index = rand() % Candidate.size();
		POSITION start = Candidate[index];

		Maze[start.y][start.x] = CREATING;
		vector<int> DirCandidate;
		for (int dir = 0; dir < DIRECTION_MAX; dir++) {
			int dx = Dir[dir].x;
			int dy = Dir[dir].y;
			if (Maze[start.y + dy][start.x + dx] == PATH && Maze[start.y + 2 * dy][start.x + 2 * dx] != CREATING)
				DirCandidate.push_back(dir);
		}
	}

	PrintMode();
	WaitKey();
	ModeState = OVER;
}

void Over() {
	PrintMode();
	WaitKey();
	ModeState = INIT;

}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(CELL_SIZE * MAZE_SIZE, CELL_SIZE * MAZE_SIZE + BLANK, 32);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		switch (ModeState) {
		case INIT:		Init();		break;
		case CREATE:	Create();	break;
		case OVER:		Over();		break;
		default:					break;
		}
	}
	DxLib_End();
	return 0;
}



#endif