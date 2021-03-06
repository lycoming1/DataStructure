#include <windows.h>      // Microsoft Windows functions
#include <GL/glut.h>      // GLUT functions for windows, keybd, mouse
#include <cmath>					// for all math, some used in circle, etc

#ifndef CIE_2D_GRAPH_H
#define CIE_2D_GRAPH_H

#define NU_PAUSE 50
#define NU_SCREENWIDTH		800		// Drawing window's width, height in pixels
#define NU_SCREENHEIGHT		600
#define NU_SCREEN_XPOS		10		// Drawing window position, in pixels.
#define NU_SCREEN_YPOS		10

#if !defined(M_PI)						// If we don't have PI defined already,
#define M_PI				3.1415926535897932384626433832795
#endif									// (PI from MS 'Calculator' app...)
#define NU_ANGLESTEP		M_PI/180.0	// draw curves in 1-degree increments

/* font options */
#define rom10 GLUT_BITMAP_TIMES_ROMAN_10
#define rom24 GLUT_BITMAP_TIMES_ROMAN_24
#define helv10 GLUT_BITMAP_HELVETICA_10
#define helv12 GLUT_BITMAP_HELVETICA_12
#define helv18 GLUT_BITMAP_HELVETICA_18

extern void display(void);			// Prototype for the display function
extern void keyboard(unsigned char key, int x, int y);	// Prototype for key handling function

namespace Cie2DGraph
{
    static int app_visible;
    static int app_time;
    void DisplayCallback();
    void KeyboardCallback(unsigned char key, int x, int y);
    void SpecialKeyCallback(int key, int x, int y);
    void MouseCallback(int button, int state, int x, int y);
    void VisibilityCallback (int visibility);
    void IdleCallback(void);
    void ReshapeCallback(int w, int h);
//------------------------------------------------------------------------------
// InitGraphics()
// InitGraphics2(title, w, h, x, y)
//
// Initializes GLUT graphics and opens a w x h window
// at x, y on the screen.
    void InitGraphics(void);
    void InitGraphics2(const char * title, int w, int h, int x, int y);

//------------------------------------------------------------------------------
// GetWindowHeight()
// GetWindowWidth()
//
// Return window height and width in pixels. Do not call until after
// InitGraphics() has been called!
    int GetWindowHeight();
    int GetWindowWidth();

/*------------------------------------------------------------------------------
Function prototypes for GLUT callbacks.  A 'callback' is a function that YOU
write, but you never call; instead, something else calls it, such as another
program, the operating system, or a collection of ready-made functions.
The GLUT library uses callbacks.  Its functions take care of all the pesky
details of putting your drawings in a proper on-screen Window, complete with
a frame, title bar, little buttons at the corner, and drag-able corners for
resizing.  When it needs your program to re-draw the screen, it calls the
'myDisplay()' function. When GLUT has nothing more to do, it calls 'myIdle()'.
GLUT has other callbacks for when the user presses a key on the keyboard,
pushes down a mouse button, moves the mouse, or releases a mouse button, etc.,
we aren't using them all here, but you're welcome to do so.  To find out how,
search the web for a GLUT tutorial.  You will need to 'register' the name
of your callback function, and make sure your function has the right arguments
and return type.
------------------------------------------------------------------------------*/

/*==============================================================================
		Function Prototypes for on-screen drawing and animation.
		WE WILL USE *ONLY* THESE FUNCTIONS for DRAWING on the SCREEN.
==============================================================================*/

//------------------------------------------------------------------------------
// DrawLine(x0, y0, x1, y1)
//
// Draw a line from (x0,y0) and ending at (x1,y1).
// (doesn't use relative addressing).
// x,y are measured in pixels.

    void DrawLine(double x0, double y0, double x1, double y1);

