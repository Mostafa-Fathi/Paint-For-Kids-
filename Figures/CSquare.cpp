#include "CSquare.h"
#include <fstream>

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
	if (Hidden==false)
	{
		pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
	}
	
}


bool CSquare::HasPoint(int x, int y) const {
	if (Hidden == false) {
		if (x >= TopLeftCorner.x && x <= TopLeftCorner.x + length &&
			y >= TopLeftCorner.y && y <= TopLeftCorner.y + length)
			return true;
	}

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
bool CSquare::Resize(float factor ,const GUI* Gui)
{	
	Point center;
	center.x = (2*TopLeftCorner.x + length) / 2;
	center.y= (2*TopLeftCorner.y + length) / 2;
	length = length * factor;
	TopLeftCorner.x = center.x - (length / 2);
	TopLeftCorner.y = center.y - (length / 2);
	Point BottomRight;
	BottomRight.x = TopLeftCorner.x + length;
	BottomRight.y = TopLeftCorner.y + length;
	if (Gui->IsValueInDrawArea(TopLeftCorner) && Gui->IsValueInDrawArea(BottomRight)) { return true; }
	else return false;


}


/// Save Square ///////////////////////////////////////
void CSquare::Save(ofstream& OutFile) {
	color figCol;
	if (this->IsSelected()) {
		figCol = this->FigGfxInfo.PrevDrawClr;
	}
	else {
		figCol = this->FigGfxInfo.DrawClr;
	}
	OutFile << "SQR" << "\t" << this->ID << "\t" << this->TopLeftCorner.x << "\t"
		<< this->TopLeftCorner.y << "\t" << this->length << "\t" << this->ConvertToString(figCol) << "\t";
	if (this->FigGfxInfo.isFilled == true) {
		OutFile << this->ConvertToString(this->FigGfxInfo.FillClr) << "\n";
	}
	else {
		OutFile << "NO_FILL" << "\n";
	}
}


void CSquare::Load(ifstream & fin)
{
	string draw, fill;
	bool is_fill = false;
	fin >> ID >> TopLeftCorner.x >> TopLeftCorner.y
		>> length >> draw >> fill;

	if (fill != "NO_FILL")
	{
		is_fill = true;
		FigGfxInfo.FillClr = ConvertToColor(fill);
	}
	else {
		is_fill = false;
		FigGfxInfo.FillClr = BLACK;
	
	}
	FigGfxInfo.DrawClr = ConvertToColor(draw);
	FigGfxInfo.isFilled = is_fill;
	FigGfxInfo.BorderWdth = 3;
	Selected = false;
	Hidden = false;
	
}

figure CSquare::GetType() const {
	return Squr;
}