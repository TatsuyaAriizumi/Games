//#define RUN_SPHERE
#ifdef RUN_SPHERE

#include "DxLib.h"
#include "MyGraphics.h"
#include <cmath>
#define WINDOWSIZE (800)

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
    SetGraphMode(WINDOWSIZE, WINDOWSIZE, 32);

    // Initialization
    MySetWindowsSize(WINDOWSIZE);
    SetLimit(0.8);
    const int numCorners = 32;
    const int numRings = numCorners / 2 + 1;
    const int numVertices = numCorners * numRings;
    POS op[numVertices];
    for (int j = 0; j < numRings; j++) {
        for (int i = 0; i < numCorners; i++) {
            int k = j * numCorners + i;
            op[k].x = sin(2 * PI * i / numCorners) * sin(2 * PI * j / numCorners);
            op[k].y = cos(2 * PI * i / numCorners) * sin(2 * PI * j / numCorners);
            op[k].z = cos(2 * PI * j / numCorners);
        }
    }
    POS p[numVertices];
    float deg = 0;

    // Main Loop
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        ClearDrawScreen();
        deg += 0.05;
        float s = sin(deg);
        float c = sin(deg);
        for (int j = 0; j < numRings; j++) {
            for (int i = 0; i < numCorners; i++) {
                int k = j * numCorners + i;
                p[k] = RotateOnY(op[k], deg);
                p[k].z += 3;
                p[k].x /= p[k].z;
                p[k].y /= p[k].z;
            }
        }
        

        // Drawing
        DrawMathAxis();
        for (int j = 0; j < numRings; j++) {
            for (int i = 0; i < numCorners; i++) {
                int k = j * numCorners + i;
                int l = k + 1;
                if (l % numCorners == 0) l -= numCorners;
                DrawMathLine(p[k].x, p[k].y, p[l].x, p[l].y, WHITE, 1.0);
                int m = (j + 1) * numCorners + i;
                if (j + 1 == numRings) continue;
                DrawMathLine(p[k].x, p[k].y, p[m].x, p[m].y, WHITE, 1.0);

                //DrawFormatString(0, 20 * k, WHITE, "%d: %f %f %f", j, op[k].x, op[k].y, op[k].z);
            }
        }
        ScreenFlip();
    }

    DxLib_End(); 
    return 0;
}
#endif // RUN