//                                               -*- C++ -*-
/**
 *  @brief Interface class for algorithms generating optimized LHS
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
#include "otlhs/OptimalLHS.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "otlhs/OptimalLHSImplementation.hxx"
#include "otlhs/SimulatedAnnealingLHS.hxx"
#include "otlhs/GeometricProfile.hxx"
#include "otlhs/SpaceFillingPhiP.hxx"

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(OptimalLHS);

/* Default constructor */
OptimalLHS::OptimalLHS(const LHSDesign & lhs)
  : TypedInterfaceObject<OptimalLHSImplementation>(new SimulatedAnnealingLHS(lhs, GeometricProfile(), SpaceFilling()))
{
  // Nothing to do
}

/* Default constructor */
OptimalLHS::OptimalLHS(const LHSDesign & lhs, const SpaceFilling & spaceFilling)
  : TypedInterfaceObject<OptimalLHSImplementation>(new OptimalLHSImplementation(lhs, spaceFilling))
{
  // Nothing to do
}

/* Constructor from implementation */
OptimalLHS::OptimalLHS(const OptimalLHSImplementation & implementation)
  : TypedInterfaceObject<OptimalLHSImplementation>(implementation.clone())
{
  // Nothing to do
}

/* Constructor from implementation */
OptimalLHS::OptimalLHS(const Implementation & p_implementation)
  : TypedInterfaceObject<OptimalLHSImplementation>(p_implementation)
{
  // Nothing to do
}

/* Constructor from implementation pointer */
OptimalLHS::OptimalLHS(OptimalLHSImplementation * p_implementation)
  : TypedInterfaceObject<OptimalLHSImplementation>(p_implementation)
{
  // Nothing to do
}

/** Attributes for lhs */
LHSDesign OptimalLHS::getLHS() const
{
  return getImplementation()->getLHS();
}

/** Attributes for SpaceFilling */
SpaceFilling OptimalLHS::getSpaceFilling() const
{
  return getImplementation()->getSpaceFilling();
}

/* Compute the design */
LHSResult OptimalLHS::generate() const
{
  return getImplementation()->generate();
}

/* String converter */
String OptimalLHS::__repr__() const
{
  OSS oss;
  oss << "class=" << OptimalLHS::GetClassName()
      << " implementation=" << getImplementation()->__repr__();
  return oss;
}


} /* namespace OTLHS */
