#include <SPI.h>

char POWER_CTL = 0x2D;  //Power Control Register
char DATA_FORMAT = 0x31;
//char DATAX0 = 0x32; //X-Axis Data 0
//char DATAX1 = 0x33; //X-Axis Data 1
//char DATAY0 = 0x34; //Y-Axis Data 0
//char DATAY1 = 0x35; //Y-Axis Data 1
//char DATAZ0 = 0x36; //Z-Axis Data 0
//char DATAZ1 = 0x37; //Z-Axis Data 1

void spiInit(){
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
}

unsigned char values[10];
int xyz[3];


void readADXL(int CS, int *xyz){  
  char address = 0x80 | 0x32 | 0x40;
  digitalWrite(CS, 0);
  SPI.transfer(address);
  for(int i=0; i<6; i++){
    values[i] = SPI.transfer(0x00);
  }
  digitalWrite(CS,1);  
  xyz[0] = ((int)values[1]<<8)|(int)values[0];  
  xyz[1] = ((int)values[3]<<8)|(int)values[2];  
  xyz[2] = ((int)values[5]<<8)|(int)values[4];
}

void writeRegister(char reg, char value, int CS){  
  digitalWrite(CS, 0);
  SPI.transfer(reg);
  SPI.transfer(value);
  digitalWrite(CS, 1);
}

void adxlInit(int CS){  
  writeRegister(DATA_FORMAT, 0x01, CS);  
  writeRegister(POWER_CTL, 0x08, CS);  //Measurement mode  
}
