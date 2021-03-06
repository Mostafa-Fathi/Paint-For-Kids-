#include <iostream>
#include "ApplicationManager.h"
#include "Actions/ActionAddSquare.h"
#include "Actions/ActionAddEllipse.h"
#include "Actions/ActionAddPolygon.h"
#include "Actions/ActionSelect.h"
#include "Actions/ActionResize.h"
#include "Actions/ActionSendToBack.h"
#include "Actions/ActionBringFront.h"
#include "Actions/ActionLoad.h"
#include "Actions/ActionSave.h"
#include "Actions/ActionDelete.h"
#include "Actions/ActionExit.h"
#include "Actions/ActionSelectMany.h"
#include "Actions/ActionFillColor.h"
#include "Actions/ActionDrawColor.h"
#include "Actions/ActionSwitchToPlay.h"
#include "Actions/ActionSwitchToDraw.h"
#include "Actions/ActionUiBackground.h"
#include "Actions/ActionPickByType.h"
#include "Actions/ActionPickByColor.h"
#include "Actions/ActionPickByTypeColor.h"
#include "Actions/ActionPlayModeSelect.h"
#include "Figures/CEllipse.h"
#include "Figures\CPolygon.h"
#include "Figures\CSquare.h"
#include <fstream>


 
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
	UI.oldFillColor = UI.FillColor;
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	pGUI->UseUpdateInterface(this);
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
		{
			if (UI.InterfaceMode == MODE_DRAW) newAct = new ActionSelect(this);
			else if (UI.InterfaceMode == MODE_PLAY) newAct = new ActionPlayModeSelect(this);
			break;
		}
		case RESIZE:
			newAct = new ActionResize(this);
			break;

		case DRAW_COLOR:
			newAct = new ActionDrawColor(this);
			break;

		case FILL_COLOR:
			newAct = new ActionFillColor(this); 
			break;

		case BACKGROUND_COLOR:
			newAct = new ActionUiBackground(this);
			break;

		case SEND_BACK:
			newAct = new ActionSendToBack(this);
			break;

		case BRING_FRONT:
			newAct = new ActionBringFront(this);
			break;

		case TO_PLAY:
			newAct = new ActionSwitchToPlay(this);
			break;

		case TO_DRAW:
			newAct = new ActionSwitchToDraw(this);
			break;

		case SAVE:
			newAct = new ActionSave(this);
			break;

		case LOAD:
			newAct = new ActionLoad(this);
			break;

		case DEL:
			newAct= new ActionDelete(this);
			break;

		case MULTI_SELECT:
			newAct = new ActionSelectMany(this);
			break;

		case EXIT:
			newAct = new ActionExit(this);
			break;

		case PICK_BY_TYPE:
			newAct = new ActionPickByType(this);
			break;

		case PICK_BY_COLOR:
			newAct = new ActionPickByColor(this);
			break;

		case PICK_BY_TYPE_COLOR:
			newAct = new ActionPickByTypeColor(this);
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

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	

	switch (UI.InterfaceMode) {
	case MODE_DRAW:
		pGUI->CreateDrawToolBar();
		break;
	case MODE_PLAY:
		pGUI->CreatePlayToolBar();
		break;
	case MODE_RESIZE:
		pGUI->CreateSizeBar();
		break;
	case MODE_BACKGROUND:
		pGUI->CreatebackgroundBar();
		break;
	case MODE_DRAWCOLOR:
		pGUI->CreateDrawColorBar();
		break;
	case MODE_FILLCOLOR:
		pGUI->CreateFillColorBar();
		break;
	}

	//pGUI->PrintMessage(pGUI->GetMessage());
	
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
	else if (_color == ORANGE) return "ORANGE";
	else if (_color == TURQUOISE) return "TURQUOISE"; 
	//brakat
	else if (_color == BROWN) return "BROWN";
	else if (_color == BURLYWOOD) return "BURLYWOOD";
	else if (_color == LIGHTGOLDENRODYELLOW) return "LIGHTGOLDENRODYELLOW";
	else if (_color == BLANCHEDALMOND) return "BLANCHEDALMOND";
	
}
/////////////////////////////////////////////////////////////////////////////////////////
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
	else if (color_as_string == "ORANGE")
		return ORANGE;
	else if (color_as_string == "TURQUOISE")
		return TURQUOISE;
	else if (color_as_string == "BROWN")
		return BROWN;
	else if (color_as_string == "BURLYWOOD")
		return BURLYWOOD;
	else if (color_as_string == "LIGHTGOLDENRODYELLOW")
		return LIGHTGOLDENRODYELLOW;
	else if (color_as_string == "BLANCHEDALMOND")
		return BLANCHEDALMOND;
	else
		return BLACK;
}
/////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::LoadTest()
{
	if (FigCount > 0)
	{
		int returnedValue = MessageBox(NULL, "Do U Want To Save Current Shapes", "Load", MB_ICONQUESTION | MB_OKCANCEL);
		if (returnedValue == IDOK)
		{
			ActionSave ActionS(this/*, getFigCount()*/);
			ActionS.Execute();
		}

	}
}
void ApplicationManager::LoadSteps(ifstream &file)
{
	int numberOfsapes;
	file >> numberOfsapes;
	string figType;
	CFigure* Figure;

	for (int x = 0; x < numberOfsapes; x++)
	{
		file >> figType;
		if (figType == "SQR")
		{
			Figure = new CSquare;
		}
		else if (figType == "POLY")
		{
			Figure = new CPolygon;
		}
		else if (figType == "ELPS")
		{
			Figure = new CEllipse;
		}

		Figure->Load(file);
		AddFigure(Figure);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ClearFigList()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i] = NULL;
	}
	FigCount = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::BringSelectedFigFront() {
	CFigure* Selected = GetSelectedFigure();
	if (Selected != NULL)
	{
		int Index = Selected->ID - 1;

		for (int i = Index; i < FigCount - 1; i++) {
			FigList[i] = FigList[i + 1];
			FigList[i]->ID = i + 1;
		}
		Selected->ID = FigCount;
		FigList[FigCount - 1] = Selected;
		pGUI->PrintMessage(Selected->GetDetails());
		pGUI->SaveMessage(Selected->GetDetails());


	}	
	else
		pGUI->PrintMessage("Firstly, Select a fig");

}
/////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SendSelectedFigBack() {

	CFigure* Selected = GetSelectedFigure();

	if (Selected != NULL)
	{
		int Index = Selected->ID - 1;

		for (int i = Index; i > 0; i--) {

			FigList[i] = FigList[i - 1];
			FigList[i]->ID = i + 1;
		}
		Selected->ID = 1;
		FigList[0] = Selected;
		pGUI->PrintMessage(Selected->GetDetails());
		pGUI->SaveMessage(Selected->GetDetails());

	}
	else
		pGUI->PrintMessage("Firstly, Select a fig");

}
/////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ShowAllFig() {
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->ShowMe();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteSelectedFig() {
	CFigure* Selected = GetSelectedFigure();
	if (Selected != NULL)
	{
		while (Selected != NULL) {
			int Index = Selected->ID - 1;
			for (int i = Index; i < FigCount - 1; i++) {
				FigList[i] = FigList[i + 1];
				FigList[i]->ID = i + 1;
			}

			FigCount--;
			FigList[FigCount] = NULL;

			delete Selected;
			Selected = GetSelectedFigure();
		}
		pGUI->ClearStatusBar();
	}
	else
		pGUI->PrintMessage("Firstly, Select a Figure");

}
/////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::UnSelectAllFig()
{
	for (int i = (FigCount - 1); i >= 0; i--) {
		if (FigList[i]->IsSelected()) {
			FigList[i]->SetSelected(false);
			FigList[i]->ChngDrawClr(FigList[i]->GetPreviousDrawColor());
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::CalcMaxScore() {
	switch (Game->Mode) {
	case ByType:
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i]->GetType() == Game->SelectedType)
			{
				Game->MaxScore++;
			}
		}
		break;


	case ByColor:
		for (int i = 0; i < FigCount; i++) {
			if (Game->SelectedFillState) {
				if (FigList[i]->GetFillColor() == Game->SelectedColor && FigList[i]->IsFilled())
				{
					Game->MaxScore++;
				}
			}
			else if (!FigList[i]->IsFilled())
			{
				Game->MaxScore++;
			}

		}
		break;
	case ByTypeAndColor:
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i]->GetType() == Game->SelectedType) {
				if (Game->SelectedFillState) {
					if (FigList[i]->GetFillColor() == Game->SelectedColor && FigList[i]->IsFilled())
					{
						Game->MaxScore++;
					}
				}
				else if (!FigList[i]->IsFilled())
				{
					Game->MaxScore++;
				}

			}

		}
		break;
	}

}
/////////////////////////////////////////////////////////////////////////////////////////
int ApplicationManager::getFigCount() {
	return FigCount;
}