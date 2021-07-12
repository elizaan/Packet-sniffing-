#include <pcap.h>
#include <stdlib.h>
#include "tcp.h"
//#include <netinet/tcp.h>
#include <stdio.h>
#include <arpa/inet.h>
/* This function will be invoked by pcap for each captured packet.
We can process each packet inside the function.
*/
struct ethheader {
    u_char ether_dhost[6];
    u_char ether_shost[6];
    u_short ether_type;

};
struct ipheader {
    unsigned char iph_ih1:4, iph_ver:4;
    unsigned char iph_tos;
    unsigned short int iph_len;
    unsigned short int iph_ident;
    unsigned short int iph_flag:3, iph_offset:13;
    unsigned char iph_tt1;
    unsigned char iph_protocol;
    unsigned short int iph_chksum;
    struct in_addr iph_sourceip;
    struct in_addr iph_destip;

};



void got_packet(u_char *args, const struct pcap_pkthdr *header,
const u_char *packet)
{
    struct ethheader *eth = (struct ethheader *)packet;
    if(ntohs(eth->ether_type) == 0x0800){
        struct ipheader *ip = (struct ipheader *)(packet + sizeof(struct ethheader));
        printf("from: %s\n",inet_ntoa(ip->iph_sourceip));
        printf("to: %s\n", inet_ntoa(ip->iph_destip));
        int ip_header_len = ip->iph_ih1 * 4;
        struct tcphdr *tcp = (struct tcphdr *)(packet + sizeof(struct ethheader) + ip_header_len);
        int tcp_header_len = tcp->doff*4;
        //u_char  *payload = (u_char *)(packet + sizeof(struct ethheader)+ ip_header_len + tcp_header_len);
        u_char  *payload = (u_char *)((int *)tcp + tcp_header_len); 
        
        if(ip->iph_protocol == IPPROTO_TCP){
            printf("Got a TCP protocol and the http payload is %s\n", payload);
        }
        else{
            printf("Other protocol found");
        }
        /*switch(ip->iph_protocol){
            case IPPROTO_TCP:
                printf("Got a TCP PROTOCOL and the payload is %s\n", payload);
                break;
            default:
                printf("protocol others\n");
                break;

        }*/
    }
}
int main()
{
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct bpf_program fp;
    char filter_exp[] = "tcp";
    bpf_u_int32 net;
// Step 1: Open live pcap session on NIC with name eth3
// Students needs to change "eth3" to the name
// found on their own machines (using ifconfig).
   handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);
// Step 2: Compile filter_exp into BPF psuedo-code
   pcap_compile(handle, &fp, filter_exp, 0, net);
   if (pcap_setfilter(handle, &fp) !=0) {
       pcap_perror(handle, "Error:");
       exit(EXIT_FAILURE);
   }
// Step 3: Capture packets
   pcap_loop(handle, -1, got_packet, NULL);
   pcap_close(handle); //Close the handle
   return 0;
}
