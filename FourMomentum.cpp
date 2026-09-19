#include "FourMomentum.h"

bool validate_energy(double specified_energy)
{
  if(specified_energy >= 0)
  {
    return true;
  }
  std::cout<<"Negative or otherwise invalid energy specified for a four momentum vector."<<std::endl;
  return false;
}
bool initial_validate_four_momentum(std::vector<double> four_momentum)
{
  double invariant_mass = pow(four_momentum[0], 2) - pow(four_momentum[1], 2) - pow(four_momentum[2], 2) - pow(four_momentum[3], 2);
  if(invariant_mass < 0 || four_momentum[0] < 0)
  {
    return false;
  }
  return true;
}

FourMomentum::FourMomentum(double E, double p_x, double p_y, double p_z)
{
  //std::cout<<"FourMomentum: Parameterised constructor called"<<std::endl;
  (four_momentum)[0] = E;
  (four_momentum)[1] = p_x;
  (four_momentum)[2] = p_y;
  (four_momentum)[3] = p_z;
  if(initial_validate_four_momentum(four_momentum) == false)
  {
    std::cout<<"Negative energy or invariant mass while initialising FourMomentum!"<<std::endl;
    exit(1);
  }
}
FourMomentum::FourMomentum(const FourMomentum & other_fourmomentum)
/* Copy constructor: Copy constructor is for a = b where a is uninitialised and b is an instance of FourMomentum class and we want "a" to be a deep copy of b in attributes,
but not in memory location*/
{
  //std::cout<<"FourMomentum: Copy constructor called"<<std::endl;
  four_momentum = (other_fourmomentum.four_momentum); // assign the value behind four_momentum to "this"'s fourmomentum
}

FourMomentum& FourMomentum::operator=(const FourMomentum& other_fourmomentum) 
/* Copy assignment: Copy assignment is for a = b where both a and b are instances of FourMomentum class and we wish to make "a" a copy of b in attributes, but not in memory
locations. */
{
  //std::cout<<"FourMomentum: Copy assignment operator called"<<std::endl;
  if(this != &other_fourmomentum)
  {
    four_momentum = (other_fourmomentum.four_momentum);
  }
  return *this;
}
FourMomentum::FourMomentum(FourMomentum&& other_fourmomentum) 
/* Move constructor: Move constructor is for a(b) where a is uninitialised and b is an instance of FourMomentum class and we want "a" to be a deep copy of b
but we would also like to delete b in the process. Essentially, we are moving "b" to a different location in memory (location of "a"), hence the nomenclature. */
{
  //std::cout<<"FourMomentum: Move constructor called"<<std::endl;
  four_momentum = (other_fourmomentum.four_momentum);
}
FourMomentum& FourMomentum::operator=(FourMomentum&& other_fourmomentum) 
/* Move assignment: Move assignment is for a = b where a and b are both instances of FourMomentum class and we want "a" to be a deep copy of b
but we would also like to delete b in the process. Essentially, we are moving "b" to a different location (location of "a"), hence the nomenclature. */
{
  //std::cout<<"FourMomentum: Move assignment called"<<std::endl;
  if (this != &other_fourmomentum) // if not the exact same instance
  {
    (this->four_momentum) = (other_fourmomentum.four_momentum);
  }
  return *this;
}

double FourMomentum::get_energy() const
{
  return (four_momentum)[0];
}
double FourMomentum::get_p_x() const
{
  return (four_momentum)[1];
}
double FourMomentum::get_p_y() const
{
  return (four_momentum)[2];
}
double FourMomentum::get_p_z() const
{
  return (four_momentum)[3];
}

void FourMomentum::set_energy(double specified_energy)
{
  if(validate_energy(specified_energy) == true)
  {
    (four_momentum)[0] = specified_energy;
  }
  else
  {
    std::cout<<"Negative or invalid energy detected in set_energy(), call aborted."<<std::endl;
  }
  return;
}
void FourMomentum::set_p_x(double specified_p_x)
{
  double new_m_inv = pow(this->get_energy(), 2) - pow(specified_p_x, 2) - pow(this->get_p_y(), 2) - pow(this->get_p_z(), 2);
  if(new_m_inv < 0)
  {
    std::cout<<"Warning: Negative or invalid invariant mass detected in set_p_x()."<<std::endl;
  }
  (four_momentum)[1] = specified_p_x;
  return;
}
void FourMomentum::set_p_y(double specified_p_y)
{
  double new_m_inv = pow(this->get_energy(), 2) - pow(this->get_p_x(), 2) - pow(specified_p_y, 2) - pow(this->get_p_z(), 2);
  if(new_m_inv < 0)
  {
    std::cout<<"Warning: Negative or invalid invariant mass detected in set_p_y()."<<std::endl;
  }
  (four_momentum)[2] = specified_p_y;
  return;
}
void FourMomentum::set_p_z(double specified_p_z)
{
  double new_m_inv = pow(this->get_energy(), 2) - pow(this->get_p_x(), 2) - pow(this->get_p_y(), 2) - pow(specified_p_z, 2);
  if(new_m_inv < 0)
  {
    std::cout<<"Warning: Negative or invalid invariant mass detected in set_p_z()."<<std::endl;
  }
  (four_momentum)[3] = specified_p_z;
  return;
}
std::string FourMomentum::format_four_momentum()
{
  std::string returned_string = "(" + std::to_string(get_energy()) + ", " + std::to_string(get_p_x()) + ", " + std::to_string(get_p_y()) + ", " + std::to_string(get_p_z()) + ")";
  return returned_string;
}
double FourMomentum::operator*(const FourMomentum & other)
{
  return ((this->four_momentum)[0] * ((other.four_momentum))[0]) - ((this->four_momentum)[1] * ((other.four_momentum))[1]) - ((this->four_momentum)[2] * ((other.four_momentum))[2]) - ((this->four_momentum)[3] * (other.four_momentum)[3]);
}
FourMomentum FourMomentum::operator*(const double & factor)
{
  FourMomentum returned_four_momentum;
  returned_four_momentum = *this;

  returned_four_momentum.set_energy(returned_four_momentum.get_energy() * factor);
  returned_four_momentum.set_p_x(returned_four_momentum.get_p_x() * factor);
  returned_four_momentum.set_p_y(returned_four_momentum.get_p_y() * factor);
  returned_four_momentum.set_p_z(returned_four_momentum.get_p_z() * factor);

  return returned_four_momentum;
}
FourMomentum FourMomentum::operator+(const FourMomentum & other)
{
  FourMomentum sum_four_momentum = FourMomentum((this->four_momentum)[0] + ((other.four_momentum))[0], (this->four_momentum)[1] + ((other.four_momentum))[1], (this->four_momentum)[2] + ((other.four_momentum))[2], (this->four_momentum)[3] + ((other.four_momentum))[3]);
  return sum_four_momentum;
}
