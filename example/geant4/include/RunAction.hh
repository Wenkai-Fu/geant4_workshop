#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "typedef.hh"
#include <cmath>
#include "G4SystemOfUnits.hh"

// to accumulate variable
#include "G4AccumulableManager.hh"
#include "G4Accumulable.hh"

#include "G4Run.hh"

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    vec_double cal_ave(G4double, G4double, G4int);

    void Accumulate_event(G4double);

  private:
    G4Accumulable<G4double> rerg;
    G4Accumulable<G4double> rerg2;
};

#endif

