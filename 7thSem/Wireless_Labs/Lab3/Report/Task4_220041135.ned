
package lab3;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;

network WirelessMediumStudy
{
    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            parameters:
                @display("p=50,50;is=s");
        }

        configurator: Ipv4NetworkConfigurator {
            parameters:
                assignDisjunctSubnetAddresses = false;
                @display("p=50,150;is=s");
        }

        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=50,250;is=s");
        }

        // Four wireless hosts competing for the same channel
        host1: WirelessHost {
            parameters:
                @display("p=150,100");
        }

        host2: WirelessHost {
            parameters:
                @display("p=350,100");
        }

        host3: WirelessHost {
            parameters:
                @display("p=150,300");
        }

        host4: WirelessHost {
            parameters:
                @display("p=350,300");
        }

        host5: WirelessHost {
            parameters:
                @display("p=200,200");
        }
        host6: WirelessHost {
            parameters:
                @display("p=333,200");
        }

        accessPoint: AccessPoint {
            parameters:
                @display("p=250,200");
        }

        // No wired connections needed: all hosts connect wirelessly
}
