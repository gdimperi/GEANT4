#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
  ~RunAction();  // is virtual in B4

  public:
    void BeginOfRunAction(const G4Run*);   // is virtual in B4
    void EndOfRunAction(const G4Run*);    // is virtual in B4
};

#endif
