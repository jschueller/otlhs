//                                               -*- C++ -*-
/**
 *  @brief SimulatedAnnealingLHS
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
#ifndef OTLHS_SIMULATEDANNEALINGLHS_HXX
#define OTLHS_SIMULATEDANNEALINGLHS_HXX

#include "otlhs/TemperatureProfile.hxx"
#include "otlhs/GeometricProfile.hxx"
#include "otlhs/SpaceFilling.hxx"
#include "otlhs/SpaceFillingMinDist.hxx"
#include "otlhs/OptimalLHSImplementation.hxx"

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
