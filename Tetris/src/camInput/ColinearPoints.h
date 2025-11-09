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

    vector<vector<cv::Point>> computeColinearPoints();
    void addPoint(cv::Point point);
		void clearPointList();
		int getPointListSize();

		void setSlopePrecision(double slope);
		void setInterceptPrecision(double intercept);

	private:
    vector<cv::Point> edgesToPoints(vector<Edge> edgeList);
    vector<cv::Point> points;
		double precisionSlope = 0.05; // Acceptable error in slope calculations
		double precisionIntercept = 10; // Acceptable error in intercept calculations

};

