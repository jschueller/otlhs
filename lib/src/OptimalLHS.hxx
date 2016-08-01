//                                               -*- C++ -*-
/**
 *  @file  OptimalLHS.hxx
 *  @brief Interface class for algorithms generating optimized LHS
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
#ifndef OTLHS_OPTIMALLHS_HXX
#define OTLHS_OPTIMALLHS_HXX

#include "openturns/TypedInterfaceObject.hxx"
#include "OptimalLHSImplementation.hxx"

namespace OTLHS
{

/**
 * @class OptimalLHS
 *
 * OptimalLHS is some optimallhs type to illustrate how to add some classes in Open TURNS
 */
class OTLHS_API OptimalLHS
  : public OT::TypedInterfaceObject<OptimalLHSImplementation>
{
  CLASSNAME;

public:

  typedef OT::Pointer<OptimalLHSImplementation>  Implementation;

  /** Default constructor */
  OptimalLHS(const LHSDesign & lhs);

  /** Constructor with SpaceFilling argument */
  OptimalLHS(const LHSDesign & lhs, const SpaceFilling & spaceFilling);

  /** Copy constructor */
  OptimalLHS(const OptimalLHSImplementation & implementation);

  /** Constructor from implementation */
  OptimalLHS(const Implementation & p_implementation);

#ifndef SWIG
  /** Constructor from implementation pointer */
  OptimalLHS(OptimalLHSImplementation * p_implementation);
#endif


  /** LHSDesign accessor */
  LHSDesign getLHS() const;

  /** SpaceFilling accessor */
  SpaceFilling getSpaceFilling() const;

  /** The main method is generating a design */
  LHSResult generate() const;

  /** String converter */
  OT::String __repr__() const;

private:

}; /* class OptimalLHS */

} /* namespace OTLHS */

#endif /* OTLHS_OPTIMALLHS_HXX */
