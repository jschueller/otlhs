//                                               -*- C++ -*-
/**
 *  @file  LHSDesign.hxx
 *  @brief LHSDesign
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
#ifndef OTLHS_LHSDESIGN_HXX
#define OTLHS_LHSDESIGN_HXX

#include "StorageManager.hxx"
#include "Interval.hxx"
#include "OTLHSprivate.hxx"
#include "NumericalSample.hxx"

namespace OTLHS
{

/**
 * @class LHSDesign
 *
 * LHSDesign generate random or centered LHS samples considering independent uniform distibutions
 */
class OTLHS_API LHSDesign
  : public OT::PersistentObject
{
  CLASSNAME;

public:
  /** Default constructor */
  LHSDesign();

  /* Constructor*/
  LHSDesign(const OT::Interval & bounds, const OT::UnsignedInteger size, const OT::Bool centeredDesign=false);

  /** Virtual constructor method */
  LHSDesign * clone() const;

  /** Attributes for bounds, size, centeredDesign */
  OT::Interval getBounds() const;
  OT::UnsignedInteger getSize() const;
  OT::Bool isCenteredDesign() const;

  /** The main method is generating a design */
  OT::NumericalSample generate() const;
  
  /** String converter */
  virtual OT::String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(OT::Advocate & adv);

private:
   OT::Interval bounds_;
   OT::UnsignedInteger size_;
   OT::Bool centeredDesign_;

}; /* class LHSDesign */

} /* namespace OTLHS */

#endif /* OTLHS_LHSDESIGN_HXX */