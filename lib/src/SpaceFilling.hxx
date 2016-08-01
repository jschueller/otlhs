//                                               -*- C++ -*-
/**
 *  @brief Base class for space filling criteria
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
#ifndef OTLHS_SPACEFILLING_HXX
#define OTLHS_SPACEFILLING_HXX

#include "openturns/TypedInterfaceObject.hxx"
#include "openturns/StorageManager.hxx"
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
