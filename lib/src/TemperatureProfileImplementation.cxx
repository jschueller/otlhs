//                                               -*- C++ -*-
/**
 *  @brief TemperatureProfileImplementation
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
#include "TemperatureProfileImplementation.hxx"
#include "openturns/PersistentObjectFactory.hxx"

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(TemperatureProfileImplementation);

static const Factory<TemperatureProfileImplementation> Factory_TemperatureProfileImplementation;


/* Default constructor */
TemperatureProfileImplementation::TemperatureProfileImplementation()
  : PersistentObject()
  , T0_()
  , iMax_()
{
  // Nothing to do
}

/** Constructor with temperature T0 & iMax*/
TemperatureProfileImplementation::TemperatureProfileImplementation(const NumericalScalar T0,
                              const UnsignedInteger iMax)
  : PersistentObject()
  , T0_(T0)
  , iMax_(iMax)
{
  // Nothing to do
}

/* Virtual constructor method */
TemperatureProfileImplementation * TemperatureProfileImplementation::clone() const
{
  return new TemperatureProfileImplementation(*this);
}

/** Compute temperature T(i) */
NumericalScalar TemperatureProfileImplementation::operator()(UnsignedInteger i) const
{
  throw NotYetImplementedException(HERE); 
}

/** get T0 */
NumericalScalar TemperatureProfileImplementation::getT0() const
{
    return T0_;
}

/** get iMax */
UnsignedInteger TemperatureProfileImplementation::getIMax() const
{
    return iMax_;
}

/* String converter */
String TemperatureProfileImplementation::__repr__() const
{
  OSS oss;
  oss << "class=" << TemperatureProfileImplementation::GetClassName()
      << " name=" << getName();
  return oss;
}

/* Method save() stores the object through the StorageManager */
void TemperatureProfileImplementation::save(Advocate & adv) const
{
  PersistentObject::save( adv );
  adv.saveAttribute("T0_", T0_);
  adv.saveAttribute("iMax_", iMax_);  
}

/* Method load() reloads the object from the StorageManager */
void TemperatureProfileImplementation::load(Advocate & adv)
{
  PersistentObject::load( adv );
  adv.loadAttribute("T0_", T0_);
  adv.loadAttribute("iMax_", iMax_);  
}


} /* namespace OTLHS */
