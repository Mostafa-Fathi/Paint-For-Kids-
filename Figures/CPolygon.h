#ifndef CPOLYGON_H
#define CPOLYGON_H

#include "CFigure.h"

class CPolygon : public CFigure
{
private:
	Point TopLeftCorner;
	Point Center;
	int length;

public:
	CPolygon(Point, int, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	virtual bool HasPoint(int x, int y) const;
	virtual string GetDetails() const;
	void Resize(float);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& fin);
};

#endif
 