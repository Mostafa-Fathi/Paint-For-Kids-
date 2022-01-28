#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"

//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	
	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);
	void SetSelected(bool );	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure
	
	//changes the figure's drawing color
	void ChngDrawClr(color Dclr);	
	
	//gets the current drawing color
	color GetDrawColor();

	//changes the figure's filling color
	void ChngFillClr(color Fclr);	

	//gets the previous drawing color of the figure
	color GetPreviousDrawColor();

	//sets the previous drawing color of the figure
	void SetPreviousDrawColor(color Pclr);

	//checks if a specific point is in the area of the figure
	virtual bool HasPoint(int, int) const = 0;

	//getting string contains all figure details
	virtual string GetDetails() const = 0;

	//Resize the figure
	virtual void Resize(float) = 0;

	
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure

	//virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	//virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif