//                                               -*- C++ -*-
/**
 *  @file  SpaceFilling.cxx
 *  @brief Base class for space filling criteria
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
#include "SpaceFilling.hxx"
#include "PersistentObjectFactory.hxx"
#include "SpaceFillingImplementation.hxx"
#include "SpaceFillingPhiP.hxx"

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(SpaceFilling);

/* Default constructor */
SpaceFilling::SpaceFilling()
  : TypedInterfaceObject<SpaceFillingImplementation>(new SpaceFillingPhiP())
{
  // Nothing to do
}

/* Constructor from implementation */
SpaceFilling::SpaceFilling(const SpaceFillingImplementation & implementation)
  : TypedInterfaceObject<SpaceFillingImplementation>(implementation.clone())
{
  // Nothing to do
}

/* Constructor from implementation */
SpaceFilling::SpaceFilling(const Implementation & p_implementation)
  : TypedInterfaceObject<SpaceFillingImplementation>(p_implementation)
{
  // Nothing to do
}

/* Constructor from implementation pointer */
SpaceFilling::SpaceFilling(SpaceFillingImplementation * p_implementation)
  : TypedInterfaceObject<SpaceFillingImplementation>(p_implementation)
{
  // Nothing to do
}

/** Evaluate criterion on a sample */
NumericalScalar SpaceFilling::evaluate(const NumericalSample & sample) const
{
  return getImplementation()->evaluate(sample);
}

/** Compute criterion when performing an elementary perturbation */
NumericalScalar SpaceFilling::perturbLHS(NumericalSample& oldDesign, OT::NumericalScalar oldCriterion,
    UnsignedInteger row1, UnsignedInteger row2, UnsignedInteger column) const
{
  return getImplementation()->perturbLHS(oldDesign, oldCriterion, row1, row2, column);
}

/** Accessor */
Bool SpaceFilling::isMinimizationProblem() const
{
  return getImplementation()->isMinimizationProblem();
}

/* String converter */
String SpaceFilling::__repr__() const
{
  OSS oss;
  oss << "class=" << SpaceFilling::GetClassName()
      << " implementation=" << getImplementation()->__repr__();
  return oss;
}


} /* namespace OTLHS */
