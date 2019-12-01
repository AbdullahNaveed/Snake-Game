//============================================================================
// Name        : game-release.cpp
// Author      : Abdullah Naveed
// Version     :
// Copyright   : (c) 2018 Reserved
// Description : Basic 2D Snake Game...
//============================================================================
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include <unistd.h>
#include<ctime>
#include<string>
//#include<sys/wait.h>
#include<stdlib.h>
//#include<stdio.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
#include<fstream>

using namespace std;


void DrawSnake(long x[],long y[]);	//prototype of func: for drawing snake
void DrawFood(void);		//prototype of func: for drawing food

void randomFood(long &x ,long &y);		//prototype of func: for generating random power food
void randomFood1(long &x ,long &y);		//prototype of func: for generating random food

void game_Menu(void); //prototype of func: of Game Menu

void high_Score(void); //prototype of func: of High Score

void boundaryHurdle(void);		//prototype of func: for drawing boundary walls of game

void game_score_counter_bar(void); 		//prototype of func: for drawing score_counter board & snake length bar

void food_disappear(void);		///prototype of func: for generating food after 15 seconds

void power_food(void);		///prototype of func: for generating power food after 1 minute

void game_Over(void); 	//prototype of func: for Game Over

void game_Pause(void); 	//prototype of func: for Game Pause

void highScore(void);	//prototype of func: for saving high score

void Developer(void); //prototype of func: for Developer's information

void Instructions(void);	//prototype of func: for information section

void hurdles(void);

void levels(void);

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */

int height=650,width=650;

void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */

int lengthSnake = 10;	//initial length of snake

const double UP=10 , DOWN=-10 , LEFT=-20 , RIGHT=20;	//storing values for all directions


////////////array size is 500 because then snake can eat 500 foods////////////////
long Snake_XAxis[500]={200,200,200,200,200,200,200,200,200,200};	//initial positon of snake on x-axis 
long Snake_YAxis[500]={200,190,180,170,160,150,140,130,120,110};	//initial postion of snake on y-axis
///////////////////////////////////////////////////////////////////////////////////

long snakeDirection;	//for storing keys

long Food1_X_Axis,Food1_Y_Axis;	//position of food
bool food1 = true;	//for checking status of food

long power_X_Axis,power_Y_Axis; // position of power food

int score_counter = 0 ;	//game score counter
int high_score;		//high score counter

int timer_counter=0; //counter that counts the number of times display function is called for 15 seconds
int power_counter=0; //counter that counts the number of times display function is called for 1 min

bool game_over = false;	 //for checking if game is over
int over_counter = 0;	//for animation of Game Over

bool game_pause = false; //for checking if game is Paused

bool game_menu = true;	////for checking if game is in menu

bool high_score_menu = true;	////for checking if game is in menu

bool Developer_menu = false;

bool Instruction_menu = false;

bool levels_menu = false;

bool Level0 = true;
bool Level1 = false;
bool Level2 = false;

int game_level = 0;

bool again_play = false;










