from visual import *
from random import randrange
from visual.graph import *


k = 9.0e9 # Electric force constant
elechg = 1.6e-19 # Proton charge in Coulombs
nuclmass = 1.67e-27 # Nucleon mass in kg
imppara = 0

numBalls = 100 # Number of particles in simulation
vscale = 0.1 
ball = []
varr = []

size = 139e-12 * 20
display(height = 400, width = 1000, title = "Waves in One Dimensional Gas", range=size)

dt = 5e-12
t = 0

scene.autoscale = True
for i in xrange(0,numBalls):
    ball.append(sphere(pos=((i-(numBalls / 2))/1e7,0,0), radius= 139e-12, color=color.cyan))
# Check the spacing later and try to get it to accurate density of air
    ball[i].velocity = vector(randrange(-3,3,1),0,0)
# Who knows if this actually should be randomized, but try to start it with more
# accurate values
    ball[i].mass = nuclmass * 14
    ball[i].charge = elechg * 7
    ball[i].momentum = ball[i].mass * ball[i].velocity

d1 = gdisplay(x = 0, y = 200, height = 400, width = 800, xmin = 0, xmax = 5000, ymin = -0.3,
              ymax = 5000, title = "Boltzmann Distribution", xtitle = "Velocity (m/s)",
              ytitle = "Number of Molecules")

drawb = gcurve(color = color.red)

while t < 1000:
    rate(200)
    for i in xrange(0,numBalls):
        for j in xrange(i+1,numBalls):
            print i
            print ball[i].pos.x
            print j
            print ball[j].pos.x
            ball[j].force = vector((((k * ball[i].charge * ball[i].charge)/ (ball[i].pos.x -ball[j].pos.x)**2)),0,0) #* (norm(ball[i].pos - ball[j].pos))
            ball[j].momentum = ball[i].momentum + ball[j].force * dt
            ball[j].pos = (ball[i].pos + ball[j].momentum * dt) / ball[i].mass
            ball[j].velocity = ball[j].momentum / ball[i].mass

#            drawb.plot(pos = (ball[i].velocity, 
            
