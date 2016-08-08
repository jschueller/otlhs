//                                               -*- C++ -*-
/**
 *  @brief SpaceFillingMinDist
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
#ifndef OTLHS_SPACEFILLINGMINDIST_HXX
#define OTLHS_SPACEFILLINGMINDIST_HXX

#include "openturns/PersistentObject.hxx"
#include "SpaceFillingImplementation.hxx"

namespace OTLHS
{

/**
 * @class SpaceFillingMinDist
 *
 * This class computes minimal distance between sample points.
 */
class OTLHS_API SpaceFillingMinDist
  : public SpaceFillingImplementation
{
  CLASSNAME;

public:
  /** Default constructor */
  SpaceFillingMinDist();

  /** Virtual constructor method */
  SpaceFillingMinDist * clone() const;

  /** String converter */
  OT::String __repr__() const;

  /** Evaluate criterion on a sample */
  OT::NumericalScalar evaluate(const OT::NumericalSample& sample) const;

}; /* class SpaceFillingMinDist */

} /* namespace OTLHS */

#endif /* OTLHS_SPACEFILLINGMINDIST_HXX */
