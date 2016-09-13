// SWIG file

%{
#include "otlhs/SpaceFilling.hxx"
%}

%include SpaceFilling_doc.i

TypedInterfaceObjectImplementationHelper(OTLHS, SpaceFilling, SpaceFillingImplementation)

%ignore OTLHS::SpaceFilling::perturbLHS;

%include otlhs/SpaceFilling.hxx
namespace OTLHS { %extend SpaceFilling { SpaceFilling(const SpaceFilling & other) { return new OTLHS::SpaceFilling(other); } } }
