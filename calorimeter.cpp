#include "calorimeter.h"

double Calorimeter::random_normal(double mu, double sigma)
{
  std::normal_distribution<double> distribution(mu, sigma);
  return distribution(rng);
}

int Calorimeter::random_binomial(int number_of_trials, double probability_of_success)
{
  std::binomial_distribution<int> distribution(number_of_trials, probability_of_success);
  return distribution(rng);
}
bool Calorimeter::check_legal_detection(int particle_id) const
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
std::string Calorimeter::get_subdetector_desc() const
{
  return m_subdetector_desc;
}
double Calorimeter::get_radial_length() const
{
  return m_radial_length;
}
std::vector<int> Calorimeter::get_detectable_particle_ids() const
{
  return m_detectable_particle_ids;
}
std::map<int, double> Calorimeter::get_efficiency_dict() const
{
  return m_efficiency_dict;
}
std::map<int, double> Calorimeter::get_precision_dict() const
{
  return m_precision_dict;
}
std::array<double, 4> Calorimeter::get_component_precisions() const
{
  return m_component_precision;
}
void Calorimeter::set_subdetector_desc(std::string description)
{
  m_subdetector_desc = description;
  return;
}
void Calorimeter::set_radial_length(double radial_length)
{
  if(radial_length > 0)
  {
    m_radial_length = radial_length;
    return;
  }
  std::cout<<"Subdetector radial length must be positive and non-zero."<<std::endl;
  return;
}
void Calorimeter::set_detectable_particle_ids(std::vector<int> particle_ids)
{
  m_detectable_particle_ids = particle_ids;
  return;
}
void Calorimeter::set_efficiency_dict(std::map<int, double> efficiency_dict)
{
  m_efficiency_dict = efficiency_dict;
  return;
}
void Calorimeter::set_precision_dict(std::map<int, double> precision_dict)
{
  m_precision_dict = precision_dict;
  return;
}
void Calorimeter::set_component_precisions(std::array<double, 4> component_precisions)
{
  m_component_precision = component_precisions;
  return;
}
void Calorimeter::dump_subdetector_info() const
{
  std::cout<<"-- Subdetector Info --"<<std::endl;
  std::cout<<"  Detector description (subdetector type by default): "<<get_subdetector_desc()<<std::endl;
  std::cout<<"  Length: "<<get_radial_length()<<std::endl;
  std::cout<<"  Default efficiency: "<<DEFAULT_EFFICIENCY<<std::endl;
  std::cout<<"  Default precision: "<<DEFAULT_PRECISION<<std::endl;
}
DetectedParticleData Calorimeter::detect_particle(Particle & particle)
{
  bool legal_detection = check_legal_detection(particle.get_id());
  if(legal_detection == false || (random_binomial(1 , get_efficiency_dict()[particle.get_id()]) == 0)) // Particle isn't detectable or isn't detected
  {
    //std::cout<<"Undetected"<<std::endl;
    return DetectedParticleData();
  }
  DetectedParticleData detection;
  detection.from_calorimeter = true;
  detection.detector_component_precision = {get_precision_dict()[particle.get_id()], 0, 0, 0}; 
  // no need for component precision on calorimeters apart from energy (since that's all they detect)
  // p_X components = 0: Won't affect total precision when added up with other DetectedParticleData's
  double detected_energy = particle.get_four_momentum().get_energy() * (1 + random_normal(0, get_precision_dict()[particle.get_id()]));
  detection.detected_four_momentum.set_energy(detected_energy);
  detection.candidate_particle_ids = get_detectable_particle_ids();
  detection.travel_distance = get_radial_length();
  return detection;
}
Calorimeter::Calorimeter()
{
  m_detectable_particle_ids = {1,2,3,4,5,6,7,11,12};  // Both ECAL and HCAL
  m_efficiency_dict = generate_constant_map(m_detectable_particle_ids, DEFAULT_EFFICIENCY);
  m_precision_dict = generate_constant_map(m_detectable_particle_ids, DEFAULT_PRECISION);
}
Calorimeter Calorimeter::createHadronCalorimeter()
{
  Calorimeter returned_calorimeter = Calorimeter();
  returned_calorimeter.m_detectable_particle_ids = {1,2,3,4,5,6,12};  // HCAL
  returned_calorimeter.m_subdetector_desc = "hadron calorimeter";
  returned_calorimeter.m_efficiency_dict = generate_constant_map(returned_calorimeter.m_detectable_particle_ids, DEFAULT_EFFICIENCY);
  returned_calorimeter.m_precision_dict = generate_constant_map(returned_calorimeter.m_detectable_particle_ids, DEFAULT_PRECISION);
  return returned_calorimeter;
}
Calorimeter Calorimeter::createElectroCalorimeter()
{
  Calorimeter returned_calorimeter = Calorimeter();
  returned_calorimeter.m_detectable_particle_ids = {7,11};  // ECAL
  returned_calorimeter.m_subdetector_desc = "electromagnetic calorimeter";
  returned_calorimeter.m_efficiency_dict = generate_constant_map(returned_calorimeter.m_detectable_particle_ids, DEFAULT_EFFICIENCY);
  returned_calorimeter.m_precision_dict = generate_constant_map(returned_calorimeter.m_detectable_particle_ids, DEFAULT_PRECISION);
  return returned_calorimeter;
}
Calorimeter::Calorimeter(Calorimeter * calorimeter)
{
  m_subdetector_desc = (*calorimeter).get_subdetector_desc();
  m_radial_length = (*calorimeter).get_radial_length();
  m_detectable_particle_ids = (*calorimeter).get_detectable_particle_ids();
  m_efficiency_dict = (*calorimeter).get_efficiency_dict();
  m_precision_dict = (*calorimeter).get_precision_dict();
  m_component_precision = (*calorimeter).get_component_precisions();
}
Calorimeter::Calorimeter(Calorimeter & calorimeter)
{
  m_subdetector_desc = (calorimeter).get_subdetector_desc();
  m_radial_length = (calorimeter).get_radial_length();
  m_detectable_particle_ids = (calorimeter).get_detectable_particle_ids();
  m_efficiency_dict = (calorimeter).get_efficiency_dict();
  m_precision_dict = (calorimeter).get_precision_dict();
  m_component_precision = (calorimeter).get_component_precisions();
}
