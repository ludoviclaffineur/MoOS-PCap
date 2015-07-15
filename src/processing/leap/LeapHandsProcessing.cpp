//
//  LeapHandsProcessing.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 4/11/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "LeapHandsProcessing.h"
#include <sstream>

using namespace Leap;
using namespace processing::leapmotion;
const std::string leftRight[] = {"Left ", "Right "};
const std::string fingerNames[] = {"Thumb ", "Index ", "Middle ", "Ring ", "Pinky "};
const std::string boneNames[] = {"Metacarpal ", "Proximal ", "Middle ", "Distal "};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

//enum BoneNameComplete { LEFT_THUMB_METACARPAL, GREEN, BLUE};
const std::string axis[] = {"X", "Y", "Z"};

enum FINGER_LIST{
	THUMB=0,
	INDEX,
	MIDDLE,
	RING,
	PINKY
};

enum Bones{
    LEFT_THUMB_METACARPAL,
    LEFT_THUMB_PROXIMITAL,
    LEFT_THUMB_MIDDLE,
    LEFT_THUMB_DISTAL,

    LEFT_INDEX_METACARPAL,
    LEFT_INDEX_PROXIMITAL,
    LEFT_INDEX_MIDDLE,
    LEFT_INDEX_DISTAL,

    LEFT_MIDDLE_METACARPAL,
    LEFT_MIDDLE_PROXIMITAL,
    LEFT_MIDDLE_MIDDLE,
    LEFT_MIDDLE_DISTAL,

    LEFT_RING_METACARPAL,
    LEFT_RING_PROXIMITAL,
    LEFT_RING_MIDDLE,
    LEFT_RING_DISTAL,

    LEFT_PINKY_METACARPAL,
    LEFT_PINKY_PROXIMITAL,
    LEFT_PINKY_MIDDLE,
    LEFT_PINKY_DISTAL,

    RIGHT_THUMB_METACARPAL,
    RIGHT_THUMB_PROXIMITAL,
    RIGHT_THUMB_MIDDLE,
    RIGHT_THUMB_DISTAL,

    RIGHT_INDEX_METACARPAL,
    RIGHT_INDEX_PROXIMITAL,
    RIGHT_INDEX_MIDDLE,
    RIGHT_INDEX_DISTAL,

    RIGHT_MIDDLE_METACARPAL,
    RIGHT_MIDDLE_PROXIMITAL,
    RIGHT_MIDDLE_MIDDLE,
    RIGHT_MIDDLE_DISTAL,

    RIGHT_RING_METACARPAL,
    RIGHT_RING_PROXIMITAL,
    RIGHT_RING_MIDDLE,
    RIGHT_RING_DISTAL,

    RIGHT_PINKY_METACARPAL,
    RIGHT_PINKY_PROXIMITAL,
    RIGHT_PINKY_MIDDLE,
    RIGHT_PINKY_DISTAL,

};

LeapHandsProcessing::LeapHandsProcessing(Grid* g){
    mActive = true;
    for (int h  = 0; h<2; h++) {
        for(int i = 0 ; i<5;i++){
            for (int j =0; j<4;j++){
                for (int k=0; k<3; k++) {
                    std::stringstream ss;
                    ss<<leftRight[h]<< fingerNames[i] << boneNames[j]<< axis[k];
                    g->addInput(ss.str().c_str(), -300, 300, -1, 0, Converter::LINEAR);
                }
            }
        }
    }
    //g->addInput("SourceLatitude", 90, -90, -1, 0, Converter::LINEAR);
    //g->addInput("SourceLongitude", -180, 180, -1, 0, Converter::LINEAR);
   // g->addInput("DestLatitude", 90, -90, -1, 0, Converter::LINEAR);
   // g->addInput("DestLongitude", -180, 180, -1, 0, Converter::LINEAR);

    //mSetDestinationLattitude = &Input::setValue;
    //mSourceLat = g->getInputWithName("SourceLatitude");
    //mSourceLong = g->getInputWithName("SourceLongitude");
    //mDestLat= g->getInputWithName("DestLatitude");
    //mDestLong = g->getInputWithName("DestLongitude");
}



void LeapHandsProcessing::process(const Leap::Controller &controller){
    const Frame frame = controller.frame();
    HandList hands = frame.hands();

    for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
        // Get the first hand
        const Hand hand = *hl;
        std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
        std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
        << ", palm position: " << hand.palmPosition() << std::endl;
        // Get the hand's normal vector and direction
        const Vector normal = hand.palmNormal();
        const Vector direction = hand.direction();

        // Calculate the hand's pitch, roll, and yaw angles
        std::cout << std::string(2, ' ') <<  "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
        << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
        << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;

        // Get the Arm bone
        Arm arm = hand.arm();
        std::cout << std::string(2, ' ') <<  "Arm direction: " << arm.direction()
        << " wrist position: " << arm.wristPosition()
        << " elbow position: " << arm.elbowPosition() << std::endl;

        // Get fingers
        const FingerList fingers = hand.fingers();
        for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
            const Finger finger = *fl;
            std::cout << std::string(4, ' ') <<  fingerNames[finger.type()]
            << " finger, id: " << finger.id()
            << ", length: " << finger.length()
            << "mm, width: " << finger.width() << std::endl;

            // Get finger bones
            for (int b = 0; b < 4; ++b) {
                Bone::Type boneType = static_cast<Bone::Type>(b);
                Bone bone = finger.bone(boneType);
                std::cout << std::string(6, ' ') <<  boneNames[boneType]
                << " bone, start: " << bone.prevJoint()
                << ", end: " << bone.nextJoint()
                << ", direction: " << bone.direction() << std::endl;
            }
        }
    }

}

void LeapHandsProcessing::setSetter(int nbrSetter, ...){

}

void LeapHandsProcessing::setActive(bool active){
    mActive = active;
}