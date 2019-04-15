#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include <TH1D.h>
#include <CLHEP/Units/SystemOfUnits.h>

class EventMessenger;

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();
  
public:
  virtual void   BeginOfEventAction(const G4Event*);
  virtual void   EndOfEventAction(const G4Event*);
  
public:

  G4double      Allener;
  G4String      Allparticl;	
  G4String      AllparticlType;	
  G4ThreeVector Allpos;
  G4double      Allstim;
  G4double      Alltim;
  G4double      AlltotalE;
  G4double      AllTotalTrackLength;
  G4double      AllTrackLength;
  G4double      AllvEdep;
  G4int         InelasticNucHits;
  G4String      creatorProcess;
  G4String      AllVolume;
  G4double      particleke;
 
  private:
 
  G4int         AllCollID;
  G4int totEvents; //total number of events processed

};

#endif
