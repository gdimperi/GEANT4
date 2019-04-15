#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

# include "G4ParticleGun.hh"


// for muon sim
//#define USE_PG

#ifdef USE_PG 
class G4ParticleGun;
#else 
class G4GeneralParticleSource;
#endif

class G4Event;
class DetectorConstruction;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(DetectorConstruction*);    
   ~PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);
    void SetRndmFlag(G4String val) { rndmFlag = val;}

  // USE ONLY IF YOU WANT THE PARTICLE GUN (MUON SIM)
  // #define USE_PG

  private:

#ifdef USE_PG
    G4ParticleGun*  particleGun;
#else
    G4GeneralParticleSource*  particleSource;	  //pointer a to G4  class
#endif

    DetectorConstruction*    Detector;  //pointer to the geometry
    G4String                 rndmFlag;	  //flag for a rndm impact point
};

#endif
