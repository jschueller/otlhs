// SWIG file

%{
#include "GeometricProfile.hxx"
%}

%include GeometricProfile_doc.i

%include GeometricProfile.hxx
namespace OTLHS { %extend GeometricProfile { GeometricProfile(const GeometricProfile & other) { return new OTLHS::GeometricProfile(other); } } }
