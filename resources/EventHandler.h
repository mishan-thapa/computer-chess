#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<vector>

#include "chessboard.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include"movement.h"
#include"startmenu.h"
#include "check.h"


using namespace sf;


//GLOBAL ENTITIES:	
extern int mouse_pos_x;
extern int mouse_pos_y;

extern	bool w_check;
extern  bool b_check;

extern int Added_width;	

extern int mouse_pos_x;
extern int mouse_pos_y;

extern int b_row,b_col,w_row,w_col;
extern SoundBuffer click,hoover,move;
extern Sound click1,hoover1,move1;


extern int white_up_or_down;
extern int black_up_or_down;
//for chess-network:
extern bool my_turn;//for same pc it is always true:
extern bool time_to_send_sever; 
extern bool to_trigger_event;
extern int who_won;


class EventHandler
{
	
    int clicked_piece;//to know clicked piece
    int row_no,col_no; //to know location of clicked piece:
    chessboard c1;
	pawn p1;
	rook r1;
	knight n1;
	bishop b1;
	queen q1;
	king k1;
    
	
	Texture tex;//to display pieces:
	Sprite sp;

	vector<vector<int>> current_possible;//to store the information of all possible moves of particular piece:
	
    Event event1;
    Texture testback1,menu2,bmenu2;//to display back button:
	Sprite stestback1,smenu2,sbmenu2;
	 


	
		
public:

    
	

   //passing game window, game_array and base squares:
   void event_function(RenderWindow &window,int (&game_array)[8][8],RectangleShape (&square)[8][8],int &current_side_to_play);
   void function_after_getting_position(RenderWindow &window,int (&game_array)[8][8],RectangleShape (&square)[8][8],int &current_side_to_play,
   int x,int y);

   void gameleftsidescreen(RenderWindow &window,int x, int y);
   void gamerightsidescreen(RenderWindow &window);
   void moveplay();
   
    


};//EventHandler class: