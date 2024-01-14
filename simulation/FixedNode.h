// FixedNode.h

#ifndef __FIXEDNODE_H_
#define __FIXEDNODE_H_

#include <omnetpp.h>

using namespace omnetpp;

class FixedNode : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendInitialSignal();
};

#endif // __FIXEDNODE_H_
