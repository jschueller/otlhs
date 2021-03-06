//                                               -*- C++ -*-
/**
 *  @brief MonteCarloLHS
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
#include "otlhs/MonteCarloLHS.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "otlhs/SpaceFillingC2.hxx"
#include "otlhs/SpaceFillingPhiP.hxx"
#include "otlhs/SpaceFillingMinDist.hxx"
#include <limits>

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(MonteCarloLHS);

static const Factory<MonteCarloLHS> Factory_MonteCarloLHS;

/* Default constructor */
MonteCarloLHS::MonteCarloLHS(const LHSDesign & lhs, const UnsignedInteger N, const SpaceFilling & spaceFilling)
  : OptimalLHSImplementation(lhs, spaceFilling),
    N_(N)
{
  // Nothing to do
}

/* Virtual constructor method */
MonteCarloLHS * MonteCarloLHS::clone() const
{
  return new MonteCarloLHS(*this);
}

/* Generate a NumericalSample. */
LHSResult MonteCarloLHS::generate() const
{
  LHSResult result(lhs_.getBounds(), spaceFilling_);
  NumericalSample history(N_, 1);
  Description historyDescription(1);
  historyDescription[0] = spaceFilling_.getImplementation()->getName() + " criterion";
  history.setDescription(historyDescription);
  // initialing algo
  NumericalSample optimalDesign;
  NumericalScalar optimalValue;
  if (spaceFilling_.isMinimizationProblem())
  {
    optimalValue = std::numeric_limits<NumericalScalar>::max();
  }
  else
  {
    optimalValue = std::numeric_limits<NumericalScalar>::min();
  }

  for (UnsignedInteger i = 0; i < N_; ++i)
  {
    const NumericalSample design(lhs_.generate());
    const NumericalScalar value(spaceFilling_.evaluate(design));
    history[i][0] = value;
    if (spaceFilling_.isMinimizationProblem() && (value < optimalValue))
    {
      optimalDesign = design;
      optimalValue = value;
    }
    if (!spaceFilling_.isMinimizationProblem() && (value > optimalValue))
    {
      optimalDesign = design;
      optimalValue = value;
    }
  }
  result.add(optimalDesign, optimalValue, SpaceFillingC2().evaluate(optimalDesign), SpaceFillingPhiP().evaluate(optimalDesign), SpaceFillingMinDist().evaluate(optimalDesign), history);
  return result;
}

/* String converter */
String MonteCarloLHS::__repr__() const
{
  OSS oss;
  oss << "class=" << MonteCarloLHS::GetClassName()
      << " name=" << getName()
      << " lhs=" << lhs_
      << " spaceFilling=" << spaceFilling_
      << " simulation size=" << N_;
  return oss;
}

/* Method save() stores the object through the StorageManager */
void MonteCarloLHS::save(Advocate & adv) const
{
  OptimalLHSImplementation::save( adv );
  adv.saveAttribute( "N_", N_ );
}

/* Method load() reloads the object from the StorageManager */
void MonteCarloLHS::load(Advocate & adv)
{
  OptimalLHSImplementation::load( adv );
  adv.loadAttribute( "N_", N_ );
}


} /* namespace OTLHS */
