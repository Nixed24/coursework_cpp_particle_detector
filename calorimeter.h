#pragma once
#define CALORIMETER_H_
//#ifndef SUBDETECTOR_BASE_H_
#include "subdetector_base.h"
//#endif

class Calorimeter : public Subdetector
{
  private:

  static std::map<int, double> generate_constant_map(std::vector<int> & keys, double value)
  {
    std::map<int, double> returned_map;

    for(auto it = keys.begin(); it != keys.end(); ++it)
    {
      returned_map[(*it)] = value;
    }
    return returned_map;
  }

  std::map<int, double> m_efficiency_dict; // int: particle ID ; double: detector efficiency for that particle | binomial sample will be used
  std::map<int, double> m_precision_dict; // int: particle ID ; double: precision for that particle | normal sample will be used ( X ~ Normal(mu, precision * mu) )

  std::array<double, 4> m_component_precision {1,1,1,1}; // precision of components relative to general precision (precision dict)

  std::random_device rd; 
  std::mt19937 rng {rd()};
  
  std::string m_subdetector_desc {"calorimeter"};

  static constexpr double DEFAULT_EFFICIENCY = 0.9;
  static constexpr double DEFAULT_PRECISION = 0.01;
  std::vector<int> m_detectable_particle_ids;

  double m_radial_length {50}; // centimetres

  double random_normal(double mu, double sigma) override;
  int random_binomial(int number_of_trials, double probability_of_success) override;
  bool check_legal_detection(int particle_id) const override;

  public:

  std::string get_subdetector_desc() const override;
  void set_subdetector_desc(std::string description) override;
  double get_radial_length() const override;
  void set_radial_length(double radial_length) override;
  std::vector<int> get_detectable_particle_ids() const override;
  void set_detectable_particle_ids(std::vector<int> particle_ids) override;
  std::map<int, double> get_efficiency_dict() const override;
  std::map<int, double> get_precision_dict() const override;
  void set_efficiency_dict(std::map<int, double> efficiency_dict) override;
  void set_precision_dict(std::map<int, double> precision_dict) override;
  std::array<double, 4> get_component_precisions() const override;
  void set_component_precisions(std::array<double, 4> precisions) override;
  void dump_subdetector_info() const override;
  DetectedParticleData detect_particle(Particle & particle) override;

  Calorimeter();

  static Calorimeter createHadronCalorimeter();
  static Calorimeter createElectroCalorimeter();
  
  Calorimeter(Calorimeter * calorimeter);
  Calorimeter(Calorimeter & calorimeter); // Compiler can't create a copy constructor for us because we have Container-type data members
};
