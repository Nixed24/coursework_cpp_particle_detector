#include "electron.h"

int Electron::get_id() const
{
  return m_id;
}
FourMomentum Electron::get_four_momentum() const
{
  FourMomentum copied_four_momentum(*(this->m_four_momentum));
  return copied_four_momentum;
}
void Electron::set_energy(double energy)
{
  (*(this->m_four_momentum)).set_energy(energy);
  return;
}
void Electron::set_p_x(double p_x)
{
  (*(this->m_four_momentum)).set_p_x(p_x);
  return;
}
void Electron::set_p_y(double p_y)
{
  (*(this->m_four_momentum)).set_p_y(p_y);
  return;
}
void Electron::set_p_z(double p_z)
{
  (*(this->m_four_momentum)).set_p_z(p_z);
  return;
}

double Electron::get_charge() const
{
  if(m_is_antiparticle)
  {
    return -1 * m_charge;
  }
  return m_charge;
}
bool Electron::get_is_antiparticle() const
{
  return m_is_antiparticle;
}
double Electron::get_rest_mass() const
{
  return m_rest_mass;
}
double Electron::get_decay_constant() const
{
  return m_decay_constant;
}
void Electron::set_charge(double charge)
{
  if((charge * m_charge == (-1 * charge * charge)) && (charge != 0))
  {
    std::cout<<"Warning: set_charge() used to conjugate charge. Do not do this, use set_is_antiparticle(true) instead!"<<std::endl;
  }
  m_charge = charge;
  return;
}
void Electron::set_is_antiparticle(bool is_antiparticle)
{
  m_is_antiparticle = is_antiparticle;
  return;
}
void Electron::set_rest_mass(double rest_mass)
{
  if(rest_mass >= 0)
  {
    m_rest_mass = rest_mass;
    return;
  }
  std::cout<<"Warning: set_rest_mass received negative rest mass! Call aborted."<<std::endl;
}
void Electron::set_decay_constant(double decay_constant)
{
  m_decay_constant = decay_constant;
  return;
}
void Electron::set_id(int id)
{
  m_id = id;
  return;
}
std::string Electron::get_type()
{
  return "electron";
}
void Electron::dump_info() const
{
  std::cout<<"--- Electron info ---"<<std::endl;
  std::cout<<"  ID: "<<get_id()<<std::endl;
  std::cout<<"  Charge: "<<get_charge()<<std::endl;
  FourMomentum & four_momentum = *(m_four_momentum);
  std::cout<<"  Four momentum: (E, p_x, p_y, p_z) = "<<four_momentum.format_four_momentum()<<std::endl;
  std::cout<<"  Decay constant: "<<get_decay_constant()<<std::endl;
  std::cout<<"  Is anti-particle: "<<get_is_antiparticle()<<std::endl;
  std::cout<<"---------------------"<<std::endl;
  return;
}
Electron::Electron()
{
  set_id(7);
  set_rest_mass(ELECTRON_REST_MASS);
  set_charge(ELECTRON_CHARGE);
}
Electron::Electron(Electron * electron)
{
  FourMomentum copied_four_momentum = (*electron).get_four_momentum();
  set_energy(copied_four_momentum.get_energy());
  set_p_x(copied_four_momentum.get_p_x());
  set_p_y(copied_four_momentum.get_p_y());
  set_p_z(copied_four_momentum.get_p_z());
  set_id((*electron).get_id());
  set_is_antiparticle((*electron).get_is_antiparticle());
  set_charge((*electron).get_charge() * (1 - 2 * get_is_antiparticle()));
  set_rest_mass((*electron).get_rest_mass());
  set_decay_constant((*electron).get_decay_constant());
}
Electron::Electron(Electron & electron)
{
  FourMomentum copied_four_momentum = (electron).get_four_momentum();
  set_energy(copied_four_momentum.get_energy());
  set_p_x(copied_four_momentum.get_p_x());
  set_p_y(copied_four_momentum.get_p_y());
  set_p_z(copied_four_momentum.get_p_z());
  set_id((electron).get_id());
  set_is_antiparticle((electron).get_is_antiparticle());
  set_charge((electron).get_charge() * (1 - 2 * get_is_antiparticle()));
  set_rest_mass((electron).get_rest_mass());
  set_decay_constant((electron).get_decay_constant());
}
