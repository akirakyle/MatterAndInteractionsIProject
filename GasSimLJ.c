//  Created by Akira Kyle on 10/26/14.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main (void) {
    //Setup
    clock_t start = clock(), diff;
    FILE *file = fopen("Developer/MatterAndInteractionsIProject/Data/gasSimData.txt", "w");
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
    const unsigned int num = 400; //total number of particles
    const int totalTime = 140; //total time simulation is run for
    const float dt = 0.01; //time step for numeric integration
    const float epsilon = 10;    //depth of Lennard Jones potential well (affects magnitude of interatomic force)
    const float forceDistance = 0.39; //atomic radius* 2^(1/6) (nm)
    //container is cylinder
    const float volume = 37.2*num; // in nm^3 (note: 22.4L/mol = 37.2nm^3/particle)
    const float hTorRaio = 600; //height/radius ratio
    
    const float temperature = .01; //e-19 temperature in Kelvin
    const float mass = 28; //particle mass (diatomic nitrogen) in amu
    const float kb = 8.3148; //e21 Boltzman constant 8.3148×10^21 amu nm^2/(s^2*K)  (atomic mass unit (chemical scale) nanometers squared per second squared kelvin)
    const float avgVelInit = sqrt(3*kb*temperature/mass); //initaizes velocity of the particles (Given by temp) (nm/sec)
    //wall that creates pressure wave
    const float wallVel = 0; //the velocity that the wall moves to create sound wave
    const float period = .5; //the time that the wall takes to move (either forward or back)
                            //actually like a half period then
    //Calculated constants
    const float sigma = forceDistance/pow(2,(1.0/6.0));  //Lennard Jones constant
    const float k = -24*epsilon*pow(sigma,6)/mass;  //Lennard Jones constant simplification
    const float cylinderHeight = pow((hTorRaio * volume/M_PI), (1.0/3.0)); //in nm
    const float cylinderRadius = pow((volume/(M_PI*hTorRaio)), (1.0/3.0)); //in nm
    float cylinderWallPosX = cylinderHeight/2;
    const float cylinderWallNegX = -cylinderHeight/2;
    const float maxVel = 0.05*cylinderRadius/dt; //limits the maximum vel of the particles (necessary b/c numeric integration and finite time step
    printf("height:%f, radius:%f, maxVel:%f\n", cylinderHeight,cylinderRadius,maxVel);
    
    //Var initalizations
    struct particleStruct particle[num];
    int iteration = 0;
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
        particle[n].vel.x = avgVelInit * sin(phi) * cos(theta);
        particle[n].vel.y = avgVelInit * sin(phi) * sin(theta);
        particle[n].vel.z = avgVelInit * cos(phi);
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
        
        for (unsigned int i=0; i<num-1; i++) {
            if (particle[i].pos.x > cylinderWallPosX) {
                particle[i].vel.x = -abs(particle[i].vel.x) - wallVel;
            }
            if (particle[i].pos.x < cylinderWallNegX) {
                particle[i].vel.x = abs(particle[i].vel.x);
            }
            if (sqrt(pow((particle[i].pos.y), 2) + pow((particle[i].pos.z), 2)) > cylinderRadius) {
                float vectConst = 1/( pow(particle[i].pos.y, 2) + pow(particle[i].pos.z, 2) );
                particle[i].vel.y = vectConst * (particle[i].vel.y * pow(particle[i].pos.z, 2) -
                                    particle[i].vel.y * pow(particle[i].pos.y, 2) -
                                    2 * particle[i].vel.z * particle[i].pos.y * particle[i].pos.z);
                particle[i].vel.z = vectConst * (particle[i].vel.z * pow(particle[i].pos.y, 2) -
                                    particle[i].vel.z * pow(particle[i].pos.z, 2) -
                                    2 * particle[i].vel.y * particle[i].pos.y * particle[i].pos.z);
            }
            for (unsigned int j=i+1; j<num; j++) {
                r = sqrt(pow((particle[i].pos.x - particle[j].pos.x), 2) +
                         pow((particle[i].pos.y - particle[j].pos.y), 2) +
                         pow((particle[i].pos.z - particle[j].pos.z), 2));
                forceMag = k*(1/pow(r,7))*(1-(2*pow(sigma,6)/pow(r,6)));
                forceX = forceMag * (particle[i].pos.x - particle[j].pos.x)/r;
                forceY = forceMag * (particle[i].pos.y - particle[j].pos.y)/r;
                forceZ = forceMag * (particle[i].pos.z - particle[j].pos.z)/r;
                
                particle[i].vel.x = particle[i].vel.x + forceX*dt;
                particle[i].vel.y = particle[i].vel.y + forceY*dt;
                particle[i].vel.z = particle[i].vel.z + forceZ*dt;
                particle[j].vel.x = particle[j].vel.x - forceX*dt;
                particle[j].vel.y = particle[j].vel.y - forceY*dt;
                particle[j].vel.z = particle[j].vel.z - forceZ*dt;
                if (particle[i].vel.x > maxVel) {
                    //printf("vel.x:%f\n",particle[i].vel.x);
                    particle[i].vel.x = maxVel;
                }
                if (particle[i].vel.y > maxVel) {
                    particle[i].vel.y = maxVel;
                }
                if (particle[i].vel.z > maxVel) {
                    particle[i].vel.z = maxVel;
                }
                if (particle[i].vel.x < -maxVel) {
                    particle[i].vel.x = -maxVel;
                }
                if (particle[i].vel.y < -maxVel) {
                    particle[i].vel.y = -maxVel;
                }
                if (particle[i].vel.z < -maxVel) {
                    particle[i].vel.z = -maxVel;
                }
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