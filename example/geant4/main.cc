#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4MTRunManager.hh"
#include "DetectorConstruction.hh"
#include "QGSP_BERT_HP.hh"
#include "ActionInitialization.hh"
#include "G4UImanager.hh"

int main(int argc,char** argv)
{
	// initialize multi-thread run manager
	G4MTRunManager* runManager = new G4MTRunManager();
	runManager -> SetNumberOfThreads(G4Threading::G4GetNumberOfCores());

	// set mandatory initialization classes
	// detector construction
	runManager -> SetUserInitialization(new DetectorConstruction());

	// physics list
	runManager -> SetUserInitialization(new QGSP_BERT_HP());

	// user action initialization
	runManager -> SetUserInitialization(new ActionInitialization());

	// UI manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// batch mode
	G4String command = "/control/execute ";
	G4String fileName = argv[1];
	UImanager -> ApplyCommand(command + fileName);

	// run manager frees the memory for the registered user actions,
	// physics list and detector_description
	if (runManager)
		delete runManager;
	return 0;
}
