#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "geomVector.hh"
#include <iostream>

/*!
 * \file
 * \brief Deklaracja instacji szablonu geom::Vector
 */

 /*!
  * \brief Instacja szablonu geom::Vector<typename,int> dla przestrzeni 3D.
  */
 typedef geom::Vector<double,3>  Vector3D;

 inline std::istream& operator>>(std::istream &is, Vector3D &vec)
 {
     is >> vec[0] >> vec[1] >> vec[2];
     return is;
 }

 inline Vector3D createVector3D(double x, double y, double z)
 {
     Vector3D vec;
     vec[0] = x;
     vec[1] = y;
     vec[2] = z;
     return vec;
 }
#endif
