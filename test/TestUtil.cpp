/*
TestUtil class definitions for the tests of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "TestUtil.hpp"

QGradientStops TestUtil::getDefaultGradientStops()
{
    QGradientStops gradientStops;
    gradientStops.append(QPair<double,QColor>(1.0, Qt::red));
    gradientStops.append(QPair<double,QColor>(0.6, QColor(255, 210, 0)));
    gradientStops.append(QPair<double,QColor>(0.5, Qt::yellow));
    gradientStops.append(QPair<double,QColor>(0.25, QColor(175, 255, 0)));
    gradientStops.append(QPair<double,QColor>(0.0, QColor(0, 200, 0)));
    return gradientStops;
}
