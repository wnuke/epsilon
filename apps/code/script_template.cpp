#include "script_template.h"

namespace Code {

constexpr ScriptTemplate emptyScriptTemplate(".py", "\x01" R"(from math import *
)");

constexpr ScriptTemplate squaresScriptTemplate("squares.py", "\x01" R"(from math import *
from turtle import *
def squares(angle=0.5):
  reset()
  L=330
  speed(10)
  penup()
  goto(-L/2,-L/2)
  pendown()
  for i in range(660):
    forward(L)
    left(90+angle)
    L=L-L*sin(angle*pi/180)
  hideturtle())");

constexpr ScriptTemplate mandelbrotScriptTemplate("mandelbrot.py", "\x01" R"(# This script draws a Mandelbrot fractal set
# N_iteration: degree of precision
import kandinsky
def mandelbrot(N_iteration):
  for x in range(320):
    for y in range(222):
# Compute the mandelbrot sequence for the point c = (c_r, c_i) with start value z = (z_r, z_i)
      z = complex(0,0)
# Rescale to fit the drawing screen 320x222
      c = complex(3.5*x/319-2.5, -2.5*y/221+1.25)
      i = 0
      while (i < N_iteration) and abs(z) < 2:
        i = i + 1
        z = z*z+c
# Choose the color of the dot from the Mandelbrot sequence
      rgb = int(255*i/N_iteration)
      col = kandinsky.color(int(rgb),int(rgb*0.75),int(rgb*0.25))
# Draw a pixel colored in 'col' at position (x,y)
      kandinsky.set_pixel(x,y,col))");

constexpr ScriptTemplate polynomialScriptTemplate("polynomial.py", "\x01" R"(from math import *
# roots(a,b,c) computes the solutions of the equation a*x**2+b*x+c=0
def roots(a,b,c):
  delta = b*b-4*a*c
  if delta == 0:
    return -b/(2*a)
  elif delta > 0:
    x_1 = (-b-sqrt(delta))/(2*a)
    x_2 = (-b+sqrt(delta))/(2*a)
    return x_1, x_2
  else:
    return None)");

constexpr ScriptTemplate pongScriptTemplate("pong.py", "\x01" R"(from math import *
  # Pong for NumWorks by boricj

  from time import *
  from kandinsky import *
  from random import *


  def pong():


  WIDTH = 320
  HEIGHT = 224


  class Paddle:
      def __init__(self, x):
          self.width = 16
          self.height = 64
          self.x = x
          self.y = ((224 - self.height) / 2)

      def move(self, dy):
          self.y = min(max(self.y + dy, 0), HEIGHT - self.height)


  class Ball:
      def __init__(self):
          self.width = 16

      def reset(self):
          self.x = (WIDTH - self.width) / 2
          self.y = (HEIGHT - self.width) / 2
          self.dx = (random() + 3) * 16
          self.dy = (random() + 3) * 16

      def collide(self, pad):
          bx1 = self.x
          by1 = self.y
          bx2 = self.x + self.width
          by2 = self.y + self.width
          px1 = pad.x
          py1 = pad.y
          px2 = pad.x + pad.width
          py2 = pad.y + pad.height
          if bx1 < px2 and bx2 > px1 and by1 < py2 and by2 > py1:
              return True
          return False


  B = Ball()
  B.reset()
  P1 = Paddle(16)
  P2 = Paddle(WIDTH - 32)
  score1 = 0
  score2 = 0
  fill_rect(0, 0, WIDTH, HEIGHT, color(0, 0, 0))

  prevTime = monotonic()
  while True:
      curTime = monotonic()
      dTime = curTime - prevTime
      prevTime = curTime
      keys = get_keys()
      oldp1x = P1.x
      oldp1y = P1.y
      oldp2x = P2.x
      oldp2y = P2.y
      oldbx = B.x
      oldby = B.y
      B.x += B.dx * dTime
      B.y += B.dy * dTime
      if "up" in keys:
          P1.move(-128 * dTime)
      elif "down" in keys:
          P1.move(128 * dTime)
      if P2.y + P2.height / 2 > B.y + B.width / 2:
          P2.move(-160 * dTime)
      else:
          P2.move(160 * dTime)
      if B.collide(P1):
          B.x = P1.x + P1.width + 1
          B.dx *= -1.1
          B.dy *= 1.1
      elif B.collide(P2):
          B.x = P2.x - B.width - 1
          B.dx *= -1.1
          B.dy *= 1.1
      if B.x < 0:
          B.reset()
          score2 += 1
      elif B.x > WIDTH:
          B.reset()
          score1 += 1
      if B.y < 0:
          B.y = 1
          B.dy = -B.dy
      elif B.y > HEIGHT - B.width:
          B.y = HEIGHT - B.width - 1
          B.dy = -B.dy
      wait_vblank()
      fill_rect(int(oldp1x), int(oldp1y), P1.width, P1.height, color(0, 0, 0))
      fill_rect(int(oldp2x), int(oldp2y), P2.width, P2.height, color(0, 0, 0))
      fill_rect(int(oldbx), int(oldby), B.width, B.width, color(0, 0, 0))
      fill_rect(int(P1.x), int(P1.y), P1.width, P1.height, color(0, 0, 255))
      fill_rect(int(P2.x), int(P2.y), P2.width, P2.height, color(255, 0, 0))
      fill_rect(int(B.x), int(B.y), B.width, B.width, color(255, 255, 255))
      draw_string(str(score1), int(WIDTH / 4), 16)
      draw_string(str(score2), int(3 * WIDTH / 4), 16)");

const ScriptTemplate * ScriptTemplate::Empty() {
        return &emptyScriptTemplate;
}

const ScriptTemplate * ScriptTemplate::Squares() {
        return &squaresScriptTemplate;
}

const ScriptTemplate * ScriptTemplate::Mandelbrot() {
        return &mandelbrotScriptTemplate;
}

const ScriptTemplate * ScriptTemplate::Polynomial() {
        return &polynomialScriptTemplate;
}

const ScriptTemplate * ScriptTemplate::Pong() {
        return &pongScriptTemplate;
}

}
