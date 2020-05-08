#include <cfloat>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "populationsimulation.h"

PopulationSimulation::PopulationSimulation() : reaction_list(), typemolecule_list() {
  diameter = 0;
  length_molecule_list = 0;
}

/* PRIVATE METHODS */

int PopulationSimulation::findTypeID(char* name) const {
  if(NULL != name) {
    for(Typemolecule_struct* t : typemolecule_list) {
      if(!strcmp(t->name, name)) return t->id;
    }
  }
  return -1;
}

void PopulationSimulation::print(void) const {
  for(int i = 0; i < length_molecule_list; i++) {
    std::cout << "-- " << molecule_list[i] << " molecules of type " << typemolecule_list.at(i)->name << std::endl;
  }
}

void PopulationSimulation::printReactions(void) const {
  for(Reaction_struct* r : reaction_list) {
    char* r1 = typemolecule_list.at(r->r1)->name;
    char* r2 = typemolecule_list.at(r->r2)->name;
    char* p1 = typemolecule_list.at(r->p1)->name;
    char* p2 = typemolecule_list.at(r->p2)->name;
    std::cout << p1 << " + " << p2 << " -> " << r1 << " + " << r2 << std::endl;
  }
}

/* PUBLIC METHODS */

void PopulationSimulation::setDiameter(int d) {
  diameter = d;
}

void PopulationSimulation::addReaction(char* r1, char* r2, char* p1, char* p2, float p) {
  int id_r1 = findTypeID(r1);
  int id_r2 = findTypeID(r2);
  int id_p1 = findTypeID(p1);
  int id_p2 = findTypeID(p2);
  Reaction_struct* r = new Reaction_struct();
  r->id = reaction_list.size();
  r->r1 = id_r1;
  r->r2 = id_r2;
  r->p1 = id_p1;
  r->p2 = id_p2;
  r->p = p;
}

void PopulationSimulation::addMolecule(char* name, int amount) {
  /* If molecule_list is empty, give it the same size as typemolecule_list */
  if(0 == length_molecule_list) {
    length_molecule_list = typemolecule_list.size();
    molecule_list = new int[length_molecule_list];
  }

  /* Add a certain amount of this molecule type */
  int typeID = findTypeID(name);
  if(typeID != -1) {
    molecule_list[typeID] = amount;
  } else {
    std::cout << "ERROR: Adding molecule of undefined molecule type " << name << std::endl;
    exit(0);
  }
}

void PopulationSimulation::addTypeMolecule(char* name) {
  Typemolecule_struct* t = new Typemolecule_struct();
  t->id = typemolecule_list.size();
  t->name = name;
  t->speed = 0;
  t->size = 0;
  typemolecule_list.push_back(t);
}

void PopulationSimulation::setTypeMoleculeSpeed(char* name, float s) {
  int id_type = findTypeID(name);
  typemolecule_list.at(id_type)->speed = s;
}

void PopulationSimulation::setTypeMoleculeSize(char* name, int s) {
  int id_type = findTypeID(name);
  typemolecule_list.at(id_type)->size = s;
}

void PopulationSimulation::run(int t_max) {
  std::srand(std::time(nullptr));
  std::cout << "Reactions in simulation:" << std::endl;
  printReactions();
  /* Each iteration is tau = 100µs */
  double alpha = 7.4e-7;
  double volume = 1./6 * M_PI * pow(diameter, 3);
  for(int t = 0; t < t_max; t++) {
    std::cout << "ITERATION " << t << std::endl;
    /* Shuffle reaction_list */
    std::random_shuffle(reaction_list.begin(), reaction_list.end());
    printReactions();
    for(Reaction_struct* r : reaction_list) {
      int r1 = r->r1;
      int r2 = r->r2;
      int p1 = r->p1;
      int p2 = r->p2;
      float p = r->p;
      /* If no reactives or products warn user an continue */
      if(r1 == -1) r1 = r2;
      if(r1 == -1) {
	std::cout << "Error in reaction, no reactives" << std::endl;
	break;
      }
      if(p1 == -1) p1 = p2;
      if(p1 == -1) {
	std::cout << "Error in reaction, no products" << std::endl;
	break;
      }
      /* If no error simulate! */
      if(r2 != -1) {
	/* Calculate propensity */
	double prop = (alpha * (molecule_list[r1] + molecule_list[r2]) * p) / volume;
	if(r1 == r2) prop /= 2;
	int e = prop;
	double f = prop-e;
	double r = (double)std::rand() / (float)RAND_MAX;
	int num_appl = e + (r<f)?1:0;
	/* Do reactions */
	molecule_list[r1] -= num_appl;
	molecule_list[r2] -= num_appl;
	molecule_list[p1] += num_appl;
	if(p2 != -1) molecule_list[p2] += num_appl;
      } else {
	/* Calculate propensity */
	double prop = molecule_list[r1] * p;
	int e = prop;
	double f = prop-e;
	double r = (double)std::rand() / (float)RAND_MAX;
	int num_appl = e + (r<f)?1:0;
        /* Do reactions */
	molecule_list[r1] -= num_appl;
	molecule_list[p1] += num_appl;
	if(p2 != -1) molecule_list[p2] += num_appl;	
      }
    }
    std::cout << std::endl << std::endl;
  }
}
