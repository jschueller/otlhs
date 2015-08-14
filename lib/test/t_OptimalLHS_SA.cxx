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
  // Specifiy if initial LHS is centered or randomized
  const Bool centered(true);
  OTLHS::LHSDesign lhs(bounds, size, centered);

  // print lhs
  std::cout << lhs << std::endl;
  std::cout << "Bounds of uniform distributions=" << lhs.getBounds() << std::endl;

  // Generate design without optimization
  NumericalSample design(lhs.generate());
  std::cout << "design=" << design << std::endl;

  // Define space fillings
  OTLHS::SpaceFillingPhiP spaceFillingPhiP(10);
  OTLHS::SpaceFillingC2 spaceFillingC2;
  OTLHS::SpaceFillingMinDist spaceFillingMinDist;

  // Print the criteria on this design
  std::cout << "PhiP=" << spaceFillingPhiP.evaluate(design)
            << ", C2=" << spaceFillingC2.evaluate(design)
            << ", MinDist=" << spaceFillingMinDist.evaluate(design)
            << std::endl;

  // --------------------------------------------------
  // -------------  Simulated annealing  --------------
  // --------------------------------------------------

  // Geometric profile
  const NumericalScalar T0(10.0);
  const UnsignedInteger iMax(2000);
  const NumericalScalar c(0.95);
  const OTLHS::GeometricProfile geomProfile(T0, c, iMax);

  // 1) Simulated Annealing LHS with geometric temperature profile, C2 optimization
  OTLHS::SimulatedAnnealingLHS optimalSA_C2(lhs, geomProfile, spaceFillingC2);

  // print lhs
  std::cout << "optimal lhs=" << optimalSA_C2 << std::endl;

  OTLHS::LHSResult result_C2(optimalSA_C2.generate());
  NumericalSample design_C2(result_C2.getOptimalDesign());

  std::cout << "Best design using geometric temperature and C2 space filling=" << design_C2 << std::endl;
  std::cout << "Final criteria: C2=" << result_C2.getC2()
            << ", PhiP=" << result_C2.getPhiP()
            << ", MinDist=" << result_C2.getMinDist()
            << std::endl;

  // 2) Simulated Annealing LHS with linear temperature profile, PhiP optimization
  const OTLHS::LinearProfile linearProfile(T0, iMax);
  OTLHS::SimulatedAnnealingLHS optimalSA_PhiP(lhs, linearProfile, spaceFillingPhiP);
  // print lhs
  std::cout << "optimal lhs=" << optimalSA_PhiP << std::endl;

  OTLHS::LHSResult result_PhiP(optimalSA_PhiP.generate());
  NumericalSample design_PhiP(result_PhiP.getOptimalDesign());

  std::cout << "Best design using linear temperature profile and PhiP space filling=" << design_PhiP << std::endl;
  std::cout << "Final criteria: C2=" << result_PhiP.getC2()
            << ", PhiP=" << result_PhiP.getPhiP()
            << ", MinDist=" << result_PhiP.getMinDist()
            << std::endl;

  // 3) Simulated Annealing LHS with linear temperature profile, PhiP optimization and nStart > 0
  const UnsignedInteger nStart(10);
  OTLHS::LHSResult result_PhiP_restart(optimalSA_PhiP.generate(nStart));

  NumericalSample design_PhiP_restart(result_PhiP_restart.getOptimalDesign());

  std::cout << "Best design using linear temperature profile and PhiP space filling=" << design_PhiP_restart << std::endl;
  std::cout << "Final criteria: C2=" << result_PhiP_restart.getC2()
            << ", PhiP=" << result_PhiP_restart.getPhiP()
            << ", MinDist=" << result_PhiP_restart.getMinDist()
            << std::endl;
  for(UnsignedInteger i = 0; i < nStart; ++i)
  {
    NumericalSample design_PhiP_i(result_PhiP_restart.getOptimalDesign(i));
    std::cout << "  Intermediate design for restart iteration number " << i << " " << design_PhiP_i << std::endl;
    std::cout << "  Final criteria: C2=" << result_PhiP_restart.getC2(i)
              << ", PhiP=" << result_PhiP_restart.getPhiP(i)
              << ", MinDist=" << result_PhiP_restart.getMinDist()
              << std::endl;
  }

  return 0;
}
