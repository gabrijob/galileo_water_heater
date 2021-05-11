#include <stdio.h>
#include <sensors.h>
#include <pwm_control.h>
#include <galileoio.h>

#define OUTPUT_FILE "temp.out"

#define KC 0.02
#define KI 0
#define KD 0

#define MAX_TEMP_OBS 1000
double temperatures[MAX_TEMP_OBS];
int last_temp_index = 0;

double goal_temps[MAX_TEMP_OBS];

void store_temperature(double temp) {
	last_temp_index++;

	if(last_temp_index >= MAX_TEMP_OBS)
		last_temp_index = 0;

	temperatures[last_temp_index] = temp;
}


double pid_controller(double goal_temp) {
	double error;
	double derivative;
	double integral;
	int i =0;

	goal_temps[last_temp_index] = goal_temp;
	// Calculate error
	error = goal_temp - temperatures[last_temp_index];
	printf(" Error:%f / ", error);
	// Calculate derivative temperature
	if(last_temp_index >= 1) {
		derivative = (goal_temps[last_temp_index] - temperatures[last_temp_index]) 
			- (goal_temps[last_temp_index-1] - temperatures[last_temp_index-1]);
	}
	else {
		derivative = 0;
	}

	// Calculate integral temperature
	integral = 0;
	for(i=0; i<last_temp_index; i++){
		integral += goal_temps[i] - temperatures[i];
	}


	return KC*error + KI*integral* + KD*derivative;
}


int main(int argc,char *argv[]) {
	int is_water_lvl;
	double temp_read;
	double pid_tension = 0;
	int goal_v = 100;
	FILE *file;

	if(argc > 1) {
		goal_v = (int) argv[1];
	}
	
        if((file=fopen(OUTPUT_FILE,"w")) == NULL)
        {
                perror("Opening output file:");
                return -1;
        }	

	//int fd_wlvl = wlvl_init() ?
	//int fd_temp = temperature_init() ?
	int fd_dc = pwm_init();

	int timestamp = 0;
	for(;;) {
		temp_read = temperature();
		store_temperature(temp_read);
		
		is_water_lvl = water_level();
		printf("Temperature:%f / Water Lv:%d / Goal temp:%d\n", temperatures[last_temp_index], is_water_lvl, goal_v);
		fprintf(file, "%f\t%d\n", temp_read, timestamp);

		if (is_water_lvl) {
			pid_tension = pid_controller(goal_v);
			printf("\n PID V:%f",pid_tension);
			pwm_tension(fd_dc, pid_tension);
		}
		else {
			printf("\n PID V:%f",0.0);
			pwm_tension(fd_dc, 0);
		}

		timestamp++;
	}

	pwm_end(fd_dc);
	fclose(file);

	return 0;
}
