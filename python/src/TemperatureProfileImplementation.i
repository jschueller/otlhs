// SWIG file

%{
#include "otlhs/TemperatureProfileImplementation.hxx"
%}

%include TemperatureProfileImplementation_doc.i

%template(TemperatureProfileImplementationdInterfaceObject)           OT::TypedInterfaceObject<OTLHS::TemperatureProfileImplementation>;

%include otlhs/TemperatureProfileImplementation.hxx
namespace OTLHS { %extend TemperatureProfileImplementation { TemperatureProfileImplementation(const TemperatureProfileImplementation & other) { return new OTLHS::TemperatureProfileImplementation(other); } } }
