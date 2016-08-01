//                                               -*- C++ -*-
/**
 *  @brief TemperatureProfileImplementation
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
#ifndef OTLHS_OPTIMALTEMPERATUREPROFILEIMPLEMENTATION_HXX
#define OTLHS_OPTIMALTEMPERATUREPROFILEIMPLEMENTATION_HXX

#include "openturns/PersistentObject.hxx"
#include "openturns/StorageManager.hxx"
#include "OTLHSprivate.hxx"

namespace OTLHS
{

/**
 * @class TemperatureProfileImplementation
 *
 * TemperatureProfileImplementation is a generic temperature profile for SimulatedAnnealing
 */
class OTLHS_API TemperatureProfileImplementation
  : public OT::PersistentObject
{
  CLASSNAME;

public:
  /** Default constructor */
  TemperatureProfileImplementation();

  /** Constructor with temperature T0 & iMax*/
  TemperatureProfileImplementation(const OT::NumericalScalar T0,
                              const OT::UnsignedInteger iMax);

  /** Virtual constructor method */
  TemperatureProfileImplementation * clone() const;

  /** Compute temperature T(i) */
  virtual OT::NumericalScalar operator()(OT::UnsignedInteger i) const;

  /** get T0 */
  virtual OT::NumericalScalar getT0() const;

  /** get iMax */
  virtual OT::UnsignedInteger getIMax() const;
  
  /** String converter */
  virtual OT::String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(OT::Advocate & adv);

protected:
    OT::NumericalScalar T0_;
    OT::UnsignedInteger iMax_;

}; /* class TemperatureProfileImplementation */

} /* namespace OTLHS */

#endif /* OTLHS_OPTIMALTEMPERATUREPROFILEIMPLEMENTATION_HXX */
