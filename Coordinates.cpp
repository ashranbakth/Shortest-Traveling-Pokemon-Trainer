#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <deque>
#include "Coordinates.h"

using namespace std; 

Coordinate::Coordinate(double x, double y, double distance, int parent, bool check) :
Xcoord(x), Ycoord(y), Distance(distance), Parent(parent), Check(check) {}


void StoreCoordinates(vector <Coordinate> & Coordinates){

	//Read the first line of the file and reserve that many entries for the Coordinates vector
	string reservenum;
	int NumReserve(0); 
	getline(cin, reservenum);
	NumReserve = stoi(reservenum);
	Coordinates.reserve(NumReserve);
	//distancematrix.resize(static_cast<int>(NumReserve), vector<double>(static_cast<int>(NumReserve))); 
	double x(0), y(0); 
	//bool CoastalPokemon(false), WaterPokemon(false), LandPokemon(false); 

	//Read through the rest of the file (x,y) coordinates and push back each of them in the Coordinates vector 
	while (cin >> x >> y){
		double distance(numeric_limits<double>::max());
		Coordinates.push_back(Coordinate(x, y,distance, -1,false)); 

		/*if ( ((x == 0 && y < 0) || (x < 0 && y == 0) || (x == 0 && y == 0)) && !CoastalPokemon ){ //Checking if Coastal Pokemon exists
			CoastalPokemon = true; 
		}
		if ( (x < 0 && y < 0) && !WaterPokemon){ //Checking if Water Pokemon exists
			WaterPokemon = true; 
		}
		if ( ((x > 0 && y >= 0) || (x >= 0 && y > 0) || (x <= 0 && y > 0) || (x > 0 && y <= 0)) && !LandPokemon){ //Checking if Land Pokemon exists //FIXED THIS
			LandPokemon = true; 
		}*/
	}
	Coordinates[0].Distance = 0; //Set the first point distance to 0. 

	//If there are pokemon both on land and on sea but no coast pokemon locations
	/*if (!CoastalPokemon && WaterPokemon && LandPokemon){
		cerr << "Cannot construct MST" << endl; 
		exit(1); 
	}*/
}

bool ValidPoints(const Coordinate & Point1, const Coordinate & Point2){
	//If the points are the same then return false.
	if ((Point1.Xcoord == Point2.Xcoord) && (Point1.Ycoord == Point2.Ycoord)){  
		return false;
	}
	//If Point2 was already checked, return false
	if (Point2.Check){
		return false; 
	}
	//If Point1 is a land pokemon
	if ( (Point1.Xcoord > 0 && Point1.Ycoord >= 0) || (Point1.Xcoord >= 0 && Point1.Ycoord > 0) || //(+,+) quadrant  //FIX THIS
		 (Point1.Xcoord <= 0 && Point1.Ycoord > 0) || /*(Point1.Xcoord < 0 && Point1.Ycoord >= 0) ||*/        //(-,+) quadrant
		 (Point1.Xcoord > 0 && Point1.Ycoord <= 0) /*|| (Point1.Xcoord >= 0 && Point1.Ycoord < 0)*/ ){ //(+,-) quadrant
		//If Point1 is a land Pokemon and Point2 is a water Pokemon, return false. 
		if ((Point2.Xcoord < 0 && Point2.Ycoord < 0)){
			return false; 
		}
		return true; 
	}
	else if ((Point1.Xcoord < 0 && Point1.Ycoord < 0)){ //If point1 is a water pokemon
		//If point1 is a water pokemon and point2 is a land pokemon, return false. 
		if ((Point2.Xcoord > 0 && Point2.Ycoord >= 0) || (Point2.Xcoord >= 0 && Point2.Ycoord > 0) || //(+,+) quadrant
			(Point2.Xcoord <= 0 && Point2.Ycoord > 0) || /*(Point2.Xcoord < 0 && Point2.Ycoord >= 0) ||*/     //(-,+) quadrant
			(Point2.Xcoord > 0 && Point2.Ycoord <= 0) /*|| (Point2.Xcoord >= 0 && Point2.Ycoord < 0)*/ ){  //(+,-) quadrant
			return false; 
		}
		return true; 
	}
	
	else{ //If point1 is a coastal then return true since it can go anywhere.
		return true; 
	}
}

