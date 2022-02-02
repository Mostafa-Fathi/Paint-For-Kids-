#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
public:
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	CSquare();
	virtual void DrawMe(GUI* pOut) const;
	virtual bool HasPoint(int x, int y) const;
	virtual string GetDetails() const;
	bool Resize(float, const GUI*);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& fin);
};

#endif