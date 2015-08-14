//                                               -*- C++ -*-
/**
 *  @file  SpaceFilling.hxx
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
#ifndef OTLHS_SPACEFILLING_HXX
#define OTLHS_SPACEFILLING_HXX

#include "TypedInterfaceObject.hxx"
#include "StorageManager.hxx"
#include "Pointer.hxx"
#include "SpaceFillingImplementation.hxx"

namespace OTLHS
{

/**
 * @class SpaceFilling
 *
 * SpaceFilling is some optimallhs type to illustrate how to add some classes in Open TURNS
 */
class OTLHS_API SpaceFilling
  : public OT::TypedInterfaceObject<SpaceFillingImplementation>
{
  CLASSNAME;

  /* Allow OptimalLHS derived classes to call perturb method */
  friend class OptimalLHS;
  friend class SimulatedAnnealingLHS;

public:

  typedef OT::Pointer<SpaceFillingImplementation>  Implementation;

  /** Default constructor */
  SpaceFilling();

  /** Copy constructor */
  SpaceFilling(const SpaceFillingImplementation & implementation);

  /** Constructor from implementation */
  SpaceFilling(const Implementation & p_implementation);

#ifndef SWIG
  /** Constructor from implementation pointer */
  SpaceFilling(SpaceFillingImplementation * p_implementation);
#endif


  /** Evaluate criterion on a sample */
  OT::NumericalScalar evaluate(const OT::NumericalSample & sample) const;

  /** Accessor */
  OT::Bool isMinimizationProblem() const;

  /** String converter */
  OT::String __repr__() const;

  /** Compute criterion when performing an elementary perturbation */
  OT::NumericalScalar perturbLHS(OT::NumericalSample& oldDesign, OT::NumericalScalar oldCriterion,
      OT::UnsignedInteger row1, OT::UnsignedInteger row2, OT::UnsignedInteger column) const;

}; /* class SpaceFilling */

} /* namespace OTLHS */

#endif /* OTLHS_SPACEFILLING_HXX */
