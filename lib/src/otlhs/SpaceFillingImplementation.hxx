//                                               -*- C++ -*-
/**
 *  @brief Abstract top-level class for all space filling criteria implementations
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
#ifndef OTLHS_SPACEFILLINGIMPLEMENTATION_HXX
#define OTLHS_SPACEFILLINGIMPLEMENTATION_HXX

#include "openturns/PersistentObject.hxx"
#include "openturns/StorageManager.hxx"
#include "openturns/NumericalSample.hxx"
#include "otlhs/OTLHSprivate.hxx"

namespace OTLHS
{

/**
 * @class SpaceFillingImplementation
 *
 * The class that implements space filling criteria.
 * This class serves an interface for derived classes.
 */
class OTLHS_API SpaceFillingImplementation
  : public OT::PersistentObject
{
  CLASSNAME;

  /* Allow OptimalLHS derived classes to call perturb method */
  friend class SpaceFilling;

public:
  /** Default constructor */
  explicit SpaceFillingImplementation(OT::Bool minimization = true);

  /** Virtual constructor method */
  SpaceFillingImplementation * clone() const;

  /** Evaluate criterion on a sample */
  virtual OT::NumericalScalar evaluate(const OT::NumericalSample& sample) const;

  /** Accessor */
  OT::Bool isMinimizationProblem() const { return minimization_; }

  /** String converter */
  virtual OT::String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv);

  /** Compute criterion when performing an elementary perturbation */
  virtual OT::NumericalScalar perturbLHS(OT::NumericalSample& oldDesign, OT::NumericalScalar oldCriterion,
      OT::UnsignedInteger row1, OT::UnsignedInteger row2, OT::UnsignedInteger column) const;

protected:
  /** Normalize argument before computing criterion */
  OT::NumericalSample normalize(const OT::NumericalSample & sample) const;


private:
  /* True if this criterion is to be minimized, false otherwise */
  OT::Bool minimization_;

}; /* class SpaceFillingImplementation */

} /* namespace OTLHS */

#endif /* OTLHS_SPACEFILLINGIMPLEMENTATION_HXX */
