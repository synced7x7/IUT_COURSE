package lab1;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211RadioMedium;

import inet.node.ethernet.Eth100M;

network WiredAndWirelessHosts3
{
    submodules:

        configurator: Ipv4NetworkConfigurator {
            @display("p=480,50;is=s");
        }
        radioMedium: Ieee80211RadioMedium {
            @display("p=380,50;is=s");
        }

        wiredHost1: StandardHost {
            @display("p=100,400");
        }
        wiredHost2: StandardHost {
            @display("p=300,400");
        }
        wiredHost3: StandardHost {
            @display("p=412,140");
        }

        wirelessHost1: WirelessHost {
            @display("p=62,250");
        }

        accessPoint: AccessPoint {
            @display("p=200,300");
        }
        router: Router {
            @display("p=412,300");
        }

    connections:
        wiredHost1.ethg++ <--> Eth100M <--> router.ethg++;
        wiredHost2.ethg++ <--> Eth100M <--> router.ethg++;
        wiredHost3.ethg++ <--> Eth100M <--> router.ethg++;
        accessPoint.ethg++ <--> Eth100M <--> router.ethg++;
}
