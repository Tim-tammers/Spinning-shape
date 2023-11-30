
#include <string.h>
#include <iostream>
#include <math.h>  
#include <stdio.h>

float A, B, C;
float x,y,z;
float shapeWidth = 20;
//float radius = 30;
int width = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode = ' ';
float incrementSpeed = 0.6;
int distanceFromCam = 100;
float ooz;
int xp, yp;
int K1 = 40;
int idx;
float borderX;
float borderY;

float calculateX(int i, int j, int k) {
  return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
         j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(int i, int j, int k) {
  return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
         j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
         i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k) {
  return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float angle, float radius, float shapeZ, char symbol) {
    x = calculateX(shapeWidth*cos(angle), shapeWidth*sin(angle), shapeZ)*radius;
    y = calculateY(shapeWidth * cos(angle), shapeWidth * sin(angle), shapeZ)*radius;
    z = calculateZ(shapeWidth * cos(angle), shapeWidth * sin(angle), shapeZ)+distanceFromCam;
    ooz = 1 / z;
    xp = (int)(width / 2 + K1 * ooz * x * 2);
    yp = (int)(height / 2 + K1 * ooz * y);
    idx = xp + yp * width;
    if (idx >= 0 && idx < width * height) {
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = symbol;
        }
    }
}


int main()
{
    printf("\x1b[2J");
    while (1) {
        memset(buffer, backgroundASCIICode, width * height);
        memset(zBuffer, 0, width * height * 4);
        //shapeWidth = 20;
        for (float angle = 0; angle < 6.28; angle += .08) {
            for (float radius = -shapeWidth; radius < 15; radius += incrementSpeed) {
               
                    calculateForSurface(angle, radius, -shapeWidth, '#');
                
            }
        }
        printf("\x1b[H");
        for (int k = 0; k < width * height; k++) {
            putchar(k % width ? buffer[k] : 10);
        }
        A += 0.15;
        B += 0.05;
        C += 0.01;
    }

    return 0;
}

