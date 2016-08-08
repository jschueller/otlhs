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
#include "openturns/PersistentObjectFactory.hxx"
#include "SimulatedAnnealingLHS.hxx"
#include "openturns/RandomGenerator.hxx"
#include "openturns/Log.hxx"
#include "SpaceFillingC2.hxx"
#include "SpaceFillingPhiP.hxx"
#include "SpaceFillingMinDist.hxx"
#include "openturns/KPermutationsDistribution.hxx"

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(SimulatedAnnealingLHS);

static const Factory<SimulatedAnnealingLHS> Factory_SimulatedAnnealingLHS;


/** Geometric temperature profil */
SimulatedAnnealingLHS::SimulatedAnnealingLHS(const LHSDesign & lhs, const TemperatureProfile & profile,
  const SpaceFilling & spaceFilling)
    : OptimalLHSImplementation(lhs, spaceFilling)
    , profile_(profile)
    , initialDesign_()
    , bounds_(lhs.getBounds())
{
  if (spaceFilling.getImplementation()->getClassName() == "SpaceFillingMinDist")
  {
    LOGWARN("MinDist criterion replaced by PhiP in SimulatedAnnealingLHS");
    spaceFilling_ = SpaceFillingPhiP();
  }
}

/** SimulatedAnnealingLHS constructor with LHS*/
SimulatedAnnealingLHS::SimulatedAnnealingLHS(const NumericalSample & initialDesign, Interval & bounds,
                        const TemperatureProfile & profile, const SpaceFilling & spaceFilling)
    : OptimalLHSImplementation()
    , profile_(profile)
    , initialDesign_(initialDesign)
    , bounds_(bounds)
{
  if (spaceFilling.getImplementation()->getClassName() == "SpaceFillingMinDist")
  {
    LOGWARN("MinDist criterion replaced by PhiP in SimulatedAnnealingLHS");
    spaceFilling_ = SpaceFillingPhiP();
  }
  else
    spaceFilling_ = spaceFilling;
  if (initialDesign_.getSize() == 0) throw InvalidArgumentException(HERE) << "Initial design must not be empty";
  if (initialDesign_.getDimension() != bounds_.getDimension()) throw InvalidArgumentException(HERE) << "Initial design dimension " << initialDesign_.getDimension() << " does not match bounds dimension " << bounds_.getDimension();
}

/* Virtual constructor method */
SimulatedAnnealingLHS * SimulatedAnnealingLHS::clone() const
{
  return new SimulatedAnnealingLHS(*this);
}

/* Generate design method */
LHSResult SimulatedAnnealingLHS::generate(OT::UnsignedInteger nRestart) const
{
  // LHSResult returns resuls for all restarts
  LHSResult result(bounds_, spaceFilling_, nRestart);
  for(UnsignedInteger index = 0; index < nRestart + 1; ++index)
  {
    // history has dimension 3 :crit, proba & temperature
    // Total size depends on convergency
    NumericalSample history(0, 3);
    Description historyDescription(3);
    historyDescription[0] = spaceFilling_.getImplementation()->getName() + " criterion";
    historyDescription[1] = "Probability";
    historyDescription[2] = "Temperature";
    history.setDescription(historyDescription);
    LOGDEBUG("Starting simulated annealing process");
    // Starting sample
    NumericalSample optimalDesign;
    if (initialDesign_.getSize() > 0)
      optimalDesign = initialDesign_;
    else
      optimalDesign = lhs_.generate();
    // Map optimalDesign into (0,1) & translate with a
    optimalDesign -= bounds_.getLowerBound();
    // scaling with dx
    const NumericalPoint dx(bounds_.getUpperBound() - bounds_.getLowerBound());
    optimalDesign /= dx;
    // Starting implementation
    UnsignedInteger iteration(0);
    NumericalScalar T(profile_.getT0());
    NumericalScalar optimalValue(spaceFilling_.evaluate(optimalDesign));
    const UnsignedInteger iMax(profile_.getIMax());
    while(iteration < iMax && T > 0)
    {
      LOGDEBUG(OSS() << "Current iteration =" <<  iteration << ", current temperature =" << T);
      // Generate rows & column indexes
      const UnsignedInteger columnIndex(RandomGenerator::IntegerGenerate(optimalDesign.getDimension()));
      const UnsignedInteger row1(RandomGenerator::IntegerGenerate(optimalDesign.getSize()));
      const UnsignedInteger row2(RandomGenerator::IntegerGenerate(optimalDesign.getSize()));
      if (row1 == row2) continue;
      // WARNING: bernoulliTrial is computed here and not in the else clause below to avoid
      //          numerical discrepancies between x86 and x86_64.  When optimalValue and
      //          newCriterion are almost equal, architectures may go to different
      //          branches.  In order to have the same random generator state,
      //          RandomGenerator::Generate() is called here.
      const NumericalScalar bernoulliTrial(RandomGenerator::Generate());
      const NumericalScalar newCriterion(spaceFilling_.perturbLHS(optimalDesign, optimalValue, row1, row2, columnIndex));
      const NumericalScalar criteriaDifference(std::min(std::exp((optimalValue-newCriterion)/T), 1.0));
      // Decision with respect to criteriaDifference
      if (optimalValue >= newCriterion)
      {
        std::swap(optimalDesign[row1][columnIndex], optimalDesign[row2][columnIndex]);
        optimalValue = newCriterion;
      }
      else
      {
        if (bernoulliTrial < criteriaDifference)
        {
          std::swap(optimalDesign[row1][columnIndex], optimalDesign[row2][columnIndex]);
          optimalValue = newCriterion;
        }
      }
      LOGDEBUG(OSS() << "Current optimal value =" << optimalValue);
      NumericalPoint historyElement(3);
      historyElement[0] = optimalValue;
      historyElement[1] = criteriaDifference;
      historyElement[2] = T;
      history.add(historyElement);
      // Update iteration, temperature
      iteration++;
      T = profile_(iteration);
    }
    LOGDEBUG("End of simulated annealing process");
    // Transform again optimalDesign
    // Map optimalDesign into (a,b)
    // scaling with dx
    optimalDesign *= dx;
    // Translating with a
    optimalDesign += bounds_.getLowerBound();
    // Add elements to result
    result.add(optimalDesign, optimalValue, SpaceFillingC2().evaluate(optimalDesign), SpaceFillingPhiP().evaluate(optimalDesign), SpaceFillingMinDist().evaluate(optimalDesign), history);
  }
  return result;
}

/* String converter */
String SimulatedAnnealingLHS::__repr__() const
{
  OSS oss;
  oss << "class=" << SimulatedAnnealingLHS::GetClassName()
      << " name=" << getName()
      << " bounds=" << bounds_
      << " spaceFilling=" << spaceFilling_
      << " profile=" << profile_;
  return oss;
}

/* Method save() stores the object through the StorageManager */
void SimulatedAnnealingLHS::save(Advocate & adv) const
{
  OptimalLHSImplementation::save( adv );
  adv.saveAttribute( "profile_", profile_ );
  adv.saveAttribute( "initialDesign_", initialDesign_ );
  adv.saveAttribute( "bounds_", bounds_ );
}

/* Method load() reloads the object from the StorageManager */
void SimulatedAnnealingLHS::load(Advocate & adv)
{
  OptimalLHSImplementation::load( adv );
  adv.loadAttribute( "profile_", profile_ );
  adv.loadAttribute( "initialDesign_", initialDesign_ );
  adv.loadAttribute( "bounds_", bounds_ );
}


} /* namespace OTLHS */
