﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

static struct termios init_setting, new_setting;
//unsigned int dot_A[8] = { 0x7001,0x8802,0x8804,0x8808,0xF810,0x8820,0x8840,0x0080 };
//unsigned int dot_B[8] = { 0xF0,0x88,0x88,0xF0,0x88,0x88,0xF0,0x00 };
//char dot_C[8] = { 0x70,0x88,0x80,0x80,0x80,0x88,0x70,0x00 };
//char dot_D[8] = { 0xE0,0x90,0x88,0x88,0x88,0x90,0xE0,0x00 };
//char dot_E[8] = { 0xF8,0x80,0x80,0xF0,0x80,0x80,0xF8,0x00 };
//char dot_F[8] = { 0xF8,0x80,0x80,0xF0,0x80,0x80,0x80,0x00 };
//char dot_G[8] = { 0x70,0x88,0x80,0x98,0x88,0x88,0x78,0x00 };
//char dot_H[8] = { 0x88,0x88,0x88,0xF8,0x88,0x88,0x88,0x00 };
//char dot_I[8] = { 0x70,0x20,0x20,0x20,0x20,0x20,0x70,0x00 };
unsigned int dot_J[8] = { 0x3801,0x1002,0x1004,0x1008,0x1010,0x9020,0x6040,0x0080 };
unsigned int dot_K[8] = { 0x8801,0x9002,0xA004,0xC008,0xA010,0x9020,0x8840,0x0080 };
//char dot_L[8] = { 0x80,0x80,0x80,0x80,0x80,0x80,0xF8,0x00 };
//char dot_M[8] = { 0x88,0xD8,0xA8,0xA8,0x88,0x88,0x88,0x00 };
//char dot_N[8] = { 0x88,0x88,0xC8,0xA8,0x98,0x88,0x88,0x00 };
//char dot_O[8] = { 0x70,0x88,0x88,0x88,0x88,0x88,0x70,0x00 };
unsigned int dot_P[8] = { 0xF001,0x8802,0x8804,0xF008,0x8010,0x8020,0x8040,0x0080 };
//char dot_Q[8] = { 0x70,0x88,0x88,0x88,0xA8,0x90,0x68,0x00 };
//char dot_R[8] = { 0xF0,0x88,0x88,0xF0,0xA0,0x90,0x88,0x00 };
//char dot_S[8] = { 0x78,0x80,0x80,0x70,0x08,0x08,0xF0,0x00 };
//char dot_T[8] = { 0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x00 };		// 1111_1000, 0010_0000
//char dot_U[8] = { 0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00 };
//char dot_V[8] = { 0x88,0x88,0x88,0x88,0x88,0x50,0x20,0x00 };
//char dot_W[8] = { 0x88,0x88,0x88,0x88,0xA8,0xA8,0x50,0x00 };
//char dot_X[8] = { 0x88,0x88,0x50,0x20,0x50,0x88,0x88,0x00 };
//char dot_Y[8] = { 0x88,0x88,0x88,0x50,0x20,0x20,0x20,0x00 };
//char dot_Z[8] = { 0xF8,0x08,0x10,0x20,0x40,0x80,0xF8,0x00 };


int main(int argc, char** argv)
{
	//10주차
	unsigned int data[8];
	char key;
	int tmp_n = 0;
	int count = 1;
	int delay_time = 0;;
	//8주차
	char buff;
	
	//device 10주차
	int dev10 = open("/dev/my_dot_matrix", O_RDWR);

	if (dev10 == -1) {
		printf("Opening10 was not possible!\n");
		return -1;
	}
	printf("Opening10 was successfull!\n");
	
	if(argv[1][0] == 'p'){
		for(int k = 0; k < 8; k++){
			data[k] = dot_P[k];
		}
	}
	else if(argv[1][0] == 'k') {
		for(int k = 0; k < 8; k++){
			data[k] = dot_K[k];
		}
	}
	else if(argv[1][0] == 'j'){
		for(int k = 0; k < 8; k++){
			data[k] = dot_J[k];
		}	
	}
	
	while(count){
		write(dev10, &data[tmp_n], 2);
		usleep(delay_time);

		tmp_n++;
		count++;
		if (tmp_n > 7) {
			tmp_n = 0;
		}
		if(count > 40000){
			count = 0;
		}
	}
	write(dev10, 0x0000, 2);
	close(dev10);
	return 0;
}