double DistanceFormula(const Coordinate & Point1, const Coordinate & Point2){
	double distance(0); 
	distance = sqrt(((Point1.Xcoord - Point2.Xcoord)*(Point1.Xcoord - Point2.Xcoord)) +
				((Point1.Ycoord - Point2.Ycoord)*(Point1.Ycoord - Point2.Ycoord)));
	return distance; 
}


void PrimsAlgorithm(vector <Coordinate> & Coordinates){

	int size(static_cast<int>(Coordinates.size()));
	int currentpoint(0); 
	Coordinates[currentpoint].Check = true; 
	double TotalWeight(0); 
	stringstream ss; 

	for (int i = 0; i < size - 1; ++i){ //Do it until the whole vector is TRUE

		for (int j = 0; j < size; ++j){//Calculate the distance between currentpoint and the rest one by one

			if ( ValidPoints(Coordinates[currentpoint], Coordinates[j]) ){
				double distance(DistanceFormula(Coordinates[currentpoint], Coordinates[j]));
				if (distance < Coordinates[j].Distance){
					Coordinates[j].Distance = distance; 
					Coordinates[j].Parent = currentpoint; 
				}

			}
		}

		double minimum(numeric_limits<double>::max());
		for (int h = 0; h < size; ++h){ //Find the minimum distance in the Coordinate vector (among the points that are still false)
			if ( !Coordinates[h].Check && Coordinates[h].Distance < minimum ){
				minimum = Coordinates[h].Distance; 
				currentpoint = h; 
			}
		}
		TotalWeight += minimum; 
		Coordinates[currentpoint].Check = true; 
		int parentpoint(Coordinates[currentpoint].Parent); 
		ss << min(currentpoint, parentpoint) << " " << max(currentpoint, parentpoint) << '\n';

	}
	cout << TotalWeight << '\n';
	cout << ss.str();
	return; 
}

bool Valid(const Coordinate & Point1, const Coordinate & Point2){
	if ((Point1.Xcoord == Point2.Xcoord) && (Point1.Ycoord == Point2.Ycoord)){
		return false;
	}
	//If Point2 was already checked, return false
	if (Point2.Check){
		return false;
	}
	return true; 
}

void FASTTSPmode(vector<Coordinate> & Coordinates){

	vector<int> Path; //Storing the whole path by storing the indexes

	int currentpoint(0); 
	int size(static_cast<int>(Coordinates.size())); 
	//double TotalWeight(0); //REMOVE
	double newminimum(numeric_limits<double>::max());
	int point(0); 

	Path.reserve(size + 1); 
	Coordinates[currentpoint].Check = true; 
	Path.push_back(currentpoint); 

	//********Nearest Neighbor Algorithm******************
	for (int i = 0; i < size - 1; ++i){

		for (int j = 0; j < size; ++j){

			if (Valid(Coordinates[currentpoint], Coordinates[j])){
				double distance(DistanceFormula(Coordinates[currentpoint], Coordinates[j]));
				Coordinates[j].Distance = distance; 
				if (distance < newminimum){
					newminimum = distance; 
					point = j; 
				}
			}
		}
		currentpoint = point; 
		Path.push_back(currentpoint); 
		Coordinates[currentpoint].Check = true; 
		//TotalWeight += newminimum; //REMOVE
		newminimum = numeric_limits<double>::max(); 
	}
	//cout << "BEFORE: " << TotalWeight << '\n';  //REMOVE
	
	
	double distance(DistanceFormula(Coordinates[0], Coordinates[currentpoint])); 
	Coordinates[0].Distance = distance; 
	//TotalWeight += distance; //REMOVE
	Path.push_back(0); 

	//cout << "AFTER: " << TotalWeight << '\n'; //REMOVE
	
	//for (int i = 0; i < static_cast<int>(Path.size()); ++i){ //REMOVE
		//cout << Path[i] << endl; 
	//}


	//**************2 OPT Algorithm*********************
	int Pathsize(static_cast<int>(Path.size())); 

	for (int i = 1; i < Pathsize - 1; i++){
		for (int j = i + 2; j < Pathsize; j++){
			double itoj(DistanceFormula(Coordinates[Path[i-1]], Coordinates[Path[j-1]]));
			double i2toj2(DistanceFormula(Coordinates[Path[i]], Coordinates[Path[j]]));
			double itoi2(DistanceFormula(Coordinates[Path[i-1]], Coordinates[Path[i]]));
			double jtoj2(DistanceFormula(Coordinates[Path[j-1]], Coordinates[Path[j]]));
			if ((itoj + i2toj2) < (itoi2 + jtoj2)){
				reverse(Path.begin() + i, Path.begin() + j);
			}
		}
	}

	//for (int i = 0; i < Path.size(); ++i){ //REMOVE
	//	cout << Path[i] << endl; 
	//}
	double weight(0); 
	int begin(0); 
	stringstream ss; 
	for (int dest(1); dest < Pathsize; ++dest){
		double distance(DistanceFormula(Coordinates[Path[begin]], Coordinates[Path[dest]])); 
		Coordinates[Path[dest]].Distance = distance; 
		weight += distance; 
		++begin; 
	}
	Path.pop_back(); 
	Pathsize = static_cast<int>(Path.size()); 

	for (int i = 0; i < Pathsize; ++i){
		if (i == Pathsize - 1){
			ss << Path[i]; 
		}
		else{
			ss << Path[i] << " ";
		}
	}
	cout << weight << '\n'; 
	cout << ss.str(); 
	return; 
}


