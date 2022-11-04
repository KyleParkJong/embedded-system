#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

static struct termios init_setting, new_setting;
char seg_num[10] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90 };
char seg_dnum[10] = { 0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02,0x58, 0x80, 0x10 };

#define D1 0x01
#define D2 0x02
#define D3 0x04
#define D4 0x08

void init_keyboard()
{
	tcgetattr(STDIN_FILENO, &init_setting);
	new_setting = init_setting;
	new_setting.c_lflag &= ~ICANON;
	new_setting.c_lflag &= ~ECHO;
	new_setting.c_cc[VMIN] = 0;
	new_setting.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_setting);
}

void close_keyboard()
{
	tcsetattr(0, TCSANOW, &init_setting);
}

char get_key()
{
	char ch = -1;

	if (read(STDIN_FILENO, &ch, 1) != 1)
		ch = -1;
	return ch;
}

void print_menu()
{
	printf("\n----------menu----------\n");
	printf("[u] or button 1 : count up\n");
	printf("[d] or button 2 : count down\n");
	printf("[p] : count reset\n");
	printf("[q] : program exit\n");
	printf("-----------------------\n\n");
}

int main(int argc, char** argv)
{
	//10주차
	unsigned short data[4];
	char key;
	int tmp_n;
	int delay_time;
	int num = 0;
	//8주차
	char buff;
	char tmp;
	char prev = 'r';

	//device 8주차
	int dev8 = open("/dev/my_gpio", O_RDWR); // if you want read-'O_RDONLY' write-'O WRONLY', read&write-'O RDUR•

	if (dev8 == -1) {
		printf("Opening8 was not possible!\n");
		return -1;
	}
	printf("Opening8 was successfull!\n");
	//device 10주차
	int dev10 = open("/dev/my_segment", O_RDWR);

	if (dev10 == -1) {
		printf("Opening10 was not possible!\n");
		return -1;
	}
	printf("Opening10 was successfull!\n");
	//
	init_keyboard();
	print_menu();
	tmp_n = 0;
	delay_time = 5000;

	//10주차 반복문
	while (1) {
		//자릿수
		data[0] = (seg_num[(num / 1000) % 10] << 4) | D1;
		data[1] = (seg_num[(num / 100) % 10] << 4) | D2;
		data[2] = (seg_num[(num / 10) % 10] << 4) | D3;
		data[3] = (seg_num[num % 10] << 4) | D4;

		read(dev8, &buff, 1);
		key = get_key();
		if (key == 'q') {
			printf("exit this program.\n");
			break;
		}
		else if (key == 'u') {
			num++;
		}
		else if (key == 'd') {
			num--;
		}
		else if (key == 'r') {
			num = 0;
		}
		//9999넘으면 초기화
		if (num > 9999) {
			num = 0;
		}
		else if (num < 0) {
			num = 9999;
		}
		else { ; }

		if ((buff) == '1') {
			num++;
		}
		else if ((buff) == '3') {
			num--;
		}

		write(dev10, &data[tmp_n], 2);
		usleep(delay_time);

		tmp_n++;
		if (tmp_n > 3) {
			tmp_n = 0;
		}
	}

	close_keyboard();
	write(dev10, 0x0000, 2);
	close(dev10);
	close(dev8);
	return 0;
}