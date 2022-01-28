#include "CPolygon.h"

CPolygon::CPolygon(Point P1, int len, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
	Center.x = TopLeftCorner.x + length / 2;
	Center.y = TopLeftCorner.y + length / 2;
}


void CPolygon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a hexagon on the screen	
	pGUI->DrawPolygon(TopLeftCorner, length, FigGfxInfo, Selected);
}

bool CPolygon::HasPoint(int x, int y) const {
	boolean c = false;
	int xs[6];
	int ys[6];

	int nOfSides = 6;
	
	float const PI = 3.14159265;
	const int nsides = 6;
	int radius = length / 2;
	float angle = 0.0f;
	float incr = 2.0 * PI / nsides;


	int newX = radius * cos(angle) + Center.x;
	int newY = radius * sin(angle) + Center.y;

	for (int i = 0; i < nsides; i++)
	{
		int oldX = newX;
		int oldY = newY;
		angle += incr;
		newX = radius * cos(angle) + Center.x;
		newY = radius * sin(angle) + Center.y;
		xs[i] = oldX;
		ys[i] = oldY;
	}
	for (int i = 0, j = 5; i < 6; j = i++)
	{
		if (((ys[i] > y) != (ys[j] > y))
			&& (x < (xs[j] - xs[i]) * (y - ys[i]) / (ys[j] - ys[i]) + xs[i]))
			c = !c;
	}
	return c;
}
string CPolygon::GetDetails() const {
	string details = "figure Id=" + to_string(ID)
		+ " | center point(" + to_string(TopLeftCorner.x + (length / 2)) + "," + to_string(TopLeftCorner.y + (length / 2))
		+ ") | length=" + to_string(length)
		+ " | radius=" + to_string(length / 2)
		+ " | area=" + to_string((3 * sqrt(3) * pow((length / 2), 2)) / 2);

	return details;
}
void CPolygon::Resize(float factor)
{
	
	length = length * factor;
	TopLeftCorner.x = (TopLeftCorner.x + Center.x) * factor;
	TopLeftCorner.y = (TopLeftCorner.y + Center.y) * factor;

	
}