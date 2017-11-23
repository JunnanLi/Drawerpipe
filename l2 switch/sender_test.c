#include "send_recv.h"

void send_packet_pthread(char * pt_send){
	send_packet(((struct sender_info *)pt_send)->send_msg, ((struct sender_info *)pt_send)->num, ((struct sender_info *)pt_send)->bpf_s);
}

void recv_packet_pthread(char * pt_recv){
	recv_packet(((struct sender_info *)pt_recv)->send_msg, ((struct sender_info *)pt_recv)->num, ((struct sender_info *)pt_recv)->bpf_s);
}


int main(int argc, char *argv[])
{
	char send_payload[2000];
	char recv_payload[2000]="";
	FILE *fp;
	fp = fopen("send_content.txt","r");
	fgets(send_payload,1450,fp);

	char bpf_recv_s[100]="(dst net 192.168.40.145) && (ip proto 252)";//"dst net 192.168.40.147";
	char bpf_send_s[100]="192.168.40.147";


	struct timeval tv_start,tv_end;

int i=0;
for(i=0;i<10;i++){
		
	pthread_t pt_send,pt_recv;
	
	struct sender_info pkt_send;
	struct sender_info pkt_recv;
	pkt_send.num = 2000;
	pkt_send.bpf_s = bpf_send_s;
	pkt_send.send_msg = send_payload;
	pkt_recv.num = 1;
	pkt_recv.bpf_s = bpf_recv_s;
	pkt_recv.send_msg = send_payload;

	gettimeofday(&tv_start,NULL);

	pthread_create(&pt_send,NULL,(void *)send_packet_pthread,(char*) &pkt_send);
	pthread_create(&pt_recv,NULL,(void *)recv_packet_pthread,(char*) &pkt_recv);
	
/*
	send_packet(send_payload,2000, bpf_send_s);
	recv_packet(recv_payload,1, bpf_recv_s);
*/
	pthread_join(pt_recv,NULL);

	gettimeofday(&tv_end,NULL);

	pthread_join(pt_send,NULL);

	long time_s;
	time_s = (tv_end.tv_sec-tv_start.tv_sec-5)*1000000+(tv_end.tv_usec-tv_start.tv_usec);
	printf("spend time: %ld us\n",time_s);

	printf("sender---ok---\n");
}

        return 0;
} 
