#ifndef LINEREADER_H
#define LINEREADER_H

#include "dxflib/dl_dxf.h"
#include "dxflib/dl_creationinterface.h"
#include <stdio.h>

class LineReader: public DL_CreationInterface {
	public:

	LineReader() {}
	 ~LineReader() {}

    /** Called for every point in the file */
    virtual void addPoint(double point[]);

    /** Called for every line in the file */
    virtual void addLine(double point1[], double point2[]);

    /** Called for every arc in the file */
	virtual void addArc(double center[],
                        double radius,
                        double angle1, double angle2,
                        bool reversed);

    /** Called for every arc in the file */
	virtual void addCircle(double center[],
                           double radius);

	/** Called for every polyline start in the file */
	virtual void addPolyline();

    /** Called for every polyline vertex in the file */
	virtual void addVertex(double point[], double bulge);

	void readLines(const char * filename);
};
#endif
