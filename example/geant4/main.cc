
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"

#include "ActionInitialization.hh"

#include "G4Threading.hh"
#include "G4ScoringManager.hh"
#include <string>

#include "QGSP_BERT_HP.hh"

#include "G4SystemOfUnits.hh"

#include "Randomize.hh"

#include "cstdlib" // environment variable setting

#include <cassert>


int main(int argc,char** argv)
{
	// Detect interactive mode
	G4UIExecutive* ui = 0;
	/* choose running mode
	 * 	GUI mode, call using:
	 *     	executable init_vis.mac
	 *  run mode, call using:
	 *  	executable run.mac reactant trench wall length physics_list (> out.txt)
	 */
	// start the UI section if the mac file name contains "init_vis.mac"
	// sometimes the argv[1] contains Linux path, e.g., ../init_vis.mac
	std::string vis_file = "init_vis.mac";
	if (std::string(argv[1]).find(vis_file) != std::string::npos)
		ui = new G4UIExecutive(argc, argv);

	// Construct run manager
#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager;
	runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
#else
	G4RunManager* runManager = new G4RunManager;
#endif

	// Set mandatory initialization classes
	// Detector construction
	runManager->SetUserInitialization(new DetectorConstruction());

	//	 Physics list
	runManager -> SetUserInitialization(new QGSP_BERT_HP());

	// User action initialization
	runManager->SetUserInitialization(new ActionInitialization());


	// Initialize visualization
	G4VisManager* visManager = new G4VisExecutive;
	visManager -> Initialize();

	// UI manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// Process macro or start UI session
	if(!ui){
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager -> ApplyCommand(command + fileName);
	}
	else{
		// interactive mode
		UImanager->ApplyCommand(G4String("/control/execute ") +
				G4String(argv[1]));
		ui -> SessionStart();
		delete ui;
	}

	// Job termination
	// Free the store: user actions, physics_list and detector_description are
	// owned and deleted by the run manager, so they should not be deleted
	// in the main() program !
	if (visManager)
		delete visManager;
	if (runManager)
		delete runManager;
	return 0;
}

