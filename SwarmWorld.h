#ifndef __BasicMarkovBrainTemplate__Chemotaxis
#define __BasicMarkovBrainTemplate__Chemotaxis
#define _USE_MATH_DEFINES //I think this is okay; but if things start acting weird look here. Maybe needs
//its own header guard?

#include "../AbstractWorld.h"
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <fstream>
#include <numeric>

class SwarmWorld: public AbstractWorld {
public:
    //Constructor and destructor.
    SwarmWorld(std::shared_ptr<ParametersTable> _PT = nullptr);
    ~SwarmWorld() = default;

    static std::shared_ptr<ParameterLink<int>> world_size_pl;
    static std::shared_ptr<ParameterLink<int>> repeats_pl;

    int repeats;
    int world_size;

    //Override AbstractWorld methods.
    virtual void evaluateSolo(std::shared_ptr<Organism> org, int analyse, int visualize, int debug) override;
    virtual int requiredInputs() override;
    virtual int requiredOutputs() override;



  };


#endif
