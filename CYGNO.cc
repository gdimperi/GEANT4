#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "Randomize.hh"
#include "time.h"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "DetectorConstruction.hh"
#include "PrimGenAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "PhysicsList.hh"

#include "Shielding.hh"
#include "G4StepLimiterBuilder.hh"

#include "G4ScoringManager.hh"

int main(int argc,char** argv)
{

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

 
  //Added Random Generator
  CLHEP::RanluxEngine defaultEngine( 1234567, 4 ); 
  G4Random::setTheEngine( &defaultEngine ); 
  G4int seed = time( NULL );
  
  // From matt to solve duplicate runs issue
   if(getenv("SEED"))
     {
    seed=atoi(getenv("SEED"));
     }
 
  G4Random::setTheSeed( seed ); 
  
  // set mandatory initialization classes
  DetectorConstruction* Det = new DetectorConstruction();
  runManager->SetUserInitialization(Det);
 
 // shielding physics list
  runManager->SetUserInitialization(new Shielding);

  // set User Action class
  runManager->SetUserAction(new PrimaryGeneratorAction(Det));
  runManager->SetUserAction(new RunAction());
  runManager->SetUserAction(new EventAction());
  runManager->SetUserAction(new SteppingAction());
  runManager->SetVerboseLevel(5);

#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  runManager->Initialize();
    
  // get the pointer to the User Interface manager 
  G4UImanager* UI = G4UImanager::GetUIpointer();  
  G4String command = "/control/execute ";
  G4String fileName = argv[1];
  UI->ApplyCommand(command+fileName);

  /*    
  G4UIsession * session = 0;
  session = new G4UIterminal();
  session->SessionStart();
  delete session;
  */
  //  job termination
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
 

}


