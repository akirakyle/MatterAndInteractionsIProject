from visual import *
from random import randrange
from visual.graph import *
numBalls = 100
vscale = 0.1
ball = []
varr = []

display(x = 0, y = 0, height = 400, width = 1000, title = "Waves in One Dimensional Gas")
for i in xrange(0,numBalls):
    ball.append(sphere(pos=((i-100)/3e9,0,0), radius= 139e-12, color=color.cyan))
    ball[i].velocity = vector(randrange(-30,30,1),0,0)

rod = cylinder(pos=(-400e-10,0,0), axis=(450e-10,0,0), radius=5e-10, color=color.white, opacity=0.1)

wallR = box(pos=(50e-10,0,0), size=(1e-10,1e-8,1e-8), color=color.blue, opacity=0.3)
wallL = box(pos=(-400e-10,0,0), size=(1e-10,1e-8,1e-8), color=color.blue, opacity=0.3)

#vmax = 5000

deltat = 0.000000000005
t = 0

#d1 = gdisplay(x = 0, y = 200, height = 400, width = 800, xmin = 0, xmax = vmax, ymin = -0.3,
#              ymax = 5000, title = "Boltzmann Distribution", xtitle = "Velocity (m/s)",
#              ytitle = "Number of Molecules")

#drawb = gcurve(color = color.red)


scene.autoscale = True

while t < 1000:
    rate(200)
    for i in xrange(0,numBalls):
        if (ball[i].pos.x > wallR.pos.x) or (ball[i].pos.x < wallL.pos.x):
            ball[i].velocity.x = -ball[i].velocity.x     
        for j in xrange (0, numBalls):
            if ((ball[i].pos.x - ball[j].pos.x) < 139e-12):
                ball[i].velocity.x = -ball[i].velocity.x
                ball[j].velocity.x = -ball[j].velocity.x

        ball[i].pos = ball[i].pos + ball[i].velocity*deltat

#        drawb.plot(pos = (mag(ball[i].velocity), 

    t = t + deltat

