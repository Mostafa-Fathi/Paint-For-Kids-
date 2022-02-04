#include "ActionSave.h"
#include "..\GUI\GUI.h"
#include "..\ApplicationManager.h"
#include <iostream>
#include <fstream>


ActionSave::ActionSave(ApplicationManager* pApp) :Action(pApp) {
	FileName = "";
}

void ActionSave::Execute() {

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Please write the file name then press ENTER");

	//read the FileName
	FileName = pGUI->GetSrting();
	
	if (!FileName.empty()) {
		ofstream OutFile;
		OutFile.open(".\\saved\\" + FileName + ".txt");
		OutFile << pManager->ConvertToString(UI.DrawColor) << "\t" << pManager->ConvertToString(UI.FillColor) << "\t" << pManager->ConvertToString(UI.BkGrndColor) << "\n" << pManager->getFigCount() << "\n";
		pManager->SaveAll(OutFile);
		pGUI->PrintMessage("File is saved successfully");
		OutFile.close();
	}



}
