#include <linux/input.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "get_mac_ip.h"
#include "debug.h"
#define DELAY_2S   sleep(2)
#define FOR_2MIM     5
#define KEY_TIMES   5
/*
#define IP_LINK_KEY (gpio235)
#define RED_LED     (hps_led0)
#define GREEN_LED   (hps_led2)
*/

typedef enum{false=0,true=!false} bool ;

int udp_sock = -1;
struct sockaddr_in addrto;
struct sockaddr_in from;
int key_value=0;
char mac_tmp[30] = {0};
int interval_count=0;
bool is_c5 = true;



void rg_off(void)
{
	if(is_c5)
	{
		system("echo 0 > /sys/class/leds/hps_led0/brightness");
	    system("echo 0 > /sys/class/leds/hps_led2/brightness");
	}
	else
	{
    	system("echo 0 > /sys/class/gpio/gpio37/value");
    	system("echo 0 > /sys/class/gpio/gpio38/value");
	}
}

void rg_on(void)
{
	if(is_c5)
	{
	    system("echo 1 > /sys/class/leds/hps_led0/brightness");
	    system("echo 1 > /sys/class/leds/hps_led2/brightness");
	}
	else
	{
	    system("echo 1 > /sys/class/gpio/gpio37/value");
	    system("echo 1 > /sys/class/gpio/gpio38/value");

	}
}

/*
//Key GPIO number 46
bool getkey_gpio_46()
{
   unsigned int value;
   FILE *pRreco = NULL;
   if(!isExist("/sys/class/gpio/gpio46"))
   {
	unsigned int value;
	FILE *pRreco = NULL;
	if((pRreco = fopen("/sys/class/gpio/export", "w")) == NULL)
	{
	    printf("Open read gpio/export\n");
		return -1;
	}
   if(fwrite("46", strlen("46"), 1, pRreco) != 1)
    printf("File Write Error!\n");
	fclose(pRreco);
  }
	if((pRreco = fopen("/sys/class/gpio/gpio46/value","r")) == NULL)
	{
	    printf("Open read recovery button failure\n");
		return -1;
	}
	fscanf(pRreco,"%d",&value);
	fclose(pRreco);
	if(value)
		return true;
	else
		return false;
}
*/

//Key GPIO number 51
bool getkey_gpio()
{
    unsigned int value;
    FILE *pRreco = NULL;
    if(is_c5)
	{
		if(!isExist("/sys/class/gpio/gpio235"))
	    {
	        unsigned int value;
	        FILE *pRreco = NULL;
	        if((pRreco = fopen("/sys/class/gpio/export", "w")) == NULL)
	        {
	            printf("Open read gpio/export\n");
	            return -1;
	        }
   
	        if(fwrite("235", strlen("235"), 1, pRreco) != 1)
	        printf("File Write Error!\n");
	        fclose(pRreco);
	    }

	    if((pRreco = fopen("/sys/class/gpio/gpio235/value","r")) == NULL)
		{
		    printf("Open read recovery button failure\n");
			return -1;
		}
	}
	else
	{
	    if(!isExist("/sys/class/gpio/gpio51"))
	    {
	        unsigned int value;
	        FILE *pRreco = NULL;
	        if((pRreco = fopen("/sys/class/gpio/export", "w")) == NULL)
	        {
	            printf("Open read gpio/export\n");
	            return -1;
	        }
   
	        if(fwrite("51", strlen("51"), 1, pRreco) != 1)
	        printf("File Write Error!\n");
	        fclose(pRreco);
	    }
	
		if((pRreco = fopen("/sys/class/gpio/gpio51/value","r")) == NULL)
		{
		    printf("Open read recovery button failure\n");
			return -1;
		}
	}
	fscanf(pRreco,"%d",&value);
	fclose(pRreco);
	
    if(!value)
    {
        printf("%s: value = %d\n", __FUNCTION__, value);
		return true;
    }
	else
    {
        printf("%s: value = %d\n", __FUNCTION__, value);
		return false;
    }
}

