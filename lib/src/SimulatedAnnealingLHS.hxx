//                                               -*- C++ -*-
/**
 *  @file  SimulatedAnnealingLHS.hxx
 *  @brief SimulatedAnnealingLHS
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
#ifndef OTLHS_SIMULATEDANNEALINGLHS_HXX
#define OTLHS_SIMULATEDANNEALINGLHS_HXX

#include "TemperatureProfile.hxx"
#include "GeometricProfile.hxx"
#include "SpaceFilling.hxx"
#include "SpaceFillingMinDist.hxx"
#include "OptimalLHSImplementation.hxx"

namespace OTLHS
{

/**
 * @class SimulatedAnnealingLHS
 *
 * SimulatedAnnealingLHS is the algorithm used for LHS optimisation
 */
class OTLHS_API SimulatedAnnealingLHS
  : public OptimalLHSImplementation
{
  CLASSNAME;

public:
  
  typedef OT::Collection<LHSResult> LHSResultCollection;

  /** SimulatedAnnealingLHS */
  SimulatedAnnealingLHS(const LHSDesign & lhs, const TemperatureProfile & profile = GeometricProfile(), const SpaceFilling & spaceFilling = SpaceFillingMinDist());

  /** SimulatedAnnealingLHS constructor with LHS*/
  SimulatedAnnealingLHS(const OT::NumericalSample & initialDesign, OT::Interval & bounds,
                        const TemperatureProfile & profile, const SpaceFilling & spaceFilling);

  /** Virtual constructor method */
  SimulatedAnnealingLHS * clone() const;

  /** Compute design method **/
  LHSResult generate(OT::UnsignedInteger nRestart = 0) const;

  /** String converter */
  OT::String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(OT::Advocate & adv);

protected:
  SimulatedAnnealingLHS() {};
  friend class OT::Factory<SimulatedAnnealingLHS>;
  
private:
   TemperatureProfile profile_;
   OT::NumericalSample initialDesign_;
   OT::Interval bounds_;

}; /* class SimulatedAnnealingLHS */

} /* namespace OTLHS */

#endif /* OTLHS_SIMULATEDANNEALINGLHS_HXX */
