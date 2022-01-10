#pragma once
#include <vector>
#include <cmath>
#define EPS (1e-10)
#define equals(a, b) (fabs((a)-(b)) < EPS)
using namespace std;

class Point {
public:
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    void operator = (Point p) { x = p.x, y = p.y; }
    Point operator + (Point p) { return Point(x + p.x, y + p.y); }
    Point operator - (Point p) { return Point(x - p.x, y - p.y); }
    Point operator * (double a) { return Point(a * x, a * y); }
    Point operator / (double a) { return Point(a / x, a / y); }

    Point operator += (Point p) { return Point(x += p.x, y += p.y); }
    Point operator -= (Point p) { return Point(x -= p.x, y -= p.y); }
    Point operator *= (double a) { return Point(a *= x, a * y); }
    Point operator /= (double a) { return Point(x /= a, y /= a); }


    double norm() { return x * x + y * y; }
    double abs() { return sqrt(norm()); }
    void setMag(double mag) {
        double length = abs();
        if (length == 0) return;
        x *= mag / length;
        y *= mag / length;
    }

    void limmit(double len) {
        if (abs() > len) setMag(len);
    }

    bool operator < (const Point& p) const {
        return x != p.x ? x < p.x : y < p.y;
    }

    bool operator == (const Point& p) const {
        return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
    }
};

typedef Point Vector;

typedef struct { Point p1, p2; } Segment;

typedef Segment Line;

class Circle {
public:
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}
};

//typedef vector<Point> Polygon;

double norm(Vector a) { return a.x * a.x + a.y * a.y; }
double abs(Vector a) { return sqrt(norm(a)); }

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

bool isOrthogonal(Vector a, Vector b) { return equals(dot(a, b), 0.0); }
bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) { return isOrthogonal(a1 - a2, b1 - b2); }
bool isOrthogonal(Segment s1, Segment s2) { return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0); }

bool isParallel(Vector a, Vector b) { return equals(cross(a, b), 0.0); }
bool isParallel(Point a1, Point a2, Point b1, Point b2) { return isParallel(a1 - a2, b1 - b2); }
bool isParallel(Segment s1, Segment s2) { return equals(cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0); }

Point project(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / norm(base);
    return s.p1 + base * r;
}

Point reflect(Segment s, Point p) { return p + (project(s, p) - p) * 2.0; }

Point reflect(Segment s, Point p, Point o) {
    Point q = reflect(s, p);
    return q + (o - q) * 2; 
}

Vector norm(Line l, Point p) {
    Vector a = p - l.p1;
    Vector b = project(l, p) - l.p1;
    return (a - b);
}

double getDistance(Point a, Point b) { return abs(a - b); }
double getDistabceLP(Line l, Point p) { return abs(cross(l.p2 - l.p1, p - l.p1)) / abs(l.p1 - l.p2); }
double getDistabceSP(Segment s, Point p) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
    return getDistabceLP(s, p);
}


static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

int ccw(Point p0, Point p1, Point p2) {
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if (cross(a, b) > EPS) return COUNTER_CLOCKWISE;
    if (cross(a, b) < -EPS) return CLOCKWISE;
    if (dot(a, b) < -EPS) return ONLINE_BACK;
    if (a.norm() < b.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
}












