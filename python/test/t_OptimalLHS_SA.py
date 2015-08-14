#! /usr/bin/env python

from __future__ import print_function
import openturns as ot
import otlhs

# Defining parameters
dimension = 3
bounds = ot.Interval(dimension)
size = 25
# Specifiy if initial LHS is centered or randomized
randomized = True

# Build standard LHS algorithm
lhs = otlhs.LHSDesign(bounds, size, randomized)
# print the object
print("lhs=", lhs)
print("Bounds of uniform distributions=", lhs.getBounds())

# Generate design without optimization
design = lhs.generate()
print("design=", design)

# Defining space fillings
spaceFillingC2 = otlhs.SpaceFillingC2()
spaceFillingPhiP = otlhs.SpaceFillingPhiP(10)

# print the criteria on this design
print("PhiP=%f, C2=%f"%(otlhs.SpaceFillingPhiP().evaluate(design), otlhs.SpaceFillingC2().evaluate(design)))

#--------------------------------------------------#
# ------------- Simulated annealing  ------------- #
#--------------------------------------------------#
# Geometric profile
T0 = 10.0
iMax = 2000
c = 0.95
geomProfile = otlhs.GeometricProfile(T0, c, iMax)

# 1) Simulated Annealing LHS with geometric temperature profile, C2 optimization
optimalLHSAlgorithm = otlhs.SimulatedAnnealingLHS(lhs, geomProfile, spaceFillingC2)
print("lhs=", optimalLHSAlgorithm)
result = optimalLHSAlgorithm.generate()
design = result.getOptimalDesign()
print("Generating design using geometric temperature profile & C2 criterion=", design)
print("Final criteria: C2=%f, PhiP=%f, MinDist=%f" %(result.getC2(), result.getPhiP(), result.getMinDist()))

# Linear profile
linearProfile = otlhs.LinearProfile(T0, iMax)

# 2) Simulated Annealing LHS with linear temperature profile, PhiP optimization
optimalLHSAlgorithm = otlhs.SimulatedAnnealingLHS(lhs, linearProfile, spaceFillingPhiP)
print("lhs=", optimalLHSAlgorithm)
result = optimalLHSAlgorithm.generate()
design = result.getOptimalDesign()
print("Generating design using linear temperature profile & PhiP criterion =", design)
print("Final criteria: C2=%f, PhiP=%f, MinDist=%f" %(result.getC2(), result.getPhiP(), result.getMinDist()))

# 3) Simulated Annealing LHS with geometric temperature profile, PhiP optimization & initial design
initialDesign = ot.NumericalSample(design)
optimalLHSAlgorithm = otlhs.SimulatedAnnealingLHS(initialDesign, bounds, geomProfile, spaceFillingPhiP)
print("lhs=", optimalLHSAlgorithm)
print("initial design=", initialDesign)
print("PhiP=%f, C2=%f"%(otlhs.SpaceFillingPhiP().evaluate(design), otlhs.SpaceFillingC2().evaluate(design)))
result = optimalLHSAlgorithm.generate()
design = result.getOptimalDesign()
print("Generating design using linear temperature profile & PhiP criterion =", design)
print("Final criteria: C2=%f, PhiP=%f, MinDist=%f" %(result.getC2(), result.getPhiP(), result.getMinDist()))

# 4) Simulated Annealing LHS with linear temperature profile, PhiP optimization and nStart > 1
nStart = 10
results = optimalLHSAlgorithm.generate(nStart)
design = results.getOptimalDesign()
print("Generating design using linear temperature profile & PhiP criterion =", design)
print("Final criteria: C2=%f, PhiP=%f, MinDist=%f" %(results.getC2(), results.getPhiP(), results.getMinDist()))
for i in range(nStart):
    design = results.getOptimalDesign(i)
    print("  Intermediate design for restart iteration number ", i, design)
    print("  Final criteria: C2=%f, PhiP=%f, MinDist=%f" %(results.getC2(i), results.getPhiP(i), results.getMinDist(i)))

