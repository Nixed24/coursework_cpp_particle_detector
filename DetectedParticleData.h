#pragma once
#define DETECTEDPARTICLEDATA_H_
#include <array>
//#ifndef FOURMOMENTUM_H_
#include "FourMomentum.h"
//#endif

struct DetectedParticleData
{
  DetectedParticleData operator+(const DetectedParticleData & x);
  void dump_detected_particle_info();

  bool from_calorimeter {false};
  FourMomentum detected_four_momentum {FourMomentum()};
  std::array<double, 4> detector_component_precision {1,1,1,1}; // precision for each component of four momentum
  std::vector<int> candidate_particle_ids {0};
  double travel_distance {0};
};
