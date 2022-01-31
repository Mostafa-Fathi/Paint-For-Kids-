#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"

class Action;	//Forward Declaration


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	//Pointers to Input and Output classes
	GUI* pGUI;
	

public:	
	int X, Y;
	ApplicationManager();
	GUI* getGUI();

	~ApplicationManager();

	

	void Run();		//to run the application
	
	// -- Action-Related Functions
	Action* CreateAction(ActionType);
	void ExecuteAction(Action*&) ; //Execute an action
	void SaveAll(ofstream& OutFile);


	// -- Figures Management Functions
	//Adds a new figure to the FigList
	void AddFigure(CFigure* pFig);
	//Search for a figure given a point inside the figure
	CFigure* GetFigure(int x, int y) const;
	//Search for the selected figure
	CFigure* GetSelectedFigure();
	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window	
	int getFigCount();
	int getFigMaxCount();
	CFigure** getFigList();



	// -- Convert Colors to string and string to colors
	static string ConvertToString(color _color);   //Convert from Color Type to String Type
	color ConvertToColor(string color_as_string);
};

#endif