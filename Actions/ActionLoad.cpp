#include "ActionLoad.h"
#include "../GUI/GUI.h"
#include "../ApplicationManager.h"
#include <fstream>
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include "ActionAddSquare.h"
#include "ActionSave.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CPolygon.h"
#include "..\Figures\CEllipse.h"
#include <iostream>
#include <Windows.h>
#include <string.h>
ifstream openFile(char* path);

ActionLoad::ActionLoad(ApplicationManager* aApp) : Action(aApp)
{

}

void ActionLoad::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pManager->LoadTest();

	//load file 
	OPENFILENAME ofn;
	char file_name[100];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0'; 
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0";
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn))
	{
		pManager->ClearFigList();
		pGUI->ClearDrawArea();

		string draw, fill, bg;
		ifstream file = openFile(ofn.lpstrFile);

		if (file.is_open()== false)
		{
			pGUI->PrintMessage("not loaded");
		}
		else {
			pGUI->PrintMessage("loaded");

			file >> draw >> fill >> bg;
			pGUI->setCrntDrawColor(pManager->ConvertToColor(draw));
			pGUI->setCrntFillColor(pManager->ConvertToColor(fill));
			pGUI->setBkGrndColor(pManager->ConvertToColor(bg));
			pManager->LoadSteps(file);
		}
		
	}
}


ifstream openFile(char* path)
{
	ifstream file;
	string line;
	file.open(path);
	return file;
}