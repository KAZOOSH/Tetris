
#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include "ofxCv.h"
#include "ofMain.h"
#include <iostream>

using namespace cv;

using std::cout;
using std::endl;
using std::ostream;

class Edge {
public:
	Edge();
	Edge(cv::Point one, cv::Point two);
	Edge(cv::Point one, cv::Point two, double slope, double intercept);
	void set1(cv::Point one);
	void set2(cv::Point two);
	void setSlope();
	cv::Point get1() const;
	cv::Point get2() const;
	double getSlope() const;
	double getIntercept() const;
	bool operator== (const Edge& rhs);

private:
	cv::Point _one;
	cv::Point _two;
	double _slope;
	double _intercept; // "b" value
	double _precisionSlope = 0.05; // Acceptable error in slope calculations
	double _precisionIntercept = 10; // Acceptable error in intercept calculations
	double _inf = std::numeric_limits<double>::infinity();
};

ostream& operator<< (ostream& os, const Edge& e);
bool operator< (const Edge & lhs, const Edge & rhs);
bool compareWithPrecision(double precision, double first, double second);
