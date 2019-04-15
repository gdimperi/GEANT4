#include "PhysicsList.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"


#include "G4BinaryLightIonReaction.hh"
#include "G4IonInelasticProcess.hh"

// Constructor /////////////////////////////////////////////////////////////
PhysicsList::PhysicsList() : G4VUserPhysicsList() {

  // range cuts
  //defaultCutValue     = 50.*micrometer;
  defaultCutValue     = 0; // is 100micrometer normally
  cutForGamma         = defaultCutValue;
  cutForElectron      = defaultCutValue;
  cutForPositron      = defaultCutValue;
 
  // verbosity
  VerboseLevel = 1;
  SetVerboseLevel(VerboseLevel);
  
}


// Destructor //////////////////////////////////////////////////////////////
PhysicsList::~PhysicsList() {

}

/////////////////////////////////////////////////////////////////////////////
// Construct Particles /////////////////////////////////////////////////////
void PhysicsList::ConstructParticle() {

  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // bosons
  G4Gamma::GammaDefinition();
  G4OpticalPhoton::OpticalPhotonDefinition();

  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();

  // baryons
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();

  //mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4Eta::EtaDefinition();
  G4EtaPrime::EtaPrimeDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();

  // ions
  G4Alpha::AlphaDefinition();
  G4Deuteron::DeuteronDefinition();
  G4Triton::TritonDefinition();
  G4He3::He3Definition();
  G4GenericIon::GenericIonDefinition();

}

/////////////////////////////////////////////////////////////////////////////
// Construct Processes //////////////////////////////////////////////////////
void PhysicsList::ConstructProcess() {

  G4cout << "\nConstructing physics processes..." << G4endl;

  AddTransportation();
  ConstructElectromagnetic();
  ConstructDecays();
  // ConstructOptical();
//// register neutron processes by UserInterface only!
  //ConstructHadronic();

}


/////////////////////////////////////////////////////////////////////////////
// Transportation ///////////////////////////////////////////////////////////
void PhysicsList::AddTransportation() {

  G4VUserPhysicsList::AddTransportation();

}

/////////////////////////////////////////////////////////////////////////////
// Electromagnetic Processes ////////////////////////////////////////////////
// all charged particles

//#include "G4MultipleScattering.hh"    // FM: file obsolete in 9.6, replaced by G4eMultipleScattering, G4hMultipleScattering or G4MuMultipleScattering depending on particle 
//call new source files (vef)

#include "G4eMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"

// gamma
//#include "G4LowEnergyRayleigh.hh"  // FM: file obsolete, replaced with G4LivermoreRayleighModel.hh
#include "G4LivermoreRayleighModel.hh"

#include "G4RayleighScattering.hh" // FM added


//#include "G4LowEnergyPhotoElectric.hh" //FM: file obsolete, replaced with G4LivermorePhotoElectricModel.hh
#include "G4LivermorePhotoElectricModel.hh"

#include "G4PhotoElectricEffect.hh" // FM added for definition of lowePhot 

// #include "G4LowEnergyCompton.hh"  //FM: file obsolete, replaced with G4LivermoreComptonModel.hh
#include "G4LivermoreComptonModel.hh"

#include "G4ComptonScattering.hh" // FM added

// #include "G4LowEnergyGammaConversion.hh" //FM: file obsolete, replaced with G4LivermoreGammaConversionModel.hh
#include "G4LivermoreGammaConversionModel.hh"

#include "G4GammaConversion.hh" // FM added

// e-

//#include "G4LowEnergyIonisation.hh" //FM: file obsolete, replaced with G4LivermoreIonisationModel.hh
#include "G4LivermoreIonisationModel.hh"

#include "G4ionIonisation.hh"

// #include "G4LowEnergyBremsstrahlung.hh" // FM:file obsolete replace with G4LivermoreBremsstrahlungModel.hh

#include "G4LivermoreBremsstrahlungModel.hh"

// e+
#include "G4eIonisation.hh" 
#include "G4eBremsstrahlung.hh" 
#include "G4eplusAnnihilation.hh"

// muons
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCaptureAtRest.hh"

// hadrons
#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"

