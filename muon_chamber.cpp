#include "muon_chamber.h"

std::map<int, double> MuonChamber::generate_constant_map(std::vector<int> & keys, double value)
{
  std::map<int, double> returned_map;

  for(auto it = keys.begin(); it != keys.end(); ++it)
  {
    returned_map[(*it)] = value;
  }
  return returned_map;
}
double MuonChamber::random_normal(double mu, double sigma)
{
  std::normal_distribution<double> distribution(mu, sigma);
  return distribution(rng);
}

int MuonChamber::random_binomial(int number_of_trials, double probability_of_success)
{
  std::binomial_distribution<int> distribution(number_of_trials, probability_of_success);
  return distribution(rng);
}
bool MuonChamber::check_legal_detection(int particle_id) const
{
  for(auto it = m_detectable_particle_ids.begin(); it != m_detectable_particle_ids.end(); ++it)
  {
    if(particle_id == (*it))
    {
      return true;
    }
  }
  return false;
}
std::string MuonChamber::get_subdetector_desc() const
{
  return m_subdetector_desc;
}
double MuonChamber::get_radial_length() const
{
  return m_radial_length;
}
std::vector<int> MuonChamber::get_detectable_particle_ids() const
{
  return m_detectable_particle_ids;
}
std::map<int, double> MuonChamber::get_efficiency_dict() const
{
  return m_efficiency_dict;
}
std::map<int, double> MuonChamber::get_precision_dict() const
{
  return m_precision_dict;
}
std::array<double, 4> MuonChamber::get_component_precisions() const
{
  return m_component_precision;
}
void MuonChamber::set_subdetector_desc(std::string description)
{
  m_subdetector_desc = description;
  return;
}
void MuonChamber::set_radial_length(double radial_length)
{
  if(radial_length > 0)
  {
    m_radial_length = radial_length;
    return;
  }
  std::cout<<"Subdetector radial length must be positive and non-zero."<<std::endl;
  return;
}
void MuonChamber::set_detectable_particle_ids(std::vector<int> particle_ids)
{
  m_detectable_particle_ids = particle_ids;
  return;
}
void MuonChamber::set_efficiency_dict(std::map<int, double> efficiency_dict)
{
  m_efficiency_dict = efficiency_dict;
  return;
}
void MuonChamber::set_precision_dict(std::map<int, double> precision_dict)
{
  m_precision_dict = precision_dict;
  return;
}
void MuonChamber::set_component_precisions(std::array<double, 4> component_precisions)
{
  m_component_precision = component_precisions;
  return;
}
void MuonChamber::dump_subdetector_info() const
{
  std::cout<<"-- Subdetector Info --"<<std::endl;
  std::cout<<"Detector description (subdetector type by default): "<<get_subdetector_desc()<<std::endl;
  std::cout<<"Length: "<<get_radial_length()<<std::endl;
  std::cout<<"Default efficiency: "<<DEFAULT_EFFICIENCY<<std::endl;
  std::cout<<"Default precision: "<<DEFAULT_PRECISION<<std::endl;
}
DetectedParticleData MuonChamber::detect_particle(Particle & particle)
{
  bool legal_detection = check_legal_detection(particle.get_id());
  if(legal_detection == false || (random_binomial(1 , get_efficiency_dict()[particle.get_id()]) == 0)) // Particle isn't detectable or isn't detected
  {
    //std::cout<<"Undetected"<<std::endl;
    return DetectedParticleData();
  }
  DetectedParticleData detection;
  detection.detector_component_precision = 
  {get_precision_dict()[particle.get_id()] * m_component_precision[0],
     get_precision_dict()[particle.get_id()] * m_component_precision[1],
      get_precision_dict()[particle.get_id()] * m_component_precision[2], 
        get_precision_dict()[particle.get_id()] * m_component_precision[3]};
  double detected_energy = particle.get_four_momentum().get_energy() * (1 + random_normal(0, detection.detector_component_precision[0]));
  double detected_p_x = particle.get_four_momentum().get_p_x() * (1 + random_normal(0, detection.detector_component_precision[1]));
  double detected_p_y = particle.get_four_momentum().get_p_y() * (1 + random_normal(0, detection.detector_component_precision[2]));
  double detected_p_z = particle.get_four_momentum().get_p_z() * (1 + random_normal(0, detection.detector_component_precision[3]));
  detection.detected_four_momentum.set_energy(detected_energy);
  detection.detected_four_momentum.set_p_x(detected_p_x);
  detection.detected_four_momentum.set_p_y(detected_p_y);
  detection.detected_four_momentum.set_p_z(detected_p_z);
  detection.candidate_particle_ids = get_detectable_particle_ids();
  detection.travel_distance = get_radial_length();
  return detection;
}
MuonChamber::MuonChamber()
{
  m_detectable_particle_ids = {8}; // Muons only
  m_efficiency_dict = generate_constant_map(m_detectable_particle_ids, DEFAULT_EFFICIENCY);
  m_precision_dict = generate_constant_map(m_detectable_particle_ids, DEFAULT_PRECISION);
}
MuonChamber::MuonChamber(MuonChamber * muon_chamber)
{
  m_subdetector_desc = (*muon_chamber).get_subdetector_desc();
  m_radial_length = (*muon_chamber).get_radial_length();
  m_detectable_particle_ids = (*muon_chamber).get_detectable_particle_ids();
  m_efficiency_dict = (*muon_chamber).get_efficiency_dict();
  m_precision_dict = (*muon_chamber).get_precision_dict();
  m_component_precision = (*muon_chamber).get_component_precisions();
}