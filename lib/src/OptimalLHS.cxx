//                                               -*- C++ -*-
/**
 *  @file  OptimalLHS.cxx
 *  @brief Interface class for algorithms generating optimized LHS
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
#include "OptimalLHS.hxx"
#include "PersistentObjectFactory.hxx"
#include "OptimalLHSImplementation.hxx"
#include "SimulatedAnnealingLHS.hxx"
#include "GeometricProfile.hxx"
#include "SpaceFillingPhiP.hxx"

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
