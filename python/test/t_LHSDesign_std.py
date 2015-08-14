#! /usr/bin/env python

import openturns as ot
import otlhs

# Bounds are [0,1]^5
bounds = ot.Interval(5)
# Size of sample
size = 10
# Factory: lhs generates
lhsDesign = otlhs.LHSDesign(bounds, size, True)
print("lhsDesign=",lhsDesign)
# Generate a design
design = lhsDesign.generate()
print("design=",design)

# Plot using PlotDesign implementation
plotDesign = otlhs.PlotDesign(design, bounds, 10, 10)
g = ot.Graph()
g.add(plotDesign)
# g.draw("lhsDesign",640,480,ot.GraphImplementation.PDF)

try:
    from otlhs.pyplotdesign import PyPlotDesign
    # Test requires matplotlib, which is not mandatory for the module
    fig = PyPlotDesign(design, bounds, 10, 10)
    plt.show()
except ImportError:
    pass