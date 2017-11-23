#include "send_recv.h"

int main(int argc, char *argv[])
{
	char send_payload[2000];
	char recv_payload[2000]="";
	FILE *fp;
	fp = fopen("send_content.txt","r");
	fgets(send_payload,1450,fp);

	char bpf_recv_s[100]="(dst net 192.168.40.147) && (ip proto 252)";
	char bpf_send_s[100]="192.168.40.146";

	

	while(1){
		switch_packet(recv_payload,send_payload,bpf_recv_s,bpf_send_s);

	}
	printf("switch---ok---\n");


        return 0;
} 
