 ////////////////////////////////////////////////////////////////////////////////
//    Fun??o para ler as informa??es de temperatura e umidade no sensor DHT11   //
 ////////////////////////////////////////////////////////////////////////////////

#define dht11_dir trisB.f1             //bit de configuração da direção I/O da porta de comunicação com o sensor DHT11
#define dht11dado portB.f1             //porta de comunicação com o sensor DHT11

//variáveis usadas na leitura do sensor de umidade e temperatura DHT11
unsigned short int temperatura1;
unsigned short int temperatura2;
unsigned short int umidade1;
unsigned short int umidade2;
unsigned short int checksum;

void Inicia_ambiente(){
	ANSELB.f1 = 0;                      //configura o pino de comunicação com o módulo DHT11 como digital
	dht11_dir = 0;                      //define porta como saída
	dht11dado = 1;                      //envia 1 na porta de saída
}

void dht11_read(){
   int count;
   INTCON.GIE = 0;                     //desliga chave geral das interrupções
   temperatura1=0;                     //zera variáveis antes da comunicação
   temperatura2=0;                     //zera variáveis antes da comunicação
   umidade1=0;                         //zera variáveis antes da comunicação
   umidade2=0;                         //zera variáveis antes da comunicação
   checksum=0;                         //zera variáveis antes da comunicação
//inicia comunicação requisitando o envio dos dados
   dht11_dir = 0;                      //define como saída
   dht11dado = 0;                      //envia 0
   delay_ms(20);                       //por 20 milisegundos
   dht11dado = 1;                      //envia 1
   delay_us(42);                       //por 42 microsegundos
   dht11_dir = 1;                      //define como entrada
   while(dht11dado);                   //aguarda inicio do recebimento dos dados
//recebe resposta
   while(!dht11dado);                  //recebe 0 (zero)
   while(dht11dado);                   //recebe 1 (um)
//inicia recepção dos dados
   while(!dht11dado);                  //recebe 0 (zero)
   for(count=1; count<=8; count++){    //recebe a 1ª parte do valor da umidade
      delay_us(40);
	  if(dht11dado){umidade1++ ; while(dht11dado);}
	  umidade1<<=1;
	  while(!dht11dado);
   }
   for(count=1; count<=8; count++){    //recebe a 2ª parte do valor da umidade
      delay_us(40);
	  if(dht11dado){umidade2++ ; while(dht11dado);}
	  umidade2<<=1;
	  while(!dht11dado);
   }
   for(count=1; count<=8; count++){    //recebe a 1ª parte do valor da temperatura
      delay_us(40);
	  if(dht11dado){temperatura1++ ; while(dht11dado);}
	  temperatura1<<=1;
	  while(!dht11dado);
   }
   for(count=1; count<=8; count++){    //recebe a 2ª parte do valor da temperatura
      delay_us(40);
	  if(dht11dado){temperatura2++ ; while(dht11dado);}
	  temperatura2<<=1;
	  while(!dht11dado);
   }
   for(count=1; count<=8; count++){    //recebe o checksum para confirmar se a mensagens foi recebida corretamente
      delay_us(40);
	  if(dht11dado){checksum++ ; while(dht11dado);}
	  checksum<<=1;
	  while(!dht11dado);
   }
   umidade1>>=1;
   temperatura1>>=1;
   checksum>>=1;
   if(checksum==temperatura1+temperatura2+umidade1+umidade2){ //se o checksum estiver correto

   }
   INTCON.GIE = 1;                     //religa chave geral das interrupções
}

