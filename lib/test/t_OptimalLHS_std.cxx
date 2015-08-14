#include <iostream>
// OT includes
#include <OT.hxx>
#include "OTLHS.hxx"

using namespace OT;

int main(int argc, char **argv)
{
  const UnsignedInteger dimension(2);
  const Interval bounds(dimension);
  const UnsignedInteger size(100);
  // Specifiy if initial LHS is centered or randomized
  const Bool randomized(true);
  OTLHS::LHSDesign lhs(bounds, size, randomized);
  Log::Show(Log::ALL);

  // print lhs
  // Default space filling = mindist
  // Default algo = SA
  std::cout << lhs << std::endl;

  // Define a collection of Space filling techniques
  Collection<OTLHS::SpaceFilling> collSpaceFilling(0);
  // Add C2 space filling to the collection
  collSpaceFilling.add(OTLHS::SpaceFillingC2());
  // Add mindist (Phip) space filling to the collection
  collSpaceFilling.add(OTLHS::SpaceFillingPhiP(50));

  // Define a collection of algorithm techniques
  // These have the generic method run
  // They also have a protected method setInitialDesign
  Collection<OTLHS::OptimalLHS> collAlgorithm(0);
  // Add a RandomBruteForce MonteCarlo with 100 designs
  const UnsignedInteger nMC(100);
  collAlgorithm.add(OTLHS::MonteCarloLHS(lhs, nMC));

  // Defining temperature profil
  const NumericalScalar T0(10);
  const NumericalScalar c(0.95);
  const UnsignedInteger iMax(2000);
  // Add to Algo collection ==> Geometric temperature
  collAlgorithm.add(OTLHS::SimulatedAnnealingLHS(lhs, OTLHS::GeometricProfile(T0, c, iMax)));
  UnsignedInteger nStart(10);
  // Add to Algo collection ==> Geometric temperature with nStart times
  // TODO What data should be stored?
  collAlgorithm.add(OTLHS::SimulatedAnnealingLHS(lhs, OTLHS::GeometricProfile(T0, c, iMax), nStart));

  // Add to Algo collection ==> Linear temperature
  collAlgorithm.add(OTLHS::SimulatedAnnealingLHS(lhs, OTLHS::LinearProfile(T0, iMax)));

  const UnsignedInteger nrAlgo(collAlgorithm.getSize());
  const UnsignedInteger nrSF(collSpaceFilling.getSize());

  for(UnsignedInteger i = 0; i < nrAlgo; ++i)
  {
    // Set algo
    lhs.setAlgorithm(collAlgorithm[i]); //method getAlgorithm also exists
    for(UnsignedInteger j = 0; j < nrSF; ++j)
    {
      // Set the space filling algo
      lhs.setSpaceFilling(collSpaceFilling[j]); //method getSpaceFilling also exists
      const NumericalSample design(lhs.generate());
      // print the criteria
      std::cout << "Phip=" << OTLHS::SpaceFillingPhiP().evaluate(design)
                << "C2=" << OTLHS::SpaceFillingC2().evaluate(design)
                << std::endl;
      // Get result ==> OptimizedLHSResult ?
      std::cout << "Result=" << lhs.getResult() << std::endl;
      // criterion is always computed, independently of SA & MC
      Graph criterionGraph(lhs.drawCriterion());
      Graph lhsGraph(OTLHS::OptimalLHS::DrawDesign(design)); //? because the method depends only on a sample
      // Behaviour with empty collections?
      Graph probaGraph(lhs.drawProbability());
      Graph tempGraph(lhs.drawProbability());
    }
  }
  return 0;
}
