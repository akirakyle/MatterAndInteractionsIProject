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

int main (void) {
    
    FILE *file = fopen("file.txt", "w");
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
    
    struct particle {
        struct position pos;
        struct velelocity vel;
    };
    
    int time = 2;
    int iteration = 0;
    unsigned long long int num = 1000;
    float dt = 0.01;
    
    struct particle particleArray[num];
    
    for (int n=0; n<num; n++) {
        particleArray[n].pos.x = (rand() % 20) - 10;
        particleArray[n].pos.y = (rand() % 20) - 10;
        particleArray[n].pos.z = (rand() % 20) - 10;
        particleArray[n].vel.x = (rand() % 20) - 10;
        particleArray[n].vel.y = (rand() % 20) - 10;
        particleArray[n].vel.z = (rand() % 20) - 10;
    }
    
    for (float t=0; t<time; t=t+dt) {
        for (unsigned long long int i=0; i<num; i++) {
            if (particleArray[i].pos.x > 10 || particleArray[i].pos.x < -10) {
                particleArray[i].vel.x = -particleArray[i].vel.x;
            }
            if (particleArray[i].pos.y > 10 || particleArray[i].pos.y < -10) {
                particleArray[i].vel.y = -particleArray[i].vel.y;
            }
            if (particleArray[i].pos.z > 10 || particleArray[i].pos.z < -10) {
                particleArray[i].vel.z = -particleArray[i].vel.z;
            }
            
            for (unsigned long long int j=i; j<num; j++) {
                if (sqrt(pow((particleArray[i].pos.x - particleArray[j].pos.x), 2) + pow((particleArray[i].pos.y - particleArray[j].pos.y), 2) + pow((particleArray[i].pos.z - particleArray[j].pos.z), 2)) < 1) {
                    particleArray[i].vel.x = -particleArray[i].vel.x;
                    particleArray[i].vel.y = -particleArray[i].vel.y;
                    particleArray[i].vel.y = -particleArray[i].vel.y;
                }
            }
            
            particleArray[i].pos.x = particleArray[i].pos.x + particleArray[i].vel.x*dt;
            particleArray[i].pos.y = particleArray[i].pos.y + particleArray[i].vel.y*dt;
            particleArray[i].pos.z = particleArray[i].pos.z + particleArray[i].vel.z*dt;
            
            if ((iteration % 20) == 0) {
                fprintf(file, "%f: (%f,%f,%f)\n",t,particleArray[i].pos.x,particleArray[i].pos.y,particleArray[i].pos.z);
            }
            //printf("%d(%f,%f,%f)\n",t,xpos[num],ypos[num],zpos[num]);
            //fprintf(file, "%d: (%f,%f,%f)\n",t,xpos[num],ypos[num],zpos[num]);
        }
        //if ((iteration % 1000) == 0) {
            printf("interation:%d\n",iteration);
        //}
        iteration++;
    }
    
    fclose(file);
    
    return 0;
}