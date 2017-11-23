#include "send_recv.h"

int main(int argc, char *argv[])
{
	char send_payload[2000];
	char recv_payload[2000]="";
	FILE *fp;
	fp = fopen("send_content.txt","r");
	fgets(send_payload,1450,fp);

	char bpf_recv_s[100]="(dst net 192.168.40.146) && (ip proto 252)";//"dst net 192.168.40.147";
	char bpf_send_s[100]="192.168.40.145";

while(1){

	recv_packet(send_payload,1000, bpf_recv_s);
	printf("receiver---ok---\n");

	sleep(5);
	send_packet(send_payload,1, bpf_send_s);
	printf("finish one time receiver\n");
}
	
        return 0;
} 
