#include "CEllipse.h"
 
CEllipse::CEllipse(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	BottomRightCorner = P2;
	Center.x = (P1.x + P2.x) / 2;
	Center.y = (P1.y + P2.y) / 2;
	radiusX = abs(TopLeftCorner.x - Center.x);
	radiusY = abs(TopLeftCorner.y - Center.y);
}


void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawEllipse to draw an Ellipse on the screen	
	pGUI->DrawEllipse(TopLeftCorner, BottomRightCorner, FigGfxInfo, Selected);
}

bool CEllipse::HasPoint(int x, int y) const {
	if (pow(x - Center.x, 2) / pow(radiusX, 2) + pow(y - Center.y, 2) / pow(radiusY, 2) <= 1) return true;

	return false;
}
string CEllipse::GetDetails() const {
	string details = "figure Id=" + to_string(ID)
		+ " | center point(" + to_string(Center.x) + "," + to_string(Center.y)
		+ ") | radius x length=" + to_string(radiusX)
		+ " | radius y length=" + to_string(radiusY)
		+ " | area=" + to_string(3.14159265 * radiusX*radiusY);
	return details;
}
void CEllipse::Resize(float factor)
{
	//resize code here
	int sgin = 1;
	if (factor < 1) { sgin = -1; }
	int vRadius = (BottomRightCorner.y- TopLeftCorner.y) / 2 * factor;
	int hRadius = (BottomRightCorner.x- TopLeftCorner.x) / 2 * factor;
	TopLeftCorner.x = Center.x - hRadius;
	TopLeftCorner.y = Center.y - vRadius;
	BottomRightCorner.x = Center.x + hRadius;
	BottomRightCorner.y = Center.y + vRadius;
}

void CEllipse::Load(ifstream& fin)
{
}