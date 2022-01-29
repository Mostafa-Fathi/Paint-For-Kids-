#include "GUI.h"

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
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
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
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
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
		if ( y >= 0 && y < UI.ToolBarHeight)
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
			case ITM_SEND_TO_BACK: return SEND_BACK;
			case ITM_BRING_TO_FORWARED: return BRING_FRONT;
			case ITM_LOAD: return LOAD;

			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
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
			case ITM_BACK2:return BACK;

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
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
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
	MenuItemImages[ITM_SQUR] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_ELPS] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_HEX] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\Menu_Poly.jpg";
	MenuItemImages[ITM_RESIZE] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\Resize.jpg";
	MenuItemImages[ITM_SEND_TO_BACK] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\sendToback.jpg";
	MenuItemImages[ITM_BRING_TO_FORWARED] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\bringtoforward.jpg";
	MenuItemImages[ITM_LOAD] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[ITM_EXIT] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\Menu_Exit.jpg";
	

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
	MenuItemImages[ITM_QUARTER] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\one-quarter.jpg";
	MenuItemImages[ITM_HALF] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\one-half.jpg";
	MenuItemImages[ITM_DOUBLE] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\2x.jpg";
	MenuItemImages[ITM_QUADRUPLE] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\4x.jpg";
	MenuItemImages[ITM_BACK2] = "C:\\Users\\abdel\\source\\repos\\Paint-For-Kids-\\images\\MenuItems\\Menu_Back_2.jpg";

	///TODO: write code to create Color mode menu
	for (int i = 0; i < SIZE_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth ,0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void GUI::CreatePlayToolBar() const
{
	CreateToolBar();
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
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
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

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
	pWind->DrawLine(P1.x, P1.y, P1.x + length, P1.y + length, style);

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

