// ZigbeeProtocol.h

#ifndef __PROTOCOLB_H_
#define __PROTOCOLB_H_

#include <omnetpp.h>

using namespace omnetpp;

class Protocolb : public cSimpleModule
{
  protected:
    std::set<int> allNodeIds;
    simtime_t firstMessageTime;
    simtime_t lastCommunicationTime;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void processInitialSignal(cMessage *msg);
    void processAggregatedMessage(cMessage *msg);
    void sendInitialSignal();
    void aggregateAndSend();
    void recordCommunicationTime();
};

#endif // __PROTOCOLB_H_
