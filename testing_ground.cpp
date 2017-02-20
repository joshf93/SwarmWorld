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


void print_world(std::vector<std::vector<int>> the_world){
  for(auto l : the_world){
    for(auto p : l){
      std::cout << p << " ";
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
  srand(std::clock());

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

  print_world(world);
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
  //Spawn the hive at the center
  world[world_size/2][world_size/2] = 1;

  print_world(world);


  return 0;
}
