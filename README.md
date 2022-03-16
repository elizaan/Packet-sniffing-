# Packet Sniffing and Spoofing Lab

## For Ubuntu 20.04 

This lab requires two machines. We are going to use one VM, and then
run a container inside the VM for the second machine. 
The lab description is updated to reflect the change on the setup. 

- There is no change caused by the OS. The change described below
is mainly caused by the use of containers.

- When sniffing packets, we need to specify the interface name. 
In 16.04, the default interface is used, so we didn't have to specify
the interface. For the container setup, we have to specify it.


## Container Setup

- A new section on the container setup is added. Most of the content
are placed in common files, which are shared by several labs.  

- The lab uses the standard OneLAN setup, which has 3 containers.
A customization is made in the Compose file so only one container
is used.

## Commands
- In labsetup folder, 
```
   docker-compose build
   docker-compose up
   docker ps (to get the IDs of the containers)
   docker exec -it (first two digits of the attacker id) /bin/bash (it will open a terminal in the corresponding container)
   docker exec -it (first two digits of the victims id) /bin/bash
```

- To install gcc and pcap on the attacker container:
   1. gcc: 
     apt update
     apt install build-essential
     apt-get install manpages-dev

   2. pcap:
     apt-get install libpcap-dev
 
- To send a HTTP post reuest from the victim's container
     1. curl -d "user = eliza & pass=abcd" -X POST www.google.com -so /dev/null

 
