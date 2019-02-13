#include "EventAction.hh"

EventAction::EventAction(RunAction* tmp)
: G4UserEventAction() {ract = tmp;}

EventAction::~EventAction() {}

void EventAction::add_energy(G4double input){erg += input;}

void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
	erg = 0.0;
}

void EventAction::EndOfEventAction(const G4Event* anEvent){
	if (erg > 1.0e-20)
		ract -> Accumulate_event(erg);
}
