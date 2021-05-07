/*
  galileoio.h: Helper functions for Galileo I/O
  
  Copyright (c) 2016, 2020 Walter Fetter Lages <w.fetter@ieee.org>

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

#ifndef GALILEO2IO_H
#define GALILEO2IO_H

#ifdef __cplusplus
extern "C"
{
#endif

enum BOARD_NAME
{
	BOARD_GALILEO_GEN1=1,
	BOARD_GALILEO_GEN2=2,
	BOARD_UNKNOWN=-1
};

extern int board_name(void);
extern char * pgets(char *s,int size,const char path[]);
extern int pputs(const char path[],const char s[]);

#ifdef __cplusplus
};
#endif

#endif
