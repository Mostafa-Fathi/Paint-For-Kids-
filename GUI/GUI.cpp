#include "GUI.h"
#include <iostream>

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 80;
	
	UI.DrawColor = BLUE;	//Drawing color
	
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.FillColor = UI.BkGrndColor;	//Filling color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//
void GUI::CreateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const 
{
	string Label;
	
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
		{
			PrintMessage("The Save action is cancelled");
			return "";	//returns nothing as user has cancelled label
		}

		if (Key == 13 && !Label.empty())	//ENTER key is pressed
			return Label;
		if (Key == 8 && Label.size() > 0)	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		PrintMessage(Label);
	}
}
bool GUI::IsValueInDrawArea(int y) const {
	if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight) 
		return true;
	return false;
}
bool GUI::IsValueInDrawArea(Point p) const {
	if ((p.y >= UI.ToolBarHeight && p.y < UI.height - UI.StatusBarHeight)&&(p.x>=0 && p.x <= UI.width))
		return true;
	return false;
}
//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType(int& x, int& y) const
{	
	int cx, cy;
	pWind->WaitMouseClick(cx, cy);	//Get the coordinates of the user click
	x = cx;
	y = cy;

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEX: return DRAW_HEX;

			case ITM_EXIT: return EXIT;	
			case ITM_RESIZE: return RESIZE;
			case ITM_DRAW_COLOR: return DRAW_COLOR;
			case ITM_FILL_COLOR: return FILL_COLOR;
			case ITM_BACKGROUND_COLOR: return BACKGROUND_COLOR;

			case ITM_SEND_TO_BACK: return SEND_BACK;
			case ITM_BRING_TO_FORWARED: return BRING_FRONT;
			case ITM_SWITCH_PLAY_MODE: return TO_PLAY;
			case ITM_SAVE: return SAVE;
			case ITM_DEL:return DEL;
			case ITM_LOAD: return LOAD;

			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (IsValueInDrawArea(y))
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	if (UI.InterfaceMode == MODE_RESIZE)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{

			case ITM_QUARTER: return QUARTER;
			case ITM_HALF: return HALF;
			case ITM_DOUBLE: return DOUBLED;
			case ITM_QUADRUPLE: return QUADRUPLE;
			case ITM_BACK2: return BACK;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	if (UI.InterfaceMode == MODE_BACKGROUND)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_BURLYWOOD: return BACKG_BURLYWOOD;
			case ITM_LIGHTGOLDENRODYELLOW: return BACKG_LIGHTGOLDENRODYELLOW;
			case ITM_BLANCHEDALMOND: return BACKG_blanchedalmond;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	if (UI.InterfaceMode == MODE_DRAWCOLOR)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{

			case ITM_DORANGE: return DRAW_ORANGE;
			case ITM_DRED: return DRAW_RED;
			case ITM_DBLUE: return DRAW_BLUE;
			case ITM_DGREEN: return DRAW_GREEN;

			default: return DRAW_RED;//  EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	if (UI.InterfaceMode == MODE_FILLCOLOR)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{

			case ITM_EMPTY: return EMPTYFILL;
			case ITM_RED: return REDFILL;
			case ITM_BLUE: return BLUEFILL;
			case ITM_GREEN: return GREENFILL;
			case ITM_WHITE: return WHITEFILL;
			case ITM_BLACK: return BLACKFILL;
			case ITM_BROWN: return BROWNFILL;
			case ITM_YELLOW: return YELLOWFILL;
			case ITM_ORANGE: return ORANGEFILL;
				 
					
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight) {

			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_TYPE: return PICK_BY_TYPE;
			case ITM_COLOR: return PICK_BY_COLOR;
			case ITM_TYPE_COLOR: return PICK_BY_TYPE_COLOR;
			case ITM_SWITCH_DRAW_MODE: return TO_DRAW;
			default: return EMPTY;
			}

		}
		else if (IsValueInDrawArea(y)) {
			return DRAWING_AREA;
		}
		else {
			return STATUS;
		}
	}	

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	CreateToolBar();
	UI.InterfaceMode = MODE_DRAW;

	

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_HEX] = "images\\MenuItems\\Menu_Poly.jpg";
	MenuItemImages[ITM_FILL_COLOR] = "images\\MenuItems\\fill.JPG";
	MenuItemImages[ITM_DRAW_COLOR] = "images\\MenuItems\\brush.JPG";
	MenuItemImages[ITM_BACKGROUND_COLOR] = "images\\MenuItems\\ui2.JPG";

	 
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\Resize.jpg";
	MenuItemImages[ITM_SEND_TO_BACK]= "images\\MenuItems\\sendToback.jpg";
	MenuItemImages[ITM_BRING_TO_FORWARED]= "images\\MenuItems\\bringtoforward.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\delete_icon.jpg";
	MenuItemImages[ITM_SWITCH_PLAY_MODE] = "images\\MenuItems\\playMode.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateSizeBar() const
{
	CreateToolBar();
	CreateStatusBar(); // clear the prev tool bar
	UI.InterfaceMode = MODE_RESIZE;

	string MenuItemImages[SIZE_ITM_COUNT];
	
	MenuItemImages[ITM_QUARTER] = "images\\MenuItems\\one-quarter.jpg";
	MenuItemImages[ITM_HALF] = "images\\MenuItems\\one-half.jpg";
	MenuItemImages[ITM_DOUBLE] = "images\\MenuItems\\2x.jpg";
	MenuItemImages[ITM_QUADRUPLE] = "images\\MenuItems\\4x.jpg";
	MenuItemImages[ITM_BACK2] = "images\\MenuItems\\Menu_Back_2.jpg";
	
	 
	///TODO: write code to create Color mode menu
	for (int i = 0; i < SIZE_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth ,0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
void GUI::CreateDrawColorBar() const
{
	CreateToolBar();
	CreateStatusBar(); // clear the prev tool bar
	UI.InterfaceMode = MODE_DRAWCOLOR;

	string MenuItemImages[Draw_Color_ITM_COUNT];
	 
	MenuItemImages[ITM_DORANGE] = "images\\MenuItems\\drawOrange.JPG";
	MenuItemImages[ITM_DRED] = "images\\MenuItems\\drawRed.JPG";
	MenuItemImages[ITM_DGREEN] = "images\\MenuItems\\drawGreen.JPG";
	MenuItemImages[ITM_DBLUE] = "images\\MenuItems\\drawBlue.JPG";


	///TODO: write code to create Color mode menu
	for (int i = 0; i < Draw_Color_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//mb+
void GUI::CreateFillColorBar() const
{
	CreateToolBar();
	CreateStatusBar(); // clear the prev tool bar
	UI.InterfaceMode = MODE_FILLCOLOR;

	string MenuFillItemImages[Fill_Color_ITM_COUNT];
 
	MenuFillItemImages[ITM_EMPTY] = "images\\MenuItems\\Empty.jpg";
	MenuFillItemImages[ITM_RED] = "images\\MenuItems\\Menu_Red.JPG";
	MenuFillItemImages[ITM_GREEN] = "images\\MenuItems\\Menu_Green.JPG";
	MenuFillItemImages[ITM_BLUE] = "images\\MenuItems\\Menu_Blue.jpg";

	MenuFillItemImages[ITM_WHITE ] = "images\\MenuItems\\Menu_White.JPG";
	MenuFillItemImages[ITM_BLACK ] = "images\\MenuItems\\Menu_Black.jpg";
	MenuFillItemImages[ITM_BROWN ] = "images\\MenuItems\\Menu_Brown.JPG";
	MenuFillItemImages[ITM_YELLOW] = "images\\MenuItems\\Menu_Yellow.JPG";
	MenuFillItemImages[ITM_ORANGE] = "images\\MenuItems\\Menu_Orange.JPG";



	///TODO: write code to create Color mode menu
	for (int i = 0; i < Fill_Color_ITM_COUNT; i++)
		pWind->DrawImage(MenuFillItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
void GUI::CreatebackgroundBar() const
{
	CreateToolBar();
	CreateStatusBar(); // clear the prev tool bar
	UI.InterfaceMode = MODE_BACKGROUND;

	string MenuItemImages[BACKGROUND_COLOR_ITM_COUNT];

	MenuItemImages[ITM_BURLYWOOD] = "images\\MenuItems\\1.jpg";
	MenuItemImages[ITM_LIGHTGOLDENRODYELLOW] = "images\\MenuItems\\2.jpg";
	MenuItemImages[ITM_BLANCHEDALMOND] = "images\\MenuItems\\3.jpg";
	  
	///TODO: write code to create Color mode menu
	for (int i = 0; i < BACKGROUND_COLOR_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//mb-
void GUI::CreatePlayToolBar() const
{
	CreateToolBar();
	

	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu

	string MenuItemImages[PLAY_ITM_COUNT];

	MenuItemImages[ITM_TYPE] = "images\\MenuItems\\byShapes.jpg";
	MenuItemImages[ITM_COLOR] = "images\\MenuItems\\byColors.jpg";
	MenuItemImages[ITM_TYPE_COLOR] = "images\\MenuItems\\byShapesAndColors.jpg";
	MenuItemImages[ITM_SWITCH_DRAW_MODE] = "images\\MenuItems\\drawRed.JPG";


	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);	
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntDrawColor(color Draw) const	//get current drwawing color
{
	UI.DrawColor = Draw;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setCrntFillColor(color Fill) const	//get current filling color
{
	UI.FillColor = Fill;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setBkGrndColor(color BKColor) const		//get current pen width
{
	UI.BkGrndColor = BKColor;
}
//////////////////////////////////////////////////////////////////////////////////////////
color GUI::getCrntDrawColor() const	//get current drwawing color
{	
	return UI.DrawColor; 
}
//////////////////////////////////////////////////////////////////////////////////////////
color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	 

}
//////////////////////////////////////////////////////////////////////////////////////////
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	

}




//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P1.x +length, P1.y+length, style);
	//pWind->DrawLine(P1.x, P1.y, P1.x + length, P1.y + length, style);

}
//Draw ellipse  
void GUI::DrawEllipse(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);
}

//Draw polygon
void GUI::DrawPolygon(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;



	//int xs[] = { 50, 100, 150, 150, 100, 50 };
	//int ys[] = { 100, 50, 100, 150, 200, 150 };

	int xs[6];
	int ys[6];

	int nOfSides = 6;

	Point center;
	center.x = P1.x + length / 2;
	center.y = P1.y + length / 2;

	int radius = length / 2;
	/////////////////////////////////
	/// calculate the points
	float const PI = 3.14159265;
	const int nsides = 6;

	float angle = 0.0f;
	float incr = 2.0 * PI / nsides;


	int newX = radius * cos(angle) + center.x;
	int newY = radius * sin(angle) + center.y;

	for (int i = 0; i < nsides; i++)
	{
		int oldX = newX;
		int oldY = newY;
		angle += incr;
		newX = radius * cos(angle) + center.x;
		newY = radius * sin(angle) + center.y;
		xs[i] = oldX;
		ys[i] = oldY;
	}
	pWind->DrawPolygon(xs, ys, nOfSides, style);

}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

