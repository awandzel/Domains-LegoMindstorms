/*
 * SoarTouchSensor.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: aaron
 */

#include "TouchSensor.h"

#include "util/WMUtil.h"
#include "util/CommUtil.h"

#include "comm/CommStructs.h"
#include "SoarManager.h"

using namespace std;

TouchSensor::TouchSensor(uint port, SoarManager* manager)
	: manager(manager), port(port), pressed(false), prev(false), rootId(0) {

}

TouchSensor::~TouchSensor(){
	if(rootId){
		rootId->DestroyWME();
		rootId = 0;
	}
}

void TouchSensor::reinit(){
  rootId = 0;
}

void TouchSensor::updateInputLink(sml::Identifier* inputLink){
	if(!rootId){
		rootId = inputLink->CreateIdWME("sensor");
		rootId->CreateStringWME("type", "touch");
		rootId->CreateIntWME("port", port);
	}
	WMUtil::updateStringWME(rootId, "current-state", (pressed ? "pressed" : "released"));
	WMUtil::updateStringWME(rootId, "previous-state", (prev ? "pressed" : "released"));
	prev = pressed;
}

bool TouchSensor::readSoarCommand(sml::Identifier* commandId){
	cout << "UNEXPECTED TOUCH SENSOR COMMAND: Port " << port << endl;
	return false;
}

void TouchSensor::readStatus(IntBuffer& buffer, uint& offset){
	offset++;

	ushort str, blank;
	unpackShorts(buffer[offset], str, blank);

	pressed = (str > 2000);
}



