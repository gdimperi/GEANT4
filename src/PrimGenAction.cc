#include "PrimGenAction.hh"
#include "DetectorConstruction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"  

#include "time.h"  


PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* DC):Detector(DC)
{

#ifdef USE_PG   //TO USE PARTICLEGUN, #deine USE_PG in some header file

  
  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* fProton = particleTable->FindParticle( (G4String)"proton" );
  G4ParticleDefinition* fNeutron = particleTable->FindParticle( (G4String)"neutron" );

  G4String particleName;
  G4ParticleDefinition* Pelectron  = particleTable->FindParticle(particleName="e-");
  G4ParticleDefinition* Pmu  = particleTable->FindParticle(particleName="mu-");
  G4ParticleDefinition* Pantimu  = particleTable->FindParticle(particleName="mu+");


#else
   particleSource  = new G4GeneralParticleSource();
#endif
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
#ifdef USE_PG
  delete particleGun;
#else
   delete particleSource;
#endif
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{





#ifdef USE_PG


  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* Pmu  = particleTable->FindParticle(particleName="mu-");
  G4ParticleDefinition* Pantimu  = particleTable->FindParticle(particleName="mu+");

  std::ifstream input("muons-boulby-test.dat");
  G4int EventNumber = anEvent->GetEventID();
  G4int Eventindex; // Evt #
  G4int Particleindex; // 10 mu+, 11 mu-
  G4double MuonEnergy, MuonX, MuonY, MuonZ, MuonPx, MuonPy, MuonPz;
 
  std::string s;
  for(int i=0; i< EventNumber; ++i)
    {
      input.ignore(256,'\n');
    }
  std::getline(input,s);
  input >> Eventindex >> Particleindex >> MuonEnergy >> MuonX >> MuonY >> MuonZ >> MuonPx >> MuonPy >> MuonPz;


  if(Particleindex = 10){
  particleGun->SetParticleDefinition(Pantimu);
  }
  if(Particleindex = 11)
    {
  particleGun->SetParticleDefinition(Pmu);
    }

  particleGun->SetParticleMomentumDirection(G4ThreeVector(MuonPx*1000,MuonPy*1000,MuonPz*1000)); // default geant4 unit is MeV/c , convert the GeV/c from MUSUN 
  // particleGun->SetParticleEnergy(MuonEnergy/GeV);
  // particleGun->SetParticlePosition(G4ThreeVector(MuonX/cm,MuonY/cm,MuonZ/cm));

  // Move to default CLHEP units
  particleGun->SetParticleEnergy(MuonEnergy*1000); // from GeV to Mev
  particleGun->SetParticlePosition(G4ThreeVector(MuonX*10,MuonY*10,MuonZ*10)); // from cm to mm

particleGun->GeneratePrimaryVertex(anEvent);

#else

  particleSource->GeneratePrimaryVertex(anEvent);
#endif
}
