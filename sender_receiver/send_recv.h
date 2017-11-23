#include <stdio.h> 
#include <pcap.h> 
#include <arpa/inet.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <libnet.h>
#include <pthread.h>

#define BUFSIZE 1514

#ifndef SEND_RECV_H__
#define SEND_RECV_H__


struct recvPktID{
	int id;
};

struct switchMSG{
	int id;
	char *sendMSG;
};

struct sender_info{
	int num;
	char *bpf_s;
}


void send_packet(char *send_msg, int num, char *bpf_send_s);
void recv_packet(char *recv_msg, int num, char *bpf_recv_s);
void switch_packet(char *recv_payload,char *send_payload,char *bpf_recv_s,char *bpf_send_s);

#endif
