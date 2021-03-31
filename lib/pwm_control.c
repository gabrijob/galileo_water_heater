/*
  pwm_control.c: Interface to control the average tension on a PWM signal from a Galileo Board
  
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



#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <galileoio.h>
#include <pwm_control.h>

#define PWM_PERIOD_STR "1000000"
#define PWM_PERIOD 1000000
#define VCC 3.3

/*
 * Initializer to pwm funcions (pwm3 for this project).
 * @return Duty cycle file handler if successful, -1 otherwise.
 */
int pwm_init() {
	int fd_dc;

        pputs("/sys/class/pwm/pwmchip0/pwm3/period", PWM_PERIOD_STR);

	if((fd_dc=open("/sys/class/pwm/pwmchip0/pwm3/duty_cycle",O_WRONLY)) < 0)
        {
                perror("Opening duty_cycle:");
                return -1;
        }
        write(fd_dc,"0\n",2);

        pputs("/sys/class/pwm/pwmchip0/pwm3/enable","1");
	return fd_dc;
}

/*
 * Sets the new average tension for pwm3.
 * @arg Duty cycle file handler
 * @arg Desired average tension 
 */ 
void pwm_tension(int fd_dc, int avg_tension) {
        int new_dc;
	char str[80];

	new_dc = avg_tension/VCC * PWM_PERIOD;

        lseek(fd_dc,0,SEEK_SET);
        snprintf(str,sizeof str,"%d\n",new_dc);
        write(fd_dc,str,strlen(str));
}

/*
 * Closes duty cycle file and disables pwm3.
 */
void pwm_end(int fd_dc) {
	close(fd_dc);
        pputs("/sys/class/pwm/pwmchip0/pwm3/enable","0");  
}
