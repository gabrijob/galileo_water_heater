#include <stdio.h>
#include <sensors.h>
#include <pwm_control.h>
#include <galileoio.h>

int main(int argc,char *argv[]) {
	int is_water_lvl;
	double temp_read;
	int pid_tension = 0;

	//int fd_wlvl = wlvl_init() ?
	//int fd_temp = temperature_init() ?
	int fd_dc = pwm_init();

	for(;;) {
		temp_read = temperature();
		is_water_lvl = water_level();
		printf("Temperature:%f / Water Lv:%d\n", temp_read, is_water_lvl);
		if (is_water_lvl == '1') {
			// TODO: calc PID tension
			pwm_tension(fd_dc, pid_tension);
		}
	}

	pwm_end(fd_dc);

	return 0;
}
