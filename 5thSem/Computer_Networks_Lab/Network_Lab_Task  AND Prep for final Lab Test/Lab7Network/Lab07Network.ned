package lab07network;

import inet.node.ethernet.Eth100M;
import inet.node.ethernet.EthernetSwitch;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;

network Lab07Network
{
    @display("bgb=1200,800");

    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=50,50");
            addStaticRoutes = false;
        }

        centralRouter: Router {
            @display("p=600,343;i=abstract/router");
        }

        engSwitch: EthernetSwitch {
            @display("p=300,200");
        }
        engHost1: StandardHost {
            @display("p=127,190");
        }
        engHost2: StandardHost {
            @display("p=236,100");
        }
        engHost3: StandardHost {
            @display("p=489,137");
        }

        mktSwitch: EthernetSwitch {
            @display("p=900,200");
        }
        mktHost1: StandardHost {
            @display("p=743,50");
        }
        mktHost2: StandardHost {
            @display("p=941,50");
        }
        mktHost3: StandardHost {
            @display("p=1098,127");
        }


        salesSwitch: EthernetSwitch {
            @display("p=200,500");
        }
        salesHost1: StandardHost {
            @display("p=80,535");
        }
        salesHost2: StandardHost {
            @display("p=248,622");
        }
        salesHost3: StandardHost {
            @display("p=362,537");
        }

        adminSwitch: EthernetSwitch {
            @display("p=600,600");
        }
        adminHost1: StandardHost {
            @display("p=442,711");
        }
        adminHost2: StandardHost {
            @display("p=743,722");
        }
        adminHost3: StandardHost {
            @display("p=756,590");
        }


        mgmtSwitch: EthernetSwitch {
            @display("p=899,397");
        }
        mgmtHost1: StandardHost {
            @display("p=986,561");
        }
        mgmtHost2: StandardHost {
            @display("p=1121,500");
        }
        mgmtHost3: StandardHost {
            @display("p=1089,343");
        }

    connections:

        engHost1.ethg++ <--> Eth100M <--> engSwitch.ethg++;
        engHost2.ethg++ <--> Eth100M <--> engSwitch.ethg++;
        engHost3.ethg++ <--> Eth100M <--> engSwitch.ethg++;
        engSwitch.ethg++ <--> Eth100M <--> centralRouter.ethg++;
        mktHost1.ethg++ <--> Eth100M <--> mktSwitch.ethg++;
        mktHost2.ethg++ <--> Eth100M <--> mktSwitch.ethg++;
        mktHost3.ethg++ <--> Eth100M <--> mktSwitch.ethg++;
        mktSwitch.ethg++ <--> Eth100M <--> centralRouter.ethg++;
        salesHost1.ethg++ <--> Eth100M <--> salesSwitch.ethg++;
        salesHost2.ethg++ <--> Eth100M <--> salesSwitch.ethg++;
        salesHost3.ethg++ <--> Eth100M <--> salesSwitch.ethg++;
        salesSwitch.ethg++ <--> Eth100M <--> centralRouter.ethg++;
        adminHost1.ethg++ <--> Eth100M <--> adminSwitch.ethg++;
        adminHost2.ethg++ <--> Eth100M <--> adminSwitch.ethg++;
        adminHost3.ethg++ <--> Eth100M <--> adminSwitch.ethg++;
        adminSwitch.ethg++ <--> Eth100M <--> centralRouter.ethg++;
        mgmtHost1.ethg++ <--> Eth100M <--> mgmtSwitch.ethg++;
        mgmtHost2.ethg++ <--> Eth100M <--> mgmtSwitch.ethg++;
        mgmtHost3.ethg++ <--> Eth100M <--> mgmtSwitch.ethg++;
        mgmtSwitch.ethg++ <--> Eth100M <--> centralRouter.ethg++;
}