    void DrawArrowLine(double x0, double y0, double x1, double y1, double s1, double s2);
//-----------------------------------------------------------------------------
// DrawBox (x0, y0, x1, y1)
//
// Draw a box using the current pen color with lower left corner at (x0,y0)
// and upper right corner at x1, y1.
// x,y are measured in pixels.

    void DrawBox(double x0, double y0, double x1, double y1);

//------------------------------------------------------------------------------
// DrawFillBox (x0, y0, x1, y1)
//
// Draw a box and fill the region inside it using the current pen color.
// You can specify the pen color with the SetPenColor() function.
// The default color is black.
// x,y are measured in pixels.

    void DrawFillBox(double x0, double y0, double x1, double y1);

    void DrawTriangle(double x0, double y0, double x1, double y1, double x2, double y2);
//------------------------------------------------------------------------------
// DrawFillTriangle(x0, y0, x1, y1, x2, y2)
//
// Draw a triangle and fill the region inside it using the current pen color
// Default fill color is black, but you can change it with the SetPenColor() function.
// x,y are measured in pixels.

    void DrawFillTriangle(double x0, double y0, double x1, double y1, double x2, double y2);


//-----------------------------------------------------------------------------
// DrawCircle(xctr, yctr, radius)
//
// Draw the outline of a circle centered at (xctr,yctr) and width of 'radius'.
// using the current pen color and line width. Default pen color is black, but
// the 'SetPenColor()' function can change it.
// Draws the circle as a sequence of very short,straight lines.
// x,y, radius are measured in pixels.

    void DrawCircle(double xctr, double yctr, double radius);


//----------------------------------------------------------------------------
// DrawFillCircle(xctr, yctr, radius)
//
// Draw a circle and fill the region inside it using the the current pen color.
// Default pen color is black, but the SetFillColor() function will change it.
// Draws the shape using filled triangles.
// x,y, radius are measured in pixels

    void DrawFillCircle(double xctr, double yctr, double radius);

//-----------------------------------------------------------------------------
// DrawEllipse(xctr, yctr, x_radius, y_radius)
//
// Draw the outline of an ellipse centered at (xctr,yctr), width of 2 * x_radius
// and height of 2 * y_radius.
// Uses the current pen color and line width.
// Draws the ellipse as a sequence of very short,straight lines.
// All values are measured in pixels.

    void DrawEllipse(double xctr, double yctr, double x_radius, double y_radius);
    void DrawDonet(double xctr, double yctr, double x_radius, double y_radius, double ratio);
//-----------------------------------------------------------------------------
// DrawFillEllipse(xctr, yctr, x_radius, y_radius)
//
// Draw an ellipse centered at (xctr,yctr), width of 2 * x_radius
// and height of 2 * y_radius.
// Uses the current pen color to fill the ellipse.
// Draws the ellipse as a sequence of very short,straight lines.
// All values are measured in pixels.

    void DrawFillEllipse(double xctr, double yctr, double x_radius, double y_radius);

    void DrawFillDonet(double xctr, double yctr, double x_radius, double y_radius, double ratio);
//-----------------------------------------------------------------------------
// DrawArc (xctr, yctr, radius, startAngle, endAngle)
//
// Draw a circular arc using the current pen color. Plots a portion of the
// circle whose center is (xctr,yctr) and width is given by 'radius', but only
// draws the portion of the circle between 'startAngle' and 'endAngle'.  Both
// the start and end angles are measured from the right-most point on the circle
// (e.g. the x-axis intercept for a circle centered at the origin) in the
// counter-clockwise direction, in degrees.  Default pen color is black, but
// the 'SetPenColor()' function can change it for you.
// Draws the arc as a sequence of short, straight-line segments.
// x,y, radius are measured in pixels
// Angles are measured in degrees

    void DrawArc (double xctr, double yctr, double radius,
			  double startAngle, double endAngle);


//-----------------------------------------------------------------------------
// DrawPieArc (xctr, yctr, radius, startAngle, endAngle)
//
// Draw a circular arc and fill the pie-slice-shaped region between the arc
// and its center point with the current pen color.  Default fill color is black,
// but the SetFillColor() function can change it.
// Draws the shape using filled triangles.
// x,y, radius are measured in pixels
// Angles are measured in degrees

