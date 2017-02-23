#include "SwarmWorld.h"
#include "../../Organism/Organism.h"

std::shared_ptr<ParameterLink<int>> SwarmWorld::world_size_pl = Parameters::register_parameter("WORLD_SWARM-world_size", 100, "Length and height of the world in grid spaces.");
std::shared_ptr<ParameterLink<int>> SwarmWorld::repeats_pl = Parameters::register_parameter("WORLD_SWARM-repeats", 5, "Number of times each genotype is tested.");
std::shared_ptr<ParameterLink<int>> SwarmWorld::updates_pl = Parameters::register_parameter("WORLD_SWARM-updates", 1000, "Number of updates each genotype is tested for.");
std::shared_ptr<ParameterLink<int>> SwarmWorld::clones_pl = Parameters::register_parameter("WORLD_SWARM-clones", 50, "Number of clones placed into the world.");
std::shared_ptr<ParameterLink<int>> SwarmWorld::amount_food_pl = Parameters::register_parameter("WORLD_SWARM-amount_food", 30, "Number of food squares in the world.");
std::shared_ptr<ParameterLink<int>> SwarmWorld::min_distance_pl = Parameters::register_parameter("WORLD_SWARM-min_distance", 3, "Food can only spawn at least this far from the hive.");


inline int manhattan_dist(int x_i, int y_i, int x_f, int y_f){
  return(abs(x_f-x_i) + abs(y_f-y_i));
}

SwarmWorld::SwarmWorld(std::shared_ptr<ParametersTable> _PT) : //Initializer
  AbstractWorld(_PT) {
    //Grab the values from the parameter list.
    world_size = (PT == nullptr) ? world_size_pl->lookup() : PT->lookupInt("WORLD_SWARM-world_size");
    repeats = (PT == nullptr) ? repeats_pl->lookup() : PT->lookupInt("WORLD_SWARM-repeats");
    updates = (PT == nullptr) ? updates_pl->lookup() : PT->lookupInt("WORLD_SWARM-updates");
    clones = (PT == nullptr) ? clones_pl->lookup() : PT->lookupInt("WORLD_SWARM-clones");
    amount_food = (PT == nullptr) ? amount_food_pl->lookup() : PT->lookupInt("WORLD_SWARM-amount_food");
    min_distance = (PT == nullptr) ? min_distance_pl->lookup() : PT->lookupInt("WORLD_SWARM-min_distance");
    //Set up data columns.
    aveFileColumns.clear();
  }

  void SwarmWorld::evaluateSolo(std::shared_ptr<Organism> org, int analyse, int visualize, int debug) {
      //Evaluate. Starts with a replicate loop.
      for(int z = 0; z < repeats; ++z){
        //Make the clones
        std::vector<std::shared_ptr<Organism>> swarm_orgs;
        for(int n = 0; n < clones; ++n){
          swarm_orgs.push_back(Organism::makeCopy(nullptr));
        }

        //Make the world
        std::vector<std::vector<int>> world;
        std::vector<int> line;
        for(int n = 0; n < world_size; ++n){
          line = {};
          for(int j = 0; j < world_size; ++j){
            line.push_back(0);
          }
          world.push_back(line);
        }

        //Spawn food in the world. Check to make sure it's possible to spawn that much.
        //https://en.wikipedia.org/wiki/Von_Neumann_neighborhood
        int max_food = (pow(world_size,2)-(1+2*(min_distance-1)*(1+min_distance-1)));
        if (amount_food > max_food){
          std::cout << "Amount_food is too large for the number of available spaces. ";
          std::cout << "You must reduce amount_food, increase world_size, or decrease min_distance.";
          std::cout << "The maximum amount of food is 1+2*(min_distance-1)*(1+(min_distance-1)). ";
          std::cout << "See: https://en.wikipedia.org/wiki/Von_Neumann_neighborhood.";
          std::cout << " The maximum amount of food given this world_size and min_distance is: ";
          std::cout << max_food << ". \nExiting." << std::endl;
           exit(1);
        }
        for(int n = 0; n < amount_food; ++n){
          int food_point_x = rand()%world_size;
          int food_point_y = rand()%world_size;
          //If the user puts in a  minimum distance and we're closer than it, redo it.
          while((manhattan_dist(food_point_x, food_point_y, world_size/2, world_size/2) < min_distance) || (world[food_point_x][food_point_y] == 2)){
            food_point_x = rand()%world_size;
            food_point_y = rand()%world_size;
          }
          world[food_point_x][food_point_y] = 2;
        }


        //Spawn them all at world_size//2
        std::vector<packet> swarm;
        for(auto m : swarm_orgs){
          swarm.push_back({m, world_size/2, world_size/2, 0});
        }

        //Idea: instead of predators, you need mostly nonmotile cells to stick around
        // and build nests. Colony fitness will depend on both nests built and food collected.
        // Maybe look at preventing switching, but maybe not. Maybe user controlled?


        //Spawn food in the world.
        for(int n = 0; n < amount_food; ++n){

        }










      }
  }

  //Proximity sensors (U,D,L,R,UL,UR,DL,DR,Center) and flags (is_food, is_pred, is_hive, is_clone, carrying_food).
  int SwarmWorld::requiredInputs() {
    return 14;
  }

  // Move U,D,L, and R.
  int SwarmWorld::requiredOutputs() {
    return 4;
  }
