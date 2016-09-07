// SWIG file

%{
#include "otlhs/LHSDesign.hxx"
%}

%include LHSDesign_doc.i

%include otlhs/LHSDesign.hxx
namespace OTLHS { %extend LHSDesign { LHSDesign(const LHSDesign & other) { return new OTLHS::LHSDesign(other); } } }
