#include "send_recv.h"

void switch_sendPacket(char *send_msg){
	send_packet(send_msg, 1, "192.168.40.146");
}


void switch_getPacket(unsigned char *send_msg, const struct pcap_pkthdr *p_pkthdr, const unsigned char *packet_content){
	//printf("----------------------------------------------------\n");
    	//printf("%s\n", ctime((time_t *)&(p_pkthdr->ts.tv_sec))); 
	//printf("len: %d,caplen: %d\n", p_pkthdr->len, p_pkthdr->caplen);
	//printf("recv\n");
	/*pthread_t pt;
	int ret;
	ret = pthread_create(&pt,NULL,(void *)switch_sendPacket,((struct switchMSG *)send_msg)->sendMSG);
	pthread_join(pt,NULL);	
	*/	
	switch_sendPacket(((struct switchMSG *)send_msg)->sendMSG);	



	//((struct switchMSG *) send_msg)->id++;
	
	//printf("id:%d\n",((struct switchMSG *) send_msg)->id);
	
}


void switch_packet(char *recv_msg,char *send_msg, char *bpf_recv_s, char *bpf_send_s){


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

	struct switchMSG switchMsg;
	switchMsg.id =0;
	switchMsg.sendMSG = send_msg;
	
	if(pcap_loop(pcap_h,-1,switch_getPacket,(char *)&switchMsg)<0){
		
		perror("pcap_next");
		exit(-1);
	}
  
    pcap_close(pcap_h);
	
} 



