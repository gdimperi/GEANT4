#ifdef G4UI_USE_ROOT
  #include "G4UIRoot.hh"
#endif

////////////////////////////
#include "SteppingAction.hh"
/////////////////////////////
#include "EventAction.hh"
#include "AllHit.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
//For outputting to ascii:
#include <iomanip>
#include <fstream>
 
EventAction::EventAction()
{
  totEvents=0; 
}

EventAction::~EventAction(){}

void EventAction::BeginOfEventAction(const G4Event* evt)
{

 G4int evtNb;
 evtNb = evt->GetEventID();

 G4SDManager * SDman = G4SDManager::GetSDMpointer();
 AllCollID = SDman->GetCollectionID("AllCollection");
   
}
void EventAction::EndOfEventAction(const G4Event* evt)
{
  totEvents++;

  G4RunManager *runMan = G4RunManager::GetRunManager();
  G4int evtNb = evt->GetEventID();
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

  AllHitsCollection* AHC = NULL;

  G4String      Allparticl;	
  G4String      AllparticlType;	
  G4ThreeVector Allpos;
  G4double      AlltotalE = 0;
  G4double      AllTotalTrackLength = 0;
  G4double      AllTrackLength = 0;
  G4double      AllvEdep = 0;
  G4String      ProcName;
  G4ThreeVector firstMomentum;
  G4ThreeVector firstMomentumDir;
  G4int         index = 7;
  G4ThreeVector initMomCoord;
  G4ThreeVector momentum;
  G4ThreeVector momentumDir;
  G4double 	nips = 0;  
  G4int         n_hit = 0;
  G4double      parentID = 0; 
  G4String      particl;
  G4String      partType;
  G4ThreeVector spos;
  G4int      trackID = 0;
  G4ThreeVector vertexMomDir;
  G4ThreeVector vertexPosition;
  G4String      volumeName;
 
  // origin in the center on the cathode
  // G4double      yCorr = 73.275*cm; // distance to center of vessel 
   G4double      yCorr = 0*cm; // distance to center of vessel in cm 
   G4double      zCorr = 0*cm; // centered in drift zx plane 
   G4double      xCorr= 0*cm;  // centered in drift zx plane 
  ////////////////////////////////////////////////////////   
  G4int         InelasticNucHits = 0;               

 
  if (HCE) AHC  = (AllHitsCollection*)    (HCE->GetHC(AllCollID));

  n_hit = AHC->entries();
  
  for (G4int i=0;i<n_hit;i++)
    {
      Allstim        = (*AHC)[i]-> GetAllsTime();
      Alltim         = (*AHC)[i]-> GetAllTime();
      Allpos         = (*AHC)[i]-> GetAllPos();
      Allparticl     = (*AHC)[i]-> GetAllParticle();	
      Allener        = (*AHC)[i]-> GetAllEnergy();
      AllvEdep       = (*AHC)[i]-> GetAllEdepV();
      AllparticlType = (*AHC)[i]-> GetAllParticleType();	
      AllTrackLength = (*AHC)[i]-> GetAllTrackLength();
      momentum       = (*AHC)[i]-> GetAllmom();
      momentumDir    = (*AHC)[i]-> GetAllmomDir();
      volumeName     = (*AHC)[i]-> GetVolName();
      trackID        = (*AHC)[i]-> GetTrackID();
      parentID       = (*AHC)[i]-> GetParentID();
      vertexPosition = (*AHC)[i]-> GetVertexPosition();
      vertexMomDir   = (*AHC)[i]-> GetVertexMomentumDirection();  

      AlltotalE += AllvEdep;	
      AllTotalTrackLength += AllTrackLength;
      
    }


   if(n_hit!=0){        
      
     if((AlltotalE !=0) && (parentID != 0)){  // must have deposited energy + take out source neutrons bug
       if((Allparticl != "neutron") && ( InelasticNucHits !=1)){ // take out secondary neutron bug from geometry

  std::ofstream theFile2("edep.dat", std::ios::app);
  theFile2    <<evtNb<<"\t"
             <<AlltotalE/keV<<"\t"
	     <<(vertexPosition.x()/cm +zCorr)<<"\t" // Z
	     <<(vertexPosition.y()/cm +xCorr)<<"\t" //x
	     <<(vertexPosition.z()/cm +yCorr)<< "\t" //y
	     <<AllTotalTrackLength/cm<<"\t"
             <<Allparticl<<G4endl;                    

  if (Allparticl=="S32[0.0]" || Allparticl=="S33[0.0]") index=0;
  if (Allparticl=="C12[0.0]") index=1;
  if (Allparticl=="F19[0.0]") index=2;
  if(Allparticl== "alpha") index=3;

  if ((index == 0)){
    std::ofstream theFile444("sulfur.dat", std::ios::app);
    theFile444  <<evtNb<<"\t"
		<<volumeName<<"\t"
		<<parentID<<"\t"
		<<trackID<<"\t"
		<<AlltotalE/keV<<"\t"
		<<Allpos.x()/cm<<"\t" // Z
		<<Allpos.y()/cm<<"\t" //x
		<<Allpos.z()/cm<< G4endl; //y 
  }
		
  if ((index == 1)){
    std::ofstream theFile555("carbon.dat", std::ios::app);
    theFile555 <<evtNb<<"\t"
	       <<volumeName<<"\t"
	       <<parentID<<"\t"
	       <<trackID<<"\t"
	       <<AlltotalE/keV<<"\t"
  	       <<Allpos.x()/cm<<"\t" // Z
	       <<Allpos.y()/cm<<"\t" //x
	       <<Allpos.z()/cm<<G4endl; //y 
  }

  if ((index == 2)){
    std::ofstream theFile666("flourine.dat", std::ios::app);
    theFile666 <<evtNb<<"\t"
	       <<volumeName<<"\t"
	       <<parentID<<"\t"
	       <<trackID<<"\t"
	       <<AlltotalE/keV<<"\t"
  	       <<Allpos.x()/cm<<"\t" // Z
	       <<Allpos.y()/cm<<"\t" //x
	       <<Allpos.z()/cm<<G4endl; //y 

  }
 
  if ((index == 3)){
    std::ofstream theFile777("Alpha.dat", std::ios::app);
    theFile777 <<evtNb<<"\t"
	       <<volumeName<<"\t"
	       <<parentID<<"\t"
	       <<trackID<<"\t"
	       <<AlltotalE/keV<<"\t"
	       <<Allpos.x()/cm<<"\t" // Z
	       <<Allpos.y()/cm<<"\t" //x
	       <<Allpos.z()/cm<<G4endl; //y 
     
  }

       }}}
   
}

