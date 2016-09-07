// SWIG file

%{
#include "otlhs/SpaceFillingC2.hxx"
%}

%include SpaceFillingC2_doc.i

%include otlhs/SpaceFillingC2.hxx
namespace OTLHS { %extend SpaceFillingC2 { SpaceFillingC2(const SpaceFillingC2 & other) { return new OTLHS::SpaceFillingC2(other); } } }
