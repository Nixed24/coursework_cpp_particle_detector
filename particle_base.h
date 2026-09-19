#pragma once
#define PARTICLE_BASE_H_
#include<array>
#include<set>
//#ifndef FOURMOMENTUM_H_
#include "FourMomentum.h"
//#endif

class Particle // base class
{

  /* 

  PARTICLE ID'S:

  0 : Default type

  1 : Proton
  2 : Neutron
  3 : Charged Pion
  4 : Neutral Pion
  5 : Charged Kaon
  6 : Neutral Kaon
  7 : Electron
  8 : Muon
  9 : Tau
  10 : Neutrino
  11 : Photon
  12 : Exotic Hadron

  */ 

  public:

  virtual int get_id() const = 0;
  virtual FourMomentum get_four_momentum() const = 0;
  virtual double get_charge() const = 0;
  virtual bool get_is_antiparticle() const = 0;
  virtual double get_rest_mass() const = 0;
  virtual double get_decay_constant() const = 0;
  virtual void set_energy(double energy) = 0;
  virtual void set_p_x(double p_x) = 0;
  virtual void set_p_y(double p_y) = 0;
  virtual void set_p_z(double p_z) = 0;
  virtual void set_id(int id) = 0;
  virtual void set_charge(double charge) = 0;
  virtual void set_is_antiparticle(bool is_antiparticle) = 0;
  virtual void set_rest_mass(double rest_mass) = 0;
  virtual void set_decay_constant(double decay_constant) = 0;

  virtual void dump_info() const = 0;

  virtual std::string get_type() = 0;

};
