// SWIG file

%{
#include "otlhs/LinearProfile.hxx"
%}

%include LinearProfile_doc.i

%include otlhs/LinearProfile.hxx
namespace OTLHS { %extend LinearProfile { LinearProfile(const LinearProfile & other) { return new OTLHS::LinearProfile(other); } } }
