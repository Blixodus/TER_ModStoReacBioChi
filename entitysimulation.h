#ifndef ENTITYSIMULATION_H
#define ENTITYSIMULATION_H
#include "molecule.h"
#include "typemolecule.h"
#include "reaction.h"
#include "vec3.h"
#include <vector>
/**
 * @file entitysimulation.cpp 
 * @brief Lance la simulation suivant le modèle entité-centré
 */
class EntitySimulation {
 private:
  int diameter;
  std::vector<TypeMolecule*> typemolecule_list;
  std::vector<Reaction*> reaction_list;
  std::vector<Molecule*> molecule_list;
  /* Find id */
  int findTypeID(char*) const;
  /* Check that a point is within boundaries */
  bool checkBounds(Vec3*, int) const;
  /* Try to react one molecule */
  bool reactOne(int);
  /* Try to react two molecules */
  bool reactTwo(int, int, bool&);
  /* Calculates the molecule in trajectory if any, parameter position in list, return position in list or -1 if none */
  int computeTrajectory(int) ; //retirer le const -> retire bug sinon pas compatible avec la fonction
  /* Print simulation state */
  void print(int) const;
  /* Print reactions in simulation */
  void printReactions(void) const;
 public:
  EntitySimulation();
  /* Set simulation diameter (used by parser) */
  void setDiameter(int);
  /* Add reaction/molecule/type of molecule to simulation (used by parser) */
  void addReaction(char*, char*, char*, char*, float);
  void addMolecule(char*, int);
  void addTypeMolecule(char*);
  /* Set molecule type parameters (used by parser) */
  void setTypeMoleculeSpeed(char*, float);
  void setTypeMoleculeSize(char*, int);
  /* Run the simulation for t ticks */
  void run(int);
};

#endif
