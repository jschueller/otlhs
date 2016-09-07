// SWIG file

%{
#include "otlhs/TemperatureProfile.hxx"
%}

%include TemperatureProfile_doc.i

TypedInterfaceObjectImplementationHelper(OTLHS, TemperatureProfile, TemperatureProfileImplementation)

%include otlhs/TemperatureProfile.hxx
namespace OTLHS { %extend TemperatureProfile { TemperatureProfile(const TemperatureProfile & other) { return new OTLHS::TemperatureProfile(other); } } }
