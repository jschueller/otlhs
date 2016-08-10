"""
    otlhs --- An OpenTURNS module
    ==================================

    Contents
    --------
      'otlhs' is a module for OpenTURNS

"""

import sys
if sys.platform.startswith('win'):
    # this ensures OT dll is loaded
    import openturns

from .otlhs import *

__version__ = '1.3'

