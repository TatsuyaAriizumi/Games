//#define BALL_RUN
#ifdef BALL_RUN

#include "DxLib.h"
#include "MyGraphics.h"
#include "CompGeometry.h"
#include "MyRandom.h"

#define WINDOWSIZE (500)

enum COLOR {
	COLOR_WHITE,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_ORANGE,
	COLOR_CYAN,
	COLOR_MAGENTA,
	COLOR_MAX
};

unsigned int Colors[COLOR_MAX]{
	WHITE,
	RED,
	GREEN,
	BLUE,
	ORANGE,
	CYAN,
	MAGENTA
};

class BALL {
private:
	Vector Position, Velocity = { 0, 0 };
	float Radius = 0.5;
	float Speed = 0.04;
	unsigned int Color = ORANGE;

public:
	BALL(float px, float py, float vx, float vy, float r, float speed, unsigned int color) {
		Position.x = px;
		Position.y = py;
		Velocity.x = vx;
		Velocity.y = vy;
		Radius = r;
		Speed = speed;
		Color = color;
	}
	void setPos(Vector pos) { Position = pos; }
	Vector getPos() { return Position; }
	void setVelocity(Vector vel) {
		Velocity = vel;
		Velocity.setMag(Speed);
	}
	void keyMove() {
		Velocity.x = Velocity.y = 0;
		if (CheckHitKey(KEY_INPUT_W)) Velocity.y = 1;
		if (CheckHitKey(KEY_INPUT_S)) Velocity.y = -1;
		if (CheckHitKey(KEY_INPUT_A)) Velocity.x = -1;
		if (CheckHitKey(KEY_INPUT_D)) Velocity.x = 1;
		Velocity.setMag(Speed);
	}
	void move() { Position = Position + Velocity; }
	void collision(Segment s) {
		double dist = getDistabceSP(s, Position);
		if (dist < Radius) {
			double over = Radius - dist;
			if (dot(s.p2 - s.p1, Position - s.p1) < 0.0) {
				Vector n = Position - s.p1;
				n.setMag(over);
				Position += n;

				n.setMag(Radius);
				Point p = Position - n + Velocity;
				Point q = reflect(s, p);
				Velocity = q - (Position - n);
				Velocity.setMag(Speed);
			}
			else if (dot(s.p1 - s.p2, Position - s.p2) < 0.0) {
				Vector n = Position - s.p1;
				n.setMag(over);
				Position += n;

				n.setMag(Radius);
				Point p = Position - n + Velocity;
				Point q = reflect(s, p);
				Velocity = q - (Position - n);
				Velocity.setMag(Speed);
			}
			else {
				Vector n = norm(s, Position);
				n.setMag(over);
				Position += n;

				n.setMag(Radius);
				Point p = Position - n + Velocity;
				Point q = reflect(s, p);
				Velocity = q - (Position - n);
				Velocity.setMag(Speed);
			}
		}
	}
	void draw() {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawMathCircle(Position.x, Position.y, Radius, Color);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 128);
	}
	void printStatus() {
		DrawFormatString(0,  0, Color, "Position: %f %f", Position.x, Position.y);
		DrawFormatString(0, 20, Color, "Velocity: %f %f", Velocity.x, Velocity.y);
		DrawFormatString(0, 40, Color, "Radius  : %f   ", Radius);
		DrawFormatString(0, 60, Color, "Speed   : %f   ", Speed);

	}
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK), SetGraphMode(WINDOWSIZE, WINDOWSIZE, 32);
	MySetWindowsSize(WINDOWSIZE);
	SetLimit(10.0);

	int ballNums = 50;
	srand((unsigned int)time(NULL));
	vector<BALL> balls;
	for (int i = 0; i < ballNums; i++) {
		BALL ball(
			randf(-3.0, 3.0),				// Position.x
			randf(-3.0, 3.0),				// Position.y
			randf(-0.05, 0.05),				// Velocity.x
			randf(-0.05, 0.05),				// Velocity.y
			randf(0.1, 1.0),				// Radius
			randf(0.01, 0.3),				// Speed
			Colors[randint(COLOR_MAX)]		// Color
		);
		balls.emplace_back(ball);
	}

	Point p[] {
		{ 1.5, -1.5 },
		{ 0, 3 },
		{ -4.5, -4.5 },
		{ 7.5, -4.5 },
		{ 1.5, 4.5 },
		{ -7.5, 4.5 }
	};

	vector <Segment> segments;
	for (int i = 0; i < 5; i++) {
		Segment seg = { { p[i].x, p[i].y }, { p[i + 1].x, p[i + 1].y } };
		segments.emplace_back(seg);
	}

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawMathAxis();
		for (auto seg : segments) {
			DrawMathLine(seg.p1.x, seg.p1.y, seg.p2.x, seg.p2.y);
		}
		
		for (BALL& ball : balls) {
			ball.move();
			ball.draw();
			for (auto seg : segments)
				ball.collision(seg);
		}
	}
	DxLib_End();
	return 0;
}


#endif