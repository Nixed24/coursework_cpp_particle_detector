#pragma once
#define FOURMOMENTUM_H_
#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<cmath>

class FourMomentum
{
  private:

  std::vector<double> four_momentum {0,0,0,0};
  
  public:

  double get_energy() const;
  double get_p_x() const;
  double get_p_y() const;
  double get_p_z() const;
  void set_energy(double specified_energy);
  void set_p_x(double specified_p_x);
  void set_p_y(double specified_p_y);
  void set_p_z(double specified_p_z);
  std::string format_four_momentum();

  FourMomentum() = default;

  FourMomentum(double E, double p_x, double p_y, double p_z);
  
  FourMomentum(const FourMomentum& other_fourmomentum);
  
  FourMomentum& operator=(const FourMomentum& other_fourmomentum);

  ~FourMomentum()
  {
    //std::cout<<"FourMomentum: Destructor called"<<std::endl;
  }

  FourMomentum(FourMomentum&& other_fourmomentum);

  FourMomentum& operator=(FourMomentum&& other_fourmomentum);

  double operator*(const FourMomentum & other);
  FourMomentum operator*(const double & factor);
  FourMomentum operator+(const FourMomentum & other);

};
