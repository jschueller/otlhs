from __future__ import print_function
import openturns as ot
import otlhs
from math import sin, pi
import matplotlib
matplotlib.use('Agg')
import matplotlib.pylab as plt
from otlhs.pyplotdesign import PyPlotDesign

# Set seed
ot.RandomGenerator.SetSeed(0)
# Definition of the Ishigami function
dimension = 3
a = 7.0
b = 0.1

# Create the Ishigami function
input_variables = ['xi1','xi2','xi3']
formula = ['sin(xi1) + (' + str(a) + ') * (sin(xi2)) ^ 2 + (' + str(b) + ') * xi3^4 * sin(xi1)']
ishigami_model = ot.NumericalMathFunction(input_variables, formula)
ishigami_model.setName('Ishigami')

#  Generating a design of size 
N = 150
# Considering independent Uniform distributions of dimension 3
# Bounds are (-pi,pi), (-pi,pi) and (-pi,pi)
bounds = ot.Interval(dimension*[-pi], dimension*[pi])
# Random LHS
lhs = otlhs.LHSDesign(bounds, N)
# Fixing C2 crit
space_filling = otlhs.SpaceFillingC2()
# Defining a temperature profile
temperatureProfile = otlhs.GeometricProfile()
# Pre conditionning : generate an optimal design with MC
nSimu = 100
algo = otlhs.MonteCarloLHS(lhs, nSimu, space_filling)
result = algo.generate()
initialDesign = result.getOptimalDesign()
print('initial design pre-computed. Performing SA optimization...')
# Use of initial design
algo = otlhs.SimulatedAnnealingLHS(initialDesign, bounds, temperatureProfile, space_filling)
result = algo.generate()
print('initial design computed')
# Retrieve optimal design
input_database = result.getOptimalDesign()

fig = PyPlotDesign(input_database, bounds, 1, 1)
fig.set_size_inches(fig.get_size_inches() * 2)
plt.suptitle('Ishigami design')
plt.savefig('design_ishigami.png')
plt.close(fig)
# Response of the model
print('sampling size = ', N)
output_database = ishigami_model(input_database)

# Learning input/output
# Usual chaos meta model
enumerate_function = ot.HyperbolicAnisotropicEnumerateFunction(dimension)
orthogonal_basis = ot.OrthogonalProductPolynomialFactory(dimension*[ot.LegendreFactory()], enumerate_function)
basis_size = 100
# Initial chaos algorithm
adaptive_strategy = ot.FixedStrategy(orthogonal_basis, basis_size)
# ProjectionStrategy ==> Sparse
fitting_algorithm = ot.KFold()
approximation_algorithm = ot.LeastSquaresMetaModelSelectionFactory(ot.LARS(), fitting_algorithm)
projection_strategy = ot.LeastSquaresStrategy(input_database, output_database, approximation_algorithm)
print('Surrogate model...')
distribution_ishigami = ot.ComposedDistribution(dimension * [ot.Uniform(-pi,pi)])
algo_pc = ot.FunctionalChaosAlgorithm(input_database, output_database, distribution_ishigami, adaptive_strategy, projection_strategy)
algo_pc.run()
chaos_result = algo_pc.getResult()
print('Surrogate model computed')

# Validation
lhs_validation = ot.LHSExperiment(distribution_ishigami, 100)
input_validation = lhs_validation.generate()
output_validation = ishigami_model(input_validation)
# Chaos model evaluation
output_metamodel_sample = chaos_result.getMetaModel()(input_validation)

# Cloud validation ==> change from matplotlib to pure OT
fig = plt.figure()
plt.plot(output_validation, output_validation, 'b-', label='Model')
plt.plot(output_validation, output_metamodel_sample, 'r.', label='SM')
plt.title('Surrogate Model validation - Ishigami use case')
plt.savefig('ishigami_model_validation.png')
