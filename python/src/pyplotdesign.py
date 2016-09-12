import openturns as ot
import matplotlib
import matplotlib.pyplot as plt

def PyPlotDesign(design, bounds, Nx, Ny, figure=None, axes=[], plot_kwargs={}, axes_kwargs={}, text_kwargs={}):
    """
    Plot a design using a scatter plot approach (plots 2D marginals)
    In addition, the function plot a grid, i.e. horizontal and vertical lines to distinguish LHS character
    The function requires Matplotlib.

    Parameters
    ----------
    design : :class:`openturns.NumericalSample` or 2D array-like
        Design
    bounds: :class:`openturns.Interval`
        Bounds of the underlying uniform distributions
    nxdiv : int
        Number of subdivisions in the X axis
    nydiv : int
        Number of subdivisions in the Y axis

    Returns
    -------
    fig : matplotlib figure
          Figure representing the LHS

    Examples
    --------
    >>> import openturns as ot
    >>> import otlhs
    >>> # Bounds are [0,1]^5
    >>> bounds = ot.Interval(5)
    >>> # Size of sample
    >>> size = 10
    >>> # Factory: lhs generates (here centered)
    >>> lhsDesign = otlhs.LHSDesign(bounds, size, True)
    >>> # Generate a design
    >>> design = lhsDesign.generate()
    >>> # Plot the design
    >>> from otlhs.pyplotdesign import PyPlotDesign
    >>> fig = PyPlotDesign(design, bounds, 10, 10)
    """

    # check that arguments are dictionnaries
    assert(isinstance(axes_kwargs, dict))
    assert(isinstance(plot_kwargs, dict))
    assert(isinstance(text_kwargs, dict))

    # retrieve data
    data = ot.NumericalSample(design)
    dim = data.getDimension()
    if dim < 2:
        raise TypeError("Expected designs of dimension >=2")
    labels = data.getDescription()

    # set bounding box
    # set figure
    if figure is None:
        figure = plt.figure()
    else:
        if len(axes) == 0:
            axes = figure.axes

    # set axes
    if len(axes) == 0:
        axes = [figure.add_subplot(111, **axes_kwargs)]

    # disable axis : grid, ticks, axis?
    axes[0].axison = False

    if 'title' in axes_kwargs:
        axes_kwargs.pop('title')
    axes_kwargs['xticks'] = []
    axes_kwargs['yticks'] = []

    # adjust font
    if (not 'fontsize' in text_kwargs) and (not 'size' in text_kwargs):
        text_kwargs['fontsize'] = max(16 - dim, 4)
    text_kwargs.setdefault('horizontalalignment', 'center')
    text_kwargs.setdefault('verticalalignment', 'center')

    # set marker
    pointStyleDict = {'square': 's', 'circle': 'o', 'triangleup': '2', 'plus': '+', 'times': '+', 'diamond': '+', 'triangledown':
                      'v', 'star': '*', 'fsquare': 's', 'fcircle': 'o', 'ftriangleup': '2', 'fdiamond': 'D', 'bullet': '.', 'dot': ',', 'none': 'None'}
    if not 'marker' in plot_kwargs:
        plot_kwargs['marker'] = pointStyleDict["square"]

    # Particular case of dim=2
    if dim == 2:
        x = data.getMarginal(0)
        y = data.getMarginal(1)
        # x axis
        x_min =  bounds.getLowerBound()[0]
        x_max = bounds.getUpperBound()[0]
        dx = x_max - x_min
        # y axis
        y_min = bounds.getLowerBound()[1]
        y_max = bounds.getUpperBound()[1]
        dy = y_max - y_min
        # Draw horizontal lines
        dydiv = float(Ny)
        xk = [x_min, x_max]
        for k in range(Ny):
            yk = [y_min + k*dy/dydiv, y_min + k*dy/dydiv]
            axes[0].plot(xk,yk,"k")
        yk = [y_max, y_max]
        axes[0].plot(xk,yk,"k")
        # Draw vertical lines
        dxdiv = float(Nx)
        yk = [y_min, y_max]
        for k in range(Nx):
            xk = [x_min + k*dx/dxdiv, x_min + k*dx/dxdiv]
            axes[0].plot(xk,yk,"k-")
        xk = [x_max, x_max]
        axes[0].plot(xk,yk,"k-")
        plot_kwargs['linestyle'] = 'None'
        axes[0].plot(x, y, **plot_kwargs)
        axes[0].set_xlabel(labels[0])
        axes[0].set_ylabel(labels[1])
        axes[0].set_xlim(x_min, x_max)
        axes[0].set_ylim(y_min, y_max)
        return figure

    for i in range(dim):
        for j in range(dim):
            if len(axes) <= dim * dim:
                axes.append(figure.add_subplot(dim, dim, 1 + i * dim + j, **axes_kwargs))
            if i != j:
                x = data.getMarginal(i)
                y = data.getMarginal(j)
                # x axis
                x_min =  bounds.getLowerBound()[i]
                x_max = bounds.getUpperBound()[i]
                dx = x_max - x_min
                # y axis
                y_min = bounds.getLowerBound()[j]
                y_max = bounds.getUpperBound()[j]
                dy = y_max - y_min
                # Draw horizontal lines
                dydiv = float(Ny)
                for k in range(Ny):
                    xk = [x_min, x_max]
                    yk = [y_min + k*dy/dydiv, y_min + k*dy/dydiv]
                    axes[1 + i * dim + j].plot(xk,yk,"k-")
                # Draw vertical lines
                dxdiv = float(Nx)
                for k in range(Nx):
                    xk = [x_min + k*dx/dxdiv, x_min + k*dx/dxdiv]
                    yk = [y_min, y_max]
                    axes[1 + i * dim + j].plot(xk,yk,"k-")
                plot_kwargs['linestyle'] = 'None'
                axes[1 + i * dim + j].plot(x, y, **plot_kwargs)
                axes[1 + i * dim + j].set_xlim(x_min, x_max)
                axes[1 + i * dim + j].set_ylim(y_min, y_max)
            else:
                text_kwargs['transform'] = axes[1 + i * dim + j].transAxes
                axes[1 + i * dim + j].text(0.5, 0.5, labels[i], **text_kwargs)

    # Finally get the figure
    return figure
