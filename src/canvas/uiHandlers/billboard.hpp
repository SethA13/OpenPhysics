#include "../../objects/definitions/point.hpp"
#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#include <math.h>

void drawDigit(const Point & topLeft, char digit);
void drawNumber(const Point & topLeft, int number);
void drawText(const Point & topLeft, const char * text);
void drawLine(const Point & begin, const Point & end,
             float red = 1.0, float green = 1.0, float blue = 1.0);

const char NUMBER_OUTLINES[10][20] =
{
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   0,10,  0, 0,  -1,-1, -1,-1},//0
  {7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//1
  {0, 0,  7, 0,   7, 0,  7, 5,   7, 5,  0, 5,   0, 5,  0,10,   0,10,  7,10},//2
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   4, 5,  7, 5,  -1,-1, -1,-1},//3
  {0, 0,  0, 5,   0, 5,  7, 5,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1},//4
  {7, 0,  0, 0,   0, 0,  0, 5,   0, 5,  7, 5,   7, 5,  7,10,   7,10,  0,10},//5
  {7, 0,  0, 0,   0, 0,  0,10,   0,10,  7,10,   7,10,  7, 5,   7, 5,  0, 5},//6
  {0, 0,  7, 0,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//7
  {0, 0,  7, 0,   0, 5,  7, 5,   0,10,  7,10,   0, 0,  0,10,   7, 0,  7,10},//8
  {0, 0,  7, 0,   7, 0,  7,10,   0, 0,  0, 5,   0, 5,  7, 5,  -1,-1, -1,-1} //9
};

void drawDigit(const Point & topLeft, char digit)
{
   // we better be only drawing digits
   assert(isdigit(digit));
   if (!isdigit(digit))
      return;

   // compute the row as specified by the digit
   int r = digit - '0';
   assert(r >= 0 && r <= 9);

   // go through each segment.
   for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4)
   {
      assert(NUMBER_OUTLINES[r][c    ] != -1 &&
             NUMBER_OUTLINES[r][c + 1] != -1 &&
             NUMBER_OUTLINES[r][c + 2] != -1 &&
             NUMBER_OUTLINES[r][c + 3] != -1);

      //Draw a line based off of the num structure for each number
      Point start;
      start.setXPosition(topLeft.getXPosition() + NUMBER_OUTLINES[r][c]);
      start.setYPosition(topLeft.getYPosition() - NUMBER_OUTLINES[r][c + 1]);
      Point end;
      end.setXPosition(topLeft.getXPosition() + NUMBER_OUTLINES[r][c + 2]);
      end.setYPosition(topLeft.getYPosition() - NUMBER_OUTLINES[r][c + 3]);
         
      drawLine(start, end);
   }
}

void drawNumber(const Point & topLeft, int number)
{
   // our cursor, if you will. It will advance as we output digits
   Point point = topLeft;
   
   // is this negative
   bool isNegative = (number < 0);
   number *= (isNegative ? -1 : 1);
   
   // render the number as text
   std::ostringstream sout;
   sout << number;
   std::string text = sout.str();

   // handle the negative
   if (isNegative)
   {
      glBegin(GL_LINES);
      glVertex2f(point.getXPosition() + 1, point.getYPosition() - 5);
      glVertex2f(point.getXPosition() + 5, point.getYPosition() - 5);
      glEnd();
      point.addX(11);
   }
   
   // walk through the text one digit at a time
   for (const char *p = text.c_str(); *p; p++)
   {
      assert(isdigit(*p));
      drawDigit(point, *p);
      point.addX(11);
   }
}

void drawText(const Point & topLeft, const char * text)
{
   void *pFont = GLUT_BITMAP_HELVETICA_12;  // also try _18

   // prepare to draw the text from the top-left corner
   glRasterPos2f(topLeft.getXPosition(), topLeft.getYPosition());

   // loop through the text
   for (const char *p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}

void drawLine(const Point & begin, const Point & end,
              float red, float green, float blue)
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f(red, green, blue);

   // Draw the actual line
   glVertex2f(begin.getXPosition(), begin.getYPosition());
   glVertex2f(  end.getXPosition(),   end.getYPosition());

   // Complete drawing
   glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
   glEnd();
}