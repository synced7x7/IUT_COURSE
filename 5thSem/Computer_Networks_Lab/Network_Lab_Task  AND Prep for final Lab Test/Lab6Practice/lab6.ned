package lab6practice;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.EthernetSwitch;
import inet.node.inet.StandardHost;
import inet.node.ethernet.Eth100M;
import ned.IdealChannel;


network lab6Network
{
    @display("bgb=1171,573");
    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=96,76");
        }
        lab1HostA: StandardHost {
            @display("p=637,62");
        }
        lab1HostB: StandardHost {
            @display("p=803,84");
        }
        lab2HostA: StandardHost {
            @display("p=1042,185");
        }
        lab2HostB: StandardHost {
            @display("p=1049,282");
        }
        lab3HostA: StandardHost {
            @display("p=628,507");
        }
        lab3HostB: StandardHost {
            @display("p=488,515");
        }
        lab4HostB: StandardHost {
            @display("p=130,298");
        }
        lab4HostA: StandardHost {
            @display("p=145,394");
        }
        lab5HostB: StandardHost {
            @display("p=278,119");
        }
        lab5HostA: StandardHost {
            @display("p=457,62");
        }
        lab5Switch: EthernetSwitch {
            @display("p=400,165");
        }
        lab1Switch: EthernetSwitch {
            @display("p=659,152");
        }
        lab2Switch: EthernetSwitch {
            @display("p=862,281");
        }
        lab3Switch: EthernetSwitch {
            @display("p=527,433");
        }
        lab4Switch: EthernetSwitch {
            @display("p=266,350");
        }
        coreSwitch: EthernetSwitch {
            @display("p=581,291");
        }
    connections:
        lab5HostB.ethg++ <--> Eth100M <--> lab5Switch.ethg++;
        lab5HostA.ethg++ <--> Eth100M <--> lab5Switch.ethg++;
        lab1HostA.ethg++ <--> Eth100M <--> lab1Switch.ethg++;
        lab1HostB.ethg++ <--> Eth100M <--> lab1Switch.ethg++;
        lab2HostA.ethg++ <--> Eth100M <--> lab2Switch.ethg++;
        lab2Switch.ethg++ <--> Eth100M <--> lab2HostB.ethg++;
        lab3Switch.ethg++ <--> Eth100M <--> lab3HostB.ethg++;
        lab3Switch.ethg++ <--> Eth100M <--> lab3HostA.ethg++;
        lab4Switch.ethg++ <--> Eth100M <--> lab4HostA.ethg++;
        lab4HostB.ethg++ <--> Eth100M <--> lab4Switch.ethg++;
        lab4Switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;
        lab5Switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;
        lab1Switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;
        lab2Switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;
        lab3Switch.ethg++ <--> Eth100M <--> coreSwitch.ethg++;
}
