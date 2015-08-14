//                                               -*- C++ -*-
/**
 *  @file  TemperatureProfile.cxx
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
#include "TemperatureProfile.hxx"
#include "PersistentObjectFactory.hxx"
#include "TemperatureProfileImplementation.hxx"
#include "GeometricProfile.hxx"

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(TemperatureProfile);

/* Default constructor */
TemperatureProfile::TemperatureProfile()
  : TypedInterfaceObject<TemperatureProfileImplementation>(new GeometricProfile())
{
  // Nothing to do
}

/* Constructor from implementation */
TemperatureProfile::TemperatureProfile(const TemperatureProfileImplementation & implementation)
  : TypedInterfaceObject<TemperatureProfileImplementation>(implementation.clone())
{
  // Nothing to do
}

/* Constructor from implementation */
TemperatureProfile::TemperatureProfile(const Implementation & p_implementation)
  : TypedInterfaceObject<TemperatureProfileImplementation>(p_implementation)
{
  // Nothing to do
}

/* Constructor from implementation pointer */
TemperatureProfile::TemperatureProfile(TemperatureProfileImplementation * p_implementation)
  : TypedInterfaceObject<TemperatureProfileImplementation>(p_implementation)
{
  // Nothing to do
}

/** Compute temperature */
NumericalScalar TemperatureProfile::operator()(UnsignedInteger i) const
{
  return getImplementation()->operator()(i);
}

/** get T0 */
NumericalScalar TemperatureProfile::getT0() const
{
  return getImplementation()->getT0();
}

/** get iMax */
UnsignedInteger TemperatureProfile::getIMax() const
{
  return getImplementation()->getIMax();
}

/* String converter */
String TemperatureProfile::__repr__() const
{
  OSS oss;
  oss << "class=" << TemperatureProfile::GetClassName()
      << " implementation=" << getImplementation()->__repr__();
  return oss;
}


} /* namespace OTLHS */
