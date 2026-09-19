#include "detector.h"

template <typename T> void give_random_four_momentum(T & particle, double max_energy_multiplier=5) // Gives a random four-momentum to a particle argument with energy = (rest energy * max_energy_multiplier)                                  
{
  if(particle.get_rest_mass() == 0)
  {
    return give_random_momentum_massless(particle, max_energy_multiplier);
  }
  std::random_device generator;
  std::uniform_real_distribution<double> theta_distribution(1,3.14);
  std::uniform_real_distribution<double> phi_distribution(1,6.28);
  std::uniform_real_distribution<double> energy_distribution(1,max_energy_multiplier);
  double particle_energy = particle.get_rest_mass() * energy_distribution(generator);
  particle.set_energy(particle_energy);
  // generating random points on a unit sphere
  double theta = theta_distribution(generator);
  double phi = phi_distribution(generator);
  // require magnitude of momentum (i.e radius of this sphere) to be such that invariant mass is zero
  double momentum_magnitude = pow(pow(particle_energy, 2) - pow(particle.get_rest_mass(), 2), 0.5);
  // project spherical coords components to find cartesian components
  double generated_p_x = momentum_magnitude * sin(theta) * cos(phi);
  double generated_p_y = momentum_magnitude * sin(theta) * sin(phi);
  double generated_p_z = momentum_magnitude * cos(theta);
  particle.set_p_x(generated_p_x);
  particle.set_p_y(generated_p_y);
  particle.set_p_z(generated_p_z);
  return;
}
template <typename T> void give_random_momentum_massless(T & particle, double average_energy=5, double energy_width=1) // Gives a random four-momentum to a massless particle argument
{
  if(average_energy - energy_width < 0) // if our variance in energy is such that we could get negative energies
  {
  energy_width = average_energy; // clamp it so that the miniumum energy is zero
  }
  std::random_device generator;
  std::uniform_real_distribution<double> theta_distribution(1,3.14);
  std::uniform_real_distribution<double> phi_distribution(1,6.28);
  std::uniform_real_distribution<double> energy_distribution(average_energy - energy_width * 0.5, average_energy + energy_width * 0.5);
  // randomly pick energy according to this distribution
  double particle_energy = energy_distribution(generator);
  particle.set_energy(particle_energy);
  // generating random points on a unit sphere
  double theta = theta_distribution(generator);
  double phi = phi_distribution(generator);
  // require magnitude of momentum (i.e radius of this sphere) to be such that invariant mass is zero
  double momentum_magnitude = pow(pow(particle_energy, 2) - pow(particle.get_rest_mass(), 2), 0.5);
  // project radius using spherical coords to find components
  double generated_p_x = momentum_magnitude * sin(theta) * cos(phi);
  double generated_p_y = momentum_magnitude * sin(theta) * sin(phi);
  double generated_p_z = momentum_magnitude * cos(theta);
  particle.set_p_x(generated_p_x);
  particle.set_p_y(generated_p_y);
  particle.set_p_z(generated_p_z);
  return;
}

int main()
{
  // Testing procedure:
  // We initiate a particle zoo array that contains (base) pointers to stationary particles (of appropriate derived class)
  // Give each one a random four momentum
  // Simulate projecting it through the detector

  Calorimeter test_hadron_calorimeter = Calorimeter().createHadronCalorimeter();

  Calorimeter test_electro_calorimeter = Calorimeter().createElectroCalorimeter();

  Tracker test_tracker;

  MuonChamber test_muon_chamber;

  Detector detector;
  detector.append_subdetector(test_tracker);
  detector.append_subdetector(test_hadron_calorimeter);
  detector.append_subdetector(test_electro_calorimeter);
  detector.append_subdetector(test_muon_chamber);
  Hadron test_proton = Hadron().createProton(); // Using named constructors to create unique hadron types
  Hadron test_neutron = Hadron().createNeutron();
  Hadron test_charged_pion = Hadron().createChargedPion();
  Hadron test_neutral_pion = Hadron().createNeutralPion();
  Hadron test_charged_kaon = Hadron().createChargedKaon();
  Hadron test_neutral_kaon = Hadron().createNeutralKaon();
  Hadron test_exotic_hadron = Hadron(); // Default constructor of a hadron returns a placeholder "exotic hadron" where we mean "exotic" to say it's not defined in this program.
  std::array<Hadron, 7> test_hadrons = {test_proton, test_neutron, test_charged_pion, test_neutral_pion,
  test_charged_kaon, test_neutral_kaon, test_exotic_hadron};
  Electron test_electron = Electron();
  Muon test_muon = Muon();
  Photon test_photon = Photon();

  std::vector<std::unique_ptr<Particle>> particle_zoo; // Creating array of base pointers to derived objects

  // Populating base pointer array
  for(auto it = test_hadrons.begin(); it != test_hadrons.end(); ++it)
  {
    particle_zoo.emplace_back(std::make_unique<Hadron>(&(*it)));
  }
  particle_zoo.emplace_back(std::make_unique<Electron>(test_electron));
  particle_zoo.emplace_back(std::make_unique<Muon>(test_muon));
  particle_zoo.emplace_back(std::make_unique<Photon>(test_photon));
  //

  detector.dump_subdetector_config();

  for(auto it = particle_zoo.begin(); it != particle_zoo.end(); ++it)
  {
    std::cout<<"--- BEGIN NEW PARTICLE ---"<<std::endl;
    give_random_four_momentum(**it); // give random four momentum to current particle
    DetectedParticleData current_detection = detector.transmit_particle(**it); // project it through the detector
    current_detection.dump_detected_particle_info(); // print detection info to screen
    detector.resolve_particle(current_detection); // use detection info to try and resolve particle type -- print result to screen
    (**it).dump_info(); // print the true info about the particle to the screen
  }
  // Base pointers are also used in the Detector class to refer to Subdetector derived classes
  return 0;
}
