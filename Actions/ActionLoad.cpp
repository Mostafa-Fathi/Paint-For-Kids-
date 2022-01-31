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
		string draw, fill, bg, figType;
		int numberOfsapes;
		ifstream file = openFile(ofn.lpstrFile);

		if (file.is_open()== false)
		{
			pGUI->PrintMessage("not loaded");
		}
		pGUI->PrintMessage("loaded");

		file >> draw >> fill >> bg;
		pGUI->setCrntDrawColor(pManager->ConvertToColor(draw));
		pGUI->setCrntFillColor(pManager->ConvertToColor(fill));
		pGUI->setBkGrndColor(pManager->ConvertToColor(bg));

		file >> numberOfsapes;
		CFigure* Figure;

		for (int x = 0; x < numberOfsapes; x++)
		{
			file >> figType;
			const char* figTypeC = figType.c_str();
			if (strcmp(figTypeC, "SQR") == 0)
			{
				Figure = new CSquare;
			}
			else if (strcmp(figTypeC, "POLY") == 0)
			{
				Figure = new CPolygon;
			}
			else if (strcmp(figTypeC, "ELPS") == 0)
			{
				Figure = new CEllipse;
			}

			Figure->Load(file);
			pManager->AddFigure(Figure);
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