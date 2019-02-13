#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction();
  SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction());

  RunAction* runAction = new RunAction();
  SetUserAction(runAction);

  EventAction* eact = new EventAction(runAction);
  SetUserAction(eact);

  SteppingAction* sact = new SteppingAction(eact);
  SetUserAction(sact);
}
