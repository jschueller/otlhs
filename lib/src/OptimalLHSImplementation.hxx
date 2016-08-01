//                                               -*- C++ -*-
/**
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
#ifndef OTLHS_OPTIMALLHSIMPLEMENTATION_HXX
#define OTLHS_OPTIMALLHSIMPLEMENTATION_HXX

#include "openturns/PersistentObject.hxx"
#include "openturns/StorageManager.hxx"
#include "OTLHSprivate.hxx"
#include "LHSDesign.hxx"
#include "SpaceFilling.hxx"
#include "LHSResult.hxx"

namespace OTLHS
{

class LHSDesign;

/**
 * @class OptimalLHSImplementation
 *
 * OptimalLHSImplementation is some optimallhs type to illustrate how to add some classes in OpenTURNS
 */
class OTLHS_API OptimalLHSImplementation
  : public OT::PersistentObject
{
  CLASSNAME;

public:
  /** Default constructor */
  OptimalLHSImplementation(const LHSDesign & lhs);

  /** Default constructor */
  OptimalLHSImplementation(const LHSDesign & lhs, const SpaceFilling & spaceFilling);

  /** Virtual constructor method */
  OptimalLHSImplementation * clone() const;

  /** Attributes for LHSDesign */
  LHSDesign getLHS() const;

  /** Attributes for SpaceFilling */
  SpaceFilling getSpaceFilling() const;

  /** The main method is generating a design */
  virtual LHSResult generate() const;

  /** String converter */
  virtual OT::String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(OT::Advocate & adv);

protected:
   LHSDesign lhs_;
   SpaceFilling spaceFilling_;

   OptimalLHSImplementation() {};
   friend class OT::Factory<OptimalLHSImplementation>;

}; /* class OptimalLHSImplementation */

} /* namespace OTLHS */

#endif /* OTLHS_OPTIMALLHSIMPLEMENTATION_HXX */
