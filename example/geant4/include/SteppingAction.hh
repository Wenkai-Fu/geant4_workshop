#ifndef INCLUDE_STEPPINGACTION_HH_
#define INCLUDE_STEPPINGACTION_HH_

#include "EventAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "globals.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(EventAction*);
	virtual ~SteppingAction();

	void UserSteppingAction(const G4Step*);

private:
	EventAction* eact;
};

#endif
