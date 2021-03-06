// SWIG file

%{
#include "otlhs/OptimalLHS.hxx"
%}

%include OptimalLHS_doc.i

TypedInterfaceObjectImplementationHelper(OTLHS, OptimalLHS, OptimalLHSImplementation)

%include otlhs/OptimalLHS.hxx
namespace OTLHS { %extend OptimalLHS { OptimalLHS(const OptimalLHS & other) { return new OTLHS::OptimalLHS(other); } } }
