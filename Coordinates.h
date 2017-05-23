#ifndef COORDINATES_H_
#define COORDINATES_H_

#include <vector> 
#include <deque>

using namespace std; 

struct Coordinate{
	double Xcoord; 
	double Ycoord; 
	double Distance;
	int Parent;
	bool Check; 
	Coordinate(double x, double y, double distance, int parent, bool check); 
};


/*
struct Distancesort{
	bool operator()(const Coordinate & a, const Coordinate & b); 
};*/

void StoreCoordinates(vector <Coordinate> & Coordinates);

bool ValidPoints(const Coordinate & Point1, const Coordinate & Point2);

double DistanceFormula(const Coordinate & Point1, const Coordinate & Point2); 

void PrimsAlgorithm(vector <Coordinate> & Coordinates); 

bool Valid(const Coordinate & Point1, const Coordinate & Point2); 

void FASTTSPmode(vector<Coordinate> & Coordinates); 

double MST(vector <Coordinate> & Coordinates, deque <int> & unvisited, vector <vector<double>> & distancematrix); 

void genPerms(deque<int> & unvisited, vector<int> & path, double & Upperbound, vector<Coordinate> & Coordinates, double & Pathlength, vector <int> & FinalPath, vector <vector<double>> & distancematrix); 

bool promising(deque<int> & unvisited, vector<int> & path, double & Upperbound, vector<Coordinate> & Coordinates, double & Pathlength,  vector <vector<double>> & distancematrix); 

double FASTTSP(vector <Coordinate> & Coordinates, vector <int> & Path, vector <vector<double>> & distancematrix); 

#endif 
