/*
 * SoarManager.h
 *
 *  Created on: Nov 20, 2013
 *      Author: aaron
 */

#ifndef SOARMANAGER_H_
#define SOARMANAGER_H_

#include "comm/CommStructs.h"

class SoarCommunicator;
class SoarDevice;
class Brick;
class Motor;

#include "sml_Client.h"

#include <ostream>

#include <string>
#include <map>
typedef std::map<uint, Motor*> OutputDevices;
typedef std::map<uint, SoarDevice*> InputDevices;

class SoarManager {
public:
	SoarManager(std::string agentSource, bool debugger);
	virtual ~SoarManager();
	
	void setCommunicator(SoarCommunicator* comm){
		this->comm = comm;
	}
	
	void readStatus(StatusList& statuses);
	
	void step();
	
	void reinit();
	
	bool isRunning(){
		return running;
	}
	
	void shutdown();
	
	// input phase callback
	static void runEventHandler(sml::smlRunEventId eventID, void* data, sml::Agent* agent, sml::smlPhase phase);
	
	static void agentEventHandler(sml::smlAgentEventId eventID, void* data, sml::Agent* agent);

	static void printEventHandler(sml::smlPrintEventId eventID, void* data, sml::Agent* agent, const char* message);

	void setPrintStream(ostream* stream){
		print_stream = stream;
	}
	
	// output link event callback
	static void outputEventHandler(void* data, sml::Agent* agent, const char* attName,  sml::WMElement* wme);
	
	void sendSoarMessage();
	void handleOutput(std::string attName, sml::WMElement* wme);
	
	void sendCommandToEv3(Ev3Command command, sml::Identifier* id);
	
private:
	void initAgent(const char* agentSource);
	void readSensorsStatus(IntBuffer& status);
	void readMotorsStatus(IntBuffer& status);
	void createSensor(uint port, uint type);
	void updateInputLink(sml::Identifier* inputLink);
	void addOutputListeners();
	
	bool readSoarCommand(sml::Identifier* id);
	bool handleCreateSensorCommand(sml::Identifier* id);
	bool handleDeleteSensorCommand(sml::Identifier* id);
	
	SoarCommunicator* comm;
	
	Brick* brick;
	Motor* motors[4];
	SoarDevice* inputs[4];
	
	// Soar agent variables
	sml::Kernel* kernel;
	sml::Agent* agent;
	int timeStep;
	
	bool running;
	
	int reinitCallbackId;
	int inputPhaseCallbackId;
	int printCallbackId;
	std::vector<int> outputCallbackIds;

	ostream* print_stream;
};

#endif /* SOARMANAGER_H_ */

