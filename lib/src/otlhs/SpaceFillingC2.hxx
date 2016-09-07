//                                               -*- C++ -*-
/**
 *  @brief Space filling criterion based on centered L2-discrepancy
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
#ifndef OTLHS_SPACEFILLINGC2_HXX
#define OTLHS_SPACEFILLINGC2_HXX

#include "otlhs/SpaceFillingImplementation.hxx"

namespace OTLHS
{

/**
 * @class SpaceFillingC2
 *
 * This class computes centered L2-discrepancy of samples.
 */
class OTLHS_API SpaceFillingC2
  : public SpaceFillingImplementation
{
  CLASSNAME;

public:
  /** Default constructor */
  SpaceFillingC2();

  /** Virtual constructor method */
  SpaceFillingC2 * clone() const;

  /** Evaluate criterion on a sample */
  OT::NumericalScalar evaluate(const OT::NumericalSample& sample) const;

  /** String converter */
  OT::String __repr__() const;

  /** Compute criterion when performing an elementary perturbation */
  OT::NumericalScalar perturbLHS(OT::NumericalSample& oldDesign, OT::NumericalScalar oldCriterion,
      OT::UnsignedInteger row1, OT::UnsignedInteger row2, OT::UnsignedInteger column) const;

private:

}; /* class SpaceFillingC2 */

} /* namespace OTLHS */

#endif /* OTLHS_SPACEFILLINGC2_HXX */
