#include <iostream>
#include "TFile.h"


using namespace std ;

int main(int argc, char** argv){
	if (argc!=3){
	cerr << "You must add some inputs here!";
	return -1;
	}
	TFile *infile= new TFile(argv[1]);
	TFile *outfile= new TFile(argv[2],"RECREATE");
	cout << "Hello world!\n";
	return 0;
}

