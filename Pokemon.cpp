#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <getopt.h>
#include <deque>
#include "Coordinates.h"

using namespace std; 


int main(int argc, char **argv){

	ios_base::sync_with_stdio(false);

	struct option longOpts[] = {
		{ "mode", required_argument, NULL, 'm' },
		{ "help", no_argument, NULL, 'h' },
		{ NULL, 0, NULL, 0 }
	};

	string begin, end;  // The begin word and end word. 
	string output; // argument string for -o

	// Turn getopt error message on (true) or off (false)
	// opterr is declared in getopt.h, is on by default
	opterr = false;

	int mflag = 0; 
	string mode;

	int opt = 0, index = 0;
	// "ab:h" repeats the allowed flags
	// The : after b dontes the required argument for option b
	while ((opt = getopt_long(argc, argv, "m:h", longOpts, &index)) != -1) {
		switch (opt) {
		case 'm':
			++mflag; 
			mode = optarg; 
			break;
		case 'h':
			cout << "GOTTA CATCH EM ALL, POKEMON!" << endl;
			exit(0); 
		default:
			cerr << "Unknown Command " << endl;
		}
	}
	
	cout << setprecision(2);
	cout << fixed;

	//**************************ALGORITHM******************************
	vector <Coordinate> Coordinates;
	vector <Coordinate> Secondmain; 
	//vector <vector<double>> distancematrix; 

	//deque <int> unvisited; 
	//vector <int> path; 
	StoreCoordinates(Coordinates);

	//Filling in the distance matrix

	//for (int i = 0; i < static_cast<int>(Coordinates.size()); ++i){
		//for (int j = 0; j < static_cast<int>(Coordinates.size()); j++){
			//distancematrix[i][j] = DistanceFormula(Coordinates[i], Coordinates[j]); 
		//}
	//}


	//path.reserve(static_cast<int>(Coordinates.size())); //FIX THIS IF NEEDED TO
	//path.push_back(0);  // path = {0} There is only one element which is zero

	//for (int i = 0; i < static_cast<int>(Coordinates.size()) - 1; ++i){
		//unvisited.push_back(i + 1); 
	//}
	//cout << MST(Coordinates, unvisited) << endl; 
	

	if(mode == "MST"){ 
		PrimsAlgorithm(Coordinates); 
	}
	else if(mode == "FASTTSP"){
		FASTTSPmode(Coordinates); 
	}
	else{
		deque <int> unvisited; 
		for (int i = 0; i < static_cast<int>(Coordinates.size()) - 1; ++i){
			unvisited.push_back(i + 1); 
		}
		vector <int> path;
		path.reserve(static_cast<int>(Coordinates.size()));
		path.push_back(0);
		vector <vector<double>> distancematrix;
		distancematrix.resize(static_cast<int>(Coordinates.size()), vector<double>(static_cast<int>(Coordinates.size())));
		
		//Filling in the distance matrix
		for (int i = 0; i < static_cast<int>(Coordinates.size()); ++i){
			for (int j = 0; j < static_cast<int>(Coordinates.size()); j++){
				distancematrix[i][j] = DistanceFormula(Coordinates[i], Coordinates[j]); 
			}
		}
		 
	
	
		vector<int> FinalPath; 
		Secondmain.assign(Coordinates.begin(), Coordinates.end());
		//cout << FASTTSP(Secondmain) << endl;
		//cout << MST(Coordinates, unvisited) << endl; 
		double Pathlength(0); 
		double Upperbound = FASTTSP(Secondmain, FinalPath, distancematrix); 
		genPerms(unvisited, path, Upperbound, Coordinates, Pathlength, FinalPath, distancematrix); 
		cout << Upperbound << '\n'; 
		for (int i = 0; i < static_cast<int>(FinalPath.size()); ++i){
			cout << FinalPath[i] << " "; 
		}
	}
	return 0; 
}
