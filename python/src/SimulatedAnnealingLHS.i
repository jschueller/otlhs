// SWIG file

%{
#include "SimulatedAnnealingLHS.hxx"
%}

%include SimulatedAnnealingLHS_doc.i

%include SimulatedAnnealingLHS.hxx
namespace OTLHS { %extend SimulatedAnnealingLHS { SimulatedAnnealingLHS(const SimulatedAnnealingLHS & other) { return new OTLHS::SimulatedAnnealingLHS(other); } } }
