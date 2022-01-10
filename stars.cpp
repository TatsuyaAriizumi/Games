//#define STRAS_RUN
#ifdef STRAS_RUN

#include "DxLib.h"
#include "MyGraphics.h"
#include <stdlib.h>

#define WINDOWSIZE (500)

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(WINDOWSIZE, WINDOWSIZE, 32);

	// Init
	MySetWindowsSize(WINDOWSIZE);
	SetLimit(1);

	int const num = 500;
	POS stars[num];
	for (int i = 0; i < num; i++) {
		stars[i].x = (float)rand() / RAND_MAX * 2 - 1.0;
		stars[i].y = (float)rand() / RAND_MAX * 2 - 1.0;
		stars[i].z = (float)rand() / RAND_MAX;
	}
	
	// Main Loop
	while (ScreenFlip() == 0 && ProcessMessage() == 0 /*&& ClearDrawScreen() == 0*/) {
		
		for (int i = 0; i < num; i++) {
			//stars[i].x /= stars[i].z;
			//stars[i].y /= stars[i].z;
			stars[i].z -= 0.008;
			if (stars[i].z <= 0)
				stars[i].z = 1;
		}
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawBox(0, 0, WINDOWSIZE + 1, WINDOWSIZE + 1, BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		for (int i = 0; i < num; i++) {
			float starSize = (1 - stars[i].z) * 10;
			DrawMathCircle(stars[i].x / stars[i].z, stars[i].y / stars[i].z, starSize);
		}
		//DrawFormatString(0, 0, WHITE, "%f %f %f", stars[0].x, stars[0].y, stars[0].z);
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}
#endif