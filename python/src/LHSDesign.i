// SWIG file

%{
#include "LHSDesign.hxx"
%}

%include LHSDesign_doc.i

%include LHSDesign.hxx
namespace OTLHS { %extend LHSDesign { LHSDesign(const LHSDesign & other) { return new OTLHS::LHSDesign(other); } } }
