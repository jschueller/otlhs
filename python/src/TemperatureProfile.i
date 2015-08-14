// SWIG file

%{
#include "TemperatureProfile.hxx"
%}

%include TemperatureProfile_doc.i

%typemap(in) const OTLHS::TemperatureProfile & {
  void * ptr = 0;
  if (SWIG_IsOK(SWIG_ConvertPtr($input, (void **) &$1, $1_descriptor, 0))) {
    // From interface class, ok
  } else if (SWIG_IsOK(SWIG_ConvertPtr($input, &ptr, SWIGTYPE_p_OTLHS__TemperatureProfileImplementation, 0))) {
    // From Implementation*
    OTLHS::TemperatureProfileImplementation * p_impl = reinterpret_cast< OTLHS::TemperatureProfileImplementation * >( ptr );
    $1 = new OTLHS::TemperatureProfile( *p_impl );
  }
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_POINTER) const OTLHS::TemperatureProfile & {
  $1 = SWIG_IsOK(SWIG_ConvertPtr($input, NULL, $1_descriptor, 0))
    || SWIG_IsOK(SWIG_ConvertPtr($input, NULL, SWIGTYPE_p_OTLHS__TemperatureProfileImplementation , 0));
}

%include TemperatureProfile.hxx
namespace OTLHS { %extend TemperatureProfile { TemperatureProfile(const TemperatureProfile & other) { return new OTLHS::TemperatureProfile(other); } } }
