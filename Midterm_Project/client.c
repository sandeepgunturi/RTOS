// Client side C/C++ program to demonstrate Socket programming
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 8888
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>

#define BUFSIZE 1024
int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello[1024];// = "Hello from client";
	char buffer[1024] = {0};
  //socket creation
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}
  //socket address and attach it to port of that address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
  //send data
	//printf("%d\n",sock);
/*while(1){
  scanf("%s",hello );
	send(sock , hello , strlen(hello) , 0 );
	memset(hello, 0, 255);
}*////////////////////////////////////////////////////////////////////////////////////
/* The sample type to use */
/* The sample type to use */
static const pa_sample_spec ss = {
		.format = PA_SAMPLE_S16LE,
		.rate = 44100,
		.channels = 2
};
pa_simple *s = NULL;
int ret = 1;
int error;

/* Create the recording stream */
if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
		fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
		goto finish;
}

for (;;) {
 uint8_t buf[BUFSIZE];

 /* Record some data ... */
 if (pa_simple_read(s, buf, sizeof(buf), &error) < 0) {
		 fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
		 goto finish;
 }

 /* And write it to STDOUT */
 /*if (loop_write(STDOUT_FILENO, buf, sizeof(buf)) != sizeof(buf)) {
		 fprintf(stderr, __FILE__": write() failed: %s\n", strerror(errno));
		 goto finish;
 }*/
 send(sock,buf,sizeof(buf),0);
}

ret = 0;

finish:

    if (s)
        pa_simple_free(s);

    return ret;
}
