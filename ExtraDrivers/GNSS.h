#ifndef GNSS_H
#define GNSS_H

#include "main.h"

struct GSVData
{
    unsigned char numMsg;	//  语句总数
	unsigned char msgNo;	//  当前语句编号
	unsigned char numSv;	//  可见卫星总数
    unsigned int SVID;		//  卫星编号
    unsigned char ele;		//  仰角
    unsigned int az;		//  方位角
    unsigned char cn0;		//  载噪比
};
typedef  struct GSVData GSVDATA;

extern GSVDATA gpgsv;


extern float latitude;                                               //  纬度
extern float longitude;                                              //  经度
extern char latitude_dir;
extern char longitude_dir;
extern unsigned char gps_time[50];


void GNSS_Init(void);



#endif