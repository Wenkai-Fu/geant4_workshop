#include "SteppingAction.hh"

SteppingAction::SteppingAction(EventAction* tmp)
:G4UserSteppingAction()
{
	eact = tmp;
}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* astep)
{
	// get step point
	G4StepPoint* pre_point = astep -> GetPreStepPoint();
	G4StepPoint* post_point = astep -> GetPostStepPoint();

	// get physical volume
	G4VPhysicalVolume* pre_pv = pre_point -> GetPhysicalVolume();
	G4VPhysicalVolume* post_pv = post_point -> GetPhysicalVolume();

	// get physical volume name
	G4String pre_name = "";
	G4String post_name = "";
	if (post_pv){
		pre_name = pre_pv -> GetName();
		post_name = post_pv -> GetName();
	}
	else
		return;

	// accumulate the deposited energy in the tank
	if (pre_name == "tank_pv"){
		G4double step_erg = astep -> GetTotalEnergyDeposit();
		if (step_erg > 1.0e-20)
			eact -> add_energy(step_erg);
	}
}
