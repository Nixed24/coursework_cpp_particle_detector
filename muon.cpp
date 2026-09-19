#include "muon.h"

int Muon::get_id() const
{
  return m_id;
}
FourMomentum Muon::get_four_momentum() const
{
  FourMomentum copied_four_momentum(*(this->m_four_momentum));
  return copied_four_momentum;
}
void Muon::set_energy(double energy)
{
  (*(this->m_four_momentum)).set_energy(energy);
  return;
}
void Muon::set_p_x(double p_x)
{
  (*(this->m_four_momentum)).set_p_x(p_x);
  return;
}
void Muon::set_p_y(double p_y)
{
  (*(this->m_four_momentum)).set_p_y(p_y);
  return;
}
void Muon::set_p_z(double p_z)
{
  (*(this->m_four_momentum)).set_p_z(p_z);
  return;
}

double Muon::get_charge() const
{
  if(m_is_antiparticle)
  {
    return -1 * m_charge;
  }
  return m_charge;
}
bool Muon::get_is_antiparticle() const
{
  return m_is_antiparticle;
}
double Muon::get_rest_mass() const
{
  return m_rest_mass;
}
double Muon::get_decay_constant() const
{
  return m_decay_constant;
}
void Muon::set_charge(double charge)
{
  if((charge * m_charge == (-1 * charge * charge)) && (charge != 0))
  {
    std::cout<<"Warning: set_charge() used to conjugate charge. Do not do this, use set_is_antiparticle(true) instead!"<<std::endl;
  }
  m_charge = charge;
  return;
}
void Muon::set_is_antiparticle(bool is_antiparticle)
{
  m_is_antiparticle = is_antiparticle;
  return;
}
void Muon::set_rest_mass(double rest_mass)
{
  if(rest_mass >= 0)
  {
    m_rest_mass = rest_mass;
    return;
  }
  std::cout<<"Warning: set_rest_mass received negative rest mass! Call aborted."<<std::endl;
}
void Muon::set_decay_constant(double decay_constant)
{
  m_decay_constant = decay_constant;
  return;
}
void Muon::set_id(int id)
{
  m_id = id;
  return;
}
std::string Muon::get_type()
{
  return "muon";
}
void Muon::dump_info() const
{
  std::cout<<"--- Muon info ---"<<std::endl;
  std::cout<<"  ID: "<<get_id()<<std::endl;
  std::cout<<"  Charge: "<<get_charge()<<std::endl;
  FourMomentum & four_momentum = *(m_four_momentum);
  std::cout<<"  Four momentum: (E, p_x, p_y, p_z) = "<<four_momentum.format_four_momentum()<<std::endl;
  std::cout<<"  Decay constant: "<<get_decay_constant()<<std::endl;
  std::cout<<"  Is anti-particle: "<<get_is_antiparticle()<<std::endl;
  std::cout<<"---------------------"<<std::endl;
  return;
}
Muon::Muon()
{
  set_id(8);
  set_rest_mass(MUON_REST_MASS);
  set_charge(MUON_CHARGE);
  set_decay_constant(MUON_DECAY_CONSTANT);
}
Muon::Muon(Muon * muon)
{
  FourMomentum copied_four_momentum = (*muon).get_four_momentum();
  set_energy(copied_four_momentum.get_energy());
  set_p_x(copied_four_momentum.get_p_x());
  set_p_y(copied_four_momentum.get_p_y());
  set_p_z(copied_four_momentum.get_p_z());
  set_id((*muon).get_id());
  set_charge((*muon).get_charge());
  set_is_antiparticle((*muon).get_is_antiparticle());
  set_rest_mass((*muon).get_rest_mass());
  set_decay_constant((*muon).get_decay_constant());
}
Muon::Muon(Muon & muon)
{
  FourMomentum copied_four_momentum = (muon).get_four_momentum();
  set_energy(copied_four_momentum.get_energy());
  set_p_x(copied_four_momentum.get_p_x());
  set_p_y(copied_four_momentum.get_p_y());
  set_p_z(copied_four_momentum.get_p_z());
  set_id((muon).get_id());
  set_is_antiparticle((muon).get_is_antiparticle());
  set_charge((muon).get_charge() * (1 - 2 * get_is_antiparticle()));
  set_rest_mass((muon).get_rest_mass());
  set_decay_constant((muon).get_decay_constant());
}
