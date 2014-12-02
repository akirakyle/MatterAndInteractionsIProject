//
//  SpeedTest.c
//  
//
//  Created by Akira Kyle on 10/26/14.
//
//

#include <stdio.h>
#include <stdlib.h>

int main (void) {
    
    FILE *file = fopen("file.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    struct particle {
        struct pos {
            float x;
            float y;
            float z;
        };
        struct vel {
            float x;
            float y;
            float z;
        };
    };
    
    int time = 1000;
    unsigned long long int num = 100000;
    int dt;
    
    struct particle particleArray[num];
    
    for (int n=0; n<num; n++) {
        particleArray[n].particle.pos.x = (rand() % 20) - 10;
        particleArray[n].particle.pos.y = (rand() % 20) - 10;
        particleArray[n].particle.pos.z = (rand() % 20) - 10;
        particleArray[n].particle.vel.x = (rand() % 20) - 10;
        particleArray[n].particle.vel.y = (rand() % 20) - 10;
        particleArray[n].particle.vel.z = (rand() % 20) - 10;
        xpos[num] = (rand() % 20) - 10;
        ypos[num] = (rand() % 20) - 10;
        zpos[num] = (rand() % 20) - 10;
        xvel[num] = (rand() % 20) - 10;
        yvel[num] = (rand() % 20) - 10;
        zvel[num] = (rand() % 20) - 10;
    }
    
    for (int t=0; t<time; t++) {
        for (unsigned long long int i=0; i<num; i++) {
            if (xpos[num] > 10 || xpos[num] < -10) {
                xvel[num] = -xvel[num];
            }
            if (ypos[num] > 10 || ypos[num] < -10) {
                yvel[num] = -yvel[num];
            }
            if (zpos[num] > 10 || zpos[num] < -10) {
                zvel[num] = -zvel[num];
            }
            xpos[num] = xpos[num] + xvel[num]*dt;
            ypos[num] = ypos[num] + yvel[num]*dt;
            zpos[num] = zpos[num] + zvel[num]*dt;
            
            if ((t % 100) == 0) {
                fprintf(file, "%d: (%f,%f,%f)\n",t,xpos[num],ypos[num],zpos[num]);
            }
            //printf("%d(%f,%f,%f)\n",t,xpos[num],ypos[num],zpos[num]);
            //fprintf(file, "%d: (%f,%f,%f)\n",t,xpos[num],ypos[num],zpos[num]);
        }
        dt++;
    }
    
    fclose(file);
    
    return 0;
}