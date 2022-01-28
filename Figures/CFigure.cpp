#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
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