#! /usr/bin/env python

import openturns as ot
import otlhs

# Defining parameters
dimension = 3
bounds = ot.Interval(dimension)
size = 100
# Specifiy if initial LHS is centered or randomized
randomized = True

# Build standard LHS algorithm
lhs = otlhs.LHSDesign(bounds, size, randomized)
# print the object
print("lhs=", lhs)
print("Bounds of uniform distributions=", lhs.getBounds())

# Generate design without optimization
design = lhs.generate()
print "design=", design

# Defining space fillings
spaceFillingC2 = otlhs.SpaceFillingC2()
spaceFillingPhiP = otlhs.SpaceFillingPhiP()

# print the criteria on this design
print "PhiP=%f, C2=%f"%(otlhs.SpaceFillingPhiP().evaluate(design), otlhs.SpaceFillingC2().evaluate(design))

# Parameters for drawing design ==> Number of points are for the "grid"
Nx = 50
Ny = 50

# Plot initial design ==> object is of type ot.Drawable
plotDesign = otlhs.PlotDesign(design, lhs.getBounds(), Nx, Ny)
# Create an empty graph
lhsGraph = ot.Graph("LHS", " ", " ", True, "topright")
# Then, draw it
lhsGraph.add(plotDesign)
lhsGraph.draw("LHSDesign")
# Show the design
# ot.Show(lhsGraph)

#--------------------------------------------------#
# ------------ MonteCarlo algorithm  ------------- #
#--------------------------------------------------#

# RandomBruteForce MonteCarlo with N designs
N = 100

# 1) LHS with C2 optimization
optimalLHSAlgorithm = otlhs.MonteCarloLHS(lhs, N, spaceFillingC2)
# print lhs
print("lhs=", optimalLHSAlgorithm)
result = optimalLHSAlgorithm.generate()
design = result.getOptimalDesign()
print "Generating design with MonteCarlo and C2 space filling=", design
print "History criterion=", result.getAlgoHistory()
print "Final criteria: C2=%f, PhiP=%f" %(result.getC2(), result.getPhiP())
# Plot the design ==> Possible to give result for drawing instead of design + bounds
plotDesign = otlhs.PlotDesign(result, Nx, Ny)
# Create an empty graph
lhsGraph = ot.Graph("LHS", " ", " ", True, "topright")
# Then, draw it
lhsGraph.add(plotDesign)
lhsGraph.draw("MC_C2_Design")
# Criterion graph ==> Graph object
criterionGraph = optimalLHSAlgorithm.DrawCriterion(result)
criterionGraph.draw("MC_C2_Criterion")

# 2) LHS with PhiP optimization (=mindist optim)
optimalLHSAlgorithm = otlhs.MonteCarloLHS(lhs, N, spaceFillingPhiP)
print("lhs=", optimalLHSAlgorithm)
result = optimalLHSAlgorithm.generate()
design = result.getOptimalDesign()
print "Generating design with MonteCarlo and PhiP optimum=", design
print "History criterion=", result.getAlgoHistory()
print "Final criteria: C2=%f, PhiP=%f" %(result.getC2(), result.getPhiP())
# Plot the design
plotDesign = otlhs.PlotDesign(result, Nx, Ny)
# Create an empty graph
lhsGraph = ot.Graph("LHS", " ", " ", True, "topright")
# Then, draw it
lhsGraph.add(plotDesign)
lhsGraph.draw("MC_PhiP_Design")
# Graph of criterion
criterionGraph = result.DrawCriterion()
criterionGraph.draw("MC_PhiP_Criterion")

#--------------------------------------------------#
# ------------- Simulated annealing  ------------- #
#--------------------------------------------------#
# Defining temperature profil ==> TO, iterations...
T0 = 10.0
iMax = 2000
c = 0.95
# Care, c should be in ]0,1[
# Geometric profil
geomProfile = otlhs.GeometricProfile(T0, c, iMax)

# 3) Simulated Annealing LHS with geometric temperature, C2 optimization
optimalLHSAlgorithm = otlhs.SimulatedAnnealingLHS(lhs, geomProfile, spaceFillingC2)
print("lhs=", optimalLHSAlgorithm)
result = optimalLHSAlgorithm.generate()
design = result.getOptimalDesign()
history = result.getAlgoHistory()
print "Generating design using SimulatedAnnealing geometric temperature & C2 criterion=", design
print "History criterion=", history[:,0]
print "History temperature=", history[:,1]
print "History probability=", history[:,2]
print "Final criteria: C2=%f, PhiP=%f" %(result.getC2(), result.getPhiP())
# Plot design
plotDesign = otlhs.PlotDesign(result, Nx, Ny)
# Create an empty graph
lhsGraph = ot.Graph("LHS", " ", " ", True, "topright")
# Then, draw it
lhsGraph.add(plotDesign)
lhsGraph.draw("SA_Geom_C2_Design")
# Criteria drawing
# SA algorithms returns also Probability & temperature
criterionGraph = result.DrawCriterion()
criterionGraph.draw("SA_Geom_C2_Criterion")
probaGraph = result.DrawProbability()
probaGraph.draw("SA_Geom_C2_Proba")
tempGraph = result.DrawTemperature()
tempGraph.draw("SA_Geom_C2_Temperature")

