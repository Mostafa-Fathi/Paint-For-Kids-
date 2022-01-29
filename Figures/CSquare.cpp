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

void CSquare::Load(ifstream& fin)
{
	string line;
	while (getline(fin, line))
	{ 
		int j = 0;
		color Color, figureColor, fill;
		bool is_fill = false;
		char* cLine = const_cast<char*>(line.c_str());
		string sqrData[7];

		char* token = strtok(cLine, "\t");
		while (token != NULL)
		{
			sqrData[j] = token;
			if (j == 6)
			{
				if (strcmp(token, "NO_FILL") != 0)
				{
					is_fill = true;
					fill = figureColor.getCurrentColor(sqrData[6]);
				}
			}
			token = strtok(NULL, "\t");
			j++;
		}
		
		GfxInfo SqrGfxInfo;
		SqrGfxInfo.isFilled = is_fill;
		SqrGfxInfo.DrawClr = figureColor.getCurrentColor(sqrData[5]);
		SqrGfxInfo.FillClr = fill;
		SqrGfxInfo.BorderWdth = 2;

		Point topLeft;
		topLeft.x = stoi(sqrData[2]);
		topLeft.y = stoi(sqrData[3]);

		this->TopLeftCorner = topLeft;
		this->ID = stoi(sqrData[1]);
		this->Selected = false;
		this->FigGfxInfo = SqrGfxInfo;
		this->length = stoi(sqrData[4]);
	}
}

