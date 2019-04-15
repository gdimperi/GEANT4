#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class PhysicsListMessenger;

class PhysicsList: public G4VUserPhysicsList {

  public:
    PhysicsList();
    virtual ~PhysicsList();

  protected:
////Construct particles and physics
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    virtual void SetCuts();
  
////Construct physics processes and register them
    virtual void ConstructDecays();
    virtual void ConstructElectromagnetic();
  //  virtual void ConstructHadronic();  Defined later
//  virtual void ConstructOptical();
    virtual void AddTransportation();

  public:
//// neutron physics registered from UI
    void ConstructHadronic();

  public:
    void SetVerbosities(G4int);

  private:
    PhysicsListMessenger* physicsMessenger;    

    G4int VerboseLevel;

    G4double cutForGamma;
    G4double cutForElectron;
    G4double cutForPositron;

  // added test
  G4double cutForNeutron;

};

#endif
