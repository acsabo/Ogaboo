/*
 * LineReader.cpp
 *
 *  Created on: 19/05/2015
 *      Author: a.sabo
 */

#include "LineReader.h"
#include <iostream>

using namespace std;

/** Called for every point in the file */
void LineReader::addPoint(double point[]) {
	fprintf(stderr, "addPoint.\n");
};

/** Called for every line in the file */
void LineReader::addLine(double point1[], double point2[]){
	fprintf(stderr, "addLine.\n");
};

/** Called for every arc in the file */
void LineReader::addArc(double center[],
                    double radius,
                    double angle1, double angle2,
                    bool reversed){
	fprintf(stderr, "addArc.\n");
};

/** Called for every arc in the file */
void LineReader::addCircle(double center[],
                       double radius){
	fprintf(stderr, "addCircle.\n");
};

/** Called for every polyline start in the file */
void LineReader::addPolyline(){
	fprintf(stderr, "addPolyline.\n");
};

/** Called for every polyline vertex in the file */
void LineReader::addVertex(double point[], double bulge){
    fprintf(stderr, "addVertex.\n");
};

void LineReader::readLines(const char * filename) {
  DL_Dxf * getData = new DL_Dxf();
  if (!getData->in(filename, this)) {
    fprintf(stderr, "ERROR.\n");
    delete getData;
    //exit(1);
  }
  delete getData;
};
