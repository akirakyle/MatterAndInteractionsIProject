from visual import *
from random import randrange
numBalls = 300
vscale = 0.1
ball = []
varr = []

for i in xrange(0,numBalls):
    ball.append(sphere(pos=(0,0,0), radius=0.5, color=color.cyan))
    ball[i].trail = curve(color=ball[i].color)
    ball[i].velocity = vector(randrange(-30,30,1),randrange(-30,30,1),randrange(-30,30,1))
    varr.append(arrow(pos=ball[i].pos, axis=vscale*ball[i].velocity, color=color.yellow))

wallL = box(pos=(-10,0,0), size=(0.2,20,20), color=color.green)
wallR = box(pos=(10,0,0), size=(0.2,20,20), color=color.green)
wallB = box(pos=(0,0,-10), size=(20,20,0.2), color=color.green)
wallU = box(pos=(0,10,0), size=(20,0.2,20), color=color.green)
wallD = box(pos=(0,-10,0), size=(20,0.2,20), color=color.green)

deltat = 0.005
t = 0
scene.autoscale = True

while t < 1000:
    rate(300)
    for i in xrange(0,numBalls):
        if (ball[i].pos.x > wallR.pos.x) or (ball[i].pos.x < wallL.pos.x):
            ball[i].velocity.x = -ball[i].velocity.x
        
        if (ball[i].pos.y > wallU.pos.y) or (ball[i].pos.y < wallD.pos.y):
            ball[i].velocity.y = -ball[i].velocity.y
        
        if (ball[i].pos.z > 10) or (ball[i].pos.z < wallB.pos.z):
            ball[i].velocity.z = -ball[i].velocity.z

        ball[i].pos = ball[i].pos + ball[i].velocity*deltat
        ball[i].trail.append(pos=ball[i].pos)
        varr[i].pos = ball[i].pos
        varr[i].axis=vscale*ball[i].velocity
    t = t + deltat
