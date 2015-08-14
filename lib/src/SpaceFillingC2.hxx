//                                               -*- C++ -*-
/**
 *  @file  SpaceFillingC2.hxx
 *  @brief Space filling criterion based on centered L2-discrepancy
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
#ifndef OTLHS_SPACEFILLINGC2_HXX
#define OTLHS_SPACEFILLINGC2_HXX

#include "SpaceFillingImplementation.hxx"

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
