
#ifndef SteppingAction_H
#define SteppingAction_H 1

#include "G4UserSteppingAction.hh"
#include "G4VProcess.hh"

#include "G4Track.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
  
  SteppingAction();
  ~SteppingAction();

public:

  virtual void UserSteppingAction(const G4Step* aStep);
  G4VProcess* GetCurrentProcess();
  // G4TrackStatus* GetTrackStatus();


private:
  G4int EvtVeto;
  G4int EvtVetoGas;
  G4int EvtVetoTop;
  G4int EvtVetoSide;
  
};

#endif

