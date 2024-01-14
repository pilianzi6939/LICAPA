// WirelessNetwork.ned

package WirelessNetwork;

import inet.node.inet.StandardHost;
import inet.node.wireless.Ieee80215ScalarRadioMedium;
import WirelessNetwork.FixedNode£»
import WirelessNetwork.DynamicNode£»

network WirelessNetwork
{
    parameters:
        int numDynamicNodes = 3000;
        @display("bgb=800,600");
    submodules:
        fixedNode: FixedNode {
            @display("p=100,100;i=device/wlan");
        }
        dynamicNode[numDynamicNodes]: DynamicNode {
            @display("p=,;");
        }
        wirelessChannel: Ieee80215ScalarRadioMedium {
            @display("p=500,300;i=red/xp");
        }
    connections:
}
