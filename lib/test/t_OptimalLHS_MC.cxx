#include <iostream>
// OT includes
#include <OT.hxx>
#include "OTLHS.hxx"

using namespace OT;

int main(int argc, char **argv)
{
  const UnsignedInteger dimension(3);
  const Interval bounds(dimension);
  const UnsignedInteger size(25);
  // Specifiy if initial LHS is centered
  const Bool centered(true);
  OTLHS::LHSDesign lhs(bounds, size, centered);

  // print lhs
  std::cout << lhs << std::endl;
  std::cout << "Bounds of uniform distributions=" << lhs.getBounds() << std::endl;

  // Generate design without optimization
  NumericalSample design(lhs.generate());
  std::cout << "design=" << design << std::endl;

  // Define space fillings
  OTLHS::SpaceFillingPhiP spaceFillingPhiP;
  OTLHS::SpaceFillingC2 spaceFillingC2;
  OTLHS::SpaceFillingMinDist spaceFillingMinDist;

  // Print the criteria on this design
  std::cout << "PhiP=" << spaceFillingPhiP.evaluate(design)
            << ", C2=" << spaceFillingC2.evaluate(design)
            << ", MinDist=" << spaceFillingMinDist.evaluate(design)
            << std::endl;

  // --------------------------------------------------
  //  ------------ MonteCarlo algorithm  ------------- 
  // --------------------------------------------------

  // RandomBruteForce MonteCarlo with N designs
  const UnsignedInteger N(10000);

  // 1) LHS with C2 optimization
  OTLHS::MonteCarloLHS optimalMC_C2(lhs, N, spaceFillingC2);

  // print lhs
  std::cout << "optimal lhs=" << optimalMC_C2 << std::endl;

  OTLHS::LHSResult result_C2(optimalMC_C2.generate());
  const NumericalSample design_C2(result_C2.getOptimalDesign());

  std::cout << "Best design with MonteCarlo and C2 space filling=" << design_C2 << std::endl;
  std::cout << "Final criteria: C2=" << result_C2.getC2()
            << ", PhiP=" << result_C2.getPhiP()
            << ", MinDist=" << result_C2.getMinDist()
            << std::endl;

  // 2) LHS with PhiP optimization
  OTLHS::MonteCarloLHS optimalMC_PhiP(lhs, N, spaceFillingPhiP);
  // print lhs
  std::cout << "optimal lhs=" << optimalMC_PhiP << std::endl;

  OTLHS::LHSResult result_PhiP(optimalMC_PhiP.generate());
  NumericalSample design_PhiP(result_PhiP.getOptimalDesign());

  std::cout << "Best design with MonteCarlo and PhiP space filling=" << design_PhiP << std::endl;
  std::cout << "Final criteria: C2=" << result_PhiP.getC2()
            << ", PhiP=" << result_PhiP.getPhiP()
            << ", MinDist=" << result_PhiP.getMinDist()
            << std::endl;

  // 3) LHS with MinDist optimization (=mindist optim)
  OTLHS::MonteCarloLHS optimalMC_MinDist(lhs, N, spaceFillingMinDist);
  // print lhs
  std::cout << "optimal lhs=" << optimalMC_MinDist << std::endl;

  OTLHS::LHSResult result_MinDist(optimalMC_MinDist.generate());
  NumericalSample design_MinDist(result_MinDist.getOptimalDesign());

  std::cout << "Best design with MonteCarlo and MinDist space filling=" << design_MinDist << std::endl;
  std::cout << "Final criteria: C2=" << result_MinDist.getC2()
            << ", PhiP=" << result_MinDist.getPhiP()
            << ", MinDist=" << result_MinDist.getMinDist()
            << std::endl;


  return 0;
}
