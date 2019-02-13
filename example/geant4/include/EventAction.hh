#ifndef INCLUDE_EVENTACTION_HH_
#define INCLUDE_EVENTACTION_HH_

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "RunAction.hh"

class EventAction : public G4UserEventAction
{
public:
	EventAction(RunAction*);
	~EventAction();

	void BeginOfEventAction(const G4Event*);
	void EndOfEventAction(const G4Event*);

	void add_energy(G4double);

private:
	G4double erg;
	RunAction* ract;
};
#endif
