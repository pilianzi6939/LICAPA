// DynamicNode.cc

#include "DynamicNode.h"

Define_Module(DynamicNode);

void DynamicNode::initialize()
{
    nodeId = getIndex();
}

void DynamicNode::handleMessage(cMessage *msg)
{
    // Handle messages received by the dynamic node module
    EV_INFO << "Dynamic node " << nodeId << " received message: " << msg->getName() << endl;

    // Process the initial signal
    if (strcmp(msg->getName(), "InitialSignal") == 0) {
        // Forward the initial signal to all other nodes
        for (int i = 0; i < getParentModule()->par("numDynamicNodes"); i++) {
            if (i != getIndex()) {
                sendDirect(msg->dup(), gate("out", i + 1));
            }
        }
    }

    // Process other messages as needed

    // Record the sender's nodeId
    receivedNodeIds.insert(msg->getSenderModule()->getIndex());

    // Process aggregation logic
    if (strcmp(msg->getName(), "InitialSignal") != 0) {
        // Perform aggregation when receiving other messages
        aggregateAndSend();
    }

    delete msg;
}

void DynamicNode::aggregateAndSend()
{
    // Aggregate received nodeIds and send the message
    cMessage *aggregatedMessage = new cMessage("AggregatedMessage");
    std::ostringstream oss;
    for (int receivedNodeId : receivedNodeIds) {
        oss << receivedNodeId << " ";
    }
    aggregatedMessage->setStringValue(oss.str().c_str());

    // Reset receivedNodeIds for the next round
    receivedNodeIds.clear();

    // Send the aggregated message to all other nodes
    for (int i = 0; i < getParentModule()->par("numDynamicNodes"); i++) {
        if (i != getIndex()) {
            sendDirect(aggregatedMessage->dup(), gate("out", i + 1));
        }
    }
}
