#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include "abstractsimulation.h"
#include "molecule.h"
#include "typemolecule.h"
#include "reaction.h"

class Simulation : public AbstractSimulation {
 private:
  int diameter;
  std::vector<TypeMolecule> typemolecule_list;
  std::vector<Reaction> reaction_list;
  std::vector<Molecule> molecule_list;
  /* Find id */
  int findTypeID(char*);
  /* Check that a point is within boundaries */
  bool checkBounds(float, float, float, int) const;
  /* Try to react one molecule */
  bool reactOne(int);
  /* Try to react two molecules */
  bool reactTwo(int, int);
  /* Calculates the molecule in trajectory if any, parameter position in list, return position in list or -1 if none */
  int computeTrajectory(int) const;
 public:
  Simulation();
  /* Set simulation diameter (used by parser) */
  void setDiameter(int);
  /* Add reaction/molecule/type of molecule to simulation (used by parser) */
  void addReaction(char*, char*, char*, char*, float);
  void addMolecule(char*, int);
  void addTypeMolecule(char*);
  /* Set molecule type parameters (used by parser) */
  void setTypeMoleculeSpeed(char*, float);
  void setTypeMoleculeSize(char*, int);
  /* Run the simulation for t ticks, default 1 tick */
  void run(int t = 1) override;
};

#endif
