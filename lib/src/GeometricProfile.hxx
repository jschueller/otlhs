//                                               -*- C++ -*-
/**
 *  @brief GeometricProfile
 *
 *  Copyright (C) 2014 EDF
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */
#ifndef OTLHS_OPTIMALGEOMETRICPROFILE_HXX
#define OTLHS_OPTIMALGEOMETRICPROFILE_HXX

#include "TemperatureProfileImplementation.hxx"

namespace OTLHS
{

/**
 * @class GeometricProfile
 *
 * GeometricProfile is a geometric temperature profile for SimulatedAnnealing
 */
class OTLHS_API GeometricProfile
  : public TemperatureProfileImplementation
{
  CLASSNAME;

public:
  /** Default constructor */
  GeometricProfile(const OT::NumericalScalar T0=10, const OT::NumericalScalar c=0.95, const OT::UnsignedInteger iMax=2000);

  /** Virtual constructor method */
  GeometricProfile * clone() const;

  /** Compute temperature T(i) */
  OT::NumericalScalar operator()(OT::UnsignedInteger i) const;

  /** String converter */
  OT::String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv);

private:
  OT::NumericalScalar c_;
  mutable OT::NumericalScalar logc_;

}; /* class GeometricProfile */

} /* namespace OTLHS */

#endif /* OTLHS_OPTIMALGEOMETRICPROFILE_HXX */
