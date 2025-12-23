#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define WR_VALUE _IOW('a', 'a', int)

//Downloaded from Joshua sub branch

int main() {
    FILE *fpw;
    char ch, temp;  
    int number, value = 0, shift = 28;
    char line[73];
    int i;

    //OPENING CHAR DRIVER
  /*  int FP = open("/dev/char_device", O_RDWR);
    
    if (FP < 0) {
        printf("Error opening char device");
    }*/

    //OPENING HEX FILES
    fpw = fopen("itcm_sram.hex", "r");
    if (fpw == NULL) {
        printf("Error\n");
    }
    
   //LOADING ITCM_SRAM
   while((fgets(line,sizeof(line),fpw)) != 0){
		//printf("Entering loop\n");
		for(i=9; i<=16; i++){
			temp = line[i];
			usleep(100);
			number = (line[i]=='a') ? 10 : (line[i]=='b') ? 11 : (line[i]=='c') ? 12 : (line[i]=='d') ? 13 : (line[i]=='e') ? 14 : (line[i]=='f') ? 15 : 0;
			if(number==0){
				number = atoi(&temp);
			}
			//printf("t:%x n:%x ",temp,number);
			number = (number << shift);
			shift -= 4;
			value = value | number;
			printf("%x\n",value);
			number=0;
		}
		printf("\n");
		shift=28;
		//ioctl(FP,WR_VALUE,&value);
		//printf("Data: %x\n",value);
		value = 0;
		if(value==0x01ff){
			break;
		}

	}
	shift = 0;

    value = 0x55555555;
    //ioctl(FP,WR_VALUE,&value);

    printf("\nloop break %x\n",value);	
    fclose(fpw);
    //close(FP);

    return 0;
}

