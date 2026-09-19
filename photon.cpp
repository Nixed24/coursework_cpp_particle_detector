#include "photon.h"

int Photon::get_id() const
{
  return m_id;
}
FourMomentum Photon::get_four_momentum() const
{
  FourMomentum copied_four_momentum(*(this->m_four_momentum));
  return copied_four_momentum;
}
void Photon::set_energy(double energy)
{
  (*(this->m_four_momentum)).set_energy(energy);
  return;
}
void Photon::set_p_x(double p_x)
{
  (*(this->m_four_momentum)).set_p_x(p_x);
  return;
}
void Photon::set_p_y(double p_y)
{
  (*(this->m_four_momentum)).set_p_y(p_y);
  return;
}
void Photon::set_p_z(double p_z)
{
  (*(this->m_four_momentum)).set_p_z(p_z);
  return;
}

double Photon::get_charge() const
{
  if(m_is_antiparticle)
  {
    return -1 * m_charge;
  }
  return m_charge;
}
bool Photon::get_is_antiparticle() const
{
  return m_is_antiparticle;
}
double Photon::get_rest_mass() const
{
  return m_rest_mass;
}
double Photon::get_decay_constant() const
{
  return m_decay_constant;
}
void Photon::set_charge(double charge)
{
  if((charge * m_charge == (-1 * charge * charge)) && (charge != 0))
  {
    std::cout<<"Warning: set_charge() used to conjugate charge. Do not do this, use set_is_antiparticle(true) instead!"<<std::endl;
  }
  m_charge = charge;
  return;
}
void Photon::set_is_antiparticle(bool is_antiparticle)
{
  m_is_antiparticle = is_antiparticle;
  return;
}
void Photon::set_rest_mass(double rest_mass)
{
  if(rest_mass >= 0)
  {
    m_rest_mass = rest_mass;
    return;
  }
  std::cout<<"Warning: set_rest_mass received negative rest mass! Call aborted."<<std::endl;
}
void Photon::set_decay_constant(double decay_constant)
{
  m_decay_constant = decay_constant;
  return;
}
void Photon::set_id(int id)
{
  m_id = id;
  return;
}
std::string Photon::get_type()
{
  return "photon";
}
void Photon::dump_info() const
{
  std::cout<<"--- Photon info ---"<<std::endl;
  std::cout<<"  ID: "<<get_id()<<std::endl;
  std::cout<<"  Charge: "<<get_charge()<<std::endl;
  FourMomentum & four_momentum = *(m_four_momentum);
  std::cout<<"  Four momentum: (E, p_x, p_y, p_z) = ("<<four_momentum.get_energy()<<", "<<four_momentum.get_p_x()<<", "<<four_momentum.get_p_y()<<", "<<four_momentum.get_p_z()<<")"<<std::endl;
  std::cout<<"  Decay constant: "<<get_decay_constant()<<std::endl;
  std::cout<<"---------------------"<<std::endl;
  return;
}

Photon::Photon()
{
  set_id(11);
  set_rest_mass(PHOTON_REST_MASS);
  set_charge(PHOTON_CHARGE);
}
Photon::Photon(Photon * photon)
{
  FourMomentum copied_four_momentum = (*photon).get_four_momentum();
  set_energy(copied_four_momentum.get_energy());
  set_p_x(copied_four_momentum.get_p_x());
  set_p_y(copied_four_momentum.get_p_y());
  set_p_z(copied_four_momentum.get_p_z());
  set_id((*photon).get_id());
  set_is_antiparticle((*photon).get_is_antiparticle());
  set_charge((*photon).get_charge() * (1 - 2 * get_is_antiparticle()));
  set_rest_mass((*photon).get_rest_mass());
  set_decay_constant((*photon).get_decay_constant());
}
Photon::Photon(Photon & photon)
{
  FourMomentum copied_four_momentum = (photon).get_four_momentum();
  set_energy(copied_four_momentum.get_energy());
  set_p_x(copied_four_momentum.get_p_x());
  set_p_y(copied_four_momentum.get_p_y());
  set_p_z(copied_four_momentum.get_p_z());
  set_id((photon).get_id());
  set_is_antiparticle((photon).get_is_antiparticle());
  set_charge((photon).get_charge() * (1 - 2 * get_is_antiparticle()));
  set_rest_mass((photon).get_rest_mass());
  set_decay_constant((photon).get_decay_constant());
}
