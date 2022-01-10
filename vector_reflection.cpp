//#define VECTOR_REFLECTION_RUN
#ifdef VECTOR_REFLECTION_RUN

#include "DxLib.h"
#include "MyGraphics.h"
#include "CompGeometry.h"
#define WINDOWSIZE (500)

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK),SetGraphMode(WINDOWSIZE, WINDOWSIZE, 32);
	MySetWindowsSize(WINDOWSIZE);
	SetLimit(1.0);
	int mouseX, mouseY;
	Segment seg = { { -0.5, 1 }, { 0.5, -1 } };
	Point origin = { 0, 0 };

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		GetMousePoint(&mouseX, &mouseY);
		POS mousePos = { (float)mouseX, (float)mouseY };
		POS mouseMathPos = TranslateToMathCoordinates(mousePos);
		Point mouseMathPoint = { mouseMathPos.x, mouseMathPos.y };

		Point reflectedPoint = reflect(seg, mouseMathPoint, origin);
		POS reflectedPos = { reflectedPoint.x, reflectedPoint.y };

		DrawMathAxis();
		DrawMathLine(seg.p1.x, seg.p1.y, seg.p2.x, seg.p2.y);
		DrawMathLine(0, 0, mouseMathPos.x, mouseMathPos.y);
		DrawMathLine(0, 0, reflectedPos.x, reflectedPos.y);
	}
	DxLib_End();
	return 0;
}


#endif 