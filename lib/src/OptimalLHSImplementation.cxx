//                                               -*- C++ -*-
/**
 *  @file  OptimalLHSImplementation.cxx
 *  @brief Abstract class for algorithms generating optimized LHS
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
#include "OptimalLHSImplementation.hxx"
#include "PersistentObjectFactory.hxx"
#include "LHSDesign.hxx"

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(OptimalLHSImplementation);

static Factory<OptimalLHSImplementation> RegisteredFactory;


/* Default constructor */
OptimalLHSImplementation::OptimalLHSImplementation(const LHSDesign & lhs)
  : PersistentObject(),
    lhs_(lhs),
    spaceFilling_()
{
  // Nothing to do
}

/* Default constructor */
OptimalLHSImplementation::OptimalLHSImplementation(const LHSDesign & lhs, const SpaceFilling & spaceFilling)
  : PersistentObject(),
    lhs_(lhs),
    spaceFilling_(spaceFilling)
{
  // Nothing to do
}

/* Virtual constructor method */
OptimalLHSImplementation * OptimalLHSImplementation::clone() const
{
  return new OptimalLHSImplementation(*this);
}

/** Attributes for dimension, size, randomDesign */
LHSDesign OptimalLHSImplementation::getLHS() const
{
  return lhs_;
}

/** Attributes for SpaceFilling */
SpaceFilling OptimalLHSImplementation::getSpaceFilling() const
{
  return spaceFilling_;
}

/** The main method is generating a design */
LHSResult OptimalLHSImplementation::generate() const
{
  throw NotYetImplementedException(HERE);
}

/* String converter */
String OptimalLHSImplementation::__repr__() const
{
  OSS oss;
  oss << "class=" << OptimalLHSImplementation::GetClassName()
      << " name=" << getName()
      << " lhs=" << lhs_
      << " spaceFilling=" << spaceFilling_;
  return oss;
}

/* Method save() stores the object through the StorageManager */
void OptimalLHSImplementation::save(Advocate & adv) const
{
  PersistentObject::save( adv );
  adv.saveAttribute("lhs_", lhs_);
  adv.saveAttribute("spaceFilling_", spaceFilling_);
}

/* Method load() reloads the object from the StorageManager */
void OptimalLHSImplementation::load(Advocate & adv)
{
  PersistentObject::load( adv );
  adv.loadAttribute("lhs_", lhs_);
  adv.loadAttribute("spaceFilling_", spaceFilling_);
}


} /* namespace OTLHS */
