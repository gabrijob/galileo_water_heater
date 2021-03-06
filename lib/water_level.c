/*
  water_level.c: Interface to scan a water level sensor for a Galileo Board
  
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

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <galileoio.h>
#include <sensors.h>


/**
 * Initializer to water level sensor funcions (ad0 for this project).
 * @return I02 file handler if successful, -1 otherwise.
 */
int init_water_lvl_sensor() {
        int water_level_sensor_1_fd;
	int fd;
        char s[20];
	int n;

		
	fd=open("/sys/devices/virtual/dmi/id/board_name",O_RDONLY);
	n=read(fd,s,sizeof s);
	close(fd);
	s[n-1]='\0'; /* Discards new line */

	if(strncmp(s,"Galileo",sizeof s) == 0)
	{
		//led_fd=open("/sys/class/gpio/gpio18/value",O_WRONLY);
		water_level_sensor_1_fd=open("/sys/class/gpio/gpio32/value",O_RDONLY);
	}
	else if(strncmp(s,"GalileoGen2",sizeof s) == 0)
	{
		perror("\nGalileoGen2 board not supported.");
		return -1;
	}
        else return -1;


	return water_level_sensor_1_fd;
}



/**
 * Returns if the minimum water level is available. 
 */
int water_level(int water_level_sensor_1_fd) {
	char w_lvl;
	
	lseek(water_level_sensor_1_fd,0,SEEK_SET);
	read(water_level_sensor_1_fd,&w_lvl,sizeof w_lvl);
	
	w_lvl = !(w_lvl-'0');  
	return (int)w_lvl;
}

/**
 * Closes I02 file.
 */
void end_water_lvl_sensor(int fd) {
	close(fd);
}
