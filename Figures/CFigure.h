#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"

//Base class for all figures
class CFigure
{
protected:
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	bool Hidden;

	/// Add more parameters if needed.

public:
	int ID;		//Each figure has an ID
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	void HideMe();
	void ShowMe();
	void SetSelected(bool);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	void fillShape(bool style) ;		//determine if shape is filled or not
	virtual void DrawMe(GUI*) const = 0;		//Draw the figure
	bool IsFilled() const; //checks if figure has fill color or not
	//changes the figure's drawing color
	void ChngDrawClr(color Dclr);

	//gets the current drawing color
	color GetDrawColor();

	//changes the figure's filling color
	void ChngFillClr(color Fclr);

	//gets the current drawing color
	color GetFillColor();

	//gets the previous drawing color of the figure
	color GetPreviousDrawColor();

	//sets the previous drawing color of the figure
	void SetPreviousDrawColor(color Pclr);

	//checks if a specific point is in the area of the figure
	virtual bool HasPoint(int, int) const = 0;

	//getting string contains all figure details
	virtual string GetDetails() const = 0;

	//Resize the figure
	virtual bool Resize(float, const GUI*)  = 0;

	//gets figure type
	virtual figure GetType() const=0;

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure

	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file

	//Load the figure parameters to the file
	virtual void Load(ifstream& Infile) = 0;

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar


	// -- Convert Colors to string and string to colors
	static string ConvertToString(color _color);   //Convert from Color Type to String Type
	color ConvertToColor(string color_as_string);
};

#endif