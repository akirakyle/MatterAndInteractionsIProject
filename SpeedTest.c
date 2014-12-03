//
//  SpeedTest.c
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
    FILE *file = fopen("Developer/MatterAndInteractionsIProject/cData.txt", "w");
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
    
    int time = 2;
    int iteration = 0;
    unsigned long long int num = 1000;
    float dt = 0.01;
    
    struct particleStruct particle[num];
    
    for (int n=0; n<num; n++) {
        particle[n].pos.x = (rand() % 18) - 9;
        particle[n].pos.y = (rand() % 18) - 9;
        particle[n].pos.z = (rand() % 18) - 9;
        particle[n].vel.x = (rand() % 20) - 10;
        particle[n].vel.y = (rand() % 20) - 10;
        particle[n].vel.z = (rand() % 20) - 10;
    }
    
    for (float t=0; t<time; t=t+dt) {
        for (unsigned long long int i=0; i<num; i++) {
            if ((particle[i].pos.x > 10) || (particle[i].pos.x) < -10) {
                particle[i].vel.x = -particle[i].vel.x;
            }
            if ((particle[i].pos.y > 10) || (particle[i].pos.y) < -10) {
                particle[i].vel.y = -particle[i].vel.y;
            }
            if ((particle[i].pos.z > 10) || (particle[i].pos.z) < -10) {
                particle[i].vel.z = -particle[i].vel.z;
            }
            
            for (unsigned long long int j=i+1; j<num; j++) {
                if (sqrt(pow((particle[i].pos.x - particle[j].pos.x), 2) + pow((particle[i].pos.y - particle[j].pos.y), 2) + pow((particle[i].pos.z - particle[j].pos.z), 2)) < 1) {
                    particle[i].vel.x = -particle[i].vel.x;
                    particle[i].vel.y = -particle[i].vel.y;
                    particle[i].vel.z = -particle[i].vel.z;
                    particle[j].vel.x = -particle[j].vel.x;
                    particle[j].vel.y = -particle[j].vel.y;
                    particle[j].vel.z = -particle[j].vel.z;
                }
            }
            
            particle[i].pos.x = particle[i].pos.x + particle[i].vel.x*dt;
            particle[i].pos.y = particle[i].pos.y + particle[i].vel.y*dt;
            particle[i].pos.z = particle[i].pos.z + particle[i].vel.z*dt;
            
            //if ((iteration % 5) == 0) {
                fprintf(file, "%f,%f,%f,%f\n",t,particle[i].pos.x,particle[i].pos.y,particle[i].pos.z);
            //}
            //printf("%d(%f,%f,%f)\n",t,xpos[num],ypos[num],zpos[num]);
            //fprintf(file, "%d: (%f,%f,%f)\n",t,xpos[num],ypos[num],zpos[num]);
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