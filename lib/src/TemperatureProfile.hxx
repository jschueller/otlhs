//                                               -*- C++ -*-
/**
 *  @file  TemperatureProfile.hxx
 *  @brief Interface class for temperature profiles
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
#ifndef OTLHS_OPTIMALTEMPERATUREPROFILE_HXX
#define OTLHS_OPTIMALTEMPERATUREPROFILE_HXX

#include "TypedInterfaceObject.hxx"
#include "TemperatureProfileImplementation.hxx"

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
