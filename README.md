# SwarmWorld
## Rationale
  SwarmWorld is a MABE world in which a swarm of genotypically identical organisms
attempt to gather food and protect their "hive" from predators. The primary focus
is to evolve phenotypic splitting from a single genotype as a way to study
phenotypic variability. The mechanism by which we select for this will vary on
the settings and final design, but the key is that there should be a strong tradeoff between each
phenotype, while forcing the same genotype.

  This will be somewhat different from the actual case of bacterial cells that
we wish to study, as the fitness effect will be on the swarm as a whole, rather
than the individual. If this system is found to be unusable in a bacterial context,
the obvious similarity to eusocial insects may allow it to be relevant in that
context.

## Overview
### The World
  The world is a square grid in which the bottom left square is (0,0) and the
upper right square is (n,n), where n is the length of the sides. At (n//2,n//2)
will be the hive. This is where the organisms spawn, and where they must
return collected food in order for it to count towards their fitness. On the
first "step" of the world, all of the organism are spawned on top of the hive.
They may then move one grid up, down, left, or right on each step of the simulation.
Food is spawned on the map, and organisms may improve their genotype's score by
returning food to the hive.

### The Organisms
  Organisms' brains have binary sensors for C,U,D,L,R,UL,UR,DL,DR, which let the
organism know that something is located in that space. A second series of binary
flags lets the organism know if at least one of the other organisms is a fellow
clone, food, the hive, or a predator. The brain outputs are to move UDLR. Organisms
may occupy the same square.

### The predators
  Predators are constant-behavior entities which try to steal food from the colony.
When enabled, they will approach the colony, and can only be stopped by contact
with a user-selected number of colony members. The predators simply move towards
the colony by a direct path, and if they are swarmed by the user selected number
of organisms they despawn. If they manage to touch the colony, they steal a user
selected amount of food, decreasing the colony's score.

## The Tradeoff
  There are multiple tradeoffs that can be made in this world. The obvious one is
the difference between guarding clones ("soldiers") and foraging clones ("foragers").
The soldiers will need to stay near the colony and guard against predators, but
the foragers will need to search far away from the colony to find food. Colony members
which attempt to compromise will move too far from the base to effectively guard it,
while not moving far enough to efficiently find food. This tradeoff can be encouraged
by requiring a large number of organisms to fend off predators, requiring a large
number of soldiers, and by spawning food only relatively far from the nest. This
discourages the evolution of intermediate phenotypes, and attempts to for the
genotype to code for both soldier and forager phenotypes.
