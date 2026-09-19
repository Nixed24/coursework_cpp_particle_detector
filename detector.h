#pragma once
#include<algorithm>

// particle include guards (commented out, as we just use #pragma once here, but these are to demonstrate the programmer understands their use!)
//#ifndef HADRONS_H_
#include "hadrons.h"
//#endif
//#ifndef ELECTRON_H_
#include "electron.h"
//#endif
//#ifndef MUON_H_
#include "muon.h"
//#endif
//#ifndef TAU_H_
#include "tau.h"
//#endif
//#ifndef PHOTON_H_
#include "photon.h"
//#endif

// subdetector include guards
//#ifndef CALORIMETER_H_
#include "calorimeter.h"
//#endif
//#ifndef TRACKER_H_
#include "tracker.h"
//#endif
//#ifndef MUON_CHAMBER_H_
#include "muon_chamber.h"
//#endif


class Detector
{
  private:

  static constexpr double CENTIMETRES_PER_METRE = 100; // centimetres per metre
  static constexpr double C_0 = 3e8; // metres per second

  std::map<int, double> M_REST_MASS_LOOKUP_TABLE = {{1, Hadron().createProton().get_rest_mass()}, 
  {2, Hadron().createNeutron().get_rest_mass()}, {3, Hadron().createChargedPion().get_rest_mass()}, {4, Hadron().createNeutralPion().get_rest_mass()}, 
  {5, Hadron().createChargedKaon().get_rest_mass()}, {6, Hadron().createNeutralKaon().get_rest_mass()}, {7, Electron().get_rest_mass()}, 
  {8, Muon().get_rest_mass()}, {9, Tau().get_rest_mass()}, {11, Photon().get_rest_mass()}, {12, -99999999}};
  // Exotic hadrons are given this rest mass in the lookup table as a placeholder to avoid a 
  // race condition between mass delta for other massless particles in resolve_particle() (if it was the default exotic hadron rest mass, 0)

  std::map<int, int> M_CHARGE_LOOKUP_TABLE = {{1, Hadron().createProton().get_charge()}, 
  {2, Hadron().createNeutron().get_charge()}, {3, Hadron().createChargedPion().get_charge()}, {4, Hadron().createNeutralPion().get_charge()}, 
  {5, Hadron().createChargedKaon().get_charge()}, {6, Hadron().createNeutralKaon().get_charge()}, {7, Electron().get_charge()}, 
  {8, Muon().get_charge()}, {9, Tau().get_charge()}, {11, Photon().get_charge()}, {12, 0}};

  std::map<int, double> M_DECAY_CONSTANT_LOOKUP_TABLE = {{1, Hadron().createProton().get_decay_constant()}, 
  {2, Hadron().createNeutron().get_decay_constant()}, {3, Hadron().createChargedPion().get_decay_constant()}, {4, Hadron().createNeutralPion().get_decay_constant()}, 
  {5, Hadron().createChargedKaon().get_decay_constant()}, {6, Hadron().createNeutralKaon().get_decay_constant()}, {7, Electron().get_decay_constant()}, 
  {8, Muon().get_decay_constant()}, {9, Tau().get_decay_constant()}, {11, Photon().get_charge()}, {12, 0}};

  std::map<int, std::string> M_NAME_LOOKUP_TABLE = {{1, "Proton"}, 
  {2, "Neutron"}, {3, "Charged Pion"}, {4, "Neutral Pion"}, 
  {5,"Charged Kaon"}, {6, "Neutral Kaon"}, {7, "Electron"}, 
  {8, "Muon"}, {9, "Tau"}, {11, "Photon"}, {12, "Exotic Hadron"}}; 



  static constexpr double M_SIGMA_MULTIPLIER = 5; // Numbers of standard deviations allowed from mass before resolve_particle() fails to resolve. 

  std::vector<std::unique_ptr<Subdetector>> subdetector_array {}; // Subdetectors are a large data type -> use pointers to avoid unnecessary memory use

  double m_radial_length {4}; // cm ; radial length OF INNER DETECTOR, not the whole detector

  void display_resolve_particle_result(DetectedParticleData & detection, int id, std::string method);
  
  public:
  
  template <class T> void append_subdetector(T & subdetector) 
  // Functions that use "template" must have their implementation and declaration in the same file, but we only include this file in main.cpp anyway so it's OK.
  {
    subdetector_array.emplace_back(std::make_unique<T>(&subdetector));
    return;
  }
  template <class T> void prepend_subdetector(T & subdetector)
  {
    subdetector_array.emplace(subdetector_array.begin(), std::make_unique<T>(&subdetector));
    return;
  }

  template <class T> DetectedParticleData transmit_particle(T & particle) const
  {
    DetectedParticleData aggregate_detection;
    aggregate_detection.travel_distance = aggregate_detection.travel_distance + m_radial_length;
    for(auto it = subdetector_array.begin(); it != subdetector_array.end(); ++it)
    {
      DetectedParticleData current_detection = (**it).detect_particle(particle);
      aggregate_detection = aggregate_detection + current_detection;
    }
    return aggregate_detection;
  }

  void resolve_particle(DetectedParticleData & detection);

  void dump_subdetector_config() const;

};
