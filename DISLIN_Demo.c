/*
 * This is an example program for plotting
 * data using the DISLIN graphics library.
 * (Adapted from exa_1 from file exa_c.c)
 * (Annotations added by instructor.    )
 * 
 * Helmut Michels
 * (C) 2011, Max Planck Institute for Solar System Research
 */

#include <stdio.h>
#include <math.h>                  
#include <string.h>
#include "dislin.h" // Required for accessing DISLIN

// Macros
#define NUM_PTS 100   // Number of data points
#define MAX_ASIZE 300 // Maximum array size

int main (void)
{       
	float x[MAX_ASIZE];             // x-axis data array
	float y1[MAX_ASIZE], y2[MAX_ASIZE]; // y-axis data arrays
	int n = NUM_PTS;                // Number of data points
	int i;                          // Loop index
	double fpi = 3.1415926 / 180.;  // Conversion deg to rads
	double step;                    // Loop step size
	double angle;                   // Sinusoid angle

	metafl ("XWIN"); // Defines the plot file format
	setpag ("da4l"); // Selects a predefined page format


	step = 360. / (n-1); // Define step size for sinusoid computation

	// Fill data arrays with values. DISLIN expects arrays of
	// type float, so double arrays must be coerced to float.
	for (i = 0; i < n; i++)
	{
		x[i] = (float) (i * step);
		angle = x[i] * fpi; /* Convert from degrees to radians */
		y1[i] = (float) sin(angle);
		y2[i] = (float) cos(angle);
	}

	// Set up plot
	disini ();              // Initialize DISLIN
	pagera ();              // Plot a page border
	hwfont ();              // Set a standard hardware font

	axspos (450, 1800);     // Determine the position of axis system
	axslen (2200, 1200);    // Define axis length for 2-D axis system

	name   ("X-axis", "x"); // Define x-axis title
	name   ("Y-axis", "y"); // Define y-axis title

	labdig (-1, "x");       // Set number of decimal places for tick labels
	ticks  (10, "xy");      // Set number of ticks

	titlin ("Demonstration of CURVE", 1);   // Define text lines for title
	titlin ("SIN(X), COS(X)", 3);

	/* Plot a 2-D axis system:
           graf (XA, XE, XOR, XSTP, YA, YE, YOR, YSTP)

           XA, XE    - lower and upper limits of the X-axis
           XOR, XSTP - first X-axis label and the step between labels
           YA, YE    - lower and upper limits of the Y-axis
           YOR, YSTP - first Y-axis label and the step between labels
        */
	graf   (0.f, 360.f, 0.f, 90.f, -1.f, 1.f, -1.f, 0.5f);

	title  ();              // Plot the title over the axis system

	color  ("red");         // Color for first curve
	curve  (x, y1, n);      // Plot curve for y1 versus x
	color  ("green");       // Color for second curve
	curve  (x, y2, n);      // Plot curve for y2 versus x

	color  ("fore");        // Reset color to default value
	dash   ();              // Set a dashed line style
	xaxgit ();              // Plot the line Y = 0

	disfin ();              // Terminates DISLIN

	return 0;
}
