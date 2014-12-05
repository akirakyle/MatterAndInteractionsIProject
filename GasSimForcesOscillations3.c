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
    //22.4L/mol = 37.2nm^3/particle
    int totalTime = 6; //total time simulation is run for
    unsigned int num = 500; //total number of particles
    float dt = 0.01; //time step for numeric integration
    float epsilon = 0.00001;    //depth of potential well
    float forceDistance = 0.39; //atomic radius* 2^(1/6) (nm)
    //container is cylinder
    float volume = 37.2*num; // in nm^3
    float cylinderHeight = 600; //in nm
    
    float temperature = 273; //temperature in Kelvin
    float mass = 28; //particle mass (diatomic nitrogen) in amu
    float kb; //Boltzman constant 8.3148×10^21 amu  nm^2/(s^2*K)  (atomic mass unit (chemical scale) nanometers squared per second squared kelvin)
    //and heres where we figured out simulating a gas is actually not gonna happen :(
    float avgVel = sqrt(3*kb*temperature/mass); //average particle velocity in nm/sec
    
    float velMax = 1; //maximum velocity of the particles
    float wallVel = 6; //the velocity that the wall moves to create sound wave
    float period = 0.5; //the time that the wall takes to move (either forward or back)
                            //actually like a half period then
    //Calculated constants
    float sigma = forceDistance/pow(2,(1.0/6.0));  //WCS constant
    float k = -24*epsilon*pow(sigma,6);  //WCS constnat simplification
    float cylinderRadius = sqrt(volume/(M_PI*cylinderHeight)); //in nm
    float cylinderWallPosX = cylinderHeight/2;
    float cylinderWallNegX = -cylinderHeight/2;
    int iteration = 0;
    
    //Var initalizations
    struct particleStruct particle[num];
    float r;
    float forceMag;
    float forceX;
    float forceY;
    float forceZ;
    
    //initilization of particle array
    for (int n=0; n<num; n++) {
        particle[n].pos.x = ((float)rand()/(float)RAND_MAX * cylinderHeight-.01) - (cylinderHeight/2-.01);
        float r = ((float)rand()/(float)RAND_MAX * cylinderRadius-.1);
        float theta = ((float)rand()/(float)RAND_MAX * 2 * M_PI);
        float phi = ((float)rand()/(float)RAND_MAX * 2 * M_PI);
        particle[n].pos.y = r * cos(theta);
        particle[n].pos.z = r * sin(theta);
        particle[n].vel.x = velMax * sin(phi) * cos(theta);
        particle[n].vel.y = velMax * sin(phi) * sin(theta);
        particle[n].vel.z = velMax * cos(phi);
        //particle[n].vel.x = ((float)rand()/(float)RAND_MAX * velMax) - velMax/2;
        //particle[n].vel.y = ((float)rand()/(float)RAND_MAX * velMax) - velMax/2;
        //particle[n].vel.z = ((float)rand()/(float)RAND_MAX * velMax) - velMax/2;
    }
    
    //start calculations
    for (float t=0; t<totalTime; t=t+dt) {
        
        int cycle = (int) floor(t/period);
        if ( cycle % 2 == 0) {
            cylinderWallPosX = cylinderHeight/2 - (t-cycle*period)*wallVel;
        }
        else {
            cylinderWallPosX = cylinderHeight/2 + (t-period-cycle*period)*wallVel;
        }
        
        for (unsigned int i=0; i<num; i++) {
            if (particle[i].pos.x > cylinderWallPosX) {
                particle[i].vel.x = -abs(particle[i].vel.x) - wallVel;
            }
            if (particle[i].pos.x < cylinderWallNegX) {
                particle[i].vel.x = abs(particle[i].vel.x);
            }
            if (sqrt(pow((particle[i].pos.y), 2) + pow((particle[i].pos.z), 2)) > cylinderRadius) {
                //sqrt(pow((particle[i].vel.y), 2) + pow((particle[i].vel.z), 2)) * sin
                //printf("befor: y:%f, z:%f, mag:%f\n",particle[i].vel.y,particle[i].vel.z, sqrt(pow((particle[i].vel.x), 2) +
                                                                                               //pow((particle[i].vel.y), 2) +
                                                                                               //pow((particle[i].vel.z), 2)));
                float vectConst = 1/( pow(particle[i].pos.y, 2) + pow(particle[i].pos.z, 2) );
                particle[i].vel.y = vectConst * (particle[i].vel.y * pow(particle[i].pos.z, 2) -
                                    particle[i].vel.y * pow(particle[i].pos.y, 2) -
                                    2 * particle[i].vel.z * particle[i].pos.y * particle[i].pos.z);
                particle[i].vel.z = vectConst * (particle[i].vel.z * pow(particle[i].pos.y, 2) -
                                    particle[i].vel.z * pow(particle[i].pos.z, 2) -
                                    2 * particle[i].vel.y * particle[i].pos.y * particle[i].pos.z);
                //printf("after: y:%f, z:%f, mag:%f\n",particle[i].vel.y,particle[i].vel.z, sqrt(pow((particle[i].vel.x), 2) +
                                                                                               //pow((particle[i].vel.y), 2) +
                                                                                               //pow((particle[i].vel.z), 2)));
                /*
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
                 */
            }
            
            for (unsigned int j=i+1; j<num; j++) {
                r = sqrt(pow((particle[i].pos.x - particle[j].pos.x), 2) +
                               pow((particle[i].pos.y - particle[j].pos.y), 2) +
                               pow((particle[i].pos.z - particle[j].pos.z), 2));
                if (r < forceDistance) {
                    forceMag = k*((1/pow(r,7))-(2*pow(sigma,6)/pow(r,13)));
                    forceX = forceMag * (particle[i].pos.x - particle[j].pos.x)/r;
                    forceY = forceMag * (particle[i].pos.y - particle[j].pos.y)/r;
                    forceZ = forceMag * (particle[i].pos.z - particle[j].pos.z)/r;
                }
                else {
                    forceX = 0;
                    forceY = 0;
                    forceZ = 0;
                }
                
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
            
            fprintf(file, "%f,%f,%f,%f,%f,%f,%f\n",t,particle[i].pos.x,particle[i].pos.y,particle[i].pos.z,particle[i].vel.x,particle[i].vel.y,particle[i].vel.z);
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