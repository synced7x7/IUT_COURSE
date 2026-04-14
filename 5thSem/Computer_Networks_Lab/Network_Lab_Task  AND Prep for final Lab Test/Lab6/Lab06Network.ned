package lab06_network;

import inet.node.ethernet.Eth100M;
import inet.node.ethernet.EthernetSwitch;
import inet.node.inet.StandardHost;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;

network Lab06Network
{
    @display("bgb=916,555");
    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=50,50");
        }
        // Lab 1
        lab1_hostA: StandardHost {
            @display("p=100,100");
        }
        lab1_hostB: StandardHost {
            @display("p=100,200");
        }
        lab1_switch: EthernetSwitch {
            @display("p=200,150");
        }

        // Lab 2
        lab2_hostA: StandardHost {
            @display("p=300,100");
        }
        lab2_hostB: StandardHost {
            @display("p=381,54");
        }
        lab2_switch: EthernetSwitch {
            @display("p=336,161");
        }

        // Lab 3
        lab3_hostA: StandardHost {
            @display("p=500,100");
        }
        lab3_hostB: StandardHost {
            @display("p=584,53");
        }
        lab3_switch: EthernetSwitch {
            @display("p=489,161");
        }

        // Lab 4
        lab4_hostA: StandardHost {
            @display("p=700,100");
        }
        lab4_hostB: StandardHost {
            @display("p=866,99");
        }
        lab4_switch: EthernetSwitch {
            @display("p=737,216");
        }

        // Lab 5
        lab5_hostA: StandardHost {
            @display("p=599,358");
        }
        lab5_hostB: StandardHost {
            @display("p=610,437");
        }
        lab5_switch: EthernetSwitch {
            @display("p=500,400");
        }

        // Core switch to connect all labs
        coreSwitch: EthernetSwitch {
            @display("p=164,357");
        }

    connections:
        // Lab 1
        lab1_hostA.ethg++ <--> Eth100M <--> lab1_switch.ethg++;
        lab1_hostB.ethg++ <--> Eth100M <--> lab1_switch.ethg++;
        lab1_switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;

        // Lab 2
        lab2_hostA.ethg++ <--> Eth100M <--> lab2_switch.ethg++;
        lab2_hostB.ethg++ <--> Eth100M <--> lab2_switch.ethg++;
        lab2_switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;

        // Lab 3
        lab3_hostA.ethg++ <--> Eth100M <--> lab3_switch.ethg++;
        lab3_hostB.ethg++ <--> Eth100M <--> lab3_switch.ethg++;
        lab3_switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;

        // Lab 4
        lab4_hostA.ethg++ <--> Eth100M <--> lab4_switch.ethg++;
        lab4_hostB.ethg++ <--> Eth100M <--> lab4_switch.ethg++;
        lab4_switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;

        // Lab 5
        lab5_hostA.ethg++ <--> Eth100M <--> lab5_switch.ethg++;
        lab5_hostB.ethg++ <--> Eth100M <--> lab5_switch.ethg++;
        lab5_switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;
}