void PhysicsList::ConstructElectromagnetic() {

  // processes


  /*

FM: Definitions of Livermore process : see 

http://geant4.web.cern.ch/geant4/UserDocumentation/Doxygen/examples_doc/html_TestEm18/html/PhysListEmLivermore_8cc_source.html

   */

  /* FM:   OLD DEFINITION- TRY NEW BELOW ( in if loops)
 

  //G4LowEnergyPhotoElectric* lowePhot = new G4LowEnergyPhotoElectric("LEPhotoElectric");// FM: old function definition
  //G4LivermorePhotoElectricModel* lowePhot = new G4LivermorePhotoElectricModel("LivermorePhElectric"); // FM: function updated, compiler unhappy
    G4LivermorePhotoElectricModel* lowePhot = new G4LivermorePhotoElectricModel(1); // try with const - compiler seems happy
  //lowePhot->SetCutForLowEnSecPhotons(250*eV);  //FM: Only one cut available now, see : http://hypernews.slac.stanford.edu/HyperNews/geant4/get/emprocess/1023/2/1.html

    G4LivermoreIonisationModel* loweIon = new G4LivermoreIonisationModel("LowEnergyIoni");// FM: function updated
    // G4LivermoreIonisationModel* loweIon = new G4LivermoreIonisationModel();
    //G4LivermoreIonisationModel* loweIon = new G4LivermoreIonisationModel(1); // try with const
  //loweIon ->SetCutForLowEnSecPhotons(250*eV); // FM: same comment as above, only one cut available

  //G4LivermoreBremsstrahlungModel* loweBrem = new G4LivermoreBremsstrahlungModel("LowEnBrem"); // FM: function updated
    G4LivermoreBremsstrahlungModel* loweBrem = new G4LivermoreBremsstrahlungModel(1); // try with const
  //loweBrem->SetCutForLowEnSecPhotons(250*eV); //FM: same comment as above, only one cut available



  */

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName      = particle->GetParticleName();
    G4String particleType      = particle->GetParticleType();
    G4double particleCharge    = particle->GetPDGCharge();
    G4double highEnergyLimit  = 250*eV; // add FM:  energy above which livermore are not used anymore


    //FM: Rewritten with Livermore Processes

    if (particleName == "gamma") {
      // gamma

      // photoelectric effect

      G4PhotoElectricEffect* lowePhot = new G4PhotoElectricEffect(); // FM new
      G4LivermorePhotoElectricModel* lowePhotModel= new G4LivermorePhotoElectricModel(); // FM new
      lowePhotModel->SetHighEnergyLimit(highEnergyLimit);
      lowePhot->AddEmModel(0,lowePhotModel);
      pmanager->AddDiscreteProcess(lowePhot);

      // rayleigh scattering

      G4RayleighScattering * loweRayl = new G4RayleighScattering();
      G4LivermoreRayleighModel * loweRaylModel = new G4LivermoreRayleighModel();
      loweRaylModel->SetHighEnergyLimit(highEnergyLimit);
      loweRayl->AddEmModel(0,loweRaylModel); 
      pmanager->AddDiscreteProcess(loweRayl);

      // Compton Scattering
     
      G4ComptonScattering * loweCompton = new G4ComptonScattering();
      G4LivermoreComptonModel * loweComptonModel = new G4LivermoreComptonModel();
      loweComptonModel->SetHighEnergyLimit(highEnergyLimit);
      loweCompton->AddEmModel(0,loweComptonModel);
      pmanager->AddDiscreteProcess(loweCompton);

      // Gamma conversion

      G4GammaConversion * loweConv = new G4GammaConversion();
      G4LivermoreGammaConversionModel * loweConvModel = new G4LivermoreGammaConversionModel();
      loweConvModel->SetHighEnergyLimit(highEnergyLimit);
      loweConv->AddEmModel(0,loweConvModel);
      pmanager->AddDiscreteProcess(loweConv);

    } else if (particleName == "e-") {
      // electron
      // G4MultipleScattering* aMultipleScattering = new G4MultipleScattering("MultipleScattering"); // FM: MultipleScattering is obsolete, 1 source file per particle
      G4eMultipleScattering* aMultipleScattering = new G4eMultipleScattering("MultipleScattering");
      G4eIonisation * loweIon = new G4eIonisation();
      G4LivermoreIonisationModel * loweIonModel = new G4LivermoreIonisationModel();
      G4eBremsstrahlung* loweBrem = new G4eBremsstrahlung();
      G4LivermoreBremsstrahlungModel * loweBremModel = new G4LivermoreBremsstrahlungModel();

      loweIonModel->SetHighEnergyLimit(highEnergyLimit);
      loweIon->AddEmModel(0,loweIonModel,0);
      loweBremModel->SetHighEnergyLimit(highEnergyLimit);
      loweBrem->AddEmModel(0,loweBremModel);

      pmanager->AddProcess(aMultipleScattering,     -1, 1, 1);
      pmanager->AddProcess(loweIon,                 -1, 2, 2);
      pmanager->AddProcess(loweBrem,                -1,-1, 3);
      
    } else if (particleName == "e+") {
      // positron
      //G4MultipleScattering* aMultipleScattering = new G4MultipleScattering("MultipleScattering"); // FM: MultipleScattering is obsolete: 1 file per lepton
      G4eMultipleScattering* aMultipleScattering = new G4eMultipleScattering("MultipleScattering");
      pmanager->AddProcess(aMultipleScattering,     -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation
			   ("eplusIonisation"),     -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung
			   ("eplusBremsstrahlung"), -1,-1, 3);
      pmanager->AddProcess(new G4eplusAnnihilation
			   ("eplusAnnihilation"),    0,-1, 4);

    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      // muon
      // G4MultipleScattering* aMultipleScattering = new G4MultipleScattering("MultipleScattering"); // FM: MultipleScattering is obsolete: 1 file per lepton
      G4MuMultipleScattering* aMultipleScattering = new G4MuMultipleScattering("MultipleScattering");
      pmanager->AddProcess(aMultipleScattering,     -1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation
			   ("MuIonisation"),        -1, 2, 2);
      pmanager->AddProcess(new G4MuBremsstrahlung
			   ("MuBremsstrahlung"),    -1,-1, 3);
      pmanager->AddProcess(new G4MuPairProduction
			   ("MuPairProduction"),    -1,-1, 4);
      if( particleName == "mu-" )
	pmanager->AddProcess(new G4MuonMinusCaptureAtRest
			   ("MuCaptureAtRest"),      0,-1,-1);

    } 
    
      else if (particleName == "GenericIon") {
      // ions
	G4hMultipleScattering * aMultipleScattering = new G4hMultipleScattering("MultipleScattering");
    
      pmanager->AddProcess(aMultipleScattering,  -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation
			   ("IonIonisation"),       -1, 2, 2);
      
    } else if (!particle->IsShortLived() &&
	       particleCharge != 0. && 
	       particleName   != "chargedgeantino") {

	G4hMultipleScattering * aMultipleScattering = new G4hMultipleScattering("MultipleScattering");
      // all other stable charged particles
      pmanager->AddProcess(aMultipleScattering,  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation
			   ("HadronIonisation"),    -1, 2, 2); 
    }


    //FM: G4MultipleScattering.hh is obsolete, this part needs a new definition
  }
}

/////////////////////////////////////////////////////////////////////////////
// Optical Processes ////////////////////////////////////////////////////////

#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"



/////////////////////////////////////////////////////////////////////////////
// Neutron Hadronic Processes //////////////////////////////////////////////
// call from UI only

// G4NeutronHP models using evaluated data libraries.
// http://geant4.web.cern.ch/geant4/G4UsersDocuments/UsersGuides
// /PhysicsReferenceManual/html/node75.html

// processes
#include "G4HadronElasticProcess.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4NeutronInelasticProcess.hh"


// neutron HP models (E<19 MeV)
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPCapture.hh"
#include "G4NeutronHPCaptureData.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPInelasticData.hh"



/*
// Muon Sim

#include "G4LElastic.hh"
#include "G4HadronInelasticDataSet.hh"
#include "G4LCapture.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4BinaryCascade.hh"

*/

//_________

void PhysicsList::ConstructHadronic() {

  G4cout << "PhysicsList::ConstructHadronic"
	 << " -- Constructing neutron processes" << G4endl;

  G4ProcessManager* pManager = G4Neutron::Neutron()->GetProcessManager();
  

  // replace by G4LElastic for the muon simulation

  
  // elastic scattering
  G4cout << "PhysicsList::ConstructHadronic"
	 << " -- G4NeutronHPElastic" << G4endl;
    G4HadronElasticProcess* theNeutronElasticProcess = 
    new G4HadronElasticProcess("neutronElastic");
  G4NeutronHPElastic* theNeutronElasticModel = new G4NeutronHPElastic;
  theNeutronElasticProcess->RegisterMe(theNeutronElasticModel);
  G4NeutronHPElasticData* theNeutronData1 = new G4NeutronHPElasticData;
  theNeutronElasticProcess->AddDataSet(theNeutronData1);
  pManager->AddDiscreteProcess(theNeutronElasticProcess);
  

  // inelastic scattering
  G4cout << "PhysicsList::ConstructHadronic"
	 << " -- G4NeutronHPInelastic" << G4endl;
  G4NeutronInelasticProcess* theNeutronInelasticProcess =
    new G4NeutronInelasticProcess("neutronInelastic");
  G4NeutronHPInelastic* theNeutronInelasticModel = new G4NeutronHPInelastic;
  theNeutronInelasticProcess->RegisterMe(theNeutronInelasticModel);
  G4NeutronHPInelasticData* theNeutronData2 = new G4NeutronHPInelasticData;
  theNeutronInelasticProcess->AddDataSet(theNeutronData2);
  pManager->AddDiscreteProcess(theNeutronInelasticProcess);

  // capture
  G4cout << "PhysicsList::ConstructHadronic"
	 << " -- G4NeutronHPCapture" << G4endl;
  G4HadronCaptureProcess* theNeutronCaptureProcess =
    new G4HadronCaptureProcess("neutronCapture");
  G4NeutronHPCapture* theNeutronCaptureModel = new G4NeutronHPCapture;
  theNeutronCaptureProcess->RegisterMe(theNeutronCaptureModel);
  G4NeutronHPCaptureData* theNeutronData3 = new G4NeutronHPCaptureData;
  theNeutronCaptureProcess->AddDataSet(theNeutronData3);
  pManager->AddDiscreteProcess(theNeutronCaptureProcess);

  

  /*
  // muon sim
G4LElastic* elasticModel = new G4LElastic();
G4HadronElasticProcess* hadElastProc = new G4HadronElasticProcess();
hadElastProc->RegisterMe(elasticModel);
pManager->AddDiscreteProcess(hadElastProc);


G4BinaryCascade* bcModel = new G4BinaryCascade();
G4NeutronInelasticProcess* ninelProc = new G4NeutronInelasticProcess();
 ninelProc->RegisterMe(bcModel);
//  G4NeutronInelasticProcess* theNeutronData2 = new G4NeutronHPInelasticData();
// ninelProc->AddDataSet(theNeutronData2);
pManager->AddDiscreteProcess(ninelProc);

G4LCapture* captureModel = new G4LCapture();
G4HadronCaptureProcess* capProcess = new G4HadronCaptureProcess();
capProcess->RegisterMe(captureModel);
pManager->AddDiscreteProcess(capProcess);

  //________________________________

  */


}

/////////////////////////////////////////////////////////////////////////////
// Decays ///////////////////////////////////////////////////////////////////
#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"
#include "G4IonTable.hh"
#include "G4Ions.hh"

void PhysicsList::ConstructDecays() {

  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (theDecayProcess->IsApplicable(*particle)) { 
      pmanager ->AddProcess(theDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }

  // Declare Radioactive Decay to the GenericIon in the IonTable.
  const G4IonTable *theIonTable = 
    G4ParticleTable::GetParticleTable()->GetIonTable();
  
  G4RadioactiveDecay *theRadioactiveDecay = 
    new G4RadioactiveDecay("RadioactiveDecay");
  
  for (G4int i=0; i<theIonTable->Entries(); i++) {
    G4String particleName = theIonTable->GetParticle(i)->GetParticleName();
    if (particleName == "GenericIon") {
      G4ProcessManager* pmanager = 
	theIonTable->GetParticle(i)->GetProcessManager();
      pmanager->SetVerboseLevel(VerboseLevel);
      pmanager ->AddProcess(theRadioactiveDecay);
      pmanager ->SetProcessOrdering(theRadioactiveDecay, idxPostStep);
      pmanager ->SetProcessOrdering(theRadioactiveDecay, idxAtRest);
    } 
  }
}


/////////////////////////////////////////////////////////////////////////////
// Cuts /////////////////////////////////////////////////////////////////////
void PhysicsList::SetCuts() {

  if (verboseLevel>0){
    G4cout << "PhysicsList::SetCuts - DefaultCutLength : " 
	   << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }

  // set cuts
  G4double lowlimit= 0.5*eV;  // originally 1kev

  G4ProductionCutsTable::GetProductionCutsTable()
    ->SetEnergyRange(lowlimit, 100.*GeV);

  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");

  if (verboseLevel>0) DumpCutValuesTable();
}

void PhysicsList::SetVerbosities(G4int val) { 

  SetVerboseLevel(val);

}
