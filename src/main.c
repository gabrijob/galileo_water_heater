#include <stdio.h>
#include <sensors.h>
#include <pwm_control.h>
#include <unistd.h>
#include <galileoio.h>
#include <stdlib.h>

#define OUTPUT_FILE "temp.out" //!< Define the output file to store the temperature values.

#define KC 0.02 //!< Define the PID Error constant value.
#define KI 0 //!< Define the PID integral constant value.
#define KD 0 //!< Define the PID derivate constant value.

#define MAX_TEMP_OBS 10000
double temperatures[MAX_TEMP_OBS];
int last_temp_index = 0;

double goal_temps[MAX_TEMP_OBS];

/**  Stores current temperature value in temperature buffer */
void store_temperature(double temp) {
	last_temp_index++;

	if(last_temp_index >= MAX_TEMP_OBS)
		last_temp_index = 0;

	temperatures[last_temp_index] = temp;
}

/** Calculate PID controller using the desired temperature */
double pid_controller(double goal_temp) {
	double error;
	double derivative;
	double integral;
	int i =0;

	goal_temps[last_temp_index] = goal_temp;
	// Calculate error
	error = goal_temp - temperatures[last_temp_index];
	//printf(" Error:%f / ", error);
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
	//TODO: usar integral anterior
	for(i=0; i<last_temp_index; i++){
		integral += goal_temps[i] - temperatures[i];
	}


	return KC*error + KI*integral + KD*derivative;
}


int main(int argc,char *argv[]) {
	int is_water_lvl;
	double temp_read;
	double pid_tension = 0;
	int goal_v = 100;
	FILE *file;

	if(argc > 1) {
		goal_v = atoi(argv[1]);
	}
	
        if((file=fopen(OUTPUT_FILE,"w")) == NULL)
        {
                perror("Opening output file:");
                return -1;
        }	

	int fd_wlvl = init_water_lvl_sensor();
	int fd_temp = init_temp_sensor();
	int fd_dc = pwm_init();

	int timestamp = 0;
	for(;;) {
		//TODO: medir tempo de execução / garantir loop a cada 0,1s
		temp_read = temperature(fd_temp);
		store_temperature(temp_read);
		
		is_water_lvl = water_level(fd_wlvl);
		printf("Temperature:%f / Water Lv:%d / Goal temp:%d\n", temperatures[last_temp_index], is_water_lvl, goal_v);
		fprintf(file, "%f\t%d\t%d\n", temp_read, goal_v, timestamp);

		if (is_water_lvl) {
			pid_tension = pid_controller(goal_v);
			//printf("\n PID V:%f",pid_tension);
			pwm_tension(fd_dc, pid_tension);
		}
		else {
			//printf("\n PID V:%f",0.0);
			pwm_tension(fd_dc, 0);
		}

		usleep(100);
		timestamp++;
	}

	pwm_end(fd_dc);
	end_temp_sensor(fd_temp);
	end_water_lvl_sensor(fd_wlvl);
	fclose(file);

	return 0;
}
