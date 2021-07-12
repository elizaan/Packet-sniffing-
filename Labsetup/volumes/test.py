from scapy.all import *
def print_pkt(pkt):
    pkt.show()

pkt = sniff(iface='br-48eb679dae9b', filter='tcp', prn= print_pkt)
