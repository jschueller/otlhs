//                                               -*- C++ -*-
/**
 *  @brief Interface class for temperature profiles
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
#ifndef OTLHS_OPTIMALTEMPERATUREPROFILE_HXX
#define OTLHS_OPTIMALTEMPERATUREPROFILE_HXX

#include "openturns/TypedInterfaceObject.hxx"
#include "otlhs/TemperatureProfileImplementation.hxx"

namespace OTLHS
{

/**
 * @class TemperatureProfile
 *
 * TemperatureProfile is the interface class for temperature profile computation for SimulatedAnnealing
 */
class OTLHS_API TemperatureProfile
  : public OT::TypedInterfaceObject<TemperatureProfileImplementation>
{
  CLASSNAME;

public:

  typedef OT::Pointer<TemperatureProfileImplementation>  Implementation;

  /** Default constructor */
  TemperatureProfile();

  /** Copy constructor */
  TemperatureProfile(const TemperatureProfileImplementation & implementation);

  /** Constructor from implementation */
  TemperatureProfile(const Implementation & p_implementation);

#ifndef SWIG
  /** Constructor from implementation pointer */
  TemperatureProfile(TemperatureProfileImplementation * p_implementation);
#endif

  /** Compute temperature */
  OT::NumericalScalar operator()(OT::UnsignedInteger i) const;

  /** get T0 */
  OT::NumericalScalar getT0() const;

  /** get iMax */
  OT::UnsignedInteger getIMax() const;

  /** String converter */
  OT::String __repr__() const;

private:

}; /* class TemperatureProfile */

} /* namespace OTLHS */

#endif /* OTLHS_OPTIMALTEMPERATUREPROFILE_HXX */
