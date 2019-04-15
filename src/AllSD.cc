#include "AllSD.hh"
#include "DetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4HEVector.hh"


AllSD::AllSD(G4String name, DetectorConstruction* SD) 
  :G4VSensitiveDetector(name),Detector(SD)
{
  G4String HCname="AllCollection";
  collectionName.insert(HCname);
}

AllSD::~AllSD()
{;}


void AllSD::Initialize(G4HCofThisEvent*)
{
  AllCollection = new AllHitsCollection
    (SensitiveDetectorName,collectionName[0]); 

  HitID = -1;
  verboseLevel=0;
}


G4bool AllSD::ProcessHits
  (G4Step* aStep, G4TouchableHistory*)
{
////Get the All hit
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  G4VPhysicalVolume* physVol = theTouchable->GetVolume(); 
  G4int AllNumber = 0;
  AllNumber= physVol->GetCopyNo();
	
	G4double edep = aStep->GetTotalEnergyDeposit();
       	
	if (edep==0) return false;
	
	
  AllHit* aAllHit = new AllHit();

  aAllHit->SetAllPos(aStep->GetPostStepPoint()->GetPosition());
  aAllHit->SetAllTime(aStep->GetPostStepPoint()->GetGlobalTime());
  aAllHit->SetAllsTime(aStep->GetPreStepPoint()->GetGlobalTime());
  aAllHit->SetAllAll(AllNumber);
  aAllHit->SetAllParticle(aStep->GetTrack()->GetDefinition()->GetParticleName());
  aAllHit->SetAllEnergy(aStep->GetTrack()->GetKineticEnergy());
  aAllHit->SetAllEdepV(aStep->GetTotalEnergyDeposit());
  aAllHit->SetAllParticleType(aStep->GetTrack()->GetDefinition()->GetParticleType());
  aAllHit->SetAllTrackLength(aStep->GetStepLength());
  aAllHit->SetAllMomentum(aStep->GetTrack()->GetMomentum());
  aAllHit->SetAllMomentumDir(aStep->GetTrack()->GetMomentumDirection());
  // aAllHit->SetVolName(aStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName());
  aAllHit->SetVolName(aStep->GetTrack()->GetVolume()->GetName());
  aAllHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  aAllHit->SetParentID(aStep->GetTrack()->GetParentID());

  //aAllHit->GetParentName(aStep->GetTrack()->GetParentID()->GetTrack()->GetParticleType());
  //  aAllHit ->SetnuclearProcess(aStep->GetTrack()->GetCreatorProcess()->GetProcessName());

  aAllHit->SetCurrentStepNumber(aStep->GetTrack()->GetCurrentStepNumber());
  aAllHit->SetVertexPosition(aStep->GetTrack()->GetVertexPosition());
  aAllHit->SetVelocity(aStep->GetTrack()->GetVelocity());
  aAllHit->SetVertexMomentumDirection(aStep->GetTrack()->GetVertexMomentumDirection());
  aAllHit->SetVertexKineticEnergy(aStep->GetTrack()->GetVertexKineticEnergy());
  aAllHit->SetMass(aStep->GetTrack()->GetDynamicParticle()->GetMass());


// hit is nuclear recoil
  if (aStep->GetTrack()->GetCreatorProcess()) {
    G4String part = aStep->GetTrack()->GetDefinition()->GetParticleType();
    G4String proc = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
    if(proc) {
        if(part=="nucleus" && 
	  (proc == "neutronElastic") ) {
	aAllHit->SetRecoil();
      }
    }
  }

 // hit is inelastic nuclear recoil
  if( aStep->GetTrack()->GetCreatorProcess() ) {
    if( aStep->GetTrack()->GetCreatorProcess()
	->GetProcessName() == "neutronInelastic") {  
      if(aStep->GetTrack()->GetDefinition()->GetParticleName() != "gamma"){
 aAllHit->SetInelasticRecoil();
       }
    }
  }

 
HitID = AllCollection->insert(aAllHit);
 
   return true;
}

void AllSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  G4String HCname = collectionName[0];
  static G4int HCID = -1;
  if(HCID<0)
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(HCname);
    HCE->AddHitsCollection(HCID,AllCollection);
  
  G4int nHits = AllCollection->entries();
  if (verboseLevel>=1) {
    G4cout << "     Number of All hits: " << nHits << G4endl;
    if (verboseLevel>=1)
      AllCollection->PrintAllHits();

  }
}

void AllSD::clear()
{;}

void AllSD::DrawAll()
{;}

void AllSD::PrintAll()
{;}
