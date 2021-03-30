/*
  pwm_control.h: Interface to control the average tension from a Galileo Board
  
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

#ifndef PWMTENSION_H
#define PWMTENSION_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int pwm_init(void);
extern void pwm_tension(int fd_dc, int avg_tension);
void pwm_end(int fd_dc);

#ifdef __cplusplus
};
#endif

#endif
