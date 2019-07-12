#ifndef DATOS_H
#define DATOS_H

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

double* getParameters(char* data){
	char **aux=new char*[10];
	for(int i=0;i<10;i++){
		aux[i]=new char [10];
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			aux[i][j]='\0';
		}
	}
	int palab=0;
	int i=0;
	int j=0;
	while(data[i]!='\0'){
		if(data[i]==','){
			palab++;
			i++;
			j=0;
		}
		if(data[i]!=' '){
			aux[palab][j]=data[i];
			j++;
		}
		i++;
	}

	double* param=new double [3];
	for(int i=2;i<5;i++){
		param[i-2]=atof(aux[i]);
	}
	for(int i=0;i<10;i++){
		delete [] aux[i];
	}
	delete [] aux;
	return param;
}

#endif