// SWIG file

%{
#include "otlhs/MonteCarloLHS.hxx"
%}

%include MonteCarloLHS_doc.i

%include otlhs/MonteCarloLHS.hxx
namespace OTLHS { %extend MonteCarloLHS { MonteCarloLHS(const MonteCarloLHS & other) { return new OTLHS::MonteCarloLHS(other); } } }
