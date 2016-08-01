//                                               -*- C++ -*-
/**
 *  @file  PlotDesign.cxx
 *  @brief PlotDesign
 *
 *  Copyright (C) 2014 EDF
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */
#include "PlotDesign.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/Log.hxx"

using namespace OT;

namespace OTLHS
{

CLASSNAMEINIT(PlotDesign);

static const Factory<PlotDesign> Factory_PlotDesign;


PlotDesign::PlotDesign(const NumericalSample & data, const Interval & bounds,
    const UnsignedInteger Nx, const UnsignedInteger Ny,
    const String & title)
  : DrawableImplementation(data),
    bounds_(bounds),
    Nx_(Nx),
    Ny_(Ny)
{
  checkData(data);
  // Set Nx=Ny=size if Nx=Ny=0
  if ((Nx_ == 0) && (Ny_ == 0))
  {
    Nx_ = data_.getSize();
    Nx_ = data_.getSize();
  }
  if (bounds_.getDimension() != data_.getDimension())
    throw InvalidDimensionException(HERE) << "Incompatible dimension betwenn data & bounds. data dimension=" << data_.getDimension()
                                          << ", bounds dimension=" << bounds_.getDimension();
  labels_ = data_.getDescription();
  if((labels_.getSize() == 0) || labels_.isBlank()) buildDefaultLabels();
}

/** Default constructor */
PlotDesign::PlotDesign(const LHSResult & result, const UnsignedInteger Nx,
    const UnsignedInteger Ny, const String & title)
  : DrawableImplementation(),
    Nx_(Nx),
    Ny_(Ny)
{
  checkData(result.getOptimalDesign());
  // Set Nx=Ny=size if Nx=Ny=0
  if ((Nx_ == 0) && (Ny_ == 0))
  {
    Nx_ = data_.getSize();
    Nx_ = data_.getSize();
  }
  bounds_ = result.getBounds();
  labels_ = data_.getDescription();
  if((labels_.getSize() == 0) || labels_.isBlank()) buildDefaultLabels();
}


/* String converter */
String PlotDesign::__repr__() const
{
  OSS oss;
  oss << "class=" << PlotDesign::GetClassName()
      << " name=" << getName()
      << " data=" << data_
      << " bounds=" << bounds_
      << " derived from " << DrawableImplementation::__repr__();
  return oss;
}

/* Accessor for first coordinate */
NumericalSample PlotDesign::getData() const
{
  return data_;
}

/* Accessor for labels */
Description PlotDesign::getLabels() const
{
  return labels_;
}

void PlotDesign::setLabels(const Description & labels)
{
  if (labels.getSize() != data_.getDimension()) throw InvalidArgumentException(HERE) << "Error: the labels size must be equal equal to the data dimension";
  labels_ = labels;
}

/* Clean all the temporary data created by draw() method */
void PlotDesign::clean() const
{
  DrawableImplementation::clean();
  if ((dataFileName_ != "") && (remove(dataFileName_.c_str()) == -1)) LOGWARN(OSS() << "Could not remove file " << dataFileName_);
}

/* Draw method */
String PlotDesign::draw() const
{
  dataFileName_ = "";
  OSS oss;
  if (pointStyle_ != "none")
  {
    // Stores the data in a temporary file
    // The specific R command for drawing
    oss << "dim_ <- " << data_.getDimension() << "\n" ;
    oss << "size_ <- " << data_.getSize() << "\n";
    oss << DrawableImplementation::draw() << "\n";
    oss << "description=c(";
    const UnsignedInteger length(data_.getDimension());
    for(UnsignedInteger i = 0; i < length - 1; ++i) oss << "\"" << labels_[i] << "\"" << ",";
    oss << "\"" << labels_[length - 1] << "\"" << ") \n";
    // DataFrame organisation
    const String code((OSS() << getPointCode(pointStyle_)));
    oss << "dataOT <- data.frame(dataOT) \n";
    oss << "names(dataOT) <- description \n";
    oss << "Nx <- " << Nx_ << "\n Ny <- " << Ny_ << "\n";

    oss << " plot.design <- function (x, labels, xlim, ylim, Nx,Ny, panel = points, ..., label.pos = 0.5, "
        << " line.main = 3, cex.labels = NULL, font.labels = 1, gap = 1, col=\"black\", pch=NULL)\n"
        << " {  textPanel <- function(x = 0.5, y = 0.5, txt, cex, font) text(x, y, txt, cex = cex, font = font)\n"
        << " localAxis <- function(side, x, y, xpd, bg, col = NULL, main, oma, ...)\n"
        << "  { xpd <- NA\n if (side%%2L == 1L && xl[j])\n xpd <- FALSE\n"
        << " if (side%%2L == 0L && yl[i])\n xpd <- FALSE\n"
        << " if (side%%2L == 1L) Axis(x, side = side, xpd = xpd, ...)\n else Axis(y, side = side, xpd = xpd, ...)}\n"
        << " localPlot <- function(..., main, oma, font.main, cex.main) plot(...)\n"
        << " dots <- list(...)\n nmdots <- names(dots) \n nc <- ncol(x) \n"
        << " if (nc < 2) stop(\"only one column in the argument to 'pairs'\")\n"
        << " doText <- TRUE\n"
        << " if (is.null(labels)) doText <- FALSE\n"
        << " oma <- if (\"oma\" %in% nmdots)\n"
        << " dots$oma\n"
        << " main <- if (\"main\" %in% nmdots)\n"
        << " dots$main\n"
        << " if (is.null(oma)) \n"
        << " oma <- c(4, 4, if (!is.null(main)) 6 else 4, 4)\n"
        << " opar <- par(mfrow = c(nc, nc), mar = rep.int(gap/2, 4), oma = oma)\n"
        << " on.exit(par(opar))\n"
        << " dev.hold()\n"
        << " on.exit(dev.flush(), add = TRUE)\n"
        << " xl <- yl <- logical(nc)\n"
        << " xl[] <- grepl(\"x\", \"\")\n"
        << " yl[] <- grepl(\"y\", \"\")\n"
        << " for (i in 1L:nc)\n"
        << " for (j in 1L:nc)\n"
        << " { l <- paste0(ifelse(xl[j], \"x\", \"\"), ifelse(yl[i], \"y\", \"\"))\n"
        << " localPlot(x[, j], x[, i], xlab = \"\", ylab = \"\", axes = FALSE, type = \"n\", ..., log = l,"
        << " xlim = xlim[j,i,], ylim=ylim[j,i,])\n"
        << " box()\n if (i == 1 && (!(j%%2L))) localAxis(1L + 2L, x[, j], x[, i], ...)\n"
        << " if (i == nc && (j%%2L)) localAxis(3L - 2L, x[, j], x[, i], ...)\n"
        << " if (j == 1 && (!(i%%2L))) localAxis(2L, x[, j], x[, i], ...)\n"
        << " if (j == nc && (i%%2L)) localAxis(4L, x[, j], x[, i], ...)\n"
        << " mfg <- par(\"mfg\")\n"
        << " if (i == j)\n"
        << " {\n"
        << " if (doText){\n"
        << " par(usr = c(0, 1, 0, 1))\n"
        << " if (is.null(cex.labels))\n {\n"
        << " l.wid <- strwidth(labels, \"user\")\n"
        << "cex.labels <- max(0.8, min(2, 0.9/max(l.wid)))\n"
        << "}\n"
        << " xlp <- if (xl[i]) 10^0.5\n"
        << " else 0.5\n"
        << " ylp <- if (yl[j]) 10^label.pos\n"
        << " else label.pos\n"
        << " textPanel(xlp, ylp, labels[i], cex = cex.labels, font = font.labels)\n"
        << "}\n"
        << "}\n"
        << "else\n"
        << "{points(as.vector(x[, j]), as.vector(x[, i]), col=col,..., pch = pch)\n"
        << "dx <- xlim[j,i,2] - xlim[j,i,1]\n"
        << "dy <- ylim[j,i,2] - ylim[j,i,1]\n"
        << " xx <- xlim[j,i,]\n"
        << "for(k in (1:Ny))\n"
        << "{ kk <- k-1\n"
        << " yy <- c(ylim[j,i,1]+kk*dy/(Ny), ylim[j,i,1]+kk*dy/(Ny))\n"
        << " lines(xx,yy,type=\"l\",lwd=0.2)}\n"
        << " yy <- c(ylim[j,i,2], ylim[j,i,2])\nlines(xx,yy,type=\"l\",lwd=0.2)\n yy <- ylim[j,i,]\n"
        << " for(k in (1:Nx))\n"
        << " { kk <- k-1\n xx <- c(xlim[j,i,1]+kk*dx/(Nx), xlim[j,i,1]+kk*dx/(Nx))\n lines(xx,yy,type=\"l\",lwd=0.2)}\n"
        << " xx <- c(xlim[j,i,2], xlim[j,i,2])\n lines(xx,yy,type=\"l\",lwd=0.2)}\n"
        << " if (any(par(\"mfg\") != mfg)) stop(\"the 'panel' function made a new plot\")\n"
        << " else par(new = FALSE)}\n"
        << " if (!is.null(main))\n"
        << " { font.main <- if (\"font.main\" %in% nmdots)\n"
        << " dots$font.main\n"
        << " else par(\"font.main\")\n"
        << " cex.main <- if (\"cex.main\" %in% nmdots)\n"
        << " dots$cex.main\n"
        << " else par(\"cex.main\")\n"
        << "mtext(main, 3, line.main, outer = TRUE, at = 0.5, cex = cex.main, font = font.main)}\n"
        << "invisible(NULL)\n}\n"
        << "xlim <- array(0, dim=c(" << bounds_.getDimension() << "," << bounds_.getDimension() << ", 2))\n"
        << "ylim <- array(0, dim=c(" << bounds_.getDimension() << "," << bounds_.getDimension() << ", 2))\n";
    for(UnsignedInteger i = 0; i< bounds_.getDimension(); ++i)
    {
      for(UnsignedInteger j = 0; j <  bounds_.getDimension(); ++j)
      {
        oss << " xlim["<< j+1 << "," << i+1 << ",1] <- " << bounds_.getLowerBound()[j] << "\n"
            << " xlim["<< j+1 << "," << i+1 << ",2] <- " << bounds_.getUpperBound()[j] << "\n"
            << " ylim["<< j+1 << "," << i+1 << ",1] <- " << bounds_.getLowerBound()[i] << "\n"
            << " ylim["<< j+1 << "," << i+1 << ",2] <- " << bounds_.getUpperBound()[i] << "\n";
      }
    }
    oss << "plot.design(dataOT"
        << ",labels=description"
        << ",xlim=xlim,ylim=ylim,Nx=Nx,Ny=Ny"
        << ",pch=" << (pointStyle_ == "dot" ? "\".\"" : code)
        << ",col=\"" << color_ << "\""
        << ",main=\"" << getTitle() << "\")";
  }
  return oss;
}

/* Clone method */
PlotDesign * PlotDesign::clone() const
{
  return new PlotDesign(*this);
}

String PlotDesign::getTitle() const
{
  return title_;
}

void PlotDesign::setTitle(const String & title)
{
  title_ = title;
}

/* Check for data validity */
void PlotDesign::checkData(const NumericalSample & data) const
{
  if (data.getDimension() < 2)
  {
    throw InvalidDimensionException(HERE) << "Expected sample of dimension >=2: got " << data.getDimension();
  }
}

/* Build default labels by taking the level values */
void PlotDesign::buildDefaultLabels()
{
  const UnsignedInteger number(data_.getDimension());
  labels_ = Description(number);
  for (UnsignedInteger i = 0; i < number; ++i) labels_[i] = OSS() << "V" << i + 1;
}

/* Method save() stores the object through the StorageManager */
void PlotDesign::save(Advocate & adv) const
{
  DrawableImplementation::save(adv);
  adv.saveAttribute( "labels_", labels_ );
  adv.saveAttribute( "title_", title_ );
}

/* Method load() reloads the object from the StorageManager */
void PlotDesign::load(Advocate & adv)
{
  DrawableImplementation::load(adv);
  adv.loadAttribute( "labels_", labels_ );
  adv.loadAttribute( "title_", title_ );
}


} /* namespace OTLHS */