# 4) Simulated Annealing LHS with geometric temperature, PhiP optimization
optimalLHSAlgorithm = otlhs.SimulatedAnnealingLHS(lhs, geomProfile, spaceFillingPhiP)
print("lhs=", optimalLHSAlgorithm)
result = optimalLHSAlgorithm.generate()
design = result.getOptimalDesign()
history = result.getAlgoHistory()
print "Generating design using SimulatedAnnealing geometric temperature & C2 criterion=", design
print "History criterion=", history[:,0]
print "History temperature=", history[:,1]
print "History probability=", history[:,2]
print "Final criteria: C2=%f, PhiP=%f" %(result.getC2(), result.getPhiP())
# Plot design
plotDesign = otlhs.PlotDesign(result, Nx, Ny)
# Create an empty graph
lhsGraph = ot.Graph("LHS", " ", " ", True, "topright")
# Then, draw it
lhsGraph.add(plotDesign)
lhsGraph.draw("SA_Geom_PhiP_Design")
# Criteria drawing
criterionGraph = result.DrawCriterion()
criterionGraph.draw("SA_Geom_PhiP_Criterion")
probaGraph = result.DrawProbability()
probaGraph.draw("SA_Geom_PhiP_Proba")
tempGraph = result.DrawTemperature()
tempGraph.draw("SA_Geom_PhiP_Temperature")

# Linear profil
linearProfile = otlhs.LinearProfile(T0, iMax)

# 5) Simulated Annealing LHS with linear temperature, C2 optimization
optimalLHSAlgorithm = otlhs.SimulatedAnnealingLHS(lhs, linearProfile, spaceFillingC2)
print("lhs=", optimalLHSAlgorithm)
result = optimalLHSAlgorithm.generate()
design = result.getOptimalDesign()
history = result.getAlgoHistory()
print "Generating design using linear temperature SimulatedAnnealing & C2 criterion =", design
print "History criterion=", history[:,0]
print "History temperature=", history[:,1]
print "History probability=", history[:,2]
print "Final criteria: C2=%f, PhiP=%f" %(result.getC2(), result.getPhiP())
# Plot design
plotDesign = otlhs.PlotDesign(result, Nx, Ny)
# Create an empty graph
lhsGraph = ot.Graph("LHS", " ", " ", True, "topright")
# Then, draw it
lhsGraph.add(plotDesign)
lhsGraph.draw("SA_Lin_C2_Design")
# Criteria drawing
criterionGraph = result.DrawCriterion()
criterionGraph.draw("SA_Lin_C2_Criterion")
probaGraph = result.DrawProbability()
probaGraph.draw("SA_Lin_C2_Proba")
tempGraph = result.DrawTemperature()
tempGraph.draw("SA_Lin_C2_Temperature")

# 6) Simulated Annealing LHS with linear temperature, PhiP optimization
optimalLHSAlgorithm = otlhs.SimulatedAnnealingLHS(lhs, linearProfile, spaceFillingPhiP)
print("lhs=", optimalLHSAlgorithm)
result = optimalLHSAlgorithm.generate()
design = result.getOptimalDesign()
history = result.getAlgoHistory()
print "Generating design using linear temperature SimulatedAnnealing & PhiP criterion =", design
print "History criterion=", history[:,0]
print "History temperature=", history[:,1]
print "History probability=", history[:,2]
print "Final criteria: C2=%f, PhiP=%f" %(result.getC2(), result.getPhiP())
# Plot design
plotDesign = otlhs.PlotDesign(result, Nx, Ny)
# Create an empty graph
lhsGraph = ot.Graph("LHS", " ", " ", True, "topright")
# Then, draw it
lhsGraph.add(plotDesign)
lhsGraph.draw("SA_Lin_PhiP_Design")
# Criteria drawing
criterionGraph = result.DrawCriterion()
criterionGraph.draw("SA_Lin_PhiP_Criterion")
probaGraph = result.DrawProbability()
probaGraph.draw("SA_Lin_PhiP_Proba")
tempGraph = result.DrawTemperature()
tempGraph.draw("SA_Lin_PhiP_Temperature")

# 7) Simulated Annealing LHS with linear temperature, Phi optimization and nStart > 1
#  Result is a collection of LHSResult
nStart = 10
results = optimalLHSAlgorithm.generate(nStart)
for i in range(nStart):
    design = results.getOptimalDesign(i)
    history = results.getAlgoHistory(i)
    print "Generating design using linear temperature SimulatedAnnealing & PhiP criterion =", design
    print "History criterion=", history[:,0]
    print "History temperature=", history[:,1]
    print "History probability=", history[:,2]
    print "Final criteria: C2=%f, PhiP=%f" %(result.getC2(i), result.getPhiP(i))
    # Plot design for the current result analysis
    plotDesign = otlhs.PlotDesign(design, Nx, Ny)
    # Create an empty graph
    lhsGraph = ot.Graph("Pairs", " ", " ", True, "topright")
    # Then, draw it
    lhsGraph.add(plotDesign)
    lhsGraph.draw("SA_Lin_PhiP_Design_MultiRestart_%d"%(i+1))
    # decreasing criterion
    criterionGraph = results.DrawCriterion(i)
    criterionGraph.draw("SA_Lin_PhiP_Criterion_MultiRestart_%d"%(i+1))
    probaGraph = results.DrawProbability(i)
    probaGraph.draw("SA_Lin_PhiP_Proba_MultiRestart_%d"%(i+1))
    tempGraph = results.DrawTemperature(i)
    tempGraph.draw("SA_Lin_PhiP_Temperature_MultiRestart_%d"%(i+1))
