#include "SwarmWorld.h"

std::shared_ptr<ParameterLink<int>> SwarmWorld::world_size_pl = Parameters::register_parameter("WORLD_SWARM-world_size", 100, "Length and height of the world in grid spaces.");
std::shared_ptr<ParameterLink<int>> SwarmWorld::repeats_pl = Parameters::register_parameter("WORLD_SWARM-repeats", 5, "Number of times each genotype is tested.");


SwarmWorld::SwarmWorld(std::shared_ptr<ParametersTable> _PT) : //Initializer
  AbstractWorld(_PT) {
    //Grab the values from the parameter list.
    world_size = (PT == nullptr) ? world_size_pl->lookup() : PT->lookupInt("WORLD_SWARM-world_size");
    repeats = (PT == nullptr) ? repeats_pl->lookup() : PT->lookupInt("WORLD_SWARM-repeats");
    //Set up data columns.
    aveFileColumns.clear();
  }

  void SwarmWorld::evaluateSolo(std::shared_ptr<Organism> org, int analyse, int visualize, int debug) {
      //Evaluate. Starts with a replicate loop.
      for(int z = 0; z < repeats; z++){
        std::cout << "Test complete." << std::endl;
      }
  }


  //Proximity sensors (U,D,L,R,UL,UR,DL,DR,Center) and flags (is_food, is_pred, is_hive, is_clone, carrying_food)
  int SwarmWorld::requiredInputs() {
    return 14;
  }

  // Move U,D,L, and R.
  int SwarmWorld::requiredOutputs() {
    return 4;
  }
