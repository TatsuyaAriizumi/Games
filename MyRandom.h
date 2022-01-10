#pragma once
#include <stdlib.h>
#include <time.h>

int randint(int n) {
	return (rand() % n);
}

float randf(float min, float max) {
	float rnd = (float)rand() / RAND_MAX;
	float range = max - min;
	rnd *= range;
	rnd += min;
	return rnd;
}