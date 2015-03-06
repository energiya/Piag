/*
=================================================================================
 Name        : piag.c
 Version     : 0.1

 Copyright (C) 2015 by Stefan Hanu, 2015, hscata@gmail.com

 More information at https://github.com/energiya/Piag
================================================================================
 */
#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include "./PCD8544/PCD8544.h"

#define __MAJOR__ 0
#define __MINOR__ 1

// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs = 3;
  
// lcd contrast 
int contrast = 0x32;

void display_pi_info()
{
    printf("Piag v%ld.%ldb%ld\n", __MAJOR__, __MINOR__, __VERSION__);
    printf("===============\n");
}
  
int main (void)
{
  // Display description on the PI
  display_pi_info();
  
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("[ERROR] Could not setup wiringPi\n");
    exit(1);
  }
  
  // init and clear lcd
  LCDInit(_sclk, _din, _dc, _cs, _rst, contrast);
  LCDclear();
  
  // show logo
  LCDshowLogo();
  
  delay(2000);
  
  for (;;)
  {
	  // clear lcd
	  LCDclear();
	  
	  // get system usage / info
	  struct sysinfo sys_info;
	  if(sysinfo(&sys_info) != 0)
	  {
		printf("sysinfo-Error\n");
	  }
	  
	  // uptime
	  char uptimeInfo[15];
      unsigned long rawtime = sys_info.uptime;
	  unsigned long uptime = rawtime / 60;
      unsigned long uptimes = rawtime % 60; 
	  sprintf(uptimeInfo, "Uptime %ldm:%lds", uptime, uptimes);
	  
	  // cpu info
	  char cpuInfo[10]; 
	  unsigned long avgCpuLoad = sys_info.loads[0] / 1000;
	  sprintf(cpuInfo, "CPU %ld%%", avgCpuLoad);
	  
	  // ram info
	  char ramInfo[10]; 
	  unsigned long totalRam = sys_info.freeram / 1024 / 1024;
	  sprintf(ramInfo, "RAM %ld MB", totalRam);
	  
	  // build screen
	  LCDdrawstring(0, 0, "Raspberry Pi:");
	  LCDdrawline(0, 10, 83, 10, BLACK);
	  LCDdrawstring(0, 12, uptimeInfo);
	  LCDdrawstring(0, 20, cpuInfo);
	  LCDdrawstring(0, 28, ramInfo);
	  LCDdisplay();
	  
	  delay(1000);
  }
  
  return 0;
}
