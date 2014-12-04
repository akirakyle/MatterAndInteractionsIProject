//  Created by Akira Kyle on 10/26/14.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main (void) {
    //Setup
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
    
    //Constants
    int totalTime = 20; //total time simulation is run for
    unsigned int num = 100; //total number of particles
    float dt = 0.01; //time step for numeric integration
    float k = 0.001;    //constant for electric force which includes k*charge1*charge2/mass
    float cylinderHeight = 10; //container is cylinder
    float cylinderRadius = 1;
    float velMax = 10; //maximum velocity of the particles
    float wallVel = 8; //the velocity that the wall moves to create sound wave
    float wallVelTime = 1; //the time that the wall takes to move (forward and back)
    
    int iteration = 0;
    
    struct particleStruct particle[num];
    
    //initilization of particle array
    for (int n=0; n<num; n++) {
        particle[n].pos.x = ((float)rand()/(float)RAND_MAX * 2*cylinderHeight-.1) - (cylinderHeight-.05);
        float r = ((float)rand()/(float)RAND_MAX * cylinderRadius-.1);
        float theta = ((float)rand()/(float)RAND_MAX * M_PI);
        particle[n].pos.y = r * cos(theta);
        particle[n].pos.z = r * sin(theta);
        particle[n].vel.x = ((float)rand()/(float)RAND_MAX * velMax) - velMax/2;
        particle[n].vel.y = ((float)rand()/(float)RAND_MAX * velMax) - velMax/2;
        particle[n].vel.z = ((float)rand()/(float)RAND_MAX * velMax) - velMax/2;
    }
    
    //start calculations
    for (float t=0; t<totalTime; t=t+dt) {
        for (unsigned int i=0; i<num; i++) {
            if (sqrt(pow((particle[i].pos.y), 2) + pow((particle[i].pos.z), 2)) > cylinderRadius) {
                if (particle[i].pos.y > 0) {
                    particle[i].vel.y = -abs(particle[i].vel.y);
                }
                if (particle[i].pos.y < 0) {
                    particle[i].vel.y = abs(particle[i].vel.y);
                }
                if (particle[i].pos.z > 0) {
                    particle[i].vel.z = -abs(particle[i].vel.z);
                }
                if (particle[i].pos.z < 0) {
                    particle[i].vel.z = abs(particle[i].vel.z);
                }
            }
            if (t < wallVelTime/2) {
                if (particle[i].pos.x > cylinderHeight - t*wallVel) {
                    particle[i].vel.x = -abs(particle[i].vel.x) - wallVel;
                }
                if (particle[i].pos.x < -cylinderHeight) {
                    particle[i].vel.x = abs(particle[i].vel.x);
                }
            }
            else if (t < wallVelTime) {
                if (particle[i].pos.x > cylinderHeight + (t-wallVelTime)*wallVel) {
                    particle[i].vel.x = -abs(particle[i].vel.x) + wallVel;
                }
                if (particle[i].pos.x < -cylinderHeight) {
                    particle[i].vel.x = abs(particle[i].vel.x);
                }
            }
            else {
                if (particle[i].pos.x > cylinderHeight) {
                    particle[i].vel.x = -abs(particle[i].vel.x);
                }
                if (particle[i].pos.x < -cylinderHeight) {
                    particle[i].vel.x = abs(particle[i].vel.x);
                }
            }
            for (unsigned int j=i+1; j<num; j++) {
                float forceX = k*(particle[i].pos.x - particle[j].pos.x)/pow(sqrt(pow((particle[i].pos.x - particle[j].pos.x), 2) + pow((particle[i].pos.y - particle[j].pos.y), 2) + pow((particle[i].pos.z - particle[j].pos.z), 2)),3);
                float forceY =k*(particle[i].pos.y - particle[j].pos.y)/pow(sqrt(pow((particle[i].pos.x - particle[j].pos.x), 2) + pow((particle[i].pos.y - particle[j].pos.y), 2) + pow((particle[i].pos.z - particle[j].pos.z), 2)),3);
                float forceZ = k*(particle[i].pos.z - particle[j].pos.z)/pow(sqrt(pow((particle[i].pos.x - particle[j].pos.x), 2) + pow((particle[i].pos.y - particle[j].pos.y), 2) + pow((particle[i].pos.z - particle[j].pos.z), 2)),3);
                particle[i].vel.x = particle[i].vel.x + forceX*dt;
                particle[i].vel.y = particle[i].vel.y + forceY*dt;
                particle[i].vel.z = particle[i].vel.z + forceZ*dt;
                particle[j].vel.x = particle[j].vel.x - forceX*dt;
                particle[j].vel.y = particle[j].vel.y - forceY*dt;
                particle[j].vel.z = particle[j].vel.z - forceZ*dt;
            }
            
            particle[i].pos.x = particle[i].pos.x + particle[i].vel.x*dt;
            particle[i].pos.y = particle[i].pos.y + particle[i].vel.y*dt;
            particle[i].pos.z = particle[i].pos.z + particle[i].vel.z*dt;
            
            fprintf(file, "%f,%f,%f,%f,\n",t,particle[i].pos.x,particle[i].pos.y,particle[i].pos.z);
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