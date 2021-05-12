/*
  sensors.h: Interface for sensors on a Galileo Board
  
  Copyright (c) 2021 Gabriel J. A. Grabher <gabriel.grabher@inf.ufrgs.br>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

#ifndef WATERLVL_H
#define WATERLVL_H

#ifdef __cplusplus
extern "C"
{
#endif

#define VCC 3.3 //!< Define the VCC value.

extern int water_level(int water_level_sensor_1_fd);
extern double temperature(int fd);
extern int init_temp_sensor(void);
extern void end_temp_sensor(int fd_temp);
extern int init_water_lvl_sensor(void);
extern void end_water_lvl_sensor(int fd);


#ifdef __cplusplus
};
#endif

#endif
