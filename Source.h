#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include <functional>
#include <fstream>

class Player;
class Enemy;

using namespace std;

#define x 50
#define y 25

void RenderMap(char Map[y][x]);
void output(char Map[y][x], Player& P);
bool Menu(bool state);
