//#define RIPPLES_RUN
#ifdef RIPPLES_RUN

#include "DxLib.h"
#include "MyGraphics.h"
#include "Wave.h"
#define WINDOWSIZE (500)


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK), SetGraphMode(WINDOWSIZE, WINDOWSIZE, 32);
	MySetWindowsSize(WINDOWSIZE);
	SetLimit(10.0);
	Wave ripple(1.0, 2.0, 256.0);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		DrawMathAxis();
		ripple.Move();
		ripple.Draw();
	}
	DxLib_End();
	return 0;
}




#endif // RIPPLES_RUN
