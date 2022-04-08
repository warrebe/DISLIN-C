/*
ECE 103
Homework #5
Benjamin Warren
Program Description: Program takes in file input of wave data and then averages that data, and plots
it using DISLIN, finally outputting averaged data into a file titled "output.txt"
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "dislin.h"

//Creates output file with averaged waveform data
void outputFile(float avgData[1500][2], int rowCount, int waveformCount) {
    int i, j;
    time_t now;
    time(&now);
    FILE *out_file;

    out_file = fopen("output.txt", "w"); //opens output file in "w"rite
    fprintf(out_file, "%s", ctime(&now));
    for(i = 0; i < rowCount; ++i) {
        for(j = 0; j < 2; ++j) {
            if(j == 1) {
                fprintf(out_file, "%f", avgData[i][j]);
            }
            else {
                fprintf(out_file, "%f,", avgData[i][j]);
            }
        }
        fprintf(out_file, "\n");
    }
    fclose(out_file);

    printf("output.txt created\n");
}

//Graphs 1st waveform data and averaged data into a DISLIN graph
void graph(int waveformCount, int rowCount, float waveData[1500][75], char graphTitle[79], char dataDate[39], char xAxis[79], char yAxis[79], float avgData[1500][2]) {
	int i;
	float y2[1500] = {0.0}, y1[1500], x[1500];
    char legend3[100] = "\0", legTitle[ ] = "\0";

    char legend1[ ] = "Noisy waveform #1";
    char legend2[ ] = "Averaged waveform";

    for(i = 0; i < rowCount; ++i) {
        x[i] = avgData[i][0];
	}

    for(i = 0; i < rowCount; ++i) {
        y1[i] = avgData[i][1];
	}

    for(i = 0; i < rowCount; ++i) {
        y2[i] = waveData[i][1];
	}


	metafl("XWIN"); // Defines the plot file format
	setpag("da4l"); // Selects a predefined page format

	// Set up plot
    scrmod("REVERSE");
	disini();              // Initialize DISLIN
	pagera();              // Plot a page border
	hwfont();              // Set a standard hardware font

	axspos(400, 1600);     // Determine the position of axis system
	axslen(2200, 1200);    // Define axis length for 2-D axis system

	name(xAxis, "x"); // Define x-axis title
	name(yAxis, "y"); // Define y-axis title

	labdig(2, "x");       // Set number of decimal places for tick labels
	ticks(10, "xy");      // Set number of ticks

	titlin(graphTitle, 1);   // Define text lines for title
    titlin (dataDate, 2);

   	graf(0.f, 50.f, 0.f, 10.f, -50.f, 50.f, -50.f, 10.f);

//    gaxpar(0.f, 100.f, "EXTEND", "X", maxValx, maxValx,maxValx, maxValx, digits);         //wasnt able to dynamically create axis parameters
 //   gaxpar(-100.f, 100.f, "EXTEND", "Y", maxValy, maxValy, maxValy, maxValy, digits);

	title();              // Plot the title over the axis system

	color ("red");         // Color for first curve
    curve (x, y2, rowCount);
	color ("blue");       // Color for second curve
	curve(x, y1, rowCount); 	      // Plot curve for y2 versus x

	legini(legend3, 2, 100);

	legclr();

	frmclr(1);;

	legtit(legTitle);

	leglin(legend3, legend1, 1);
	leglin(legend3, legend2, 2);

	legend(legend3, 1);

	color("fore");        // Reset color to default value
	dash ();              // Set a dashed line style
	xaxgit();              // Plot the line Y = 0

	disfin();              // Terminates DISLIN
}

//Averages data from input file
void average(int waveformCount, int rowCount, float waveData[1500][75], char graphTitle[79], char dataDate[39], char xAxis[79], char yAxis[79]) {
    float avgData[1500][2];
    float average;
    int i, j;

    for(i = 0; i < rowCount; ++i) {
        avgData[i][0] = waveData[i][0];
    }

    for (i = 0; i < rowCount; ++i) {
        average = 0.0;
        for(j = 1; j <= waveformCount; ++j) {
            average += waveData[i][j];
        }
        avgData[i][1] = (average / waveformCount);
    }

    graph(waveformCount, rowCount, waveData, graphTitle, dataDate, xAxis, yAxis, avgData); //Calls graph function

    outputFile(avgData, rowCount, waveformCount); //calls output function
}

//Reads selected input file of waveform data
int fileRead() {
    char dataFile[100]; // file to open
    int waveforms; // number of waveforms
    float data[1500][75];// floating point waveform data values
    char title[79], date[39], x[79], y[79]; // file/graph subtexts
    int i = 0, j;
    int rows;
    FILE *in_file;

    printf("Enter name of data file to read: ");
    fgets(dataFile, 100, stdin);
    dataFile[strlen(dataFile) - 1] = '\0';

    in_file = fopen(dataFile, "r");

    if (in_file == NULL) {
        printf("\nError cannot open file\n");
        return -1;
    }
    else {
        fscanf(in_file, "%d", &waveforms);
        while(fgetc(in_file) != 'E') {
            for(j = 0; j <= waveforms; ++j) {
                if(j == 0) {
                    fscanf(in_file, "%f", &data[i][j]);
                }
                else {
                    fscanf(in_file, ",%f", &data[i][j]);
                }
            }
            ++i;
        }
        rows = i - 1;

        fgets(title, 80, in_file);
        fgets(title, 80, in_file);
        fgets(date, 40, in_file);
        fgets(x, 79, in_file);
        fgets(y, 80, in_file);

        average(waveforms, rows, data, title, date, x, y); //calls average function

        fclose(in_file);
    }

    return 1;
}

//Main function, start and end of program
int main() {
    if(fileRead() < 0) { //if input file is not found, return error
        return -1;
    }
    else  {
        return 0;
    }
}
