package lab7practice;

import inet.node.ethernet.EthernetSwitch;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.node.ethernet.Eth100M;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;

network lab7Network
{
    @display("bgb=1200,700");

    submodules:
		configurator: Ipv4NetworkConfigurator {
        	@display("p=80,50");
    	}

        // ===== ROUTERS =====
        routerA: Router {
            @display("p=450,320");
        }
        routerB: Router {
            @display("p=750,320");
        }

        // ===== ENGINEERING SUBNET (Router A) =====
        engSwitch: EthernetSwitch {
            @display("p=200,150");
        }
        engHostA: StandardHost {
            @display("p=80,80");
        }
        engHostB: StandardHost {
            @display("p=200,60");
        }
        engHostC: StandardHost {
            @display("p=320,80");
        }

        // ===== MARKETING SUBNET (Router A) =====
        marketingSwitch: EthernetSwitch {
            @display("p=200,480");
        }
        marketingHostA: StandardHost {
            @display("p=80,560");
        }
        marketingHostB: StandardHost {
            @display("p=200,600");
        }
        marketingHostC: StandardHost {
            @display("p=320,560");
        }

        // ===== SALES SUBNET (Router A) =====
        salesSwitch: EthernetSwitch {
            @display("p=572,537");
        }
        salesHostA: StandardHost {
            @display("p=486,619");
        }
        salesHostB: StandardHost {
            @display("p=617,658");
        }
        salesHostC: StandardHost {
            @display("p=691,629");
        }

        // ===== MANAGEMENT SUBNET (Router B) =====
        mgmtSwitch: EthernetSwitch {
            @display("p=1000,150");
        }
        mgmtHostA: StandardHost {
            @display("p=880,80");
        }
        mgmtHostB: StandardHost {
            @display("p=1000,60");
        }
        mgmtHostC: StandardHost {
            @display("p=1120,80");
        }

        // ===== ADMINISTRATION SUBNET (Router B) =====
        adminSwitch: EthernetSwitch {
            @display("p=1000,480");
        }
        adminHostA: StandardHost {
            @display("p=880,560");
        }
        adminHostB: StandardHost {
            @display("p=1000,600");
        }
        adminHostC: StandardHost {
            @display("p=1120,560");
        }

    connections:

        // ===== ROUTER A <--> ROUTER B (point-to-point link) =====


        // ===== ROUTER A <--> ENGINEERING SWITCH =====
        routerA.ethg++ <--> Eth100M <--> engSwitch.ethg++;
        engHostA.ethg++ <--> Eth100M <--> engSwitch.ethg++;
        engHostB.ethg++ <--> Eth100M <--> engSwitch.ethg++;
        engHostC.ethg++ <--> Eth100M <--> engSwitch.ethg++;

        // ===== ROUTER A <--> MARKETING SWITCH =====
        routerA.ethg++ <--> Eth100M <--> marketingSwitch.ethg++;
        marketingHostA.ethg++ <--> Eth100M <--> marketingSwitch.ethg++;
        marketingHostB.ethg++ <--> Eth100M <--> marketingSwitch.ethg++;
        marketingHostC.ethg++ <--> Eth100M <--> marketingSwitch.ethg++;

        // ===== ROUTER A <--> SALES SWITCH =====
        routerA.ethg++ <--> Eth100M <--> salesSwitch.ethg++;
        salesHostA.ethg++ <--> Eth100M <--> salesSwitch.ethg++;
        salesHostB.ethg++ <--> Eth100M <--> salesSwitch.ethg++;
        salesHostC.ethg++ <--> Eth100M <--> salesSwitch.ethg++;

        // ===== ROUTER B <--> MANAGEMENT SWITCH =====
        routerB.ethg++ <--> Eth100M <--> mgmtSwitch.ethg++;
        mgmtHostA.ethg++ <--> Eth100M <--> mgmtSwitch.ethg++;
        mgmtHostB.ethg++ <--> Eth100M <--> mgmtSwitch.ethg++;
        mgmtHostC.ethg++ <--> Eth100M <--> mgmtSwitch.ethg++;

        // ===== ROUTER B <--> ADMINISTRATION SWITCH =====
        routerB.ethg++ <--> Eth100M <--> adminSwitch.ethg++;
        adminHostA.ethg++ <--> Eth100M <--> adminSwitch.ethg++;
        adminHostB.ethg++ <--> Eth100M <--> adminSwitch.ethg++;
        adminHostC.ethg++ <--> Eth100M <--> adminSwitch.ethg++;

        routerA.ethg++ <--> Eth100M <--> routerB.ethg++;
}
