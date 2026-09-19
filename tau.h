#pragma once
#define TAU_H_
//#ifndef PARTICLE_BASE_H_
#include "particle_base.h"
//#endif

class Tau : public Particle
{
  private:

  static constexpr bool is_hadron {false};
  static constexpr bool is_lepton {true};

  static constexpr double TAU_REST_MASS {1780}; // in units of MeV
  static constexpr double TAU_CHARGE {-1}; // in units of electronic charge
  static constexpr double TAU_DECAY_CONSTANT {2.9e-15}; // in units of s^-1

  std::unique_ptr<FourMomentum> m_four_momentum {std::make_unique<FourMomentum>()};
  double m_charge {0}; // in units of electronic charge
  bool m_is_antiparticle {false};
  double m_rest_mass {0}; // in units of MeV
  double m_decay_constant {0}; // in units of s^-1

  int m_id {0};

  public:

  int get_id() const override;
  FourMomentum get_four_momentum() const override;
  double get_charge() const override;
  bool get_is_antiparticle() const override;
  double get_rest_mass() const override;
  double get_decay_constant() const override;
  void set_id(int id) override;
  void set_energy(double energy) override;
  void set_p_x(double p_x) override;
  void set_p_y(double p_y) override;
  void set_p_z(double p_z) override;
  void set_charge(double charge) override;
  void set_is_antiparticle(bool is_antiparticle) override;
  void set_rest_mass(double rest_mass) override;
  void set_decay_constant(double decay_constant) override;
  void dump_info() const override;

  std::string get_type() override;

  Tau();
  Tau(Tau * tau);
  Tau(Tau & tau);
};
