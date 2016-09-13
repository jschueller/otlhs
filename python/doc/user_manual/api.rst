API
---
The description of available classes and their methods as defined by the docstrings.

.. currentmodule:: otlhs

Optimal LHS generation
^^^^^^^^^^^^^^^^^^^^^^

.. autosummary::
    :toctree: _generated/
    :template: class.rst_t

    LHSDesign
    OptimalLHS
    OptimalLHSImplementation
    MonteCarloLHS
    SimulatedAnnealingLHS
    LHSResult

Space Filling
~~~~~~~~~~~~~
Used to define the optimization criterion in :class:`~otgui.OptimalLHS`.

.. autosummary::
    :toctree: _generated/
    :template: class.rst_t

    SpaceFilling
    SpaceFillingImplementation
    SpaceFillingC2
    SpaceFillingMinDist
    SpaceFillingPhiP

Temperature Profile
~~~~~~~~~~~~~~~~~~~
Used to control the optimization in :class:`~otgui.SimulatedAnnealingLHS`.

.. autosummary::
    :toctree: _generated/
    :template: class.rst_t

    TemperatureProfile
    TemperatureProfileImplementation
    LinearProfile
    GeometricProfile

Optimal LHS plots
^^^^^^^^^^^^^^^^^
This automates plot methods decicated to LHS designs.

.. autosummary::
    :toctree: _generated/
    :template: class.rst_t

    PlotDesign 
