// SWIG file

%module(package="otlhs", docstring="otlhs module") otlhs
//%feature("autodoc","1");

%{
#include "OT.hxx"
#include "PythonWrappingFunctions.hxx"
%}

// Prerequisites needed
%include typemaps.i
%include exception.i

// Fix where to add this
// Because of OT::, the ignore defined in Types.i is not taken into account
%ignore *::load(OT::Advocate & adv);
%ignore *::save(OT::Advocate & adv) const;

%import base_module.i
%import uncertainty_module.i

// The new classes
%include OTLHSprivate.hxx
%include LHSDesign.i
%include LHSResult.i
%include PlotDesign.i
%include TemperatureProfileImplementation.i
%include TemperatureProfile.i
%include GeometricProfile.i
%include LinearProfile.i
%include SpaceFillingImplementation.i
%include SpaceFilling.i
%include SpaceFillingC2.i
%include SpaceFillingMinDist.i
%include SpaceFillingPhiP.i
%include OptimalLHSImplementation.i
%include OptimalLHS.i
%include MonteCarloLHS.i
%include SimulatedAnnealingLHS.i


