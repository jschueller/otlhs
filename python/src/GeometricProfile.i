// SWIG file

%{
#include "otlhs/GeometricProfile.hxx"
%}

%include GeometricProfile_doc.i

%include otlhs/GeometricProfile.hxx
namespace OTLHS { %extend GeometricProfile { GeometricProfile(const GeometricProfile & other) { return new OTLHS::GeometricProfile(other); } } }
