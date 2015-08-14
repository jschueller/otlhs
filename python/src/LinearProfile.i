// SWIG file

%{
#include "LinearProfile.hxx"
%}

%include LinearProfile_doc.i

%include LinearProfile.hxx
namespace OTLHS { %extend LinearProfile { LinearProfile(const LinearProfile & other) { return new OTLHS::LinearProfile(other); } } }