void Display(){
    // set the background color using function glClearColotgr.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
    
    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
            0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    
    //DrawSquare( 300 , 300 ,100,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
    //DrawString( 50, 600, "Here are some are basic shapes", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
    //DrawString( 50, 570, "You will use these to make your game", colors[MISTY_ROSE]); // this will print given string at x=50 , y=570
    //DrawCircle( 200 , 200 , 50 , colors[5]); // This will draw a circle at x=200,y=200 of radius 50
																		
																		//                    v1( x,y )   v2( x,y )  , v3( x,y ) 
    //DrawTriangle( 300, 50 , 500, 50 , 400 , 250, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
    
    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
    //DrawLine( 550 , 50 ,  550 , 600 , 20 , colors[MISTY_ROSE] );
   
   if(game_menu == true)	//when user is in main menu
   {
   					 game_Menu();
   }
   else
   {	
   		if(high_score_menu == true)	//when user is in high score
   		{
   			high_Score();
   		}

   		else if(Developer_menu == true)
   		{
   			Developer();
   		}

   		else if( game_menu == true)	//when user is again in main menu
   		{
   			game_Menu();
   		}
 		else if( levels_menu == true)	//when user is in levels
   		{
   			levels();
   		}

   		else if( Instruction_menu == true)	//when user is again in main menu
   		{
   			Instructions();
   		}

   		else
   		{
				    if( (game_over == false) && (game_pause == false) )	// if game is running
				    {
				    	food_disappear();
				    	if(Level0 == false)
				    	{
					    	boundaryHurdle();
					    	hurdles();
					    }
					    game_score_counter_bar();
						DrawFood();
						power_food();
						DrawSnake(Snake_XAxis,Snake_YAxis);
					}
					else  if (game_over == true)	//if game is over
					{
						game_Over();
						/*if(again_play == true)
						{
							again_play = false;
							score_counter = 0;
							lengthSnake = 10;
							game_over = false;
						}*/
					}

					else if(game_pause == true)	//if game is paused
					{
						game_Pause();
					}
		}
		
	}

   glutSwapBuffers(); {// do not modify this line..
	}
	
	
	
   
}


