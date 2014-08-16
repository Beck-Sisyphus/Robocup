/* 
  Robot.h

  Created by Wang PG on 14-8-12.
  Copyright (c) 2014年 Wang PG. All rights reserved.


  File: Robot.i
*/  


%module Robot  
  
%{  
#define SWIG_FILE_WITH_INIT  
#include "Robot.h"  
%}  
  
int getPixel(IplImage* img,int x, int y);

void setPixel(IplImage* img,int x, int y,int value);

IplImage* reSize(IplImage* img, double scale);

IplImage* threshold(IplImage* img, int k);

int getError(IplImage* img);

int CompareHist(const char* imagefile1, const char* imagefile2);
