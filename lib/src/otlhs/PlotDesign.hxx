//                                               -*- C++ -*-
/**
 *  @brief PlotDesign
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

#ifndef OTLHS_OPTIMALPLOTDESIGN_HXX
#define OTLHS_OPTIMALPLOTDESIGN_HXX

#include "openturns/DrawableImplementation.hxx"
#include "openturns/NumericalSample.hxx"
#include "openturns/Interval.hxx"
#include "otlhs/LHSResult.hxx"

namespace OTLHS
{

/**
 * @class PlotDesign
 *
 * PlotDesign plots data 2 by 2, using a subdivision of the figure on dxd sub-figures
 */
class  OTLHS_API PlotDesign
  : public OT::DrawableImplementation
{
  CLASSNAME;

public:
  /** Default constructor */
  PlotDesign(const OT::NumericalSample & data, const OT::Interval & bounds, 
             const OT::UnsignedInteger Nx = 0, const OT::UnsignedInteger Ny = 0,
             const OT::String & title = "LHS");

  /** Default constructor */
  PlotDesign(const LHSResult & result, const OT::UnsignedInteger Nx = 0,
             const OT::UnsignedInteger Ny = 0, const OT::String & title = "LHS");

  /** String converter */
  OT::String __repr__() const;

  /** Accessor for first coordinate */
  OT::NumericalSample getData() const;

  /** Accessor for labels */
  OT::Description getLabels() const;
  void setLabels(const OT::Description & labels);

  /** Accessor for title */
  OT::String getTitle() const;
  void setTitle(const OT::String & title);


  /** Draw method */
  OT::String draw() const;

  /** Clone method */
  virtual PlotDesign * clone() const;

  /** Build default labels */
  void buildDefaultLabels();

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() stores the object through the StorageManager */
  void load(OT::Advocate & adv);

  /** Clean all the temporary data created by draw() method */
  virtual void clean() const;

protected:
  /** Check for data validity */
  virtual void checkData(const OT::NumericalSample & data) const;

private:

  PlotDesign() {};
  friend class OT::Factory<PlotDesign>;

  /** Labels of the level sets. If none is given, it defaults to the level values. */
  OT::Description labels_;

  /** Title of the main */
  OT::String title_;

  /** Bound arguments */
  OT::Interval bounds_;
  
  /** Number of points for meshing */
  OT::UnsignedInteger Nx_;
  OT::UnsignedInteger Ny_;

}; /* class PlotDesign */

} /* namespace OTLHS */

#endif /* OTLHS_OPTIMALPLOTDESIGN_HXX */