void DrawSnake(long x[],long y[])	//func: for drawing snake
{
	
	/////////////////////snake body mechanism/////////////////
	for ( int counter=(lengthSnake-1) ; counter>0 ; counter-- )	//moving each box of snake to the position of box ahead of it
	{
		Snake_XAxis[counter] = Snake_XAxis[counter-1] ;	//for x-axis //this changes the x-axis of boxes to the x-axis of box ahead of it

		Snake_YAxis[counter] = Snake_YAxis[counter-1] ;	//for y-axis //this changes the y-axis of boxes to the y-axis of box ahead of it

	}
	///////////////////////////////////////////////////////////


	/////////////////snake movement///////////////
	if (snakeDirection == LEFT) //if user press left then snake moves left by jumping 10px each time
	{
		Snake_XAxis[0]-=10;
	}
	else if (snakeDirection == RIGHT) //if user press left then snake moves right by jumping 10px each time
	{
		Snake_XAxis[0]+=10;
	}
	else if (snakeDirection == UP) //if user press left then snake moves up by jumping 10px each time
	{
		Snake_YAxis[0]+=10;
	}
	else if (snakeDirection == DOWN) //if user press left then snake moves down by jumping 10px each time
	{
		Snake_YAxis[0]-=10;
	}
	///////////////////////////////////////////////


	for(int counter1=0 ; counter1<lengthSnake ; counter1++)	//drawing snake in array
	{

		if(counter1==0)
		{
			DrawCircle( ((x[counter1]/10)*10)+4 , ((y[counter1]/10)*10)+4 , 7 , colors[33] );	//for the head of snake
		}
		else
		{
			DrawSquare( ((x[counter1])/10)*10 , ((y[counter1])/10)*10 , 10 , colors[27] );	//for the rest of the body of snake	
		}
		
	}


	/////////////if level0 //////

if(Level0 == true)
{
	if(x[0] >=0 && x[0] <= 630 && y[0] >= 630)	
	{
		y[0] = 1;
	}

	if(x[0] <= 0 && y[0] >= 0 && y[0] <= 630)	//for y-axis on left
	{
		x[0] = 629;
	}
	
	if(x[0] >= 630 && y[0] >= 0 && y[0] <= 630)	//for y-axis on left
	{
		x[0] = 2;
	}

	if(x[0] >= 0 && x[0] <= 630  && y[0] <= 0 )	//for y-axis on left
	{
		y[0] = 630;
	}

}
	////////////////////////////




	///////////////food generation///////////////////




	///////power food ////////
	if( (x[0] == (power_X_Axis/10)*10 && y[0] == (power_Y_Axis/10)*10  ) ) 
	{
		lengthSnake+=5;	// length of snake increases 2 times
		score_counter += 40;	//score increases 20 points
		power_counter = 0;		//timer again to 0
	}

	////this does the same thing except that if snake is slightly far from the power food still the snake eats it and get's bigger////

	for (int counter=1 ; counter<=30 ; counter++)
	{

		if( (x[0] == (power_X_Axis/10)*10  ) && (y[0] == ( ((power_Y_Axis/10)*10) + counter)  ) )
		{
			lengthSnake+=2;	// length of snake increases 2 times
			score_counter += 40;	//score increases 20 points
			power_counter = 0;		//timer again to 0
		}
		if( (x[0] == ( ((power_X_Axis/10)*10) + counter) ) && (y[0] == (power_Y_Axis/10)*10  ) )
		{
			lengthSnake+=2;	// length of snake increases 2 times
			score_counter += 40;	//score increases 20 points
			power_counter = 0;		//timer again to 0
		}
	}

	for (int counter=30 ; counter>=0 ; counter--)
	{

		if( (x[0] == (power_X_Axis/10)*10 ) && (y[0] == ( ((power_Y_Axis/10)*10) - counter) ) )
		{
			lengthSnake+=2;	// length of snake increases 2 times
			score_counter += 40;	//score increases 20 points
			power_counter = 0;		//timer again to 0
		}
		if( (x[0] == ( ((power_X_Axis/10)*10) - counter) ) && (y[0] == (power_Y_Axis/10)*10 ) )
		{
			lengthSnake+=2;	// length of snake increases 2 times
			score_counter += 40;	//score increases 20 points
			power_counter = 0;		//timer again to 0
		}
	}  


	/////////////////////////

	//food1//

	//if snake head axis is exactly equal to food axis then:
	if( (x[0] == (Food1_X_Axis/10)*10 && y[0] == (Food1_Y_Axis/10)*10  ) ) 
	{
		lengthSnake+=3;	// length of snake increases
		food1 = true;	//food is generated again at a random place
		score_counter += 15;
	}

	////this does the same thing except that if snake is slightly far from the food still the snake eats it and get's bigger////

	for (int counter=1 ; counter<=20 ; counter++)
	{

		if( (x[0] == (Food1_X_Axis/10)*10  ) && (y[0] == ( ((Food1_Y_Axis/10)*10) + counter)  ) )
		{
			lengthSnake+=3;	//length of snake increases
			food1 = true;	//food is generated again at a random place
			score_counter += 15;
		}
		if( (x[0] == ( ((Food1_X_Axis/10)*10) + counter) ) && (y[0] == (Food1_Y_Axis/10)*10  ) )
		{
			lengthSnake+=3;	//length of snake increases
			food1 = true;	//food is generated again at a random place
			score_counter += 15;
		}
	}

	for (int counter=20 ; counter>=0 ; counter--)
	{

		if( (x[0] == (Food1_X_Axis/10)*10 ) && (y[0] == ( ((Food1_Y_Axis/10)*10) - counter) ) )
		{
			lengthSnake+=3;	//length of snake increases
			food1 = true;	//food is generated again at a random place
			score_counter += 15;
		}
		if( (x[0] == ( ((Food1_X_Axis/10)*10) - counter) ) && (y[0] == (Food1_Y_Axis/10)*10 ) )
		{
			lengthSnake+=3;	//length of snake increases
			food1 = true;	//food is generated again at a random place
			score_counter += 15;
		}
	}  

	
	/////////////////////////////////////////////////////////////////////

	///length of Snake when it reaches maxiumum/// it will remain maximum///
	if(lengthSnake >= 499)
	{
		lengthSnake = 499;
	}

	//////////////////////////////////////////

	/////levels/////
if(game_level == 0)
{
	if(score_counter >= 500)
	{
		Level0 = false;
		Level1 = true;
		Level2 = false;	
		
	}	
	if(score_counter >= 1000)
	{
		Level0 = false;
		Level1 = false;
		Level2 = true;	
		
	}	
}
	if(game_level == 1)
	{
			Level0 = true;
			Level1 = false;
			Level2 = false;	
	}
	if(game_level == 2)
	{
			Level0 = false;
			Level1 = true;
			Level2 = false;	
	}
	if(game_level == 3)
	{
			Level0 = false;
			Level1 = false;
			Level2 = true;	
	}


	///////////////

	/////////if snake touches it's body////////////

	for(int counter=10 ; counter<lengthSnake ; counter++)	//it is starting after snake initial body
	{
		if( ( x[0] == x[counter] ) && ( y[0] == y[counter] )   )
		{
			highScore();
			game_over = true;
		}

	}


	///////////////////////////////////////////////

	//////////////if snake touches the hurdle/////////////////////
	if(Level2 == true)
	{

		if ( x[0]>=110 && x[0]<=530 && y[0] == 470 )
		{
			highScore();
			game_over = true;

		}

		if ( x[0]>=110 && x[0]<=530 && y[0] == 170 )
		{
			highScore();
			game_over = true;

		}

	}
	//////////////////////////////////////////////////////////////////////



	

	//////////////if snake touches the boundary walls/////////////////////
	if(Level0 == false)
	{

		if ( x[0]==0 || x[0]==630 || y[0]==0 || y[0]==630 )
		{
			highScore();
			game_over = true;

		}

	}
	//////////////////////////////////////////////////////////////////////



}

