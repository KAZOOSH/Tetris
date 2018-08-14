
#pragma once

#include "Edge.h"

Edge::Edge() {
	_one = cv::Point();
	_two = cv::Point();
	_slope = 0.0;
	_intercept = 0.0;
}

Edge::Edge(cv::Point one, cv::Point two) {
	_one = one;
	_two = two;
	setSlope();
	// y = mx + b, so b = y - mx
	_intercept = one.y - (_slope * one.x);
}

Edge::Edge(cv::Point one, cv::Point two, double slope, double intercept) {
	_one = one;
	_two = two;
	setSlope();
	_precisionSlope = slope;
	_precisionIntercept = intercept;
	// y = mx + b, so b = y - mx
	_intercept = one.y - (_slope * one.x);
}


void Edge::set1(cv::Point one) {
	_one = one;
}

void Edge::set2(cv::Point two) {
	_two = two;
}


void Edge::setSlope() {
	double x;
	double y;
	double slope;
	x = (_two.x - _one.x);
	y = (_two.y - _one.y);
	if (x == 0) {
		slope = std::numeric_limits<double>::infinity();
	}
	else {
		slope = (y / x);
	}
	_slope = slope;
}

cv::Point Edge::get1() const {
	return _one;
}

cv::Point Edge::get2() const {
	return _two;
}

double Edge::getSlope() const {
	return _slope;
}

double Edge::getIntercept() const {
	return _intercept;
}

bool operator< (const Edge & lhs, const Edge & rhs) {
	return lhs.getSlope() < rhs.getSlope();
}

ostream& operator<< (ostream& os, const Edge& e) {
	os << "(" << e.get1() << ", " << e.get2() << ")" << endl << "\tSlope: "
		<< e.getSlope() << " Intercept: " << e.getIntercept();
	return os;
}

bool compareWithPrecision(double precision, double first, double second) {
	return (abs(second - first) <= precision);
}

bool Edge::operator== (const Edge& rhs) {
	cout << _precisionSlope << ":" << _precisionIntercept << " - " << abs(rhs._slope - _slope) << ":" << abs(rhs._intercept - _intercept) << endl;
	if (_slope == _inf && rhs._slope == _inf) return true;
	else return (compareWithPrecision(_precisionSlope, _slope, rhs._slope) 
		&& compareWithPrecision(_precisionIntercept, _intercept, rhs._intercept));
}
