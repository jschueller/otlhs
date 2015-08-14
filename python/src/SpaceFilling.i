// SWIG file

%{
#include "SpaceFilling.hxx"
%}

%include SpaceFilling_doc.i

%typemap(in) const OTLHS::SpaceFilling & {
  void * ptr = 0;
  if (SWIG_IsOK(SWIG_ConvertPtr($input, (void **) &$1, $1_descriptor, 0))) {
    // From interface class, ok
  } else if (SWIG_IsOK(SWIG_ConvertPtr($input, &ptr, SWIGTYPE_p_OTLHS__SpaceFillingImplementation, 0))) {
    // From Implementation*
    OTLHS::SpaceFillingImplementation * p_impl = reinterpret_cast< OTLHS::SpaceFillingImplementation * >( ptr );
    $1 = new OTLHS::SpaceFilling( *p_impl );
  }
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_POINTER) const OTLHS::SpaceFilling & {
  $1 = SWIG_IsOK(SWIG_ConvertPtr($input, NULL, $1_descriptor, 0))
    || SWIG_IsOK(SWIG_ConvertPtr($input, NULL, SWIGTYPE_p_OTLHS__SpaceFillingImplementation , 0));
}

%include SpaceFilling.hxx
namespace OTLHS { %extend SpaceFilling { SpaceFilling(const SpaceFilling & other) { return new OTLHS::SpaceFilling(other); } } }
