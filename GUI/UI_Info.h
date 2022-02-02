#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_RESIZE,
	MODE_DRAWCOLOR,
	MODE_FILLCOLOR,
	MODE_BACKGROUND
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SQUR,		//Square item in menu
	ITM_ELPS,		//Ellipse item in menu
	ITM_HEX,		//Polygon item in menu
	//TODO: Add more items names here
	ITM_DRAW_COLOR,    //draw color icon
	ITM_FILL_COLOR,   //fill color icon
	ITM_BACKGROUND_COLOR,
	ITM_RESIZE,		//resize menu
	ITM_SEND_TO_BACK,
	ITM_BRING_TO_FORWARED,
	ITM_SAVE,
	ITM_LOAD,
	ITM_DEL,
	ITM_EXIT,//Exit item

	//no. of menu items ==> This should be the last line in this enum
	DRAW_ITM_COUNT
	
};
enum SizeMenuItem // The items of colors
{
	ITM_QUARTER,
	ITM_HALF,
	ITM_DOUBLE,
	ITM_QUADRUPLE,
	ITM_BACK2,

	SIZE_ITM_COUNT
};
//background colors
enum BackgroundMenuItem // The items of draw colors
{
	ITM_BLANCHEDALMOND,
	ITM_BURLYWOOD,
	ITM_LIGHTGOLDENRODYELLOW,
	BACKGROUND_COLOR_ITM_COUNT
};
//draw colors
enum DrawColorMenuItem // The items of draw colors
{
	ITM_DORANGE,
	ITM_DRED,
	ITM_DGREEN,
	ITM_DBLUE, 
	Draw_Color_ITM_COUNT
};
//mbfillcolor
enum FillColorMenuItem // The items of fill colors
{
	ITM_EMPTY,
	ITM_RED,
	ITM_GREEN,
	ITM_BLUE,
	ITM_WHITE,
	ITM_BLACK,
	ITM_BROWN,
	ITM_YELLOW,
	ITM_ORANGE,

	Fill_Color_ITM_COUNT
};

 
enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	 
	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color oldFillColor;
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	bool ShapeIsFilled = false;
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif