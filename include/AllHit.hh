#ifndef AllHit_h
#define AllHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"


#include <G4VProcess.hh>

class AllHit : public G4VHit 
{
  public:

      AllHit();
 
      AllHit(const AllHit&);
      const AllHit& operator=(const AllHit&);
      int operator==(const AllHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

  void Print();

   public:
     inline void SetAllPos(G4ThreeVector Allxyz)       {pos=Allxyz;};
     inline G4ThreeVector GetAllPos()               const {return pos;};

     inline void SetAllMomentum(G4ThreeVector Allmom)       {mom=Allmom;};
     inline G4ThreeVector GetAllmom()               const {return mom;};

     inline void SetAllMomentumDir(G4ThreeVector AllmomDir)       {momDir=AllmomDir;};
     inline G4ThreeVector GetAllmomDir()               const {return momDir;};

     inline void SetAllTime(G4double Allt)             {time=Allt;};
     inline G4double GetAllTime()                   const {return time;};

     inline void SetAllsTime(G4double sAllt)             {stime=sAllt;};
     inline G4double GetAllsTime()                   const {return stime;};

     inline void SetTrackID(G4double TrackID)             {trackid=TrackID;};
     inline G4double GetTrackID()                   const {return trackid;};

     inline void SetParentID(G4double ParentID)             {parentid=ParentID;};
     inline G4double GetParentID()                   const {return parentid;};

     inline void SetAllAll(G4int Allp)             {Allves=Allp;};
     inline G4int GetAllAll()                   const {return Allves;};

     inline void SetAllParticle(G4String Allpart) {Allparticle=Allpart;};
     inline G4String GetAllParticle()                const {return Allparticle;};

     inline void SetVolName(G4String VolName) {volName=VolName;};
     inline G4String GetVolName()                const {return volName;};

     inline void SetAllEnergy(G4double Allener) {Allenergy=Allener;};
     inline G4double GetAllEnergy()                  const {return Allenergy;};

     inline void SetMass(G4double Mass) {mass=Mass;};
     inline G4double GetMass()                  const {return mass;};

     inline void SetAllTrackLength(G4double Alltrackl) {AllTrackLength=Alltrackl;};
     inline G4double GetAllTrackLength()                   const {return AllTrackLength;};

     inline void SetAllEdepV(G4double AllenerV) {AllenergyV=AllenerV;};
     inline G4double GetAllEdepV()                   const {return AllenergyV;};

     inline void SetAllParticleType(G4String AllpartType) {AllparticleType=AllpartType;};
     inline G4String GetAllParticleType()                const {return AllparticleType;};

     inline void SetCurrentStepNumber(G4double step) {Step=step;};
     inline G4double GetCurrentStepNumber()                  const {return Step;};

     inline void SetVertexPosition(G4ThreeVector vertex) {Vertex=vertex;};
     inline G4ThreeVector GetVertexPosition()                  const {return Vertex;};

     inline void SetVertexMomentumDirection(G4ThreeVector vertexmom) {Vertexmom=vertexmom;};
     inline G4ThreeVector GetVertexMomentumDirection()                  const {return Vertexmom;};

     inline void SetVelocity(G4double Velocity)       {velocity=Velocity;};
     inline G4double GetVelocity()               const {return velocity;};

     inline void SetVertexKineticEnergy(G4double vertexke) {Vertexke=vertexke;};
     inline G4double GetVertexKineticEnergy()                  const {return Vertexke;};
    
      void SetRecoil                  (void)     { rec = true;};
      void SetInelasticRecoil         (void)     { InelasticRec = true;};

      G4bool GetRecoil()                         { return rec; };
      G4bool GetInelasticRecoil()                { return InelasticRec; };

 private:
  G4ThreeVector pos;
  G4double time;
  G4double stime;
  G4int Allves;
  G4String Allparticle;
  G4double Allenergy;
  G4String AllparticleType;
  G4double AllenergyV;
  G4double AllTrackLength; 
  G4ThreeVector mom;
  G4ThreeVector momDir;
  G4String volName;  
  G4double trackid;
  G4double parentid;
  G4double Step;
  G4ThreeVector Vertex;
  G4ThreeVector Vertexmom;
  G4double velocity;
  G4double Vertexke;
  G4double mass;
  G4String creatorProces;
  G4bool rec;
  G4bool InelasticRec;
  G4String parentname;

};

// vector collection of one type of hits
typedef G4THitsCollection<AllHit> AllHitsCollection;

// crystals

typedef G4THitsCollection<AllHit> AllHitsCollectionC1;
typedef G4THitsCollection<AllHit> AllHitsCollectionC2;
typedef G4THitsCollection<AllHit> AllHitsCollectionC3;
typedef G4THitsCollection<AllHit> AllHitsCollectionC4;
typedef G4THitsCollection<AllHit> AllHitsCollectionC5;
typedef G4THitsCollection<AllHit> AllHitsCollectionC6;
typedef G4THitsCollection<AllHit> AllHitsCollectionC7;
typedef G4THitsCollection<AllHit> AllHitsCollectionC8;


extern G4Allocator<AllHit> AllHitsAllocator;

inline void* AllHit::operator new(size_t) {
  void* aAllHit;
  aAllHit = (void*) AllHitsAllocator.MallocSingle();
  return aAllHit;
}

inline void AllHit::operator delete(void* aAllHit) {
  AllHitsAllocator.FreeSingle((AllHit*) aAllHit);
}

#endif
