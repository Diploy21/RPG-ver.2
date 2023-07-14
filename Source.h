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
#include "Items.h"

#define x 50
#define y 25


using namespace std;
using Items::Item;


class Player;
class Enemy;
class Item;


void RenderMap(char Map[y][x]);
void output(char Map[y][x], Player& P);
bool Menu(bool state);
