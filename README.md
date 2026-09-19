_*No AI was used in the making of this project, nor the report*_

The report for this project can be found [here](https://github.com/Nixed24/particle_detector_cpp_coursework/blob/main/Project%20report.pdf).

A Particle Detector: Objected-Oriented Programming in C++ Project

HOW TO COMPILE:

On Windows:
Run "```g++ -Wall -o particle_detector.exe *.cpp```" in a terminal with the cloned repo as the current directory.

On Linux/Mac:
Run "```g++ -Wall -o particle_detector.o *.cpp```" in a terminal with the cloned repo as the current directory.

DESCRIPTION:

This repository contains code that simulates a particle detector, including individual subdetector components, their detector efficiency and measurement precision. This is done using class hierarchies (for particles and subdetectors) that are headed by pure abstract base classes. The pure abstract base classes contain virtual function declarations (but the functions are only implemented in overrides in the derived classes). These declarations specify the expected set of functions a derived class should have for the program to accept it. There also exists independent classes for a detector (that is essentially a wrapper for ```Subdetector```-derived instances) and ```FourMomentum``` (which is essentially a wrapper of an energy-momentum four-vector). ```main.cpp``` contains code that tests the functionality of the class hierarchies, including all derived classes for ```Subdetector``` and most for ```Particle``` (```Tau``` was intentionally left out as a sandbox class due to its similiarity in the code to ```Muon```)

IMPORTANT INFO:
This program outputs data in *natural units* by default.
Energy/momenta are in units of MeV.


HOW TO EXTEND:

```Particle```: Adding new particles
```particle_base.h``` contains declarations of all necessary functions for a derived class to have. These do include setter and getter functions (e.g ```get_id()```), which ideally should be setters and getters of data members in any derived class. The expected nature of the functions should otherwise be self-evident: ```dump_info()``` prints information about the particle to the screen, ```get_type()``` returns a human-readable description, usually the particle name. The main choice the user must make to extend this class is to pick a positive integer that is used as the ID for that particle type (```m_id```), which must be unoccupied by any other particle. 

By default, the occupied ID's are:
0 : Default type
1 : Proton
2 : Neutron
3 : Charged Pion
4 : Neutral Pion
5 : Charged Kaon
6 : Neutral Kaon
7 : Electron
8 : Muon
9 : Tau
10 : (Intended for Neutrino, but can be used for a user-defined particle without errors or unexpected behaviour)
11 : Photon
12 : Exotic Hadron (generic, specific exotic hadrons like Eta mesons are free to occupy their own ID's)

If the user wishes to add a hadron, it may be easier to do so by implementing a new named constructor in ```hadrons.h```, following the process of the named constructors already present to construct a hadron with desired attributes.

```Subdetector```: Adding new subdetectors
Similarly to ```Particle```, the definition of ```Subdetector``` specifies the expected set of functions the user should create and implement, and the inferrable data members to have. The main rule to follow is the consistency of implementation of random number generation. This is characterised by the use of ```std::random_device``` that powers a ```std::mt19937``` random number generator, which is sampled according to binomial and normal distributions for detector efficiency and imprecision respectively. This is simply a safeguard to ensure the robustness of the stochastic features in the program.

```Particle``` and ```Subdetector```: Making a custom particle detectable

The detectable particles types of the default ```Subdetector```-derived objects is controlled by ```m_detectable_particle_ids```, which ```get_detectable_particle_ids()``` acts as a getter for. This is then checked against detected particle ID in the ```detect_particle()``` function. This is the intended paradigm for the user to follow. To make a particle detectable by a default subdetector, simply add its ID to the initialised vector of ```m_detectable_particle_ids``` in the default constructor.

The default subdetector types also have ```std::map```'s that map particle ID to efficiency and imprecision for that particle. In the default constructors, this is made a constant value for each particle ID in ```m_detectable_particle_ids``` using ```generate_constant_map()```, where the constant value is specified by ```static constexpr double DEFAULT_*``` (```* = EFFICIENCY, PRECISION```). The user can modify this by generating their own map, either by manually specifying it, or perhaps using ```generate_constant_map()``` and modifying its values for desired keys within the default constructor.

```Detector```: Making a custom particle resolvable

The final thing to do to ensure a custom particle interfaces with all program features is to add it to the lookup tables of ```Detector```, located in ```Detector.h```. These are lookup tables for rest mass, charge, decay constant, and particle name (for UI use). Their syntax and names are self-documenting. The user may wish to alter ```resolve_particle()``` to add additional methods of resolution, or to perhaps add their particle as a fallback in the way the Exotic Hadron placeholder and Photon are. The function is well-commented to aid the user in doing this.




