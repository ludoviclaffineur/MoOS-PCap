#include "LeapFingerProcessing.h"


#include <sstream>
using namespace Leap;
using namespace processing::leapmotion;

    const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
LeapFingerProcessing::LeapFingerProcessing(Grid* g, int finger){
    mFinger = finger;

    std::stringstream ss1;
    ss1 << fingerNames[mFinger] << "_x";
    std::stringstream ss2;
    ss2 << fingerNames[mFinger] << "_y";
    std::stringstream ss3;
    ss3 << fingerNames[mFinger] << "_z";


    g->addInput(ss1.str().c_str(), -300, 300, -1, 0, Converter::LINEAR);
    g->addInput(ss2.str().c_str(), -300, 300, -1, 0, Converter::LINEAR);
    g->addInput(ss3.str().c_str(), -300, 300, -1, 0, Converter::LINEAR);
    mSetFingerX = g->getInputWithName(ss1.str().c_str());
    mSetFingerY = g->getInputWithName(ss2.str().c_str());
    mSetFingerZ = g->getInputWithName(ss3.str().c_str());
}

void LeapFingerProcessing::process (const Leap::Controller& controller){
	const Frame frame = controller.frame();
	HandList hands = frame.hands();

	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
		// Get the first hand
		const Hand hand = *hl;
		std::string handType = hand.isLeft() ? "Left hand" : "Right hand";


		// Get the hand's normal vector and direction
		const Vector normal = hand.palmNormal();
		const Vector direction = hand.direction();
		HandList hands = frame.hands();

		// Get fingers
		const FingerList fingers = hand.fingers();
		for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
			const Finger finger = *fl;
            int valeur=finger.type();
            if(valeur == mFinger){
                Vector fingerPosition= finger.tipPosition();
                //std::cout << "C'est le pouce!" << std::endl;
                mSetFingerX->setValue(fingerPosition.x);
                mSetFingerY->setValue(fingerPosition.y);
                mSetFingerZ->setValue(fingerPosition.z);
            }
        }
    }

}
void LeapFingerProcessing::setActive(bool active){

}