//                                               -*- C++ -*-
/**
 *  @brief SpaceFillingPhiP
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
#include "otlhs/SpaceFillingPhiP.hxx"
#include "openturns/PersistentObjectFactory.hxx"

#include <limits>

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(SpaceFillingPhiP);

static const Factory<SpaceFillingPhiP> Factory_SpaceFillingPhiP;


/* Default constructor */
SpaceFillingPhiP::SpaceFillingPhiP(UnsignedInteger p)
  : SpaceFillingImplementation(true),
    p_(p)
{
  if (p == 0) throw InvalidArgumentException(HERE) << "Error: p must be positive";
  setName("PhiP");
}

/* Virtual constructor method */
SpaceFillingPhiP * SpaceFillingPhiP::clone() const
{
  return new SpaceFillingPhiP(*this);
}

/** Evaluate criterion on a sample */
NumericalScalar SpaceFillingPhiP::evaluate(const NumericalSample & sample) const
{
  const UnsignedInteger size(sample.getSize());
  const UnsignedInteger dimension(sample.getDimension());
  NumericalScalar sum = 0.0;
  const NumericalScalar* addr_sample = &sample[0][0];
  for (UnsignedInteger i = 0; i < size; ++i)
  {
    const NumericalScalar* ptI(addr_sample + i * dimension);
    for (UnsignedInteger j = 0; j < i; ++j)
    {
      NumericalScalar squaredNorm = 0.0;
      const NumericalScalar* ptJ(addr_sample + j * dimension);
      for (UnsignedInteger d = 0; d < dimension; ++d)
      {
        const NumericalScalar delta(ptI[d] - ptJ[d]);
        squaredNorm += delta * delta;
      }
      if (squaredNorm == 0.0) return std::numeric_limits<NumericalScalar>::max();
      sum += std::exp(-0.5 * p_ * std::log(squaredNorm));
    }
  }
  return std::exp(std::log(sum) / p_);
}

/** Compute criterion when performing an elementary perturbation */
NumericalScalar SpaceFillingPhiP::perturbLHS(NumericalSample& oldDesign, OT::NumericalScalar oldCriterion,
    UnsignedInteger row1, UnsignedInteger row2, UnsignedInteger column) const
{
  if (row1 == row2) return oldCriterion;
  if (p_ > 5) return SpaceFillingImplementation::perturbLHS(oldDesign, oldCriterion, row1, row2, column);

  const UnsignedInteger size(oldDesign.getSize());
  const UnsignedInteger dimension(oldDesign.getDimension());
  const NumericalScalar* addr_sample = &oldDesign[0][0];

  NumericalScalar result = (oldCriterion <= 0.0 ? 0.0 : std::exp(p_ * std::log(oldCriterion)));
  NumericalScalar oldSum = 0.0;
  NumericalScalar* pt1(&oldDesign[0][0] + dimension * row1);
  NumericalScalar* pt2(&oldDesign[0][0] + dimension * row2);
  for(UnsignedInteger i = 0; i < size; ++i)
  {
    if (i == row1 || i == row2) continue;
    const NumericalScalar* ptI(addr_sample + dimension * i);
    NumericalScalar d1 = 0.0;
    NumericalScalar d2 = 0.0;
    for(UnsignedInteger d = 0; d < dimension; ++d)
    {
      const NumericalScalar delta1(pt1[d] - ptI[d]);
      d1 += delta1 * delta1;
      const NumericalScalar delta2(pt2[d] - ptI[d]);
      d2 += delta2 * delta2;
    }
    oldSum += std::exp(-0.5 * p_ * std::log(d1)) + std::exp(-0.5 * p_ * std::log(d2));
  }
  // Swap coordinates
  std::swap(pt1[column], pt2[column]);
  NumericalScalar newSum = 0.0;
  for(UnsignedInteger i = 0; i < size; ++i)
  {
    if (i == row1 || i == row2) continue;
    const NumericalScalar* ptI(addr_sample + dimension * i);
    NumericalScalar d1 = 0.0;
    NumericalScalar d2 = 0.0;
    for(UnsignedInteger d = 0; d < dimension; ++d)
    {
      const NumericalScalar delta1(pt1[d] - ptI[d]);
      d1 += delta1 * delta1;
      const NumericalScalar delta2(pt2[d] - ptI[d]);
      d2 += delta2 * delta2;
    }
    newSum += std::exp(-0.5 * p_ * std::log(d1)) + std::exp(-0.5 * p_ * std::log(d2));
  }
  // Swap coordinates to restore original sample
  std::swap(pt1[column], pt2[column]);

  result += newSum - oldSum;
  if (result <= 0.0) return 0.0;
  return std::exp(std::log(result) / p_);
}

/* String converter */
String SpaceFillingPhiP::__repr__() const
{
  OSS oss;
  oss << "class=" << SpaceFillingPhiP::GetClassName()
      << " p=" << p_;
  return oss;
}

/* Method save() stores the object through the StorageManager */
void SpaceFillingPhiP::save(Advocate & adv) const
{
  SpaceFillingImplementation::save( adv );
  adv.saveAttribute( "p_", p_ );
}

/* Method load() reloads the object from the StorageManager */
void SpaceFillingPhiP::load(Advocate & adv)
{
  SpaceFillingImplementation::load( adv );
  adv.loadAttribute( "p_", p_ );
}


} /* namespace OTLHS */
