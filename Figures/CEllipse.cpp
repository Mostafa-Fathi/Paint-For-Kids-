#include "CEllipse.h"
#include <fstream>
 
CEllipse::CEllipse(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	BottomRightCorner = P2;
	Center.x = (P1.x + P2.x) / 2;
	Center.y = (P1.y + P2.y) / 2;
	radiusX = Center.x - TopLeftCorner.x;
	radiusY = Center.y - TopLeftCorner.y;
}

CEllipse::CEllipse()
{

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

bool CEllipse::Resize(float factor,const GUI* Gui)  
{
	//resize code here
	//if (radiusX > 25 && radiusY > 25) {
		//int vRadius = (BottomRightCorner.y- TopLeftCorner.y) / 2 * factor;
		//int hRadius = (BottomRightCorner.x- TopLeftCorner.x) / 2 * factor;
		radiusX *= factor;
		radiusY *= factor;
		TopLeftCorner.x = Center.x - radiusX;
		TopLeftCorner.y = Center.y - radiusY;
		BottomRightCorner.x = Center.x + radiusX;
		BottomRightCorner.y = Center.y + radiusY;
		if (Gui->IsValueInDrawArea(TopLeftCorner) && Gui->IsValueInDrawArea(BottomRightCorner)) { return true; }
		else return false;
	//}
}


void CEllipse::Save(ofstream& OutFile) {
	color figCol;
	if (this->IsSelected()) {
		figCol = this->FigGfxInfo.PrevDrawClr;
	}
	else {
		figCol = this->FigGfxInfo.DrawClr;
	}
	OutFile << "ELPS" << "\t" << this->ID << "\t" << this->TopLeftCorner.x << "\t"
		<< this->TopLeftCorner.y << "\t" << this->BottomRightCorner.x << "\t" << this->BottomRightCorner.y << "\t" << this->ConvertToString(figCol) << "\t";
	if (this->FigGfxInfo.isFilled == true) {
		OutFile << this->ConvertToString(this->FigGfxInfo.FillClr) << "\n";
	}
	else {
		OutFile << "NO_FILL" << "\n";
	}
}

void CEllipse::Load(ifstream& fin)
{
	string draw, fill;
	bool is_fill = false;
	fin >> ID >> TopLeftCorner.x >> TopLeftCorner.y
		>> BottomRightCorner.x >> BottomRightCorner.y >> draw >> fill;

	if (strcmp(fill.c_str(), "NO_FILL") != 0)
	{
		is_fill = true;
		FigGfxInfo.FillClr = ConvertToColor(fill);
	}

	FigGfxInfo.DrawClr = ConvertToColor(draw);
	FigGfxInfo.isFilled = is_fill;
	FigGfxInfo.BorderWdth = 3;
	Selected = false;

	Center.x = (TopLeftCorner.x + BottomRightCorner.x) / 2;
	Center.y = (TopLeftCorner.y + BottomRightCorner.y) / 2;
	radiusX = abs(TopLeftCorner.x - Center.x);
	radiusY = abs(TopLeftCorner.y - Center.y);
}