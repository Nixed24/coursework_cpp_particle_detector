#pragma once
#define SUBDETECTOR_BASE_H_
#include <map>
#include <random>
#include <ctime>
//#ifndef PARTICLE_BASE_H_
#include "particle_base.h"
//#endif
//#ifndef DETECTEDPARTICLEDATA_H_
#include "DetectedParticleData.h"
//#endif

class Subdetector // Pure abstract base class: No data members, declares only virtual functions
{
  public:

  virtual double random_normal(double mu, double sigma) = 0; // normal distribution for detector imprecision (fractional)
  virtual int random_binomial(int number_of_trials, double probability_of_success) = 0; // binomial distribution for detector efficiency
  virtual bool check_legal_detection(int particle_id) const = 0;
  
  virtual std::string get_subdetector_desc() const = 0;
  virtual void set_subdetector_desc(std::string description) = 0;
  virtual double get_radial_length() const = 0;
  virtual void set_radial_length(double radial_length) = 0;

  virtual std::vector<int> get_detectable_particle_ids() const = 0;
  virtual void set_detectable_particle_ids(std::vector<int> particle_ids) = 0;
  virtual std::map<int, double> get_efficiency_dict() const = 0;
  virtual std::map<int, double> get_precision_dict() const = 0;
  virtual void set_efficiency_dict(std::map<int, double> efficiency_dict) = 0;
  virtual void set_precision_dict(std::map<int, double> precision_dict) = 0;
  virtual std::array<double, 4> get_component_precisions() const = 0;
  virtual void set_component_precisions(std::array<double, 4> precisions) = 0;
  virtual void dump_subdetector_info() const = 0;
  virtual DetectedParticleData detect_particle(Particle & particle) = 0;
};