double MST(vector <Coordinate> & Coordinates, deque <int> & unvisited, vector <vector<double>> & distancematrix){
	 
	int unvisitedsize(static_cast<int>(unvisited.size())); 
	int size(static_cast<int>(Coordinates.size()));
	int currentpoint(unvisited.front());
	Coordinates[currentpoint].Check = true;
	double TotalWeight(0);
	//stringstream ss;

	for (int i = 0; i < unvisitedsize - 1; ++i){ //Do it until the whole vector is TRUE

		for (int j = 0; j < unvisitedsize; ++j){//Calculate the distance between currentpoint and the rest one by one

			if (Valid(Coordinates[currentpoint], Coordinates[unvisited[j]])){
				//double distance = DistanceFormula(Coordinates[currentpoint], Coordinates[unvisited[j]]);
				double distance(distancematrix[currentpoint][unvisited[j]]); 
				if (distance < Coordinates[unvisited[j]].Distance){
					Coordinates[unvisited[j]].Distance = distance;
					//Coordinates[unvisited[j]].Parent = currentpoint;
				}

			}
		}

		double minimum(numeric_limits<double>::max());
		for (int h = 1; h < size; ++h){ //Find the minimum distance in the Coordinate vector (among the points that are still false)
			if (!Coordinates[h].Check && Coordinates[h].Distance < minimum){
				minimum = Coordinates[h].Distance;
				currentpoint = h;
			}
		}

		TotalWeight += minimum;
		Coordinates[currentpoint].Check = true;
		//int parentpoint = Coordinates[currentpoint].Parent;
		//ss << min(currentpoint, parentpoint) << " " << max(currentpoint, parentpoint) << '\n';

	}
	return TotalWeight; 
}

void genPerms(deque<int> & unvisited, vector<int> & path, double & Upperbound, vector<Coordinate> & Coordinates, double & Pathlength, vector <int> & FinalPath, vector <vector<double>> & distancematrix){
	if (unvisited.empty()){
		if (Pathlength < Upperbound){
			//double EndtoBegin(DistanceFormula(Coordinates[path.back()], Coordinates[0])); 
			double EndtoBegin(distancematrix[path.back()][0]); 
			double oldlength(Pathlength); 
			Pathlength += EndtoBegin;
			//path.push_back(0); 
			if (Pathlength < Upperbound){
				FinalPath.assign(path.begin(), path.end()); 
				Upperbound = Pathlength; 
			}
			Pathlength = oldlength; 
		}
		return; 
	}
	if (!promising(unvisited, path, Upperbound,Coordinates, Pathlength, distancematrix)){
		return; 
	}
	for (unsigned k = 0; k != unvisited.size(); k++){
		double oldlength(Pathlength); 
		//Pathlength += DistanceFormula(Coordinates[unvisited.front()], Coordinates[path.back()]); 
		Pathlength += distancematrix[unvisited.front()][path.back()]; 
		path.push_back(unvisited.front()); 
		unvisited.pop_front(); 
		genPerms(unvisited, path, Upperbound, Coordinates, Pathlength, FinalPath, distancematrix);
		unvisited.push_back(path.back()); 
		path.pop_back(); 
		Pathlength = oldlength; 
		//Pathlength -= DistanceFormula(Coordinates[unvisited.back()], Coordinates[path.back()]); 
	}
}

