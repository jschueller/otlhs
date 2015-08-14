// SWIG file

%{
#include "MonteCarloLHS.hxx"
%}

%include MonteCarloLHS_doc.i

%include MonteCarloLHS.hxx
namespace OTLHS { %extend MonteCarloLHS { MonteCarloLHS(const MonteCarloLHS & other) { return new OTLHS::MonteCarloLHS(other); } } }
