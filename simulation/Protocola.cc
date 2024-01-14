// Protocola.cc

#include "Protocola.h"

Define_Module(Protocola);

void Protocola::initialize()
{
    if (getIndex() == 0) {
        // Fixed node initiates initial signal
        sendInitialSignal();
    }

    firstMessageTime = -1.0;  // Initialize to an invalid time
}

void Protocola::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "InitialSignal") == 0) {
        // Process the initial signal
        processInitialSignal(msg);
    } else if (strcmp(msg->getName(), "AggregatedMessage") == 0) {
        // Process the aggregated message
        processAggregatedMessage(msg);
    } else {
        // Handle other messages as needed
    }

    delete msg;
}

void Protocola::processInitialSignal(cMessage *msg)
{
    // Forward the initial signal to all other nodes
    for (int i = 0; i < getParentModule()->par("numDynamicNodes"); i++) {
        if (i != getIndex()) {
            sendDirect(msg->dup(), gate("out", i + 1));
        }
    }

    // Record the nodeId from the initial signal
    allNodeIds.insert(getIndex());
}

void Protocola::processAggregatedMessage(cMessage *msg)
{
    // Handle the aggregated message as needed
    // Extract information from the message and update node state
    EV_INFO << "Node " << getIndex() << " received aggregated message: " << msg->getStringValue() << endl;

    // Record the nodeId from the aggregated message
    allNodeIds.insert(getIndex());

    // Perform further processing, aggregation, or updating of node state
    // ...

    // Forward the aggregated message to all other nodes
    aggregateAndSend();

    // Check if all nodes have been recorded and this is the first time
    if (allNodeIds.size() == getParentModule()->par("numDynamicNodes") + 1 && firstMessageTime == -1.0) {
        // Record the simulation time when all nodes are present in the message
        firstMessageTime = simTime();
        EV_INFO << "First message with all nodes received at time: " << firstMessageTime << endl;
    }
}

void Protocola::sendInitialSignal()
{
    // Fixed node sends an initial signal to a random dynamic node
    int randomDynamicNode = intuniform(0, getParentModule()->par("numDynamicNodes") - 1);
    cMessage *initialSignal = new cMessage("InitialSignal");
    sendDirect(initialSignal, gate("out", randomDynamicNode + 1));
}

void Protocola::aggregateAndSend()
{
    // Aggregate node information and send the message
    cMessage *aggregatedMessage = new cMessage("AggregatedMessage");
    std::ostringstream oss;
    // Extract and aggregate relevant information from the node state
    for (int nodeId : allNodeIds) {
        oss << nodeId << " ";
    }
    aggregatedMessage->setStringValue(oss.str().c_str());

    // Reset the recorded nodeIds for the next round
    allNodeIds.clear();

    // Forward the aggregated message to all other nodes
    for (int i = 0; i < getParentModule()->par("numDynamicNodes"); i++) {
        if (i != getIndex()) {
            sendDirect(aggregatedMessage->dup(), gate("out", i + 1));
        }
    }
}
