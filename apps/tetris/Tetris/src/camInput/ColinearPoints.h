#pragma once

#include "ofxCv.h"
#include "ofMain.h"
#include "Edge.h"

using namespace ofxCv;
using namespace cv;


class ColinearPoints
{
	public:
		ColinearPoints();
		~ColinearPoints();

		vector<vector<Point>> computeColinearPoints();
		void addPoint(Point point);
		void clearPointList();
		int getPointListSize();

		void setSlopePrecision(double slope);
		void setInterceptPrecision(double intercept);

	private:
		vector<Point> edgesToPoints(vector<Edge> edgeList);
		vector<Point> points;
		double precisionSlope = 0.05; // Acceptable error in slope calculations
		double precisionIntercept = 10; // Acceptable error in intercept calculations

};

