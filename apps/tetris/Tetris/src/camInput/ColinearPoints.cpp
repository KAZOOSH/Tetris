#include "ColinearPoints.h"

ColinearPoints::ColinearPoints()
{
}

void ColinearPoints::addPoint(cv::Point point) {
	points.push_back(point);
}

void ColinearPoints::clearPointList() {
	points.clear();
}

int ColinearPoints::getPointListSize() {
	return points.size();
}

void ColinearPoints::setSlopePrecision(double slope) {
	precisionSlope = slope;
}

void ColinearPoints::setInterceptPrecision(double intercept) {
	precisionIntercept = intercept;
}

vector<vector<cv::Point>> ColinearPoints::computeColinearPoints()
{
	vector<Edge> edgeList;
	vector <cv::Point> tempPoints;
	tempPoints = points;

    for(cv::Point& a : points) {
        for(cv::Point& b : tempPoints) {
			if (a != b) edgeList.push_back(Edge(a, b, precisionSlope, precisionIntercept));
		}
		tempPoints.erase(tempPoints.begin());
	}

	// Sort by slope
	// O(K log K), where K is N^2 elements
	sort(edgeList.begin(), edgeList.end());

	// Find collinear points
	//O(K), where K is N^2 elements
	vector<Edge> matchedEdges;
	vector<vector<cv::Point>> answerList;
	// Don't bother looking for groups of collinear points if there aren't
	// at least 3 edges. This check also makes sure there are enough
	// items in the list to avoid accessing an element that doesn't exist.
	if (edgeList.size() < 3) {
	/*	cout << endl
			<< "Not enough input points to find collinear points."
			<< endl;*/
		exit(1);
	}


	while (!edgeList.empty()) {
		if (edgeList[0] == edgeList[1]) {
			matchedEdges.push_back(edgeList[0]);
			edgeList.erase(edgeList.begin());
			if (edgeList.size() == 1) {
				matchedEdges.push_back(edgeList[0]);
				edgeList.erase(edgeList.begin());
				if (matchedEdges.size() >= 3) {
					answerList.push_back(edgesToPoints(matchedEdges));
				}
			}
		}
		else {
			matchedEdges.push_back(edgeList[0]);
			edgeList.erase(edgeList.begin());
			if (edgeList.size() == 1) {
				edgeList.erase(edgeList.begin());
			}
			if (matchedEdges.size() >= 3) {
				answerList.push_back(edgesToPoints(matchedEdges));
			}
			matchedEdges.clear();
		}
	}

	// Print the lines with collinear points
	//cout << endl;
	if (answerList.size() <= 0) {
		//cout << "No groups of 3 or more collinear points." << endl;
	}
	else {
		int n = 1;
        for(vector<cv::Point>& v : answerList) {
			/*cout << "Line " << n << " has "
				<< v.size() << " collinear points: ";*/
			int p = 0;
			// Print first two points directly beside text
			// This is safe because any v will have at least 4 points
			//cout << v[p] << ", ";
			p++;
			//cout << v[p] << ", ";
			p++;
			// Print the rest of the points, 3 per line, indented
			while (p < v.size()) {
				//if ((p + 1) % 3 == 0) cout << endl << "\t";
				//cout << v[p] << ", ";
				p++;
			}
			//cout << endl << endl;
			n++;
		}
	}
	return answerList;
}

vector<cv::Point> ColinearPoints::edgesToPoints(vector<Edge> edgeList)
{
	vector<cv::Point> answers;
    for(Edge& e : edgeList) {
		bool oneInList(false);
		bool twoInList(false);
		if (answers.empty()) {
			answers.push_back(e.get1());
		}
        for(cv::Point& p : answers) {
			if (p == e.get1()) {
				oneInList = true;
			}
			if (p == e.get2()) {
				twoInList = true;
			}
		}
		if (!oneInList) {
			answers.push_back(e.get1());
		}
		if (!twoInList) {
			answers.push_back(e.get2());
		}
	}
	return answers;
}

ColinearPoints::~ColinearPoints()
{
}
