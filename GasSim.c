//
//  GasSim.c
//  
//
//  Created by Akira Kyle on 10/26/14.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main (void) {
    clock_t start = clock(), diff;
    FILE *file = fopen("Developer/MatterAndInteractionsIProject/gasSimData.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    struct position {
        float x;
        float y;
        float z;
    };
    struct velelocity {
        float x;
        float y;
        float z;
    };
    
    struct particleStruct {
        struct position pos;
        struct velelocity vel;
    };
    
    int time = 50;
    int iteration = 0;
    unsigned long long int num = 100;
    float dt = 0.01;
    
    struct particleStruct particle[num];
    
    for (int n=0; n<num; n++) {
        particle[n].pos.x = ((float)rand()/(float)RAND_MAX * 19.9) - 9.95;
        float r = ((float)rand()/(float)RAND_MAX * 4.95);
        float theta = ((float)rand()/(float)RAND_MAX * M_PI);
        particle[n].pos.y = r * cos(theta);
        particle[n].pos.z = r * sin(theta);
        //particle[n].pos.y = ((float)rand()/(float)RAND_MAX * 5) - 2.5;
        //particle[n].pos.z = ((float)rand()/(float)RAND_MAX * 5) - 2.5;
        particle[n].vel.x = ((float)rand()/(float)RAND_MAX * 10) - 5;
        particle[n].vel.y = ((float)rand()/(float)RAND_MAX * 10) - 5;
        particle[n].vel.z = ((float)rand()/(float)RAND_MAX * 10) - 5;
        //printf("pos:%f, vel:%f\n",particle[n].pos.x,particle[n].vel.x);
    }
    
    for (float t=0; t<time; t=t+dt) {
        for (unsigned long long int i=0; i<num; i++) {
            if (sqrt(pow((particle[i].pos.y), 2) + pow((particle[i].pos.z), 2)) > 5) {
                particle[i].vel.y = -particle[i].vel.y;
                particle[i].vel.z = -particle[i].vel.z;
            }
            if (t < 2) {
                if (particle[i].pos.x > 10-t*2) {
                    particle[i].vel.x = -abs(particle[i].vel.x)-1;
                }
                if (particle[i].pos.x < -10) {
                    particle[i].vel.x = abs(particle[i].vel.x);
                }
            }
            else {
                if (particle[i].pos.x > 10) {
                    particle[i].vel.x = -abs(particle[i].vel.x);
                }
                if (particle[i].pos.x < -10) {
                    particle[i].vel.x = abs(particle[i].vel.x);
                }
            }
            for (unsigned long long int j=i+1; j<num; j++) {
                if (sqrt(pow((particle[i].pos.x - particle[j].pos.x), 2) + pow((particle[i].pos.y - particle[j].pos.y), 2) + pow((particle[i].pos.z - particle[j].pos.z), 2)) < 1) {
                    //printf("Distance from particle %llu to %llu: %f\n",i,j,sqrt(pow((particle[i].pos.x - particle[j].pos.x), 2) + pow((particle[i].pos.y - particle[j].pos.y), 2) + pow((particle[i].pos.z - particle[j].pos.z), 2)));
                    particle[i].vel.x = particle[j].vel.x;
                    particle[i].vel.y = particle[j].vel.y;
                    particle[i].vel.z = particle[j].vel.z;
                    particle[j].vel.x = particle[i].vel.x;
                    particle[j].vel.y = particle[i].vel.y;
                    particle[j].vel.z = particle[i].vel.z;
                }
            }
            
            particle[i].pos.x = particle[i].pos.x + particle[i].vel.x*dt;
            particle[i].pos.y = particle[i].pos.y + particle[i].vel.y*dt;
            particle[i].pos.z = particle[i].pos.z + particle[i].vel.z*dt;
            
            fprintf(file, "%f,%f,%f,%f\n",t,particle[i].pos.x,particle[i].pos.y,particle[i].pos.z);
        }
        if ((iteration % 50) == 0) {
            printf("interation:%d\n",iteration);
            printf("time:%g\n",t);
            
        }
        iteration++;
    }
    
    fclose(file);
    
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
    
    return 0;
}