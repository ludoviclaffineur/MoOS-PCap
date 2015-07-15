#ifndef __MoOS__LeapFingerProcessing__
#define __MoOS__LeapFingerProcessing__

#include "LeapProcessing.h"
#include "Grid.h"
#include "Setter.h"
namespace processing{
namespace leapmotion{
using namespace mapping;
class LeapFingerProcessing : public LeapProcessing{
public:
    LeapFingerProcessing(Grid* g, int finger);
    void process (const Leap::Controller& controller);
    void setActive(bool active);
private:

    void setSetter(int nbrSetter,...){};

    int mFinger;

    Setter<float>* mSetFingerX;
    Setter<float>* mSetFingerY;
    Setter<float>* mSetFingerZ;
};
}
}
#endif
