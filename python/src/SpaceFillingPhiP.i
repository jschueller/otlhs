// SWIG file

%{
#include "SpaceFillingPhiP.hxx"
%}

%include SpaceFillingPhiP_doc.i

%include SpaceFillingPhiP.hxx
namespace OTLHS { %extend SpaceFillingPhiP { SpaceFillingPhiP(const SpaceFillingPhiP & other) { return new OTLHS::SpaceFillingPhiP(other); } } }
