#pragma once
#define HADRONS_H_
//#ifndef PARTICLE_BASE_H_
#include "particle_base.h"
//#endif

class Hadron : public Particle
{

  private:

  static constexpr bool m_is_hadron {true};
  static constexpr bool m_is_lepton {false};

  static constexpr std::array<std::string_view, 3> ALLOWED_HADRON_TYPES {"meson", "baryon", "none"};

  static constexpr std::array<std::string_view, 5> ALLOWED_HADRON_NAMES {"proton", "neutron", "pion", "kaon", "exotic"};

  static constexpr double PROTON_REST_MASS {938}; // MeV
  static constexpr double NEUTRON_REST_MASS {940};
  static constexpr double CHARGED_PION_REST_MASS {140};
  static constexpr double NEUTRAL_PION_REST_MASS {135};
  static constexpr double CHARGED_KAON_REST_MASS {494};
  static constexpr double NEUTRAL_KAON_REST_MASS {498};

  static constexpr double PROTON_DECAY_CONSTANT {0}; // s^-1
  static constexpr double NEUTRON_DECAY_CONSTANT {0.00113};
  static constexpr double CHARGED_PION_DECAY_CONSTANT {38500000};
  static constexpr double NEUTRAL_PION_DECAY_CONSTANT {-1}; // So small as to be undetectable directly (c * lifetime << 1mm)
  static constexpr double CHARGED_KAON_DECAY_CONSTANT {77900000};
  static constexpr double NEUTRAL_KAON_DECAY_CONSTANT {19500000}; // We take the long-lived neutral Kaon decay constant

  std::string m_hadron_type {"none"};
  std::string m_hadron_name {"none"};

  std::unique_ptr<FourMomentum> m_four_momentum {std::make_unique<FourMomentum>()};
  double m_charge {0}; // in units of electronic charge
  bool m_is_antiparticle {false};
  double m_rest_mass {0}; // in units o
  double m_decay_constant {0};

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

  std::string get_hadron_type() const;

  void set_hadron_type(std::string type);

  std::string get_hadron_name() const;

  void set_hadron_name(std::string name);

  std::string format_hadron_name() const;


  Hadron();

  static Hadron createProton(); // Named constructor to create a Proton
  static Hadron createNeutron(); // Named constructor to create a Neutron
  static Hadron createChargedPion(); // Named constructor to create a Charged Pion
  static Hadron createNeutralPion(); // Named constructor to create a Neutral Pion
  static Hadron createChargedKaon(); // Named constructor to create a Charged Kaon
  static Hadron createNeutralKaon(); // Named constructor to create a Neutral Kaon

  Hadron(Hadron * hadron);
  Hadron(Hadron & hadron);
};