bool promising(deque<int> & unvisited, vector<int> & path, double & Upperbound, vector<Coordinate> & Coordinates, double & Pathlength,  vector <vector<double>> & distancematrix){

	double MSTUnvisited(MST(Coordinates,unvisited,distancematrix)); 
	
	for (int i = 0; i < static_cast<int>(Coordinates.size()); ++i){
		Coordinates[i].Check = false; 
		Coordinates[i].Distance = numeric_limits<double>::max(); 
	}
	
	int front(path.front()); 
	int back(path.back()); 
	
	double FrontDistance(numeric_limits<double>::max()); 
	double BackDistance(numeric_limits<double>::max()); 

	for (int i = 0; i < static_cast<int>(Coordinates.size()); ++i){
		if (Valid(Coordinates[front], Coordinates[i])){
			//double distance(DistanceFormula(Coordinates[front], Coordinates[i]));
			double distance(distancematrix[front][i]);  
			if (distance < FrontDistance){
				FrontDistance = distance; 
			}
		}
		if (Valid(Coordinates[back], Coordinates[i])){
			//double distance(DistanceFormula(Coordinates[back], Coordinates[i])); 
			double distance(distancematrix[back][i]); 
			if (distance < BackDistance){
				BackDistance = distance; 
			}
		}
	}

	double LowerBound(MSTUnvisited + FrontDistance + BackDistance + Pathlength); 

	return LowerBound < Upperbound; 
}

double FASTTSP(vector <Coordinate> & Coordinates, vector <int> & Path, vector <vector<double>> & distancematrix){
	
	int currentpoint(0);
	int size(static_cast<int>(Coordinates.size()));
	//double TotalWeight(0); 
	double newminimum(numeric_limits<double>::max());
	int point(0);

	Path.reserve(size + 1);
	Coordinates[currentpoint].Check = true;
	Path.push_back(currentpoint);

	//********Nearest Neighbor Algorithm******************
	for (int i = 0; i < size - 1; ++i){

		for (int j = 0; j < size; ++j){

			if (Valid(Coordinates[currentpoint], Coordinates[j])){
				//double distance = DistanceFormula(Coordinates[currentpoint], Coordinates[j]);
				double distance(distancematrix[currentpoint][j]); 
				Coordinates[j].Distance = distance;
				if (distance < newminimum){
					newminimum = distance;
					point = j;
				}
			}
		}
		currentpoint = point;
		Path.push_back(currentpoint);
		Coordinates[currentpoint].Check = true;
		//TotalWeight += newminimum; 
		newminimum = numeric_limits<double>::max();
	}
	//cout << "BEFORE: " << TotalWeight << '\n';  //REMOVE
	//double distance(DistanceFormula(Coordinates[0], Coordinates[currentpoint]));
	double distance(distancematrix[0][currentpoint]); 
	Coordinates[0].Distance = distance;
	//TotalWeight += distance;
	Path.push_back(0);


	//**************2OPT Algorithm*********************
	int Pathsize(static_cast<int>(Path.size()));

	for (int i = 1; i < Pathsize - 1; i++){
		for (int j = i + 2; j < Pathsize; j++){
			/*double itoj(DistanceFormula(Coordinates[Path[i - 1]], Coordinates[Path[j - 1]]));
			double i2toj2(DistanceFormula(Coordinates[Path[i]], Coordinates[Path[j]]));
			double itoi2(DistanceFormula(Coordinates[Path[i - 1]], Coordinates[Path[i]]));
			double jtoj2(DistanceFormula(Coordinates[Path[j - 1]], Coordinates[Path[j]]));*/
			double itoj(distancematrix[Path[i - 1]][Path[j - 1]]); 
			double i2toj2(distancematrix[Path[i]][Path[j]]); 
			double itoi2(distancematrix[Path[i - 1]][Path[i]]); 
			double jtoj2(distancematrix[Path[j - 1]][Path[j]]); 
			if ((itoj + i2toj2) < (itoi2 + jtoj2)){
				reverse(Path.begin() + i, Path.begin() + j);
			}
		}
	}

	
	double weight(0);
	int begin(0);
	//stringstream ss;
	for (int dest(1); dest < Pathsize; ++dest){
		//double distance(DistanceFormula(Coordinates[Path[begin]], Coordinates[Path[dest]]));
		double distance(distancematrix[Path[begin]][Path[dest]]); 
		Coordinates[Path[dest]].Distance = distance;
		weight += distance;
		++begin;
	}
	Path.pop_back(); 
	return weight; 
}
