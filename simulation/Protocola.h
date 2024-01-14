// ZigbeeProtocol.h

#ifndef __PROTOCOLA_H_
#define __PROTOCOLA_H_

#include <omnetpp.h>

using namespace omnetpp;

class Protocola : public cSimpleModule
{
  protected:
    std::set<int> allNodeIds;
    simtime_t firstMessageTime;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void processInitialSignal(cMessage *msg);
    void processAggregatedMessage(cMessage *msg);
    void sendInitialSignal();
    void aggregateAndSend();
};

#endif // __PROTOCOLA_H_
