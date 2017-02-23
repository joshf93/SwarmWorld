// Testing pieces of SwarmWorld

#include <vector>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <numeric>
#include <chrono>
#define _USE_MATH_DEFINES

struct org_sim{
  int x;
  int y;
  bool carrying_food;
};

struct cell{
  int flag;
  int num_orgs;
  bool has_food;
  bool has_nest;
  bool is_hive;
};

void update_world(std::vector<std::vector<cell>>& the_world){
  //Updates the world's flags. Only need to really call this when we print the world.
  for(auto &l : the_world){
    for(auto &p : l){
      if(p.num_orgs >= 1){
        p.flag = 5;
      }
    }
  }
}

void print_world(std::vector<std::vector<cell>>& the_world){
  update_world(the_world);
  for(auto l : the_world){
    for(auto p : l){
      std::cout << p.flag << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "\n" << std::endl;
}

inline int manhattan_dist(int x_i, int y_i, int x_f, int y_f){
  return(abs(x_f-x_i) + abs(y_f-y_i));
}

int main(){
  int world_size = 30;
  int amount_food = 719;
  int min_distance = 10;
  int clones = 5;
  int steps = 1000;
  srand(std::clock());

  /*Make the world. The world integer guide is as follows:
  0: nothing
  1: the hive
  2: food
  3: an organism
  4: an organism ontop of food
  5: an organism ontop of the hive
  6: a nest
  7: an organism ontop of a nests
  */
  std::vector<std::vector<cell>> world;
  std::vector<cell> line;
  for(int n = 0; n < world_size; ++n){
    line = {};
    for(int j = 0; j < world_size; ++j){
      line.push_back({0, 0, 0, 0, 0});
    }
    world.push_back(line);
  }

  print_world(world);
  //Spawn food in the world. Check to make sure it's possible to spawn that much.
  //https://en.wikipedia.org/wiki/Von_Neumann_neighborhood d
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
    while((manhattan_dist(food_point_x, food_point_y, world_size/2, world_size/2) < min_distance) || (world[food_point_y][food_point_x].has_food)){
      food_point_x = rand()%world_size;
      food_point_y = rand()%world_size;
    }
    world[food_point_y][food_point_x].has_food = true;
    world[food_point_y][food_point_x].flag = 2;
  }
  //Spawn the hive at the center
  world[world_size/2][world_size/2].has_nest = true;
  world[world_size/2][world_size/2].flag = 1;

  print_world(world);

  //Make a vector of organisms to move about
  std::vector<org_sim> swarm_orgs;
  for (int n = 0; n < clones; ++n){
    swarm_orgs.push_back({world_size/2, world_size/2, false});
    world[world_size/2][world_size/2].num_orgs += 1;
  }

  //Main loop
  for(int j = 0; j < steps; ++j){
    for(auto &organismal : swarm_orgs){
      int sign_x;
      int sign_y;
      int temp_x;
      int temp_y;

      if(rand()%2 == 0){sign_x = 0;}
      else{
        if(rand()%2 == 0){sign_x = -1;}
        else{sign_x = 1;}
      }
      if(rand()%2 == 0){sign_y = 0;}
      else{
        if(rand()%2 == 0){sign_y = -1;}
        else{sign_y = 1;}
      }
      //Move
      temp_x = organismal.x + (sign_x*rand()%2);
      temp_y = organismal.y + (sign_y*rand()%2);

      //Bound check!
      if (temp_x < 0 || temp_x > (world_size-1)){
        temp_x = organismal.x;
      }
      if (temp_y < 0 || temp_y > (world_size-1)){
        temp_y = organismal.y;
      }

      world[organismal.y][organismal.x].num_orgs -= 1;
      world[temp_y][temp_x].num_orgs += 1;
      organismal.x = temp_x;
      organismal.y = temp_y;
    }
  }
  print_world(world);
  return 0;
}
