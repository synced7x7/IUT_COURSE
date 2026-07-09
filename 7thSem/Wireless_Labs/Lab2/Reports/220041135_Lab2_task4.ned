

package lab1;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211RadioMedium;
import inet.visualizer.canvas.integrated.IntegratedCanvasVisualizer;

network WiredAndWirelessHosts
{
    submodules:
        visualizer: IntegratedCanvasVisualizer {
            @display("p=580,50;is=s");
        }
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


        wirelessHost1: WirelessHost {
            @display("p=62,219");
        }

        wirelessHost2: WirelessHost {
            @display("p=62,140");
        }


        accessPoint: AccessPoint {
            @display("p=200,300");
        }
        router: Router {
            @display("p=412,300");
        }

    connections:
        accessPoint.ethg++ <--> Eth100M <--> router.ethg++;
        router.ethg++ <--> Eth100M <--> wiredHost2.ethg++;
        router.ethg++ <--> Eth100M <--> wiredHost1.ethg++;
}

network WiredAndWirelessHostsExtra
{
    submodules:
        visualizer: IntegratedCanvasVisualizer {
            @display("p=580,50;is=s");
        }
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


        wirelessHost1: WirelessHost {
            @display("p=62,219");
        }

        wirelessHost2: WirelessHost {
            @display("p=62,140");
        }

        interferer: WirelessHost {
            parameters:
                @display("p=62,269");
        }


        accessPoint: AccessPoint {
            @display("p=200,300");
        }
        router: Router {
            @display("p=412,300");
        }



    connections:
        accessPoint.ethg++ <--> Eth100M <--> router.ethg++;
        router.ethg++ <--> Eth100M <--> wiredHost2.ethg++;
        router.ethg++ <--> Eth100M <--> wiredHost1.ethg++;
}

