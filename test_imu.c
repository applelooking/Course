// Sample Code for testing MPU-9150 operation
// James Strawson - 2013

#include <robotics_cape.h>
	#define DEFAULT_SAMPLE_RATE	50  // This is also the fastest speed the DMP will do
	#define TIME_CONSTANT 0.2

		float G = 0;
		float G_prev = 0;
		float A = 0;
		float A_prev = 0;
		float theta_gyro = 0;
		float theta_acc = 0;
		float theta = 0;
		int xGyroOffset;
		float gyro_to_rad_per_sec;
		unsigned short gyro_fsr; //full scale range of gyro
		
int print_imu_data(){
	mpudata_t mpu; //struct to read IMU data into
	memset(&mpu, 0, sizeof(mpudata_t)); //make sure it's clean before starting
	if (mpu9150_read(&mpu) == 0) {
		printf("\n");
		
		printf("X: %0.1f  ", mpu.fusedEuler[VEC3_X]* RAD_TO_DEGREE);
		
		/*
		printf("X: %0.1f Y: %0.1f Z: %0.1f ",
		mpu.fusedEuler[VEC3_X] * RAD_TO_DEGREE, 
		mpu.fusedEuler[VEC3_Y] * RAD_TO_DEGREE, 
		mpu.fusedEuler[VEC3_Z] * RAD_TO_DEGREE);
		*/
		
		// unsigned short gyro_fsr; //full scale range of gyro
		// mpu_get_gyro_fsr(&gyro_fsr);
		
		// printf("%d", gyro_fsr);
		
		/*
		printf("Xg: %05d Yg: %05d Zg: %05d ",
		mpu.rawGyro[VEC3_X], 
		mpu.rawGyro[VEC3_Y], 
		mpu.rawGyro[VEC3_Z]);
		*/
		
		float Xg = (float)(((float)(mpu.rawGyro[VEC3_X]) - xGyroOffset)/16.4f);
		// float Yg = (float)(((float)(mpu.rawGyro[VEC3_Y]) - yGyroOffset)/16.4f); , Zg = (float)(((float)(mpu.rawGyro[VEC3_Z]) - zGyroOffset)/16.4f);;
		
		/*
		printf("Xg: %0.1f Yg: %0.1f Zg: %0.1f ",
		Xg,
		Yg,
		Zg);
		*/
		
		float y = (float)(mpu.calibratedAccel[VEC3_Y]), z = (float)(mpu.calibratedAccel[VEC3_Z]), result;
		
		result = (float)(atan2 (y,z));
		
		// float G ;
		// float G_prev;
		
		G_prev = G;
		
		G = ((float)Xg / DEFAULT_SAMPLE_RATE) + G_prev;
		
		float a1 = 0.9524, b1 = 0.9048;
		
		// printf("Xg %f G %f G_prev %f", G, G_prev);
		
		theta_gyro  = (float)(a1 * G) + (float)(- a1 * G_prev) - (float)(- b1 * theta_gyro);
		
		// printf("Xg %f G %f G_prev %f", G, G_prev);
		
		
		printf("theta_gyro %f ", theta_gyro);
		
		float a2 =  0.04762, b2 = - 0.9048;
		
		A_prev = A;
		
		A = result * RAD_TO_DEGREE;
		
		// printf(" %f ", A);
		
		theta_acc = (float)(a2 * A) + (float)(a2 * A_prev) - (float)(b2 * theta_acc);
		
		printf("theta_acc %f ", theta_acc);
		
		// float scale = (float)(TIME_CONSTANT / (TIME_CONSTANT + (float)(1.0 / DEFAULT_SAMPLE_RATE)));
		
		// theta = (float)(scale * (theta_gyro + ((float)Xg / DEFAULT_SAMPLE_RATE))) + (float)((1.0 - scale) * theta_acc);
		
		theta = theta_gyro + theta_acc;
		
	    printf(" theta %f ",theta);
		
		
		/*
		printf("Xg: %05d Yg: %05d Zg: %05d ",
		mpu.rawGyro[VEC3_X], 
		mpu.rawGyro[VEC3_Y], 
		mpu.rawGyro[VEC3_Z]);
		*/
		
		// printf("Xa: %05d Ya: %05d Za: %05d ",
		// mpu.calibratedAccel[VEC3_X], 
		// mpu.calibratedAccel[VEC3_Y], 
		// mpu.calibratedAccel[VEC3_Z]);
		
		// printf("Xm: %03d Ym: %03d Zm: %03d ",
		// mpu.calibratedMag[VEC3_X], 
		// mpu.calibratedMag[VEC3_Y], 
		// mpu.calibratedMag[VEC3_Z]);

		// printf("W: %0.2f X: %0.2f Y: %0.2f Z: %0.2f ",
		// mpu.fusedQuat[QUAT_W],
		// mpu.fusedQuat[QUAT_X],
		// mpu.fusedQuat[QUAT_Y],
		// mpu.fusedQuat[QUAT_Z]);
		
			
		fflush(stdout);
	}
	return 0; 
}

/*
// Filter Initialization sampling
float sum_ax, sum_az, sum_gy;
int warmup_samples;

int sample_imu(){
	if (mpu9150_read(&mpu) == 0) {
		sum_ax += mpu.rawAccel[VEC3_X];
		sum_az += mpu.rawAccel[VEC3_Z]; 
		sum_gy += mpu.rawGyro[VEC3_Y];
		warmup_samples ++;
	}
	return 0; 
}
*/
    
int main(int argc, char *argv[]){
	int sample_rate;
	signed char orientation[9] = ORIENTATION_FLAT; 
	//signed char orientation[9] = ORIENTATION_UPRIGHT;
	
	
	// read the gyro full-scale range
	mpu_get_gyro_fsr(&gyro_fsr);
	gyro_to_rad_per_sec = gyro_fsr /32768;
	
	// now start initiating filter by sampling sensors for a second
	/*
	set_imu_interrupt_func(&sample_imu);
	sleep(1);
	set_imu_interrupt_func(&null_func); //stop interrupt routine
	xGyroOffset = sum_gy/warmup_samples;	// offset to correct for gyro bias
    theta_acc = atan2(sum_az, -sum_ax); 	// initialize accLP at current theta
	theta = theta_acc;								// start theta based on accel
	printf("xGyroOffset = %d\n", xGyroOffset);
	*/

	// start the filter
	set_imu_interrupt_func(&print_imu_data); 
	
	// start slow thread printing data
	// pthread_t slow_thread;
	// pthread_create(&slow_thread, NULL, slow_loop_func, (void*) NULL);
	
	if (argc==1){
		sample_rate = DEFAULT_SAMPLE_RATE;
    }
	else{
		sample_rate = atoi(argv[1]);
		if((sample_rate>MAX_SAMPLE_RATE)||(sample_rate<MIN_SAMPLE_RATE)){
			printf("sample rate should be between %d and %d\n", MIN_SAMPLE_RATE,MAX_SAMPLE_RATE);
			return -1;
		}
	}
	
	initialize_cape();
	initialize_imu(sample_rate, orientation);
	set_imu_interrupt_func(&print_imu_data); //start the interrupt handler
	
	//now just wait, print_imu_data will run
	while (get_state() != EXITING) {
		sleep(1);
	}
	cleanup_cape();
	return 0;
}