void hurdles(void)
{
	if(Level2 == true)
	{
		DrawSquare(120 , 470 , 18 , colors[69]);	DrawSquare(120 , 170 , 18 , colors[69]);
		DrawSquare(140 , 470 , 18 , colors[69]);	DrawSquare(140 , 170 , 18 , colors[69]);
		DrawSquare(160 , 470 , 18 , colors[69]);	DrawSquare(160 , 170 , 18 , colors[69]);
		DrawSquare(180 , 470 , 18 , colors[69]);	DrawSquare(180 , 170 , 18 , colors[69]);
		DrawSquare(200 , 470 , 18 , colors[69]);	DrawSquare(200 , 170 , 18 , colors[69]);
		DrawSquare(220 , 470 , 18 , colors[69]);	DrawSquare(220 , 170 , 18 , colors[69]);
		DrawSquare(240 , 470 , 18 , colors[69]);	DrawSquare(240 , 170 , 18 , colors[69]);
		DrawSquare(260 , 470 , 18 , colors[69]);	DrawSquare(260 , 170 , 18 , colors[69]);
		DrawSquare(280 , 470 , 18 , colors[69]);	DrawSquare(280 , 170 , 18 , colors[69]);
		DrawSquare(300 , 470 , 18 , colors[69]);	DrawSquare(300 , 170 , 18 , colors[69]);
		DrawSquare(320 , 470 , 18 , colors[69]);	DrawSquare(320 , 170 , 18 , colors[69]);
		DrawSquare(340 , 470 , 18 , colors[69]);	DrawSquare(340 , 170 , 18 , colors[69]);
		DrawSquare(360 , 470 , 18 , colors[69]);	DrawSquare(360 , 170 , 18 , colors[69]);
		DrawSquare(380 , 470 , 18 , colors[69]);	DrawSquare(380 , 170 , 18 , colors[69]);
		DrawSquare(400 , 470 , 18 , colors[69]);	DrawSquare(400 , 170 , 18 , colors[69]);
		DrawSquare(420 , 470 , 18 , colors[69]);	DrawSquare(420 , 170 , 18 , colors[69]);
		DrawSquare(440 , 470 , 18 , colors[69]);	DrawSquare(440 , 170 , 18 , colors[69]);
		DrawSquare(460 , 470 , 18 , colors[69]);	DrawSquare(460 , 170 , 18 , colors[69]);
		DrawSquare(480 , 470 , 18 , colors[69]);	DrawSquare(480 , 170 , 18 , colors[69]);
		DrawSquare(500 , 470 , 18 , colors[69]);	DrawSquare(500 , 170 , 18 , colors[69]);
		DrawSquare(520 , 470 , 18 , colors[69]);	DrawSquare(520 , 170 , 18 , colors[69]);
		
	}

} 

