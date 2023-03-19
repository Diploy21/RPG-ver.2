#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <thread>
#include <chrono>


using namespace std;

#define x 50
#define y 25

void RenderMap(char Map[y][x]);
void output(char Map[y][x], int H = 0, int A = 0, int G = 0);
void Sleep1(unsigned a);
bool Menu(bool state);
