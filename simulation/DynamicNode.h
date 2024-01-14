// DynamicNode.h

#ifndef __DYNAMICNODE_H_
#define __DYNAMICNODE_H_

#include <omnetpp.h>

using namespace omnetpp;

class DynamicNode : public cSimpleModule
{
  protected:
    int nodeId;
    std::set<int> receivedNodeIds;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void aggregateAndSend();
};

#endif // __DYNAMICNODE_H_
