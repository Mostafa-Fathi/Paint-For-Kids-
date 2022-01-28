#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CFigure.h"

class CEllipse : public CFigure
{
private:
	Point TopLeftCorner;
	Point BottomRightCorner; 
	Point Center;
	int radiusX;
	int radiusY;

public: 
	CEllipse(Point, Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	virtual bool HasPoint(int x, int y) const;
	virtual string GetDetails() const;
};

#endif