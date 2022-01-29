#include "ActionLoad.h"
#include "../GUI/GUI.h"
#include "../ApplicationManager.h"
#include <fstream>
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include "ActionAddSquare.h"
#include "..\Figures\CSquare.h"
#include <iostream>
#include <Windows.h>
ifstream openFile(char* path);

ActionLoad::ActionLoad(ApplicationManager* aApp) : Action(aApp)
{

}

void ActionLoad::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	int figCounts = pManager->getFigCount();
	if (figCounts > 0)
	{
		int returnedValue = MessageBox(NULL, "Do U Want To Save Current Shapes", "Load", MB_ICONQUESTION | MB_OKCANCEL);
		//	OK--> return one  //
		//  Cancel --> return two  //
		if (returnedValue == IDOK)
		{
			// call saveAll function -----------remeber add it to have many errors :(   ----------------
			// call deleteAll function -----------remeber add it to have many errors :(   ----------------
			pGUI->PrintMessage("saved");
		}
		else if (returnedValue == IDCANCEL)
		{
			// do nothing
			// just test         ----------remeber delete it :)------
			pGUI->PrintMessage("not saved");
		}
		//call save here -----------------------------------------
	}

	// clean window
	////// delete here -------------------remeber it ---------------------------
	//load file
	OPENFILENAME ofn;
	char file_name[100];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	//type of files
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0";

	if (GetOpenFileName(&ofn))
	{
		string line;
		int numberOfsapes;
		pGUI->PrintMessage("load");
		//display file
		ifstream file = openFile(ofn.lpstrFile);
		int i = 0;
		char type;
		string shapeData = line;
		while (getline(file, line))
		{
			i++;
			shapeData = line;
			if (i == 1)
			{
				char* chLine = const_cast<char*>(line.c_str());
				char* token = strtok(chLine, "\t");
				int k = 0;
				while (token != NULL)
				{
					k++;
					color windowColor;
					if (k == 1)
					{
						pGUI->setCrntDrawColor(windowColor.getCurrentColor(token));
					}
					if (k == 2)
					{
						pGUI->setCrntFillColor(windowColor.getCurrentColor(token));
					}
					if (k == 3)
					{
						pGUI->setBkGrndColor(windowColor.getCurrentColor(token));
					}
					token = strtok(NULL, "\t");
				}

			}
			if (i == 2)
			{
				numberOfsapes = std::stoi(line);
				cout << numberOfsapes;

				for (int x = 0; x < numberOfsapes; x++)
				{

					while (getline(file, line))
					{

						int j = 0;
						shapeData = line;

						ofstream shapefile("data.txt");

						char* cLine = const_cast<char*>(line.c_str());
						//cout << c;
						char* token = strtok(cLine, "\t");
						while (token != NULL)
						{
							j++;
							if (j == 1)
							{
								if (strcmp(token, "SQR") == 0)
								{
									type = 'S';
									shapefile << shapeData << endl;
									shapefile.close();

								}
							}
							token = strtok(NULL, "\t");
							break;

						}
						ifstream read = openFile("data.txt");

						switch (type)
						{
						case 'S':
							CFigure * C = new CSquare();
							C->Load(read);
							pManager->AddFigure(C);

							// ---------remember---------//
							// handle other shapes save here -----------------------------------------
							// add load in others ---------------------------------------
							// handle all used color
						}
						read.close();
					}

				}

			}
		}
		file.close();

	}// end of line
	else
	{
		pGUI->PrintMessage("not loaded");
	}

}


ifstream openFile(char* path)
{
	ifstream file;
	string line;
	int number_of_lines = 0;
	file.open(path);
	return file;
}



