#pragma once
#include "CompGeometry.h"
#include "MyGraphics.h"
#include <time.h>
#include <math.h>

const double FPS = 60;

/*

class WAVE {
private:
	double WaveLength, Speed, Frequency, Amplitude;
	POS Center;
	clock_t LaunchedTime;
public:
	WAVE(double wavelength, double speed, double amplitude) {
		WaveLength = wavelength;
		Speed = Speed;
		Frequency = Speed / WaveLength;
		Amplitude = amplitude;
	}

	void SetWavelength(double wavelength) {
		WaveLength = wavelength;
	}

	void SetSpeed(double speed) {
		Speed = speed;
	}

	void SetFrequency(double frequency) {
		Frequency = frequency;
	}

	void SetAmplitude(double amplitude) {
		Amplitude = amplitude;
	}

	void SetCenter(double x, double y) {
		Center = { (float)x, (float)y };
	}

	void SetLaunchedTime() {
		LaunchedTime = clock();
	}

	double GetWaveLength() {
		return WaveLength;
	}

	double GetSpeed() {
		return Speed;
	}

	double GetFrequency() {
		return Frequency;
	}

	double GetAmplitude() {
		return Amplitude;
	}

	clock_t GetLaunchedTime() {
		return LaunchedTime;
	}

	POS GetCenter() {
		return Center;
	}

	double GetHeight(double r, double t) {
		return Amplitude * cos(r - Speed * t);
	}

	double GetT() {
		time_t now = clock();
		double t = (now - LaunchedTime) / CLOCKS_PER_SEC;
		return t;
	}

	void Draw() {
		double t = GetT();
		double r = 0;
		while (r < double(2 * WINDOWSIZE)) {
			double h = GetHeight(r, t);
			unsigned int color = GetColor(
				(int)floor((h + Amplitude) * 256 / (2 * Amplitude)),
				(int)floor((h + Amplitude) * 256 / (2 * Amplitude)),
				(int)floor((h + Amplitude) * 256 / (2 * Amplitude))
			);
			DrawMathCircle(Center.x, Center.y, r, color, false, 1);
			r += 0.1;
		}
	}

	void DrawPartly() {
		double t = GetT();
		double r = 0;
		while (r < double(2 * WINDOWSIZE)) {
			double h = GetHeight(r, t);
			if (abs(h - Amplitude) < Amplitude * EPS) {
				DrawMathCircle(Center.x, Center.y, r, RED, false, 1);
			}
			else if (abs(h - 0) < Amplitude * EPS) {
				DrawMathCircle(Center.x, Center.y, r, GREEN, false, 1);
			}
			else if (abs(h - (-Amplitude)) < Amplitude * EPS) {
				DrawMathCircle(Center.x, Center.y, r, BLUE, false, 1);
			}
			r += 0.1;
		}
	}

};
*/


typedef struct {
	double r, displacement;
} WavePoint;

class Wave {
private:
	double WaveLength, Speed, Frequency, Amplitude;
	POS Center;
	static const int SeperateNums = 64;
	WavePoint p[SeperateNums];
	

public:
	Wave(double l, double v, double a) {
		WaveLength = l;
		Speed = v;
		Amplitude = a;
		for (int i = 0; i < SeperateNums; i++) {
			p[i].r = -2 * PI / (double)SeperateNums * (double)i;
			p[i].displacement = Amplitude * cos(p[i].r);
		}
		Center.x = 0.0;
		Center.y = 0.0;
	}

	void SetCenter(double x, double y) {
		Center.x = x;
		Center.y = y;
	}

	void Move() {
		for (int i = 0; i < SeperateNums; i++) {
			p[i].r += Speed / FPS;
			if (p[i].r > 0)
				p[i].displacement = Amplitude * cos(p[i].r) / p[i].r;
		}
	}

	void Draw() {
		for (int i = 0; i < SeperateNums; i++) {
			if (p[i].r > 0) {
				double hue = 180 * p[i].r / PI;
				while (hue > 360.0) hue -= 360.0;
				unsigned int color = GetColorHSV(hue, 255, 255);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
				DrawMathCircle(Center.x, Center.y, p[i].r, color, false, 5); 
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 128);
			}
		}
	}

	void DrawMono() {
		for (int i = 0; i < SeperateNums; i++) {
			if (p[i].r > 0) {
				int brightness = (int)round((p[i].displacement + 1) * 255 / 2);
				unsigned int color = GetColor(brightness, brightness, brightness);
				DrawMathCircle(Center.x, Center.y, p[i].r, color, false, 1);
			}
		}
	}

};
