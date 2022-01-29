#include "CSquare.h"

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
}

CSquare::CSquare()
{

}
	

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}



bool CSquare::HasPoint(int x, int y) const {
	if (x >= TopLeftCorner.x && x <= TopLeftCorner.x + length &&
		y >= TopLeftCorner.y && y <= TopLeftCorner.y + length)
		return true;

	return false;
}
string CSquare::GetDetails() const {
	string details = "figure Id=" + to_string(ID)
		+ " | start point(" + to_string(TopLeftCorner.x) + "," + to_string(TopLeftCorner.y)
		+ ") | end point(" + to_string(TopLeftCorner.x + length)
		+ "," + to_string(TopLeftCorner.y + length)
		+ ") | center point(" + to_string(TopLeftCorner.x + (length / 2))
		+ "," + to_string(TopLeftCorner.y + (length / 2))
		+ ") | length=" + to_string(length)
		+ " | area=" + to_string(length * length);
	return details;
}
void CSquare::Resize(float factor)
{	
	Point center;
	center.x = (2*TopLeftCorner.x + length) / 2;
	center.y= (2*TopLeftCorner.y + length) / 2;
	length = length * factor;
	TopLeftCorner.x = center.x - (length / 2);
	TopLeftCorner.y = center.y - (length / 2);

}