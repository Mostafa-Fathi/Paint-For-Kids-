#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

CFigure::CFigure()
{

}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
}

void CFigure::ChngDrawClr(color Dclr)
{
	FigGfxInfo.DrawClr = Dclr;
}
color CFigure::GetDrawColor() {
	return FigGfxInfo.DrawClr;
}
void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}
color CFigure::GetPreviousDrawColor() {
	return FigGfxInfo.PrevDrawClr;
}
void CFigure::SetPreviousDrawColor(color Pclr) {
	FigGfxInfo.PrevDrawClr = Pclr;
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
	else if (color_as_string == "MAGENTA")
		return MAGENTA;
	else if (color_as_string == "BROWN")
		return BROWN;
	else if (color_as_string == "TURQUOISE")
		return TURQUOISE;
	else
		return BLACK;
}