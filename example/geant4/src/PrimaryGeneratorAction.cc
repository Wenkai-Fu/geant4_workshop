#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
	generator = new G4GeneralParticleSource();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  if (generator)
	  delete generator;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	generator->	GeneratePrimaryVertex(anEvent);
}
