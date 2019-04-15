#ifndef EventMessenger_h
#define EventMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class EventAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

class EventMessenger: public G4UImessenger
{
  public:
    EventMessenger(EventAction* );
   ~EventMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
  EventAction* EvAct;
   
    G4UIdirectory*             EADir;
    G4UIcmdWithAString*        SetFileCmd;
    G4UIcmdWithAnInteger*        SetThresholdCmd;
};

#endif
