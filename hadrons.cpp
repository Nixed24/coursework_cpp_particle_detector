#include "hadrons.h"

int Hadron::get_id() const
{
  return m_id;
}
FourMomentum Hadron::get_four_momentum() const
{
  FourMomentum copied_four_momentum(*(this->m_four_momentum));
  return copied_four_momentum;
}
void Hadron::set_energy(double energy)
{
  (*(this->m_four_momentum)).set_energy(energy);
  return;
}
void Hadron::set_p_x(double p_x)
{
  (*(this->m_four_momentum)).set_p_x(p_x);
  return;
}
void Hadron::set_p_y(double p_y)
{
  (*(this->m_four_momentum)).set_p_y(p_y);
  return;
}
void Hadron::set_p_z(double p_z)
{
  (*(this->m_four_momentum)).set_p_z(p_z);
  return;
}

double Hadron::get_charge() const
{
  if(m_is_antiparticle)
  {
    return -1 * m_charge;
  }
  return m_charge;
}
bool Hadron::get_is_antiparticle() const
{
  return m_is_antiparticle;
}
double Hadron::get_rest_mass() const
{
  return m_rest_mass;
}
double Hadron::get_decay_constant() const
{
  return m_decay_constant;
}
void Hadron::set_charge(double charge)
{
  if((charge * m_charge == (-1 * charge * charge)) && (charge != 0))
  {
    std::cout<<"Warning: set_charge() used to conjugate charge. Do not do this, use set_is_antiparticle(true) instead!"<<std::endl;
  }
  m_charge = charge;
  return;
}
void Hadron::set_is_antiparticle(bool is_antiparticle)
{
  m_is_antiparticle = is_antiparticle;
  return;
}
void Hadron::set_rest_mass(double rest_mass)
{
  if(rest_mass >= 0)
  {
    m_rest_mass = rest_mass;
    return;
  }
  std::cout<<"Warning: set_rest_mass received negative rest mass! Call aborted."<<std::endl;
}
void Hadron::set_decay_constant(double decay_constant)
{
  m_decay_constant = decay_constant;
  return;
}
void Hadron::set_id(int id)
{
  m_id = id;
  return;
}
void Hadron::dump_info() const
{
  std::cout<<"--- Hadron info ---"<<std::endl;
  std::cout<<"  Type: "<<get_hadron_type()<<std::endl;
  std::cout<<"  Formatted name: "<<format_hadron_name()<<std::endl;
  std::cout<<"  Charge: "<<get_charge()<<std::endl;
  std::cout<<"  Is antiparticle: "<<get_is_antiparticle()<<std::endl;
  FourMomentum & four_momentum = *(m_four_momentum);
  std::cout<<"  Four momentum: (E, p_x, p_y, p_z) = "<<four_momentum.format_four_momentum()<<std::endl;
  std::cout<<"  Decay constant: "<<get_decay_constant()<<std::endl;
  std::cout<<"  ID: "<<get_id()<<std::endl;
  std::cout<<"---------------------"<<std::endl;
  return;
}
std::string Hadron::get_type()
{
  return format_hadron_name();
}

std::string Hadron::get_hadron_name() const
{
  return m_hadron_name;
}
void Hadron::set_hadron_name(std::string name)
{
  for(auto it = ALLOWED_HADRON_NAMES.begin(); it != ALLOWED_HADRON_NAMES.end(); ++it)
  {
    if(*it == name)
    {
      m_hadron_name = name;
      return;
    }
  }
  std::cout<<"Unrecognised hadron name: '"<<name<<"'"<<std::endl;
}

std::string Hadron::get_hadron_type() const
{
  return m_hadron_type;
}
void Hadron::set_hadron_type(std::string type)
{
  for(auto it = ALLOWED_HADRON_TYPES.begin(); it != ALLOWED_HADRON_TYPES.end(); ++it)
  {
    if(*it == type)
    {
      m_hadron_type = type;
      return;
    }
  }
  std::cout<<"Unrecognised hadron type: '"<<type<<"'"<<std::endl;
}

std::string Hadron::format_hadron_name() const
{
  std::string type_string = get_hadron_type();
  std::string anti_string = "";
  std::string name_string = get_hadron_name();

  if(m_is_antiparticle == true)
  {
    anti_string = "anti-";
  }
  if(name_string == "exotic")
  {
    return (name_string + " " + anti_string + type_string); // e.g (exotic anti-baryon)
  }
  return (anti_string + name_string);
}

Hadron::Hadron()
{
  set_hadron_name("exotic");
  set_id(12); // Exotic hadron: Let the user do everything else
}