    void DrawPieArc(double xctr, double yctr, double radius,
				  double startAngle, double endAngle);


//-----------------------------------------------------------------------------
// DrawText2D(font, x0, y0, pString)
//
//  Write the text string stored at 'pString' to the display screen using the
//  current pen color and the specified font.
//  It places the lower left corner of the first line of text
//  at position x0,y0.
//	Example:  DrawText2D(helv18, 10,20,"Hello!");
//
// See #defined values at the top of this file for a list of available fonts


    void DrawText2D(void *font, double x0, double y0, const char* pString);

//-----------------------------------------------------------------------------
// ClearWindow()
//
//  Calls OpenGL 'clear screen' function; fills the screen with background color.
//  You can change that by calling the SetBackgndColor() function

    void ClearWindow(void);

//------------------------------------------------------------------------------
// SetPenColor(red, green, blue)
// SetPenColorHex(unsigned long color)
//
// Set the drawing color.
//   red, green, blue range from 0.0 to 1.0
//   color is a single "web" color value, e.g., 0xFF33EE.
//
//   Commonly used colors:
//		(0.0,0.0,0.0) = 0x0 = black		   (1.0,1.0,1.0) = 0xFFFFFF = white
//		(1.0,0.0,0.0) = 0xFF0000 = red	   (0.0,1.0,1.0) = 0x00FFFF = cyan
//		(0.0,1.0,0.0) = 0x00FF00 = green   (1.0,0.0,1.0) = 0xFF00FF = magenta
//		(0.0,0.0,1.0) = 0x0000FF = blue	   (1.0,1.0,0.0) = 0xFFFF00 = yellow
//		(0.5,0.5,0.5) = 0x808080 = grey	   (1.0,0.5,0.0) = 0xFFA500 = orange
//		(0.5,0.0,0.5) = 0x800080 = purple  (0.5,0.25,0.0) = 0xA52A2A = brown
//		(0.0,0.25,0.0) = 0x228B22 = forest green
//		(0.0,0.0,0.25) = 0x191970 = midnight blue
//
//   Note: the hexadecimal versions are common browser definitions, as listed at
//
//     http://www.w3schools.com/html/html_colornames.asp
//
//   and not identical to the red, green, blue values.
//
//   Try fractional amounts of red,green,blue, for other, more subtle colors.
//   You have 2^24 = 24 Million different color combinations available!


    void SetPenColor(double red, double green, double blue);
    void SetPenColorHex(unsigned long color);

//-----------------------------------------------------------------------------
//
// Set the drawing color, using a single hexadecimal color integer.



//-----------------------------------------------------------------------------
// SetBackgndColor(red, green, blue)
// SetBackgndColorHex(color)
//
//  Sets the color used by 'ClearWindow()' function, and then fills the entire
// window with that color.

    void SetBackgndColor(double red, double green, double blue);
    void SetBackgndColorHex(unsigned long color);

//----------------------------------------------------------------------------
// SetDottedLines()
//
//  Change pen to draw dotted lines instead of solid lines. All lines drawn
//  after this call will be drawn dotted until you call the 'DrawSolidLines()'
//  function.

    void SetDottedLines(void);


//-----------------------------------------------------------------------------
// SetSolidLines()
//
//  Change the pen back to the default of drawing solid lines.  All lines drawn
//  after this call will be drawn solid until you call the 'DrawDottedLines()'
//  function.

    void SetSolidLines(void);


//-----------------------------------------------------------------------------
// SetLineWidth(wide)
//
//  Change the width (in pixels) of the lines drawn by the pen.  Default value is 3.0;
//  Careful! if you set 'wide' to zero, all lines drawn are invisible!

    void SetLineWidth(double wide);
}
#endif
