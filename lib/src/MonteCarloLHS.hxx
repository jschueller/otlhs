//                                               -*- C++ -*-
/**
 *  @brief MonteCarloLHS
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
#ifndef OTLHS_MONTECARLOLHS_HXX
#define OTLHS_MONTECARLOLHS_HXX

#include "openturns/PersistentObject.hxx"
#include "openturns/StorageManager.hxx"
#include "SpaceFilling.hxx"
#include "OptimalLHSImplementation.hxx"
#include "LHSDesign.hxx"
#include "SpaceFillingMinDist.hxx"

namespace OTLHS
{

/**
 * @class MonteCarloLHS
 *
 * MonteCarloLHS is the algorithm used for LHS optimisation (Random Brute Force)
 */
class OTLHS_API MonteCarloLHS
  : public OptimalLHSImplementation
{
  CLASSNAME;

public:

  /** Default constructor */
  MonteCarloLHS(const LHSDesign & lhs, const OT::UnsignedInteger N, const SpaceFilling & spaceFilling = SpaceFillingMinDist());

  /** Virtual constructor method */
  MonteCarloLHS * clone() const;

  /** Compute next design method **/
  LHSResult generate() const;

  /** String converter */
  OT::String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(OT::Advocate & adv);

private:
   OT::UnsignedInteger N_;
   MonteCarloLHS() {};
   friend class OT::Factory<MonteCarloLHS>;
}; /* class MonteCarloLHS */

} /* namespace OTLHS */

#endif /* OTLHS_MONTECARLOLHS_HXX */
