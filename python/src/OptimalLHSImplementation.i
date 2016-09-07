// SWIG file

%{
#include "otlhs/OptimalLHSImplementation.hxx"
%}

%include OptimalLHSImplementation_doc.i

%template(OptimalLHSImplementationdInterfaceObject)           OT::TypedInterfaceObject<OTLHS::OptimalLHSImplementation>;

%include otlhs/OptimalLHSImplementation.hxx
namespace OTLHS { %extend OptimalLHSImplementation { OptimalLHSImplementation(const OptimalLHSImplementation & other) { return new OTLHS::OptimalLHSImplementation(other); } } }
