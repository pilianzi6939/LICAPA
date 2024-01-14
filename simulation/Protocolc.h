// Protocolc.h

#ifndef __PROTOCOLC_H_
#define __PROTOCOLC_H_

#include <omnetpp.h>

using namespace omnetpp;

class Protocolc : public cSimpleModule
{
  protected:
    std::set<int> allNodeIds;
    simtime_t firstMessageTime;
    simtime_t lastCommunicationTime;

    // New data structure to store communication records
    struct CommunicationRecord {
        int nodeId;
        simtime_t communicationTime;
    };
    std::vector<CommunicationRecord> communicationRecords;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void processInitialSignal(cMessage *msg);
    void processAggregatedMessage(cMessage *msg);
    void sendInitialSignal();
    void aggregateAndSend();
    void recordCommunicationTime();
    void updateCommunicationRecords(int nodeId, simtime_t communicationTime);
    void sendCommunicationRecords(int destNode);
};

#endif // __PROTOCOLC_H_
