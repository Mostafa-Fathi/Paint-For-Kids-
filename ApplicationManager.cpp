#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddEllipse.h"
#include "Actions\ActionAddPolygon.h"
#include "Actions\ActionSelect.h"
#include "Actions/ActionResize.h"
#include "Actions/ActionSendToBack.h"
#include "Actions/ActionBringFront.h"
#include "Actions/ActionLoad.h"
#include "Actions/ActionSave.h"
#include "Actions/ActionDelete.h"
#include "Actions/ActionExit.h"
#include <iostream>


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
			newAct = new ActionResize(this);
			break;

		case SEND_BACK:
			newAct = new ActionSendToBack(this);
			break;

		case BRING_FRONT:
			newAct = new ActionBringFront(this);
			break;
		case SAVE:
			newAct = new ActionSave(this, FigCount);
			break;
		case LOAD:
			newAct = new ActionLoad(this);
			break;
		case DEL:
			newAct= new ActionDelete(this);
			break;
		case EXIT:
			newAct = new ActionExit(this);
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
//////////////////////////////////////////////////////////////////////
// Save the file
void ApplicationManager::SaveAll(ofstream& OutFile)
{
	for (int i = 0; i < FigCount; i++) {
		FigList[i]->Save(OutFile);
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
CFigure* ApplicationManager::GetSelectedFigure( ) 
{
	//If a figure is found return a pointer to it.
	//if there is no selected figure return NULL
	//retrun index of selected figure by passing index by referance 

	for (int i = (FigCount - 1); i >= 0; i--) {
		if (FigList[i]->IsSelected()) { 
			
			return FigList[i]; }
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::CleanFigureList()
{	
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
	}
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pGUI->ClearDrawArea();
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
/////////////////////////////////////////////////////////////////////////////////////////

string ApplicationManager::ConvertToString(color _color)
{
	
	if (_color == BLACK) return "BLACK";
	else if (_color == WHITE) return "WHITE";
	else if (_color == BLUE) return "BLUE";
	else if (_color == RED) return "RED";
	else if (_color == YELLOW) return "YELLOW";
	else if (_color == GREEN) return "GREEN";
	else if (_color == LIGHTGOLDENRODYELLOW) return "LIGHTGOLDENRODYELLOW";
	else if (_color == MAGENTA) return "MAGENTA";
	else if (_color == TURQUOISE) return "TURQUOISE";
}

color ApplicationManager::ConvertToColor(string color_as_string)
{
	if (color_as_string == "BLUE")
		return BLUE;
	else if (color_as_string == "WHITE")
		return WHITE;
	else if (color_as_string == "RED")
		return RED;
	else if (color_as_string == "YELLOW")
		return YELLOW;
	else if (color_as_string == "GREEN")
		return GREEN;
	else if (color_as_string == "LIGHTGOLDENRODYELLOW")
		return LIGHTGOLDENRODYELLOW;
	else if (color_as_string == "MAGENTA")
		return MAGENTA;
	else if (color_as_string == "TURQUOISE")
		return TURQUOISE;
	else
		return BLACK;
}

void ApplicationManager::LoadTest()
{
	if (FigCount > 0)
	{
		int returnedValue = MessageBox(NULL, "Do U Want To Save Current Shapes", "Load", MB_ICONQUESTION | MB_OKCANCEL);
		if (returnedValue == IDOK)
		{
			ActionSave ActionS(this, getFigCount());
			ActionS.Execute();
		}
		ClearFigList();
		pGUI->ClearDrawArea();
	}
}
void ApplicationManager::ClearFigList()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i] = NULL;
	}
	FigCount = 0;
}
void ApplicationManager::BringSelectedFigFront() {
	CFigure* Selected = GetSelectedFigure();
	if (Selected != NULL)
	{
		int Index = Selected->ID - 1;

		for (int i = Index; i < FigCount - 1; i++) {
			cout << "\n fig count is =" << FigCount - 1;
			FigList[i] = FigList[i + 1];
			FigList[i]->ID = i + 1;

			cout << "\n id of fig is :" << FigList[i]->ID;
		}
		Selected->ID = FigCount;
		FigList[FigCount - 1] = Selected;
		pGUI->PrintMessage(Selected->GetDetails());

	}	
	else
		pGUI->PrintMessage("Firstly, Select a fig");

}
void ApplicationManager::SendSelectedFigBack() {

	CFigure* Selected = GetSelectedFigure();

	if (Selected != NULL)
	{
		int Index = Selected->ID - 1;

		for (int i = Index; i > 0; i--) {

			FigList[i] = FigList[i - 1];
			FigList[i]->ID = i + 1;

			cout << "\n id of fig is :" << FigList[i]->ID;
		}
		Selected->ID = 1;
		FigList[0] = Selected;
		pGUI->PrintMessage(Selected->GetDetails());

	}
	else
		pGUI->PrintMessage("Firstly, Select a fig");

}
void ApplicationManager::DeleteSelectedFig() {
	CFigure* Selected = GetSelectedFigure();
	if (Selected != NULL)
	{
		int Index = Selected->ID - 1;

		for (int i = Index; i < FigCount - 1; i++) {
			cout << "\n fig count is =" << FigCount - 1;
			FigList[i] = FigList[i + 1];
			FigList[i]->ID = i + 1;

			cout << "\n id of fig is :" << FigList[i]->ID;
		}
		
		FigCount--;
		delete Selected;
		pGUI->ClearStatusBar();
	}
	else
		pGUI->PrintMessage("Firstly, Select a fig");

}
