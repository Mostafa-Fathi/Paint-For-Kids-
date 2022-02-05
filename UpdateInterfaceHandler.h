#pragma once
#include "ApplicationManager.h"
class UpdateInerfaceHandler {
public:
	void callback(ApplicationManager* pManger) {
	
		pManger->UpdateInterface();
	}
};