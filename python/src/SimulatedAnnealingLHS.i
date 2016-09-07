// SWIG file

%{
#include "otlhs/SimulatedAnnealingLHS.hxx"
%}

%include SimulatedAnnealingLHS_doc.i

%include otlhs/SimulatedAnnealingLHS.hxx
namespace OTLHS { %extend SimulatedAnnealingLHS { SimulatedAnnealingLHS(const SimulatedAnnealingLHS & other) { return new OTLHS::SimulatedAnnealingLHS(other); } } }
