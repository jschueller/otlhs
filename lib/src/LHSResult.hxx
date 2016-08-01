//                                               -*- C++ -*-
/**
 *  @brief LHSResult
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
#ifndef OTLHS_LHSRESULT_HXX
#define OTLHS_LHSRESULT_HXX

#include "openturns/PersistentObject.hxx"
#include "openturns/StorageManager.hxx"
#include "OTLHSprivate.hxx"
#include "SpaceFilling.hxx"
#include "LHSResult.hxx"
#include "openturns/PersistentCollection.hxx"
#include "openturns/NumericalSample.hxx"
#include "openturns/Interval.hxx"
#include "openturns/Graph.hxx"

namespace OTLHS
{

/**
 * @class LHSResult
 *
 * LHSResult is the interface class for temperature profile computation for SimulatedAnnealing
 */
class OTLHS_API LHSResult
  : public OT::PersistentObject
{
  CLASSNAME;

public:

  typedef OT::PersistentCollection<OT::NumericalSample> NumericalSamplePersistentCollection;

  /** Default constructor */
  LHSResult();

  /** Default constructor */
  LHSResult(const OT::Interval & bounds, const OTLHS::SpaceFilling & spaceFilling, OT::UnsignedInteger restart = 0);

  /** Virtual constructor */
  virtual LHSResult * clone() const;

  /** Accessors */
  OT::Interval getBounds() const;
  OT::UnsignedInteger getNumberOfRestarts() const;

  /** Attributes for getting elements of result */
  OT::NumericalSample getOptimalDesign() const;
  OT::NumericalSample getOptimalDesign(OT::UnsignedInteger restart) const;
  OT::NumericalScalar getOptimalValue() const;
  OT::NumericalScalar getOptimalValue(OT::UnsignedInteger restart) const;
  OT::NumericalSample getAlgoHistory() const;
  OT::NumericalSample getAlgoHistory(OT::UnsignedInteger restart) const;
  OT::NumericalScalar getC2() const;
  OT::NumericalScalar getC2(OT::UnsignedInteger restart) const;
  OT::NumericalScalar getPhiP() const;
  OT::NumericalScalar getPhiP(OT::UnsignedInteger restart) const;
  OT::NumericalScalar getMinDist() const;
  OT::NumericalScalar getMinDist(OT::UnsignedInteger restart) const;

  /** Graphical methods - Draw criterion history */
  OT::Graph drawHistoryCriterion(const OT::String & title = "") const;
  OT::Graph drawHistoryCriterion(OT::UnsignedInteger restart, const OT::String & title = "") const;
  OT::Graph drawHistoryProbability(const OT::String & title = "") const;
  OT::Graph drawHistoryProbability(OT::UnsignedInteger restart, const OT::String & title = "") const;
  OT::Graph drawHistoryTemperature(const OT::String & title = "") const;
  OT::Graph drawHistoryTemperature(OT::UnsignedInteger restart, const OT::String & title = "") const;

  /** Add an optimal design with its history */
  void add(const OT::NumericalSample & optimalDesign, OT::NumericalScalar criterion,
           OT::NumericalScalar C2, OT::NumericalScalar PhiP, OT::NumericalScalar MinDist,
           const OT::NumericalSample & algoHistory);

  /** String converter */
  OT::String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv);

private:
  /** Method that draw data */
  OT::Graph drawCurveData(const OT::NumericalSample & data, const OT::String & title) const;

  /** Method to extract field index from data */
  OT::UnsignedInteger findDescription(const char *text) const;

private:
  /** Bounds */
  OT::Interval bounds_;

  /** Space filling criterion */
  SpaceFilling spaceFilling_;

  /** Number of restarts */
  OT::UnsignedInteger restart_;

  /** Best criterion value */
  mutable OT::NumericalScalar optimalCriterion_;

  /** Index of the best designs in all restarts */
  mutable OT::UnsignedInteger optimalIndex_;

  /** Collection of best designs (size 1+restart_)*/
  NumericalSamplePersistentCollection collDesigns_;

  /** Collection of algo histories (size 1+restart_, dimension depending on algorithm)*/
  NumericalSamplePersistentCollection collAlgoHistory_;

  /** Collection of all result criteria (size 1+restart_, dimension 4)*/
  OT::NumericalSample criteria_;

}; /* class LHSResult */

} /* namespace OTLHS */

#endif /* OTLHS_LHSRESULT_HXX */
