#include <cstdio>
#include <string>
#include <stdlib.h>
#include <signal.h>
#include <unordered_set>
#include "oneMillionNetfilter.h"

using namespace std;

unordered_set<string>* targets;

void usage(void){
	puts("syntax : 1m-block <site list file>");
	puts("sample : 1m-block top-1m.txt");
}

void sigintHandler(int sig){
	puts("Restoring Iptable rules");
	system("sudo netfilter-persistent reload");
	puts("Terminating Firewall\n");
	exit(0);
}

int main(int argc, char* argv[]){
	if (argc != 2) {
		usage();
		return -1;
	}
	char hostname[256];
	FILE* listFile = fopen(argv[1],"r");		//list file
	targets = new unordered_set<string>();

	while(fscanf(listFile,"%s",hostname)!=EOF){
		targets->insert(hostname);
	}

	struct sigaction sigintAction;			//signal handler for program termination
    
	sigemptyset(&sigintAction.sa_mask);
	sigintAction.sa_flags = 0;
	sigintAction.sa_handler = sigintHandler;
	sigaction(SIGINT,&sigintAction,0);
    
	system("./setRules.sh");		 		//setting up iptable rules to use NFQUEUE

	filterPackets();						//initiate packet filtering
}
