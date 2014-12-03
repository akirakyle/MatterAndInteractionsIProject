from visual import *
from random import randrange
import time

start = time.time()

file = open("pyData.txt","w")

num = 1000
particle = []
class Data:
    def __init__(self, pos, vel):
        self.pos = pos
        self.vel = vel

for i in xrange(0,num):
    particle.append(Data(vector(randrange(-10,10,1),randrange(-10,10,1),randrange(-10,10,1)), vector(randrange(-10,10,1),randrange(-10,10,1),randrange(-10,10,1))))

iteration = 0
totTime = 2
dt = 0.01
t = 0

while t <= totTime+dt:
    for i in xrange(0,num):
        if (particle[i].pos.x > 10) or (particle[i].pos.x < -10):
            particle[i].vel.x = -particle[i].vel.x
        
        if (particle[i].pos.y > 10) or (particle[i].pos.y < -10):
            particle[i].vel.y = -particle[i].vel.y
        
        if (particle[i].pos.z > 10) or (particle[i].pos.z < 10):
            particle[i].vel.z = -particle[i].vel.z

        for j in xrange(i+1,num):
            if (mag(particle[i].pos-particle[j].pos) < 1):
                particle[i].vel = -particle[i].vel
                particle[j].vel = -particle[j].vel

        particle[i].pos = particle[i].pos + particle[i].vel*dt
        if ((iteration % 20) == 0):
            file.write(str(t)+": "+str(particle[i].pos)+"\n")
    if ((iteration % 20) == 0):
            print iteration
    iteration = iteration + 1
    t = t + dt

end = time.time()
print end - start
