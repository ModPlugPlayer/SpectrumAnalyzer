/*
Dimmable class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/
#pragma once

class Dimmable {
public:
    inline Dimmable();
    //darker if dimmingPercentage is between -99 and -1
    //lighter if dimmingPercentage is between 1 and 99
    //black if dimmingPercentage is -100
    //white if dimmingPercentage is 100
    inline int getDimmingPercentage() const;
    inline void setDimmingPercentage(const int &dimmingPercentage);

    inline unsigned char getTransparencyPercentage() const;
    inline void setTransparencyPercentage(unsigned const char &transparencyPercentage);

private:
    int dimmingPercentage;
    unsigned char transparencyPercentage;
};

inline Dimmable::Dimmable()
{
    this->dimmingPercentage = 0;
    this->transparencyPercentage = 0;
}

inline int Dimmable::getDimmingPercentage() const {
    return dimmingPercentage;
}

inline void Dimmable::setDimmingPercentage(const int &dimmingPercentage) {
    this->dimmingPercentage = dimmingPercentage;
}

inline unsigned char Dimmable::getTransparencyPercentage() const {
    return transparencyPercentage;
}

inline void Dimmable::setTransparencyPercentage(const unsigned char &transparencyPercentage) {
    this->transparencyPercentage = transparencyPercentage;
}
