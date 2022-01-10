#define STRING_RUN
#ifdef STRING_RUN

#include "DxLib.h"
#include "CompGeometry.h"
#include "MyGraphics.h"
#define WINDOWSIZE (800)

class SEG {
public:
    Vector sp, ep;
    float len = 0;
    float angle = 0;
    void follow(Vector& pos) {
        ep = pos;
        Vector vec = pos - sp;
        angle = atan2(vec.y, vec.x);
        vec.setMag(len);
        sp = pos - vec;
    }
    void setPos(Vector& pos) {
        sp = pos;
        Vector vec(cos(angle), sin(angle));
        ep = sp + vec * len;
    }
    void draw(float thickness) {
        //DrawLineAA(sp.x, sp.y, ep.x, ep.y, WHITE, thickness);
        DrawCircleAA(sp.x, sp.y, thickness, 32, WHITE);
    }
};




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
    SetGraphMode(WINDOWSIZE, WINDOWSIZE, 32);

    // Initialization
    MySetWindowsSize(WINDOWSIZE);

    Vector center(WINDOWSIZE / 2, WINDOWSIZE / 2);
    const int num = 200;
    vector<SEG> segs(num);
    for (int i = 0; i < num; i++) {
        segs[i].sp = center;
        segs[i].sp = center;
        segs[i].len = 1;
    }
    int mouseX = WINDOWSIZE / 2;
    int mouseY = WINDOWSIZE / 2;
    Vector root = center;

    float thickness = 5;

    // Main Loop
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        if (GetMousePoint(&mouseX, &mouseY));
        Vector mouse(mouseX, mouseY);
        Vector dist = mouse - center;
        dist.limmit(num);

        Vector fp = center + dist;
        for (int i = num - 1; i >= 0; i--) {
            segs[i].follow(fp);
            fp = segs[i].sp;
        }
        Vector sp = root;
        for (int i = 0; i < num; i++) {
            segs[i].setPos(sp);
            sp = segs[i].ep;
        }

        // Drawing
        ClearDrawScreen();
        for (int i = 0; i < num; i++) segs[i].draw(thickness);
        //DrawFormatString(WINDOWSIZE / 2, WINDOWSIZE / 2, WHITE, "%f %f", center.x, center.y);

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}

#endif