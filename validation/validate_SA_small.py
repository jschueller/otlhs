#! /usr/bin/env python

import openturns as ot
import otlhs
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
from openturns.viewer import View
from otlhs.pyplotdesign import PyPlotDesign
import time

ot.RandomGenerator.SetSeed(0)
ot.Log.Show(ot.Log.INFO)

# Bounds are [0,1]^dimension
dimension = 2
bounds = ot.Interval(dimension)

# Size of sample
size = 10

# Factory: lhs generates
lhsDesign = otlhs.LHSDesign(bounds, size)

geomProfile = otlhs.GeometricProfile(10.0, 0.999, 50000)
c2 = otlhs.SpaceFillingC2()
sa = otlhs.SimulatedAnnealingLHS(lhsDesign, geomProfile, c2)
tic = time.time()
result = sa.generate()
toc = time.time()
dt1 = toc-tic
print("time=%f"%dt1)
print("dimension=%d, size=%d,sa=%s"%(dimension, size, sa))
print str(result.getOptimalValue())+" c2="+str(result.getC2())+" phiP="+str(result.getPhiP())+" minDist="+str(result.getMinDist())

# plot design
fig = PyPlotDesign(result.getOptimalDesign(), bounds, 10, 10, plot_kwargs={'color':'blue', 'marker': 'o', 'ms': 6})
plt.suptitle('LHS design of size=%d - Optimization of %s criterion using geometric SA'%(size,c2.getName()))

fig.savefig("lhs_sa_geom_%d.png"%size)
plt.close(fig)

crit = result.drawHistoryCriterion()
proba = result.drawHistoryProbability()
temp = result.drawHistoryTemperature()

pp = PdfPages('small_OTLHS.pdf')
# Criterion
fig = View(crit, plot_kwargs={'color':'blue'}).getFigure()
fig.savefig("crit_sa_geom.png")
pp.savefig(fig)
plt.close(fig)
# Proba
fig = View(proba, plot_kwargs={'marker': 'o', 'ms': 0.6}, axes_kwargs={'ylim': [-0.05, 1.05]}).getFigure()
fig.savefig("lhs_c2_proba.png")
pp.savefig(fig)
plt.close(fig)
# Temperature
fig = View(temp).getFigure()
pp.savefig(fig)
plt.close(fig)

linearProfile = otlhs.LinearProfile(10.0, 50000)
minDist = otlhs.SpaceFillingMinDist()
sa = otlhs.SimulatedAnnealingLHS(lhsDesign, linearProfile, minDist)
tic = time.time()
result = sa.generate()
toc = time.time()
dt2 = toc-tic
print("time=%f"%dt2)
print("dimension=%d, size=%d,sa=%s"%(dimension, size, sa))
print str(result.getOptimalValue())+" c2="+str(result.getC2())+" phiP="+str(result.getPhiP())+" minDist="+str(result.getMinDist())

# plot design
fig = PyPlotDesign(result.getOptimalDesign(), bounds, 10, 10, plot_kwargs={'color':'blue', 'marker': 'o', 'ms': 6})
plt.suptitle('LHS design of size=%d - Optimization of %s criterion using linear SA'%(size,minDist.getName()))
fig.savefig("lhs_sa_lin_%d.png"%size)
plt.close(fig)

crit = result.drawHistoryCriterion()
proba = result.drawHistoryProbability()
temp = result.drawHistoryTemperature()

# Criterion
fig = View(crit, plot_kwargs={'color':'blue'}).getFigure()
fig.savefig("crit_sa_lin.png")
pp.savefig(fig)
plt.close(fig)
# Proba
fig = View(proba, plot_kwargs={'marker': 'o', 'ms': 0.6}, axes_kwargs={'ylim': [-0.05, 1.05]}).getFigure()
fig.savefig("lhs_mindist_proba.png")
pp.savefig(fig)
plt.close(fig)
# Temperature
fig = View(temp).getFigure()
pp.savefig(fig)
plt.close(fig)

pp.close()
