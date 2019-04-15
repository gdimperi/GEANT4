#ifndef AllSD_h
#define AllSD_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"
#include "AllHit.hh"

class DetectorConstruction;
class G4Step;
class G4HCofThisEvent;

class AllSD : public G4VSensitiveDetector {

   public:
  
     AllSD(G4String, DetectorConstruction*);
     ~AllSD();
  
     void Initialize(G4HCofThisEvent*);
     G4bool ProcessHits(G4Step*,G4TouchableHistory*);
     void EndOfEvent(G4HCofThisEvent*);
     void clear();
     void DrawAll();
     void PrintAll();

  
  private:
  
     AllHitsCollection* AllCollection;
     DetectorConstruction* Detector;
     G4int HitID;
};

#endif
