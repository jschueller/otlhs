// SWIG file

%{
#include "SpaceFilling.hxx"
%}

%include SpaceFilling_doc.i

TypedInterfaceObjectImplementationHelper(OTLHS, SpaceFilling, SpaceFillingImplementation)

%include SpaceFilling.hxx
namespace OTLHS { %extend SpaceFilling { SpaceFilling(const SpaceFilling & other) { return new OTLHS::SpaceFilling(other); } } }
