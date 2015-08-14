// SWIG file

%{
#include "TemperatureProfileImplementation.hxx"
%}

%include TemperatureProfileImplementation_doc.i

%template(TemperatureProfileImplementationdInterfaceObject)           OT::TypedInterfaceObject<OTLHS::TemperatureProfileImplementation>;

%include TemperatureProfileImplementation.hxx
namespace OTLHS { %extend TemperatureProfileImplementation { TemperatureProfileImplementation(const TemperatureProfileImplementation & other) { return new OTLHS::TemperatureProfileImplementation(other); } } }
