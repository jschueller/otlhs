//                                               -*- C++ -*-
/**
 *  @file  SpaceFillingMinDist.hxx
 *  @brief SpaceFillingMinDist
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
#ifndef OTLHS_SPACEFILLINGMINDIST_HXX
#define OTLHS_SPACEFILLINGMINDIST_HXX

#include "PersistentObject.hxx"
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
