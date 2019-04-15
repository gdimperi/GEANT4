# GEANT4
GEANT4 model of CYGNO vessel

The GEANT4 version is 9.6-p03
The Physics list used is Shielding
The Makefile directories should be changed as required before compilation

The mac vis.mac can be run to view the detector geometery
The other macs are used to model gamma emission from the isotope activities within the camera and from a GEM

When the code is run the user is asked to enter the fraction of CF4 and He gas, please enter as decimal (e.g. 0.3 and 0.7). If other gas mixtures are required such as a mixture containing SF6 then this should be entered directly into the CYGNO_gas Material listed in the src code DetectorConstruction.cc. 

The energy deposited within the gas volume during a run is recorded in the output file edep.dat. Nuclear recoils are also output as: "fluorine.dat", "carbon.dat", "Alpha.dat" or "sulfur.dat" if SF6 is used. The format of these data files is listed in the src code EventAction.cc.

The src code SteppingAction.cc is setup at the moment to return additional information on gas recoils using the output file Recoils.dat. This can be commented out or edited to return recoil information as required. 

The GEANT4 code is based on the code used for DRIFT although significant changes have been made.

Any questions or comments please email me at warren.lynch@sheffield.ac.uk

