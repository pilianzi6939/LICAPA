// FixedNode.cc

#include "FixedNode.h"

Define_Module(FixedNode);

void FixedNode::initialize()
{
    sendInitialSignal();
}

void FixedNode::handleMessage(cMessage *msg)
{
    // Handle messages received by the fixed node module
    EV_INFO << "Fixed node received message: " << msg->getName() << endl;

    // Process other messages as needed

    delete msg;
}

void FixedNode::sendInitialSignal()
{
    // Fixed node sends an initial signal to a random dynamic node
    int randomDynamicNode = intuniform(0, getParentModule()->par("numDynamicNodes") - 1);
    cMessage *initialSignal = new cMessage("InitialSignal");
    sendDirect(initialSignal, gate("out", randomDynamicNode + 1));
}
