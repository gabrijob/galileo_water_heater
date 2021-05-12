/*
  temperature.c: Interface to scan a temperature sensor for a Galileo Board
  
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

#include <byteswap.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <galileoio.h>
#include <sensors.h>

#define R2 10000		//!< Voltate divider resistance
#define B 3460			//!< Thermistor gain
#define R_THERM_DEFAULT 10000	//!< Thermistor resistance at base temperature
#define T1 298.15		//!< Themistor base temperature  


double scale;

/**
 * Initializer to temperature sensor funcions (ad0 for this project).
 * @return AD0 file handler if successful, -1 otherwise.
 */
int init_temp_sensor() {
	int fd_temp;
	char data_str[80];
        //double scale;

	if((fd_temp=open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw",O_RDONLY)) < 0)
        {
                perror("Opening in_voltage0raw:");
                return -1;
        }
	pgets(data_str,sizeof data_str,"/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
        scale=atof(data_str)/1000.0;
        
	return fd_temp;
}



/** Calculates the NTCs resistance through a voltage divider */
double R_thermistor(double v_in) {
	return R2*(VCC - v_in) / v_in;
}

/** Calculate NTC temperature using its measured tension plus compnent constants*/
double calc_temp(double v_in) {
	double R_therm = R2*(VCC - v_in) / v_in;
	double a;
	double b;
	double c;
	double d;
	
	a = 1/T1;
	b = log(R_THERM_DEFAULT/R_therm);
	c = b/B;
	d = 1/(a-c);

	return d - 273.15;
}


/** Reads raw voltage from AD0 and returns the temperature in Cº*/
double temperature(int fd_temp) {
        char data_str[80];
        uint16_t raw; /* be:u12/16>>0 */
	

        lseek(fd_temp,0,SEEK_SET);
        read(fd_temp,data_str,sizeof data_str);
        raw=atoi(data_str);
        //raw=bswap_16(raw) & 0xfff;

	
        return calc_temp(raw * scale);
}

/**
 * Closes ad0 file.
 */
void end_temp_sensor(int fd_temp) {
	close(fd_temp);
}