void highScore(void)
{
	/////////////////////SAVING HIGH SCORE////

	if(score_counter >= high_score)
	{
		high_score = score_counter;
	}

	fstream OutputFile;
	OutputFile.open("HighScore.txt", ios::out);
	OutputFile<<high_score;
	OutputFile.close();

	//////////////////////////////////////////
}

void game_score_counter_bar(void)
{
	//////////////////score_counter///////////////////////////////////////////////////////////////

	DrawString( 50 , 600 , "Score = " , colors[MISTY_ROSE] ) ;	//string to display score_counter
	DrawString( 130 , 600 , to_string(score_counter) , colors[MISTY_ROSE] ) ;	// a func: used to display integer value in string

	/////////////////////////////////////////////////////////////////////////////////////

	////displaying levels/////
	if(Level0 == true)
	{
		DrawString( 180, 600, "Level 1", colors[MISTY_ROSE]);	//string to display snake bar
	}
	if(Level1 == true)
	{
		DrawString( 180, 600, "Level 2", colors[MISTY_ROSE]);	//string to display snake bar
	}
	if(Level2 == true)
	{
		DrawString( 180, 600, "Level 3", colors[MISTY_ROSE]);	//string to display snake bar
	}
	///////////////////////SNAKE LENGTH BAR//////////////////////////

	DrawString( 300, 600, "Snake", colors[MISTY_ROSE]);	//string to display snake bar

	for(int counter=1 ; counter<lengthSnake ; counter+=1)
	{
		if (counter + 375 >= 625)	//if the bar reaches the end then bar stops
		{
			break;
		}

		DrawSquare( 365+counter , 600+5 , 8 ,colors[54]);	//drawing bar
	}
	////////////////////////////////////////////////////////////////


}


void food_disappear()	//func: for re-generating food after 15 seconds
{
	timer_counter += 1;	// on each call of display fun: timer is increased one value

	if(timer_counter == 230)	// my fps is 15 so timer function is called approx 230 times in 15 seconds
	{
		randomFood1(Food1_X_Axis,Food1_Y_Axis);
	}

	if(timer_counter == 230)	//after 15 seconds counter is reset
	{
		timer_counter = 0;
	}
}


void power_food()
{
	power_counter += 1;

	if(power_counter == 920)
	{
		randomFood(power_X_Axis,power_Y_Axis);	// so power food doesn't show up open another exsisting food

		while ( power_X_Axis == Food1_X_Axis || power_Y_Axis == Food1_Y_Axis)
		{
			randomFood(power_X_Axis,power_Y_Axis);
		}

		for(int counter=(lengthSnake-1) ; counter>0 ; counter--)	//so power food doesn't show up on snake body
		{
			if(Snake_XAxis[counter] == power_X_Axis && Snake_YAxis[counter] == power_Y_Axis)
			{
				randomFood(power_X_Axis,power_Y_Axis);
			}
		}

		if(Level2 == true)
		{
			while(power_X_Axis >= 90 && power_X_Axis <= 550 && power_Y_Axis >= 440 && power_Y_Axis <= 490)	//for hurdle
			{
				randomFood(Food1_X_Axis,Food1_Y_Axis);
			}
			while(power_X_Axis >= 90 && power_X_Axis <= 550 && power_Y_Axis >= 140 && power_Y_Axis <= 190)	//for hurdle
			{
				randomFood(Food1_X_Axis,Food1_Y_Axis);
			}
		}



	}

	if(power_counter >= 920)
	{
		DrawSquare( (power_X_Axis/10)*10 , (power_Y_Axis/10)*10 , 15 , colors[84] );	// power food after 1 minute
	}

	if(power_counter >= 1150)	//after 15 seconds power food will disappear
	{
		power_counter = 0;  
	}
}


