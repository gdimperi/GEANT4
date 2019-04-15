#include "G4SteppingManager.hh"
#include "SteppingAction.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "globals.hh" 
#include "G4StepPoint.hh" 
#include "G4StepStatus.hh"
#include "G4ReactionProduct.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"
#include "RunAction.hh"


//For outputting to ascii:
#include <iomanip>
#include <iostream>
#include <fstream>

SteppingAction::SteppingAction()
{}
 
SteppingAction::~SteppingAction()
{}

G4VProcess* SteppingAction::GetCurrentProcess()
{
  return fpSteppingManager->GetfCurrentProcess();
}
 void SteppingAction::UserSteppingAction(const G4Step* aStep)
{

  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
  G4int eID = 0;
  if(evt) eID = evt->GetEventID();

  std::ofstream File("Recoils.dat",std::ios::app);
 
  if(aStep->GetTrack()->GetVolume()->GetName()=="GAS_phys") {

    File << eID << "\t"
	 << aStep->GetTrack()->GetTrackID() << "\t"
	 << aStep->GetTrack()->GetParentID() << "\t"
	 << aStep->GetTrack()->GetDefinition()->GetParticleName() << "\t"
	 << aStep->GetTrack()->GetPosition()[0] << "\t"
	 << aStep->GetTrack()->GetPosition()[1] << "\t"
	 << aStep->GetTrack()->GetPosition()[2] << "\t"
	 << aStep->GetTrack()->GetKineticEnergy()*1000 << "\t"
	 << aStep->GetTotalEnergyDeposit()*1000 << G4endl;
  }
}







