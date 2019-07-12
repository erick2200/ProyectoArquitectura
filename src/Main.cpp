#include "DEFINITIONS.hpp"
#include <time.h>
#include "Game.hpp"
#include "Objects/DireccionesGiros.hpp"
#include "datos.h"

void inputAcelerometro()
{
    
    int sock, length, n;
    socklen_t fromlen;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buf[1024];
    
    sock=socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("Opening socket");
    length = sizeof(server);
    bzero(&server,length);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    std::cout<<INADDR_ANY<<std::endl;
    server.sin_port=htons(5500);
    if (bind(sock,(struct sockaddr *)&server,length)<0) 
        error("binding");
    fromlen = sizeof(struct sockaddr_in);

    while (DireccionAcelerometro::abierto) {
        n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
        if (n < 0) error("recvfrom");
        double* l=getParameters(buf);
        std::cout<<"\nParametros: \n";

        if( l[1] < -3.0f )
        {
            DireccionAcelerometro::derecha = false;
            DireccionAcelerometro::izquierda = true;
        }
        else if ( l[1] < 3.0f )
        {
            DireccionAcelerometro::derecha = false;
            DireccionAcelerometro::izquierda = false;
        }   
        else
        {
            DireccionAcelerometro::derecha = true;
            DireccionAcelerometro::izquierda = false;
        }

        for(int i=0;i<3;i++){
                std::cout<<l[i]<<" ";

        }
        std::cout<<std::endl;
        delete [] l;
    }


}

void juego()
{
    cp::Game(SCREEN_WIDTH,SCREEN_HEIGHT, "SFML POPL2 Chor Police Project");
}

int main()
{
    srand(time(NULL));

    std::thread first (inputAcelerometro) ;
    std::thread second (juego) ;

    first.join() ;
    second.join( ) ;
    
    return EXIT_SUCCESS;
}