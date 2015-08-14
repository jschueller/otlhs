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
spaceFillingPhiP = otlhs.SpaceFillingPhiP()
spaceFillingC2 = otlhs.SpaceFillingC2()
spaceFillingMinDist = otlhs.SpaceFillingMinDist()

# print the criteria on this design
print("PhiP=%f, C2=%f, MinDist=%f"%(spaceFillingPhiP.evaluate(design), spaceFillingC2.evaluate(design), spaceFillingMinDist.evaluate(design)))

#--------------------------------------------------#
# ------------ MonteCarlo algorithm  ------------- #
#--------------------------------------------------#

# RandomBruteForce MonteCarlo with N designs
N = 10000

# 1) LHS with C2 optimization
optimalLHSAlgorithmC2 = otlhs.MonteCarloLHS(lhs, N, spaceFillingC2)
# print lhs
print("optimal lhs=", optimalLHSAlgorithmC2)
resultC2 = optimalLHSAlgorithmC2.generate()
design = resultC2.getOptimalDesign()
print("Best design with MonteCarlo and C2 space filling=", design)
print("Final criteria: C2=%f, PhiP=%f, MinDist=%f" %(resultC2.getC2(), resultC2.getPhiP(), resultC2.getMinDist()))

# 2) LHS with PhiP optimization
optimalLHSAlgorithmPhiP = otlhs.MonteCarloLHS(lhs, N, spaceFillingPhiP)
print("optimal lhs=", optimalLHSAlgorithmPhiP)
resultPhiP = optimalLHSAlgorithmPhiP.generate()
design = resultPhiP.getOptimalDesign()
print("Best design with MonteCarlo and PhiP space filling=", design)
print("Final criteria: C2=%f, PhiP=%f, MinDist=%f" %(resultPhiP.getC2(), resultPhiP.getPhiP(), resultPhiP.getMinDist()))

# 3) LHS with MinDist optimization
optimalLHSAlgorithmMinDist = otlhs.MonteCarloLHS(lhs, N, spaceFillingMinDist)
print("optimal lhs=", optimalLHSAlgorithmMinDist)
resultMinDist = optimalLHSAlgorithmMinDist.generate()
design = resultMinDist.getOptimalDesign()
print("Best design with MonteCarlo and MinDist space filling=", design)
print("Final criteria: C2=%f, PhiP=%f, MinDist=%f" %(resultMinDist.getC2(), resultMinDist.getPhiP(), resultMinDist.getMinDist()))
