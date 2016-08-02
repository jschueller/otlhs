// SWIG file

%{
#include "TemperatureProfile.hxx"
%}

%include TemperatureProfile_doc.i

TypedInterfaceObjectImplementationHelper(OTLHS, TemperatureProfile, TemperatureProfileImplementation)

%include TemperatureProfile.hxx
namespace OTLHS { %extend TemperatureProfile { TemperatureProfile(const TemperatureProfile & other) { return new OTLHS::TemperatureProfile(other); } } }
