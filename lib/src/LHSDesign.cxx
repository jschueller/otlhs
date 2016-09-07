//                                               -*- C++ -*-
/**
 *  @brief LHSDesign
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
#include "otlhs/LHSDesign.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/ComposedDistribution.hxx"
#include "openturns/Uniform.hxx"
#include "openturns/KPermutationsDistribution.hxx"
#include "openturns/RandomGenerator.hxx"

#include <cmath>

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(LHSDesign);

static const Factory<LHSDesign> Factory_LHSDesign;

LHSDesign::LHSDesign()
  : PersistentObject()
  , centeredDesign_()
{
  // Nothing to do
}


/* Default constructor */
LHSDesign::LHSDesign(const Interval & bounds, const UnsignedInteger size, const Bool centeredDesign)
  : PersistentObject()
  , bounds_(bounds)
  , size_(size)
  , centeredDesign_(centeredDesign)
{
  //Nothing to do
}

/* Virtual constructor method */
LHSDesign * LHSDesign::clone() const
{
  return new LHSDesign(*this);
}

/** Attributes for bounds, size, randomDesign */
Interval LHSDesign::getBounds() const
{
  return bounds_;
}

UnsignedInteger LHSDesign::getSize() const
{
  return size_;
}

Bool LHSDesign::isCenteredDesign() const
{
  return centeredDesign_;
}

/** The main method is generating a design */
NumericalSample LHSDesign::generate() const
{
  const UnsignedInteger dimension(bounds_.getDimension());
  const UnsignedInteger size(size_);
  // Randomized LHS: U[0,1]^dimension
  // Sampling of size x dimension values
  NumericalSample shuffle(dimension, size);
  // Randomized case
  for(UnsignedInteger j = 0; j < dimension; ++j)
    for(UnsignedInteger i = 0; i < size; ++i)
        if (centeredDesign_) shuffle[j][i] = 0.5;
        else shuffle[j][i] = RandomGenerator::Generate();

  // Use the shuffle to generate a sample
  NumericalSample sample(size, dimension);
  // KPermutationDistribution ==> Generate a permutation of k in N
  // Here k=N
  const KPermutationsDistribution dist(size, size);
  
  for(UnsignedInteger j = 0; j < dimension; ++j)
  {
    // Generate a point of permutations
    const NumericalPoint indexes(dist.getRealization());
    // Probability vector
    NumericalPoint weights(indexes + shuffle[j]);
    for(UnsignedInteger i = 0; i < size; ++i) sample[i][j] = weights[i];
  }
  // Map [0,N] into [a,b] ==> (b-a) * [0,N] / N + a
  const NumericalPoint dx(bounds_.getUpperBound() - bounds_.getLowerBound());
  sample *= dx / size;
  // Translating with a
  sample += bounds_.getLowerBound();
  return sample;
}

/* String converter */
String LHSDesign::__repr__() const
{
  OSS oss;
  oss << "class=" << LHSDesign::GetClassName()
      << " name=" << getName()
      << " centeredDesign=" << centeredDesign_
      << " bounds=" << bounds_
      << " size=" << size_;
  return oss;
}

/* Method save() stores the object through the StorageManager */
void LHSDesign::save(Advocate & adv) const
{
  PersistentObject::save( adv );
  adv.saveAttribute("bounds_", bounds_);
  adv.saveAttribute("size_", size_);
  adv.saveAttribute("centeredDesign_", centeredDesign_);
}

/* Method load() reloads the object from the StorageManager */
void LHSDesign::load(Advocate & adv)
{
  PersistentObject::load( adv );
  adv.loadAttribute("bounds_", bounds_);
  adv.loadAttribute("size_", size_);
  adv.loadAttribute("centeredDesign_", centeredDesign_);
}


} /* namespace OTLHS */
