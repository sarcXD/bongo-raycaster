/*
Copyright (c) 2004-2019, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define mapWidth 8
#define mapHeight 8
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight] = 
{
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,2,3,2,0,1},
  {1,0,0,0,0,4,2,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1},
}

int main(int argc, char argv[])
{
  double posX = 2.0, posY = 2.0; // initial position vector
  double dirX = 1, dirY = 0; // initial direction vector
  double planeX = 0, planeY = 0.66; //2d raycaster camera plane, fov 66deg

  double time = 0; // current frame time
  double oldTime = 0; // previous frame time

  screen(screenWidth, screenHeight, 0, "Raycaster"); // init screen

  // gameloop
  while(!done())
  {
    // raycasting loop
    double w = screenWidth;
    for(int x = 0; x<w; x++)
    {
      double cameraX = 2 * double(x) / w - 1;
      double rayDirx = dirX + cameraX * planeX;
      double rayDiry = dirY + cameraY * planeY;
      
      // map box location
      int mapX = int(posX);
      int mapY = int(posY);

      // ray length from current x/y to next x/y
      double sideDistX;
      double sideDistY;

      // length of ray from 1 x/y to next x/y block
      double deltaDistX = std::abs(1/rayDirx);
      double deltaDistY = std::abs(1/rayDiry);
      double perpWallDist;

      // direction to step in x/y direction (+1/-1)
      int stepX;
      int stepY;

      int hit=0;
      int side; //NS wall or EW wall?

      // calculate step and initial sideDist
      if (rayDirx < 0)
      {
        stepX = -1;
        sideDistX = (mapX - posX) * deltaDistX;
      }
      else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if (rayDiry < 0)
      {
        stepY = -1;
        sideDistY = (mapY - posY) * deltaDistY;
      }
      else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }

      //perform DDA
      while (hit == 0)
      {
        // jumpt to next map square, Or in x-direction, Or in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        if (worldMap[mapX][mapY] > 0) hit = 1;
      }
      // calculating distance from wall the ray hit
      if (side == 0) 
      {
        perpWallDist = (mapX - posX + (1 - stepX)/2)/rayDirx;
      }
      else
      {
        perpWallDist = (mapY - posY + (1 - stepY)/2)/rayDiry;
      }

      int h = screenHeight;
      // calculate line height
      int lineheight = (int) (h/perpWallDist);

      // calculate lowest and highest pixel to fill in curr stripe
      int drawStart = - lineheight / 2 + h/2;
      if (drawStart < 0) drawStart = 0;
      int drawEnd = lineheight / 2 + h/2;
      if (drawEnd > h) drawEnd = h - 1;
      
      // things left, adding SDL, incorporating framerate count & cap,
      // rotating and moving player
    }
  }
}
