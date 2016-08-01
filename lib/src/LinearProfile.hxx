//                                               -*- C++ -*-
/**
 *  @brief LinearProfile
 *
 *  Copyright 2005-2016 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef OTLHS_OPTIMALLINEARPROFILE_HXX
#define OTLHS_OPTIMALLINEARPROFILE_HXX

#include "TemperatureProfileImplementation.hxx"

namespace OTLHS
{

/**
 * @class LinearProfile
 *
 * LinearProfile is a linear temperature profile for SimulatedAnnealing
 */
class OTLHS_API LinearProfile
  : public TemperatureProfileImplementation
{
  CLASSNAME;

public:
  /** Default constructor */
  LinearProfile(const OT::NumericalScalar T0=10.0, const OT::UnsignedInteger iMax=2000);

  /** Virtual constructor method */
  LinearProfile * clone() const;

  /** Compute temperature T(i) */
  OT::NumericalScalar operator()(OT::UnsignedInteger i) const;

  /** String converter */
  OT::String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv);

private:
  mutable OT::NumericalScalar iMaxInv_;

  friend class OT::Factory<LinearProfile>;
}; /* class LinearProfile */

} /* namespace OTLHS */

#endif /* OTLHS_OPTIMALLINEARPROFILE_HXX */
