#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

#include"piece.h"

using namespace std;
using namespace sf;
class knight
{
	vector <pair<int,int>> step_direction={
		{-2,-1},{-2,1},
		{-1,2},{1,2},
		{2,1},{2,-1},
		{1,-2},{-1,-2}
	};
	piece piece1;
public:
	void showpath(RenderWindow& window, int(&board)[8][8],RectangleShape (&square)[8][8],int row,int col,
		int piece,vector<vector<int>> &current_possible);
};

