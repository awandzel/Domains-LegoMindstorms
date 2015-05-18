#include <iostream>
#include <string>

#include <unistd.h>

#include "comm/SoarCommunication.h"
#include "soar/SoarManager.h"

using namespace std;


int main(int argc, char** argv){
	if(argc < 3){
		cout << "Param 1: IP addrss of Robot" << endl;
		cout << "Param 2: filepath for agent source file" << endl;
		return 0;
	}

	RemoteSoarCommunicator comm(argv[1]);
	
	string filepath = argv[2];
	string parentPath = filepath.substr(0, filepath.find_last_of("/\\"));
	string filename = filepath.substr(filepath.find_last_of("/\\")+1, -1);
	
	if (parentPath.size() == 0)
	{
		parentPath = filepath.substr(0, filepath.find_last_of("/"));
		filename = filepath.substr(filepath.find_last_of("/")+1, -1);
	}
	
	chdir(parentPath.c_str());
	
	SoarManager manager(&comm, filename.c_str(), true);
	comm.assignManager(&manager);
	comm.start();

	while(true){
//		manager.step();
		sleep(1);

	}

	return 0;
}