//To determine whether a file exists
int isExist(char *filename)
{
    return (access(filename, 0) == 0);
}

//Green light quickly Blink a few times
int success_action()
{
    int i;
	
	if(is_c5)
	{
		for(i=0;i<3;i++)
	    {
	        system("echo 0 > /sys/class/leds/hps_led2/brightness");
	        sleep (1);
	        system("echo 1 > /sys/class/leds/hps_led2/brightness");
	        sleep (1);
	    }
	    system("echo 0 > /sys/class/leds/hps_led2/brightness");
	}
	else
	{
		for(i=0;i<3;i++)
	    {
	        system("echo 0 > /sys/class/gpio/gpio38/value");
	        sleep (1);
	        system("echo 1 > /sys/class/gpio/gpio38/value");
	        sleep (1);
	    }
	    system("echo 0 > /sys/class/gpio/gpio38/value");
	}
	
   
}

//The Red light Blinking fast,continue 6s Red Light
int failure_action()
{
    int i;
    if(is_c5)
	{
		for(i=0;i<3;i++)
    	{
        	system("echo 0 > /sys/class/leds/hps_led0/brightness");
        	sleep(1);
        	system("echo 1 > /sys/class/leds/hps_led0/brightness");
        	sleep(1);
    	}
    	system("echo 0 > /sys/class/leds/hps_led0/brightness");
	}
	else
	{
	    for(i=0;i<3;i++)
	    {
	        system("echo 0 > /sys/class/gpio/gpio37/value");
	        sleep(1);
	        system("echo 1 > /sys/class/gpio/gpio37/value");
	        sleep(1);
	    }
	    system("echo 0 > /sys/class/gpio/gpio37/value");
	}
}