void DrawFood(void)	//func: for drawing food
{
	if(food1 == true)	//if food is eaten or not present
	{
		randomFood1(Food1_X_Axis,Food1_Y_Axis);	//calling func: for generating random numbers

		for(int counter=(lengthSnake-1) ; counter>0 ; counter--)	//so food doesn't show up on snake body
		{
			while(Snake_XAxis[counter] == Food1_X_Axis && Snake_YAxis[counter] == Food1_Y_Axis)
			{
				randomFood1(Food1_X_Axis,Food1_Y_Axis);
			}
		}

		if(Level2 == true)
		{
			while(Food1_X_Axis >= 90 && Food1_X_Axis <= 550 && Food1_Y_Axis >= 440 && Food1_Y_Axis <= 490)	//for hurdle
			{
				randomFood1(Food1_X_Axis,Food1_Y_Axis);
			}
			while(Food1_X_Axis >= 90 && Food1_X_Axis <= 550 && Food1_Y_Axis >= 140 && Food1_Y_Axis <= 190)	//for hurdle
			{
				randomFood1(Food1_X_Axis,Food1_Y_Axis);
			}
		}

	}
		food1 = false;

	DrawSquare( (Food1_X_Axis/10)*10 , (Food1_Y_Axis/10)*10 , 13 , colors[5] );	// food displaying
	
}

void randomFood(long &x,long &y)	//func: for generating random locations
{
		srand(time(NULL));

		x = (rand()%400) + 100;
		y = (rand()%400) + 100;
}

void randomFood1(long &x,long &y)	//func: for generating random locations
{
		srand(time(NULL));

		x = (rand()%550)+50;
		y = (rand()%550)+50;
}

void boundaryHurdle(void)	//func: for boundary walls
{
	for(int xdown=0 ; xdown<width ; xdown++)	//for x-axis on bottom
	{
		DrawSquare( xdown , 0 , 20 ,colors[99]);
	}

	for(int yleft=0 ; yleft<height ; yleft++)	//for y-axis on left
	{
		DrawSquare( 0 , yleft , 20 ,colors[99]);
	}
	
	for(int yright=0 ; yright<height ; yright++)	//for y-axis on right
	{
		DrawSquare( 630 , yright , 30 ,colors[99]);
	}
	for(int xup=0 ; xup<width ; xup++)		//for x-axis on top
	{
		DrawSquare( xup , 630 , 30 ,colors[99]);
	}
}

void game_Over()	//func: for game over
{
	over_counter += 1;	//for animation

	if(over_counter %20 != 0 )	//animation display
	{
		DrawString( 220, 450, "GAME OVER..!!!", colors[138]); //text "game over"
	}
	

	if(over_counter %30 != 0 )	//animation display
	{
		DrawString( 210, 350, "Your Score was ", colors[138]);	//text "score"
		DrawString( 390, 350, to_string(score_counter), colors[138]); // displaying score of player
	}

	if(over_counter %30 != 0 )	//animation display
	{
		DrawString( 210, 250, "Highest Score is ", colors[138]);	//text "high score"
		DrawString( 390, 250, to_string(high_score), colors[138]); // displaying high score of player
	}

	//DrawString( 210, 150, "Press A to Play Again", colors[138]);

}

void game_Pause()	//func: for game pause
{
	DrawString( 210, 450, "GAME PAUSED..!!!", colors[138]);
	DrawString( 210, 350, "[R] RESUME GAME", colors[138]);
}


void game_Menu()	//func: for game menu
{
	DrawString( 200, 570, "[Enter] PLAY GAME", colors[138]);
	DrawString( 200, 500, "[I] INSTRUCTIONS", colors[138]);			
	DrawString( 200, 430, "[H] HIGH SCORE", colors[138]);		
	DrawString( 200, 350, "[D] DEVELOPER'S INFO", colors[138]);
	DrawString( 200, 280, "[L] LEVELS", colors[138]);
	DrawString( 200, 210, "[ESC] END GAME", colors[138]);

////for restoring value of high score back in game////
	fstream InputFile;
	InputFile.open("HighScore.txt", ios::in);
	InputFile>>high_score;
	InputFile.close();
///////////////////////////////////////////////////////
}


