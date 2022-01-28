#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddEllipse.h"
#include "Actions\ActionAddPolygon.h"
#include "Actions\ActionSelect.h"
#include "Actions\ResizeAction.h"
#include "Actions/ActionSendToBack.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}
int ApplicationManager::getFigCount() {
	return FigCount;
}
int ApplicationManager::getFigMaxCount() {
	return MaxFigCount;
}
CFigure** ApplicationManager::getFigList() {
	return FigList;
}


void ApplicationManager::Run()
{
	int x, y;
	ActionType ActType;
	do
	{	
		//1- Read user action
		ActType = pGUI->MapInputToActionType(x, y);
		X = x; Y = y;

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	int selectedIndex;
	CFigure* selectedFigure = GetSelectedFigure(selectedIndex);

	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;

		case DRAW_ELPS:
			newAct = new ActionAddEllipse(this);
			break;

		case DRAW_HEX:
			newAct = new ActionAddPolygon(this);
			break;

		case DRAWING_AREA:
			newAct = new ActionSelect(this);
			break;

		case RESIZE:
			newAct = new ActionResize(this, selectedFigure);
			break;

		case SEND_BACK:
			newAct = new ActionSendToBack(this , selectedFigure, selectedIndex);
			break;

		case BRNG_FRNT:
			break;

		case EXIT:
			///create ExitAction here
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
	pFig->ID = FigCount;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	for (int i = (FigCount - 1); i >= 0; i--) {
		if (FigList[i]->HasPoint(x, y)) return FigList[i];
	}

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetSelectedFigure(int & index ) 
{

	//If a figure is found return a pointer to it.
	//if there is no selected figure return NULL

	for (int i = (FigCount - 1); i >= 0; i--) {
		if (FigList[i]->IsSelected()) { 
			index = i;
			return FigList[i]; }
	}

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}