int udp_init()
{
  if ((udp_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		printf("socket error");
		return -1;
	}

	const int opt = 1;
	//set socker broadcast type
	int nb = 0;
	nb = setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if(nb == -1)
	{
	 printf("set socket error...");
	 return -1;
	}
	bzero(&addrto, sizeof(struct sockaddr_in));
	addrto.sin_family=AF_INET;
	addrto.sin_addr.s_addr=htonl(INADDR_BROADCAST);
	addrto.sin_port=htons(14235);

    ///*
	bzero(&from, sizeof(struct sockaddr_in));
	from.sin_family = AF_INET;
	from.sin_addr.s_addr = htonl(INADDR_ANY);
	from.sin_port = htons(14236);
	if(bind(udp_sock,(struct sockaddr *)&(from), sizeof(struct sockaddr_in)) == -1)
	{
		printf("bind error...");
		return 0;
	}
   //*/
}

int send_ipmac()              //sleep 2s ,发送一次，接收函数需要无阻塞
{
  char sendmsg[100];
  char mac_data[30];
  char ipaddr[40];
  memset(mac_data,0,sizeof(char)*30);
  memset(ipaddr,0,sizeof(char)*40);
  memset(sendmsg,0,sizeof(char)*100);

  if(!get_ip("eth0",ipaddr))
  {
     DEBUG_printf("get IP error\n");
  }
  get_macforkey(mac_data,"eth0");
  strncpy(mac_tmp,mac_data,strlen(mac_data));
  strcpy(sendmsg,ipaddr);
  strcat(sendmsg,",");
  strcat(sendmsg,mac_data);

  int ret=sendto(udp_sock, sendmsg, strlen(sendmsg), 0, (struct sockaddr*)&addrto, sizeof(addrto));
  if(ret<0)
  {
   DEBUG_printf("send error....");
  }
  else
  {
   DEBUG_printf("send ipmac:\n%s\n",sendmsg);
  }
 //DELAY_2S;
  return 1;
 }

int send_ack(char *ack)
{
    int ret=sendto(udp_sock, ack, (size_t)10, 0, (struct sockaddr*)&addrto, sizeof(addrto));
    if(ret<0)
    {
        DEBUG_printf("send error....");
    }
    else
    {
        DEBUG_printf("send ack OK!\n ");
    }
}

//if retrun 1,then break the check_result
//if return 0,then Continue unfinished sent 2 minutes
int check_result()
{
    fd_set rev_fd;
    struct timeval timeout={2,0};
  
    FD_ZERO(&rev_fd);
    FD_SET(udp_sock,&rev_fd); //Add the descriptor
    
    char *r_mac=NULL;
    r_mac=(char*)calloc(30,sizeof(char));

    switch(select((udp_sock+1),&rev_fd,NULL,NULL,&timeout))
    {
        case -1:
            exit(-1);
            break;

        case 0:
            interval_count++;
            break;
   
        default:
            if(FD_ISSET(udp_sock,&rev_fd)) //read test
            {
                //从广播地址接受消息
                int nlen=sizeof(from);
                int ret=recvfrom(udp_sock, r_mac, (size_t)30, 0, (struct sockaddr*)&from,(socklen_t*)&nlen);
                if(ret<=0)
                {
                    DEBUG_printf("read error....");
                    interval_count++;
                }
                else
                {
                    DEBUG_printf("rev:\n%s\t", r_mac);
                    interval_count=0;
                    if(0==strncmp(r_mac,mac_tmp,strlen(mac_tmp))) // The match is successful
                    {
                        //匹配发送1  &&  绿灯快速几次，蜂鸣器响一声
                        DEBUG_printf("send_ack(\"1\");\n");
                        success_action();
                        send_ack("OK");
                    }
                    else
                    {                                            //Matching is not successful
                        //不匹配发送0 && 红灯快速闪烁，蜂鸣器响1s以上
                        DEBUG_printf("send_ack(\"0\");");
                        failure_action();
                        send_ack("FAILD");
                        free(r_mac);
                        return 0;  //not Matching ,Continue unfinished sent 2 minutes
                    }
                    free(r_mac);
                    return 1;  //OK OK
                }
            }
            break;
    }
    if(interval_count==FOR_2MIM)
    {
        interval_count=0;
        DEBUG_printf("Time Out\n");
        free(r_mac);
        return 1;  //time out
    }
  
    free(r_mac);
    return 0;   // no ACK to read
}

int key_test()             //Removing jitter
{
    int i=0;
    int key_times=0;
 
    for(i=0;i<KEY_TIMES;i++)
    {
        if((getkey_gpio() == true))  //button down
        {
            usleep(20*1000);
            key_times++;
        }
    }
 
    if(KEY_TIMES==key_times)
    {
        rg_on();
        return 1;
    }
    
    return 0;
}

bool isC5_Board()
{
    FILE *fd;
    char board_type[32];
    int isC5=0;

    memset(board_type,'\0',32);

    fd=fopen("/usr/bin/ctrl_bd","rb");
    if(fd)
    {
        fread(board_type,1,32,fd);
        fclose(fd);

        if(strstr(board_type,"XILINX"))
        {
            isC5=0;
        }
        else isC5=1;
    }
    else
    {
        isC5=1;
    }

    if(isC5)
        return true;
    else 
        return false;
}


int main(int argc, char **argv)
{
	int count = 0;
	int state = 0;
	struct timeval start,end;
	is_c5 = isC5_Board();
	DEBUG_printf("monitor-ipsig compile %s--%s\n", __DATE__,__TIME__);
	udp_init();

    while(1)
	{
        if(1==key_test())  //button down
        {
            while(1)
            {
                DEBUG_printf("Key Down!!!!!\n");
                send_ipmac();
                if(1==check_result())
                {
                    printf("check_result() == 1\n");
                    break;
                }
            }
        }
        else
        {
            usleep(400*1000);  //500ms
        }
	}
}







