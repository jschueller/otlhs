// SWIG file

%{
#include "OptimalLHS.hxx"
%}

%include OptimalLHS_doc.i

%typemap(in) const OTLHS::OptimalLHS & {
  void * ptr = 0;
  if (SWIG_IsOK(SWIG_ConvertPtr($input, (void **) &$1, $1_descriptor, 0))) {
    // From interface class, ok
  } else if (SWIG_IsOK(SWIG_ConvertPtr($input, &ptr, SWIGTYPE_p_OTLHS__OptimalLHSImplementation, 0))) {
    // From Implementation*
    OTLHS::OptimalLHSImplementation * p_impl = reinterpret_cast< OTLHS::OptimalLHSImplementation * >( ptr );
    $1 = new OTLHS::OptimalLHS( *p_impl );
  }
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_POINTER) const OTLHS::OptimalLHS & {
  $1 = SWIG_IsOK(SWIG_ConvertPtr($input, NULL, $1_descriptor, 0))
    || SWIG_IsOK(SWIG_ConvertPtr($input, NULL, SWIGTYPE_p_OTLHS__OptimalLHSImplementation , 0));
}

%include OptimalLHS.hxx
namespace OTLHS { %extend OptimalLHS { OptimalLHS(const OptimalLHS & other) { return new OTLHS::OptimalLHS(other); } } }
