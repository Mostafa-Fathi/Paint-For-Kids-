#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contais some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_SQUARE,	//Draw a Square
	DRAW_ELPS,		//Draw an Ellipse
	DRAW_HEX,		//Draw a Hexagon
	//fill colors
	FILL_COLOR,   // fill color 
	EMPTYFILL,		//empty fill
	REDFILL,		//red
	BLUEFILL,		//blue
	GREENFILL,		//green
	WHITEFILL,
	BLACKFILL,
	BROWNFILL,
	YELLOWFILL,
	ORANGEFILL,

	//draw colors
	DRAW_COLOR,
	DRAW_BLUE,
	DRAW_GREEN,
	DRAW_RED,
	DRAW_ORANGE,

	//background color 
	BACKGROUND_COLOR,
	BACKG_BURLYWOOD,
	BACKG_blanchedalmond,
	BACKG_LIGHTGOLDENRODYELLOW,

	CHNG_DRAW_CLR,	//Change the drawing 

	CHNG_FILL_CLR,	//Change the filling color
	CHNG_BK_CLR,	//Change background color
	DEL,			//Delete a figure(s)
	MOVE,			//Move a figure(s)
	RESIZE,			//Resize a figure(s)
	ROTATE,			//Rotate a figure(s)
	SEND_BACK,		//Send a figure to the back of all figures
	BRING_FRONT,	//Bring a figure to the front of all figures
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	EXIT,			//Exit the application
	MULTI_SELECT,
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,			//Switch interface to Play mode
		////// Actions of Size mode //////
	TO_SIZE,
	QUARTER,
	HALF,
	DOUBLED,
	QUADRUPLE,

	// Actions related to play mode
	PICK_BY_TYPE,
	PICK_BY_COLOR,
	PICK_BY_TYPE_COLOR,

	BACK

	///TODO: Add more action types (if needed)
	

};

struct Point	//To be used for figures points
{ int x,y; 
};

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color PrevDrawClr; //the previous draw color of the figure
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders
	//float Resize_Factor;//Size Factor
};


#endif