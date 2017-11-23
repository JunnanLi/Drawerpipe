#include "send_recv.h"


void get_packet(unsigned char *argument, const struct pcap_pkthdr *p_pkthdr, const unsigned char *packet_content){
	//printf("----------------------------------------------------\n");
    	//printf("%s\n", ctime((time_t *)&(p_pkthdr->ts.tv_sec))); 
	//printf("len: %d,caplen: %d\n", p_pkthdr->len, p_pkthdr->caplen);
	//printf("recv\n");
	//(((struct recvPktID*) argument)->id)++;
	//printf("id: %d\n",((struct recvPktID*) argument)->id);
}


void recv_packet(char *recv_msg, int num, char *bpf_recv_s){
	struct recvPktID recvPID;
	recvPID.id = 0;


    pcap_t * pcap_h = NULL;  
    char error_content[100] = "";
    const unsigned char *packet = NULL;
    char *p_net_interface_name = NULL;
    struct pcap_pkthdr p_pkthdr;
  
    p_net_interface_name = pcap_lookupdev(error_content);  
    if(NULL == p_net_interface_name)  
    {  
        perror("pcap_lookupdev");  
        exit(-1);  
    }     
    //p_net_interface_name ="ens33";
 
    pcap_h = pcap_open_live(p_net_interface_name,BUFSIZE,0,0,error_content);
    if(pcap_h == NULL){
        printf("error_pcap_handle\n");
        exit(0);
    }

	//BPF filter;
	struct bpf_program filter;
	pcap_compile(pcap_h, &filter, bpf_recv_s, 1, 0);
	//"dst port 8080", 1, 0);bpf_recv_s
	//and dst net 192.168.40.147
	//ip proto 253
	pcap_setfilter(pcap_h, &filter);

	
	if(pcap_loop(pcap_h,num,get_packet,(char *)&recvPID)<0){
		
		perror("pcap_next");
		exit(-1);
	}
  
    pcap_close(pcap_h);
	
} 



