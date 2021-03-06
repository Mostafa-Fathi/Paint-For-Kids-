#include "CFigure.h"
#include "../GUI/GUI.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	Hidden = false;
}

CFigure::CFigure()
{

}
void CFigure::HideMe() {

	Hidden = true;
}
void CFigure::ShowMe() {
	Hidden = false;

}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
}
bool CFigure::IsFilled() const {
	return FigGfxInfo.isFilled;
}

void CFigure::fillShape(bool s)
{
	FigGfxInfo.isFilled = s;
}
void CFigure::ChngDrawClr(color Dclr)
{
	if (Selected) {
		FigGfxInfo.PrevDrawClr = Dclr;
	}
	else {
		FigGfxInfo.DrawClr = Dclr;
	}
}
color CFigure::GetDrawColor() {
	return FigGfxInfo.DrawClr;
}

color CFigure::GetFillColor() {
	return FigGfxInfo.FillClr;
}

void CFigure::ChngFillClr(color Fclr)
{ 
		FigGfxInfo.FillClr = Fclr; 
}
color CFigure::GetPreviousDrawColor() {
	return FigGfxInfo.PrevDrawClr;
}
void CFigure::SetPreviousDrawColor(color Pclr) {
	FigGfxInfo.PrevDrawClr = Pclr;
}

string CFigure::ConvertToString(color _color)
{
	if (_color == BLACK) return "BLACK";
	else if (_color == WHITE) return "WHITE";
	else if (_color == BLUE) return "BLUE";
	else if (_color == RED) return "RED";
	else if (_color == YELLOW) return "YELLOW";
	else if (_color == GREEN) return "GREEN";
	else if (_color == LIGHTGOLDENRODYELLOW) return "LIGHTGOLDENRODYELLOW";
	else if (_color == ORANGE) return "ORANGE";
	else if (_color == TURQUOISE) return "TURQUOISE";
	//brakat
	else if (_color == BROWN) return "BROWN";
	else if (_color == BURLYWOOD) return "BURLYWOOD";
	else if (_color == BLANCHEDALMOND) return "BLANCHEDALMOND";
	else if (_color == LIGHTGOLDENRODYELLOW) return "LIGHTGOLDENRODYELLOW";

}

color CFigure::ConvertToColor(string color_as_string)
{
	if (color_as_string == "BLUE")
		return BLUE;
	else if (color_as_string == "WHITE")
		return WHITE;
	else if (color_as_string == "RED")
		return RED;
	else if (color_as_string == "YELLOW")
		return YELLOW;
	else if (color_as_string == "GREEN")
		return GREEN;
	else if (color_as_string == "LIGHTGOLDENRODYELLOW")
		return LIGHTGOLDENRODYELLOW;
	else if (color_as_string == "ORANGE")
		return ORANGE;
	else if (color_as_string == "TURQUOISE")
		return TURQUOISE;

	//brakat 
	else if (color_as_string == "BROWN")
		return BROWN;
	else if (color_as_string == "BURLYWOOD")
		return BURLYWOOD;
	else if (color_as_string == "LIGHTGOLDENRODYELLOW")
		return LIGHTGOLDENRODYELLOW;
	else if (color_as_string == "BLANCHEDALMOND")
		return BLANCHEDALMOND;
	else
		return BLACK;
	
}