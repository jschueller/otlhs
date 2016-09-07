#include <iostream>
// OT includes
#include <openturns/OT.hxx>
#include "otlhs/OTLHS.hxx"

using namespace OT;
using namespace OTLHS;

int main(int argc, char **argv)
{
  const UnsignedInteger dimension(5);
  const UnsignedInteger size(100);

  Collection<Distribution> distributions(dimension);
  for(UnsignedInteger i = 0; i < dimension; ++i)
    distributions[i] = Uniform();

  LHSExperiment lhs(ComposedDistribution(distributions), size);
  NumericalSample design(lhs.generate());

  // Defining space fillings
  SpaceFillingC2 spaceFillingC2;
  SpaceFillingMinDist spaceFillingMinDist;
  SpaceFillingPhiP spaceFillingPhiP;
  SpaceFillingPhiP spaceFillingPhiP50(50);

  // Print the criteria on this design
  std::cout << "C2=" << spaceFillingC2.evaluate(design)
            << ", MinDist=" << spaceFillingMinDist.evaluate(design)
            << ", Phip=" << spaceFillingPhiP.evaluate(design)
            << ", Phip(50)=" << spaceFillingPhiP50.evaluate(design)
            << std::endl;
  return 0;
}
