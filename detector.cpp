#include "detector.h"

void Detector::display_resolve_particle_result(DetectedParticleData & detection, int id, std::string method)
{
if(M_DECAY_CONSTANT_LOOKUP_TABLE[id] != 0) // if particle is unstable
{
    double total_distance = (detection.travel_distance + m_radial_length) / CENTIMETRES_PER_METRE;
    double decay_constant = M_DECAY_CONSTANT_LOOKUP_TABLE[id];
    double travel_time = total_distance / (C_0);
    double decay_probability = 1 - exp(-1 * decay_constant * travel_time);
    std::cout<<"-----------Detector particle resolution routine-----------"<<std::endl;
    std::cout<<"Resolved particle (by "<<method<<") : "<<M_NAME_LOOKUP_TABLE[id]<<std::endl;
    std::cout<<"Approximate probability of decay if product of beam: "<<decay_probability<<std::endl;
    std::cout<<"----------------------------------------------------------"<<std::endl;
    return;
}
std::cout<<"-----------Detector particle resolution routine-----------"<<std::endl;
std::cout<<"Resolved particle (by "<<method<<") : "<<M_NAME_LOOKUP_TABLE[id]<<std::endl;
std::cout<<"----------------------------------------------------------"<<std::endl;
return;
}

void Detector::resolve_particle(DetectedParticleData & detection)
{

if(detection.candidate_particle_ids[0] == 0) // if the passed detection is just the null detection
{
    std::cout<<"resolve_particle(): Particle was not detected!"<<std::endl;
    return;
}

std::map<int, double> mass_deltas;
std::map<double, int> mass_deltas_reversed;
std::string anti_string = "";
FourMomentum particle_four_momentum = detection.detected_four_momentum;

auto get_invariant_mass = [](FourMomentum x) { // lambda function to compute invariant mass from a FourMomentum object
    double m_squared = (pow(x.get_energy(), 2) - pow(x.get_p_x(), 2) - pow(x.get_p_y(), 2) - pow(x.get_p_z(), 2));
    if(m_squared > 0)
    {
    return pow(m_squared, 0.5);
    }
    return double {0};
};
    
// getting imprecision on invariant mass
double invar_mass_imprecision_radical = (pow(detection.detector_component_precision[0], 2) * pow(particle_four_momentum.get_energy(), 4))
+ (pow(detection.detector_component_precision[1], 2) * pow(particle_four_momentum.get_p_x(), 4))
+ (pow(detection.detector_component_precision[2], 2) * pow(particle_four_momentum.get_p_y(), 4))
+ (pow(detection.detector_component_precision[3], 2) * pow(particle_four_momentum.get_p_z(), 4));

double invar_mass = get_invariant_mass(particle_four_momentum);

double invar_mass_imprecision = pow(invar_mass_imprecision_radical, 0.5) / pow(invar_mass, 2);
//

std::vector<int> candidate_ids = detection.candidate_particle_ids;
int counter = 0;
if(detection.from_calorimeter == false) 
// detection not entirely from calorimeter
// => there is at least one tracker-type with a hit => particle must be charged; anti-particles do not have different particle IDs so we dont worry about that here.
// so we'll remove any neutral particles from the candidates by deep copying candidate_ids, clearing it, then iterating through the copy, checking if the current
// ID points to a charged particle and adding it to the cleared candidate_ids if true.
{
    std::vector<int> candidate_ids_copy = candidate_ids;
    candidate_ids.clear();
    for(auto it = candidate_ids_copy.begin(); it != candidate_ids_copy.end(); ++it)
    {
    if(!(M_CHARGE_LOOKUP_TABLE[(*it)] == 0 && ((*it) != 12))) // Keep exotic hadron as its charge varies
    {
        candidate_ids.push_back((*it));
        counter++;
    }
    }
}

if(candidate_ids.size() == 1) // if we are left with only one possible particle
{
    display_resolve_particle_result(detection, candidate_ids[0], "charge elimination");
    return;
}

// Now we'll make a bidirectional map of (particle id) <-> (difference in particle invariant mass and detection invariant mass)
// by having a mass_deltas that has id -> difference and a mass_deltas_reversed that has difference->id
// This takes advantage of the fact that the std::map container is sorted automatically by keys.
for (auto it = candidate_ids.begin(); it != candidate_ids.end(); ++it)
{
    mass_deltas.insert_or_assign((*it) , std::abs(M_REST_MASS_LOOKUP_TABLE[(*it)] - invar_mass));
}
for (auto it = mass_deltas.begin(); it != mass_deltas.end(); ++it)
{
    mass_deltas_reversed.insert_or_assign(it->second, it->first);
}
//

if((mass_deltas_reversed.begin()->first < std::abs(M_SIGMA_MULTIPLIER * invar_mass * invar_mass_imprecision))) 
// If closest mass particle is less than (M_SIGMA_MULTIPLIER) * sigma from detected mass
{
    display_resolve_particle_result(detection, mass_deltas_reversed.begin()->second, "charge elimination + mass proximity");
    return;
}
else
{
    if(mass_deltas.count(12) == 1) // No nearby mass but exotic hadron detectable -> probably an exotic hadron
    {
    display_resolve_particle_result(detection, 12, "negative elimination");
    return;
    }
    if(mass_deltas.count(11) == 1 && detection.from_calorimeter == true) // No nearby mass, not an exotic hadron and possibly neutral -> probably a photon
    {
    display_resolve_particle_result(detection, 11, "negative elimination");
    return;
    }
}
std::cout<<"resolve_particle() could not find a good candidate particle at "<<M_SIGMA_MULTIPLIER<<"-sigma level. Closest mass match: "<<M_NAME_LOOKUP_TABLE[mass_deltas_reversed.begin()->second]<<std::endl;
return;
}

void Detector::dump_subdetector_config() const
{
  std::cout<<"-- Detector configuration --"<<std::endl;
  std::cout<<"- Radially outward: -"<<std::endl;
  std::cout<<"-  (inner detector) -"<<std::endl;
  for(auto it = subdetector_array.begin(); it != subdetector_array.end(); ++it)
  { 
    std::cout<<"-  "<<(**it).get_subdetector_desc()<<" -"<<std::endl;
  }
  std::cout<<"---------------------------"<<std::endl;
  return;
}
