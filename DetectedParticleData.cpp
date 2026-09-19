#include "DetectedParticleData.h"

DetectedParticleData DetectedParticleData::operator+(const DetectedParticleData & other_struct)
{
  // checks if one particle is undetected -> treats it as an additive identity
  if(candidate_particle_ids[0] == 0) 
  {
    return other_struct;
  }
  if(other_struct.candidate_particle_ids[0] == 0)
  {
    return *this;
  }
  //
  DetectedParticleData returned_object = DetectedParticleData();
  FourMomentum four_momentum_sum = FourMomentum();
  std::array<double, 4> combined_component_precision {0,0,0,0};
  std::vector<int> returned_object_candidate_particle_ids = candidate_particle_ids;

  // energy validated externally by its setter

  double weighted_energy = (detected_four_momentum.get_energy() * pow(detector_component_precision[0] * detected_four_momentum.get_energy(), -2) 
  + other_struct.detected_four_momentum.get_energy() * pow(other_struct.detector_component_precision[0] * other_struct.detected_four_momentum.get_energy(), -2)) 
  / ( pow(detector_component_precision[0] * detected_four_momentum.get_energy(), -2) 
  + pow(other_struct.detector_component_precision[0] * other_struct.detected_four_momentum.get_energy(), -2) );

  four_momentum_sum.set_energy(weighted_energy);

  // weights don't exist when p_X = 0 so we'll use raw precision instead to stop divbyzero errors, at a slight cost of accuracy
  // (error handling code for this would be too long and convoluted)

  if(from_calorimeter == true && other_struct.from_calorimeter == false)
  {
    four_momentum_sum.set_p_x(other_struct.detected_four_momentum.get_p_x());
    four_momentum_sum.set_p_y(other_struct.detected_four_momentum.get_p_y());
    four_momentum_sum.set_p_z(other_struct.detected_four_momentum.get_p_z());
  }
  if(other_struct.from_calorimeter == true && from_calorimeter == false)
  {
    four_momentum_sum.set_p_x(detected_four_momentum.get_p_x());
    four_momentum_sum.set_p_y(detected_four_momentum.get_p_y());
    four_momentum_sum.set_p_z(detected_four_momentum.get_p_z());
  }
  if(from_calorimeter == false && other_struct.from_calorimeter == false)
  {
    double weighted_p_x = (detected_four_momentum.get_p_x() * pow(detector_component_precision[1], -2) + other_struct.detected_four_momentum.get_p_x() * pow(other_struct.detector_component_precision[1], -2)) 
    / ( pow(detector_component_precision[1], -2) + pow(other_struct.detector_component_precision[1], -2) );

    double weighted_p_y = (detected_four_momentum.get_p_y() * pow(detector_component_precision[2], -2) + other_struct.detected_four_momentum.get_p_y() * pow(other_struct.detector_component_precision[2], -2)) 
    / ( pow(detector_component_precision[2], -2) + pow(other_struct.detector_component_precision[2], -2) );

    double weighted_p_z = (detected_four_momentum.get_p_z() * pow(detector_component_precision[3], -2) + other_struct.detected_four_momentum.get_p_z() * pow(other_struct.detector_component_precision[3], -2)) 
    / ( pow(detector_component_precision[3], -2) + pow(other_struct.detector_component_precision[3], -2) );

    four_momentum_sum.set_p_x(weighted_p_x);
    four_momentum_sum.set_p_y(weighted_p_y);
    four_momentum_sum.set_p_z(weighted_p_z);
  }
  for(size_t i = 0; i < 4; i++)
  {
    combined_component_precision[i] = (pow(pow(detector_component_precision[i], 2) + pow(other_struct.detector_component_precision[i], 2), 0.5)) / pow(2,0.5); // standard error
  }
  for(auto it = other_struct.candidate_particle_ids.begin(); it != other_struct.candidate_particle_ids.end(); ++it)
  {
    returned_object_candidate_particle_ids.push_back((*it));
  }
  returned_object.detected_four_momentum = four_momentum_sum;
  returned_object.detector_component_precision = combined_component_precision;
  returned_object.candidate_particle_ids = returned_object_candidate_particle_ids;
  returned_object.travel_distance = travel_distance + other_struct.travel_distance;
  return returned_object;
}

void DetectedParticleData::dump_detected_particle_info()
{
  std::cout<<"-- Detection data --"<<std::endl;
  std::cout<<"  Entirely calorimeter detection:  "<<from_calorimeter<<std::endl;
  std::cout<<"  Detected (E, p_x, p_y, p_z): "<<detected_four_momentum.format_four_momentum()<<std::endl;
  std::cout<<"  Precision: ("<<detector_component_precision[0]<<", "<<detector_component_precision[1]<<", "<<detector_component_precision[2]<<", "<<detector_component_precision[3]<<")"<<std::endl;
  std::string particle_ids_string = "";
  for(auto it = candidate_particle_ids.begin(); it != candidate_particle_ids.end(); ++it)
  {
    particle_ids_string = particle_ids_string + std::to_string((*it)) + ", ";
  }
  std::cout<<"  Candidate particle ID's: "<<particle_ids_string<<std::endl;
  std::cout<<"---------------------"<<std::endl;
  return;
}
