#pragma once
#include "DxLib.h"
#include <cmath>

#define PI (DX_PI)

typedef struct {
    double x, y, z;
} POS;

const unsigned int WHITE = GetColor(255, 255, 255);
const unsigned int BLACK = GetColor(0, 0, 0);
const unsigned int GREY = GetColor(128, 128, 128);
const unsigned int RED = GetColor(255, 0, 0);
const unsigned int GREEN = GetColor(0, 255, 0);
const unsigned int BLUE = GetColor(0, 0, 255);
const unsigned int ORANGE = GetColor(255, 102, 0);
const unsigned int CYAN = GetColor(0, 160, 233);
const unsigned int MAGENTA = GetColor(255, 0, 255);



int WINDOWSIZE;
double LIMIT;

void SetLimit(double limit) {
	LIMIT = limit;
}

void MySetWindowsSize(int windowSize) {
    WINDOWSIZE = windowSize;
}

void FillScreen(unsigned int color) {
    DrawBox(0, 0, WINDOWSIZE + 1, WINDOWSIZE + 1, color, TRUE);
}

POS TranslateToComputerCoordinates(POS p) {
    p.x *= (double)WINDOWSIZE / 2 / LIMIT;
    p.x += (double)WINDOWSIZE / 2;
    p.y *= -(double)WINDOWSIZE / 2 / LIMIT;
    p.y += (double)WINDOWSIZE / 2;
    POS q = { p.x, p.y, p.z };
    return q;
}

POS TranslateToMathCoordinates(POS p) {
    p.x -= (double)WINDOWSIZE / 2;
    p.x /= (double)WINDOWSIZE / 2 / LIMIT;
    p.y -= (double)WINDOWSIZE / 2;
    p.y /= -(double)WINDOWSIZE / 2 / LIMIT;
    POS q = { p.x, p.y, p.z };
    return q;
}

void DrawMathAxis(unsigned int color = GREY) {
    POS x1 = { -LIMIT, 0 };
    POS x2 = { LIMIT, 0 };
    POS y1 = { 0, -LIMIT };
    POS y2 = { 0, LIMIT };
    POS qx1 = TranslateToComputerCoordinates(x1);
    POS qx2 = TranslateToComputerCoordinates(x2);
    POS qy1 = TranslateToComputerCoordinates(y1);
    POS qy2 = TranslateToComputerCoordinates(y2);

    DrawLineAA(qx1.x, qx1.y, qx2.x, qx2.y, GREY);
    DrawLineAA(qy1.x, qy1.y, qy2.x, qy2.y, GREY);
}

void DrawMathPoint(double x, double y, unsigned int color = WHITE) {
    POS p = { x, y };
    POS q = TranslateToComputerCoordinates(p);
    DrawCircle((int)q.x, (int)q.y, WINDOWSIZE / 200 ,color);
}

void DrawMathLine(double x1, double y1, double x2, double y2, unsigned int color = WHITE, double thickness = 3.0) {
    POS p1 = { x1, y1 };
    POS p2 = { x2, y2 };
    POS q1 = TranslateToComputerCoordinates(p1);
    POS q2 = TranslateToComputerCoordinates(p2);
    DrawLineAA(q1.x, q1.y, q2.x, q2.y, color = WHITE, thickness);
}

void DrawMathCircle(double x, double y, double r, unsigned int color = WHITE, bool filled = true, int thickness = 1) {
    POS p = { x, y };
    POS q = TranslateToComputerCoordinates(p);
    r *= (double)WINDOWSIZE / 2 / LIMIT;
    DrawCircleAA(q.x, q.y, r, 64, color, filled, thickness);
}

POS RotateOnX(POS op, double degree) {
    POS p;
    double s = sin(degree);
    double c = cos(degree);
    p.x = op.x;
    p.y = op.y * c + op.z * -s;
    p.z = op.y * s + op.z * c;
    return p;
}

POS RotateOnY(POS op, double degree) {
    POS p;
    double s = sin(degree);
    double c = cos(degree);
    p.x = op.x * c + op.z * -s;
    p.y = op.y;
    p.z = op.x * s + op.z * c;
    return p;
}

POS RotateOnZ(POS op, double degree) {
    POS p;
    double s = sin(degree);
    double c = cos(degree);
    p.x = op.x * c + op.y * -s;
    p.y = op.x * s + op.y * c;
    p.z = op.z;
    return p;
}

// H : 色相　有効範囲 0.0 ～ 360.0
// S : 彩度　有効範囲 0.0 ～ 255.0
// V : 明度　有効範囲 0.0 ～ 255.0
int GetColorHSV(double H, double S, double V)
{
    double max = V;
    double min = max - ((S / 255.0) * max);
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    if (0.0 <= H && H < 60.0) {
        r = max;
        g = (H / 60.0) * (max - min) + min;
        b = min;
    }
    if (60.0 <= H && H < 120.0) {
        r = ((120.0 - H) / 60.0) * (max - min) + min;
        g = max;
        b = min;
    }
    if (120.0 <= H && H < 180.0) {
        r = min;
        g = max;
        b = ((H - 120.0) / 60.0) * (max - min) + min;
    }
    if (180.0 <= H && H < 240.0) {
        r = min;
        g = ((240.0 - H) / 60.0) * (max - min) + min;
        b = max;
    }
    if (240.0 <= H && H < 300.0) {
        r = ((H - 240.0) / 60.0) * (max - min) + min;
        g = min;
        b = max;
    }
    if (300.0 <= H && H <= 360.0){
        r = max;
        g = min;
        b = ((360.0 - H) / 60.0) * (max - min) + min;
    }
    return GetColor((int)round(r), (int)round(g), (int)round(b));
}