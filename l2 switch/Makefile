all:
	gcc -o t_sender sender_test.c sendPacket.c recvPacket.c -lnet -lpcap -lpthread
	gcc -o t_receiver receiver_test.c sendPacket.c recvPacket.c -lnet -lpcap -lpthread
	gcc -o t_switch switch_test.c switchPacket.c sendPacket.c recvPacket.c -lnet -lpcap -lpthread
clean:
	rm t_sender
	rm t_receiver