void Developer(void)
{

	DrawString( 30 , 550 , "Developer: " , colors[MISTY_ROSE] ) ;

	DrawString( 30 , 500 , "Abdullah Naveed" , colors[MISTY_ROSE] ) ;
	DrawString( 30 , 450 , "Mail- --" , colors[MISTY_ROSE] ) ;
	DrawString( 30 , 400 , "Contact- ---" , colors[MISTY_ROSE] ) ;


	DrawString( 210, 300, "[Enter] PLAY GAME", colors[138]);
	DrawString( 210, 250, "[M] MAIN MENU", colors[138]);
	DrawString( 210, 200, "[I] INSTRUCTIONS", colors[138]);
	DrawString( 210, 150, "[H] HIGH SCORE", colors[138]);
	DrawString( 210, 100, "[L] LEVELS", colors[138]);
	DrawString( 210, 50, "[ESC] END GAME", colors[138]);



}

void high_Score()	//func: for game high score
{
	DrawString( 210, 550, "Highest Score is ", colors[84]);
	DrawString( 410, 550, to_string(high_score), colors[138]);

	DrawString( 210, 300, "[Enter] PLAY GAME", colors[138]);
	DrawString( 210, 250, "[M] MAIN MENU", colors[138]);
	DrawString( 210, 200, "[I] INSTRUCTIONS", colors[138]);
	DrawString( 210, 150, "[D] DEVELOPER'S INFO", colors[138]);
	DrawString( 210, 100, "[L] LEVELS", colors[138]);
	DrawString( 210, 50, "[ESC] END GAME", colors[138]);
}

void Instructions()	//func: for instructions
{
	DrawString( 150, 550, "Welcome To Instruction Manual", colors[84]);
	DrawString( 30 , 500 , "[1] Use Arrow keys to MOVE SNAKE" , colors[MISTY_ROSE] ) ;
	DrawString( 30 , 450 , "[2] Eat the Food to get SnakeLength + Score" , colors[MISTY_ROSE] ) ;
	DrawString( 30 , 400 , "[3] Eat the Power Food to get MORE SnakeLength + Score" , colors[MISTY_ROSE] ) ;
	DrawString( 30 , 350 , "[4] Press P during the gameplay to PAUSE" , colors[MISTY_ROSE] ) ;

	DrawString( 210, 300, "[Enter] PLAY GAME", colors[138]);
	DrawString( 210, 250, "[M] MAIN MENU", colors[138]);
	DrawString( 210, 200, "[H] HIGH SCORE", colors[138]);
	DrawString( 210, 150, "[D] DEVELOPER'S INFO", colors[138]);
	DrawString( 210, 100, "[L] LEVELS", colors[138]);
	DrawString( 210, 50, "[ESC] END GAME", colors[138]);
}

void levels(void)
{
	DrawString( 150, 550, "Select Your Desired Level", colors[84]);
	DrawString( 80 , 500 , "[1] Level 1" , colors[MISTY_ROSE] ) ;
	DrawString( 80 , 450 , "[2] Level 2" , colors[MISTY_ROSE] ) ;
	DrawString( 80 , 400 , "[3] Level 3" , colors[MISTY_ROSE] ) ;
	DrawString( 80 , 350 , "[4] Default" , colors[MISTY_ROSE] ) ;


	if(game_level == 1)
    		{
    			DrawString( 20 , 500 , "==>" , colors[5] ) ;
    		}

	if(game_level == 2)
    		{
    			DrawString( 20 , 450 , "==>" , colors[5] ) ;
    		}

	if(game_level == 3)
    		{
    			DrawString( 20 , 400 , "==>" , colors[5] ) ;
    		}

	if(game_level == 0)
    		{
    			DrawString( 20 , 350 , "==>" , colors[5] ) ;
    		}

    DrawString( 210, 250, "[Enter] PLAY GAME", colors[138]);
	DrawString( 210, 200, "[M] MAIN MENU", colors[138]);
	DrawString( 210, 150, "[H] HIGH SCORE", colors[138]);
	DrawString( 210, 100, "[D] DEVELOPER'S INFO", colors[138]);
	DrawString( 210, 50, "[ESC] END GAME", colors[138]);
}



