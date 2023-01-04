default:
	rm ipc
	mkfifo ipc
	gcc sender.c -o sender.o
	gcc reciever.c -o reciever.o
	./sender.o & ./reciever.o