Hadron Hadron::createProton() // Named constructor to create a Proton
{
  Hadron returned_hadron = Hadron();
  returned_hadron.set_id(1);
  returned_hadron.set_charge(1);
  returned_hadron.set_rest_mass(PROTON_REST_MASS);
  returned_hadron.set_decay_constant(PROTON_DECAY_CONSTANT);
  returned_hadron.set_hadron_type("baryon");
  returned_hadron.set_hadron_name("proton");
  return returned_hadron;
}
Hadron Hadron::createNeutron() // Named constructor to create a Neutron
{
  Hadron returned_hadron = Hadron();
  returned_hadron.set_id(2);
  returned_hadron.set_charge(0);
  returned_hadron.set_rest_mass(NEUTRON_REST_MASS);
  returned_hadron.set_decay_constant(NEUTRON_DECAY_CONSTANT);
  returned_hadron.set_hadron_type("baryon");
  returned_hadron.set_hadron_name("neutron");
  return returned_hadron;
}
Hadron Hadron::createChargedPion() // Named constructor to create a Charged Pion
{
  Hadron returned_hadron = Hadron();
  returned_hadron.set_id(3);
  returned_hadron.set_charge(1);
  returned_hadron.set_rest_mass(CHARGED_PION_REST_MASS);
  returned_hadron.set_decay_constant(CHARGED_PION_DECAY_CONSTANT);
  returned_hadron.set_hadron_type("meson");
  returned_hadron.set_hadron_name("pion");
  return returned_hadron;
}
Hadron Hadron::createNeutralPion() // Named constructor to create a Neutral Pion
{
  Hadron returned_hadron = Hadron();
  returned_hadron.set_id(4);
  returned_hadron.set_charge(0);
  returned_hadron.set_rest_mass(NEUTRAL_PION_REST_MASS);
  returned_hadron.set_decay_constant(NEUTRAL_PION_DECAY_CONSTANT);
  returned_hadron.set_hadron_type("meson");
  returned_hadron.set_hadron_name("pion");
  return returned_hadron;
}
Hadron Hadron::createChargedKaon() // Named constructor to create a Charged Kaon
{
  Hadron returned_hadron = Hadron();
  returned_hadron.set_id(5);
  returned_hadron.set_charge(1);
  returned_hadron.set_rest_mass(CHARGED_KAON_REST_MASS);
  returned_hadron.set_decay_constant(CHARGED_KAON_DECAY_CONSTANT);
  returned_hadron.set_hadron_type("meson");
  returned_hadron.set_hadron_name("kaon");
  return returned_hadron;
}
Hadron Hadron::createNeutralKaon() // Named constructor to create a Neutral Kaon
{
  Hadron returned_hadron = Hadron();
  returned_hadron.set_id(6);
  returned_hadron.set_charge(0);
  returned_hadron.set_rest_mass(NEUTRAL_KAON_REST_MASS);
  returned_hadron.set_decay_constant(NEUTRAL_KAON_DECAY_CONSTANT);
  returned_hadron.set_hadron_type("meson");
  returned_hadron.set_hadron_name("kaon");
  return returned_hadron;
}

Hadron::Hadron(Hadron * hadron)
{
  FourMomentum copied_four_momentum = (*hadron).get_four_momentum();
  set_energy(copied_four_momentum.get_energy());
  set_p_x(copied_four_momentum.get_p_x());
  set_p_y(copied_four_momentum.get_p_y());
  set_p_z(copied_four_momentum.get_p_z());
  set_id((*hadron).get_id());
  set_is_antiparticle((*hadron).get_is_antiparticle());
  set_charge((*hadron).get_charge() * (1 - 2 * get_is_antiparticle()));
  set_rest_mass((*hadron).get_rest_mass());
  set_decay_constant((*hadron).get_decay_constant());
  set_hadron_type((*hadron).get_hadron_type());
  set_hadron_name((*hadron).get_hadron_name());
}
Hadron::Hadron(Hadron & hadron)
{
  FourMomentum copied_four_momentum = (hadron).get_four_momentum();
  set_energy(copied_four_momentum.get_energy());
  set_p_x(copied_four_momentum.get_p_x());
  set_p_y(copied_four_momentum.get_p_y());
  set_p_z(copied_four_momentum.get_p_z());
  set_id((hadron).get_id());
  set_is_antiparticle((hadron).get_is_antiparticle());
  set_charge((hadron).get_charge() * (1 - 2 * get_is_antiparticle()));
  set_rest_mass((hadron).get_rest_mass());
  set_decay_constant((hadron).get_decay_constant());
  set_hadron_type((hadron).get_hadron_type());
  set_hadron_name((hadron).get_hadron_name());
}
