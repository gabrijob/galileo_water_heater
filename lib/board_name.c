/*
  board_name.c: Returns board name identification.
  
  Copyright (c) 2020 Walter Fetter Lages <w.fetter@ieee.org>

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

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <galileoio.h>

int board_name(void)
{
	int fd;
	char s[20];
	int n;
	
	fd=open("/sys/devices/virtual/dmi/id/board_name",O_RDONLY);
	n=read(fd,s,sizeof s);
	close(fd);
	s[n-1]='\0'; /* Discards new line */

	if(strncmp(s,"Galileo",sizeof s) == 0)
		return BOARD_GALILEO_GEN1;
	else if(strncmp(s,"GalileoGen2",sizeof s) == 0)
		return BOARD_GALILEO_GEN2;
        else return BOARD_UNKNOWN;
}
