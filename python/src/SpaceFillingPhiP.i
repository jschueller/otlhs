// SWIG file

%{
#include "otlhs/SpaceFillingPhiP.hxx"
%}

%include SpaceFillingPhiP_doc.i

%include otlhs/SpaceFillingPhiP.hxx
namespace OTLHS { %extend SpaceFillingPhiP { SpaceFillingPhiP(const SpaceFillingPhiP & other) { return new OTLHS::SpaceFillingPhiP(other); } } }