/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) 
{ 

	
	    if (key == GLUT_KEY_LEFT) //when left key pressed  
				{
					if(snakeDirection != RIGHT)	//if right key is pressed already then left key will not work
					{								
							 snakeDirection=LEFT;	//for left
				    }
				    
				    
	      		}

	    if (key == GLUT_KEY_RIGHT)  //when right key pressed
				{
					if(snakeDirection != LEFT)	//if left key is pressed already then right key will not work
					{						
			      		snakeDirection=RIGHT;	//for right
			      	}
			      
			      	
			     }

	    if (key == GLUT_KEY_UP) //when up key pressed
	       		{
			      	if(snakeDirection != DOWN)	//if down key is pressed already then up key will not work
			      	{					
			      		snakeDirection=UP;	//for up
			      	}
			      	
			      	
			     }

	    if (key == GLUT_KEY_DOWN)  //when down key pressed  
				{
			    	if(snakeDirection != UP)		//if up key is pressed already then down key will not work			
			     	{
			     		 snakeDirection=DOWN;	//for down
			     	}
			     
			     	
	    		}
	 

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {				//for resuming game

    	game_pause = false;

        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }

    if (key == 13 /* Enter key ASCII*/) {		// for entering the game

    	game_menu = false;
    	high_score_menu = false;
    	Developer_menu = false;
    	Instruction_menu = false;
    	levels_menu = false;

    }

    if (key == 'p' || key=='P'/* P key ASCII*/) {		// for pausing the game

    	game_menu = false;

        game_pause =  true;
    }

    if (key == 'M' || key=='m'/* M key ASCII*/) {	//for main menu

    	game_menu = true;

        high_score_menu =  false;

        Developer_menu = false;

        Instruction_menu = false;

        levels_menu = false;
    }

    if (key == 'H' || key=='h'/* H key ASCII*/) {	//for high score

    	game_menu = false;

    	high_score_menu = true;

    	Developer_menu = false;

    	Instruction_menu = false;

    	levels_menu = false;
    }

    if (key == 'D' || key=='d'/* D key ASCII*/) {	//for Developer information

    	game_menu = false;

    	Developer_menu = true;

    	high_score_menu=false;

    	Instruction_menu = false;

    	levels_menu = false;
    }

    if (key == 'I' || key=='i'/* I key ASCII*/) {	//for Developer information

    	game_menu = false;

    	Developer_menu = false;

    	high_score_menu=false;

    	Instruction_menu = true;

    	levels_menu = false;
    }


    if (key == 'A' || key=='a'/* A key ASCII*/) {	//for Developer information

    	//again_play = true;
    	
    }
    

    if (key == 'L' || key=='l'/* L key ASCII*/) {	//for Developer information

    	game_menu = false;

    	Developer_menu = false;

    	high_score_menu=false;

    	Instruction_menu = false;

    	levels_menu = true;

    }
    if(levels_menu == true)
    {
    		if(key == '1')
    		{
    			game_level = 1 ;
       		}

    		if(key == '2')
    		{
    			game_level = 2 ;
    		}

    		if(key == '3')
    		{
    			game_level = 3 ;
    		}

    		if(key == '4')
    		{
    			game_level = 0 ;
    		}
    }
    
    else if (int(key) == 13)
    {  
	}
    
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}



/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 650, height = 650; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("PF's Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...

// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);

// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}

