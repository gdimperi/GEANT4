#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"

class PhysicsList;

class PhysicsListMessenger: public G4UImessenger {

  public:
    PhysicsListMessenger(PhysicsList*);
   ~PhysicsListMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    PhysicsList* physList;

    G4UIdirectory*             physDir;
    G4UIcmdWithAnInteger*      verboseCmd;
    G4UIcmdWithoutParameter*   setHadCmd;

};

#endif
