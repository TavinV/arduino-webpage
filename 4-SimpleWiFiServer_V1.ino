//https://lobodarobotica.com/blog/web-server-com-esp32-conexao-wifi/

#include <WiFi.h> // inclusão da biblioteca WiFi

const char* ssid     = "Igor teixeira.";// SSID é o nome da rede a ser conectada
const char* password = "12344321";      // senha da rede
String html = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin> <link href=\"https://fonts.googleapis.com/css2?family=Poppins:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap\" rel=\"stylesheet\"> <script src=\"https://unpkg.com/boxicons@2.1.4/dist/boxicons.js\"></script> <title>Led Switch</title> </head> <body> <div class=\"page-contents\"> <div class=\"esp32-controller\"> <div class=\"title-container\"> <ion-icon class=\"icon\" size=\"medium\" name=\"settings-sharp\"></ion-icon> Controles do LED </div> <div class=\"buttons\"> <a class=\"link\" href=\"/H\\\"> <button class=\"button\"> Ligar o Led <ion-icon id=\"icon2\" size=\"medium\" name=\"sunny-sharp\"></ion-icon> </button> </a> <a class=\"link\" href=\"/L\\\"> <button class=\"button\"> Desligar o Led <ion-icon id=\"icon2\" name=\"sunny-outline\"></ion-icon> </button> </a> </div> <div class=\"esp-info\"> <span class=\"text-icon\"> <ion-icon name=\"hardware-chip-outline\"></ion-icon> MAC Address : A8:42:E3:8F:BO:B4 </span> <span class=\"text-icon\"> <ion-icon name=\"wifi-outline\"></ion-icon> IP Address : 10.105.220.65 </span> </div> </div> </div> <style> * { font-family: \"Poppins\", sans-serif; text-decoration: none; } .icon { color: white; } .icon2 { color: black; } .link { width: 90%; height: 25%; display: flex; justify-content: center; align-items: center; } .page-contents { height: 100%; width: 100%; position: absolute; top: 0; left: 0; background-color: aliceblue; display: flex; justify-content: center; align-items: center; } .esp32-controller { height: 45vh; width: 25vw; background-color: rgb(143, 131, 255); border-radius: 10px; } .title-container { margin-top: 5px; height: 10%; width: 100%; display: flex; justify-content: center; align-items: center; color: white; gap: 10px; font-weight: 500; font-size: 1.5vw; } .buttons { display: flex; flex-direction: column; justify-content: flex-start; align-items: center; padding-top: 30px; gap: 30px; height: 69%; width: 100%; } .button { color: black; border: none; outline: none; font-size: 25px; font-weight: 500; width: 100%; height: 100%; display: flex; justify-content: center; align-items: center; gap: 15px; background-color: aliceblue; border-radius: 5px; transition: all, 0.2s ease; } .esp-info { height: 10%; margin-left: 20px; display: flex; justify-content: center; align-items: flex-start; flex-direction: column; margin-bottom: 5px; } .text-icon { color: white; font-weight: 400; display: flex; justify-content: center; align-items: center; gap: 5px; } .button:hover { background: transparent; border: 2px solid; color: white; } .button:active { transform: scale(0.95); } </style> <script type=\"module\" src=\"https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.esm.js\"></script> <script nomodule src=\"https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.js\"></script> </body> </html>";


WiFiServer server(80);                    //Em WiFiServer, é designada a porta que o servidor vai usar

void setup()
{
    Serial.begin(115200);           //boudrate da comunicação serial com o monitor serial
    pinMode(2, OUTPUT);             //define o pino 2 da placa para ligar e desligar
    delay(10);                      // delay de 10ms
    Serial.println();               //pular linha
    Serial.print("Conectado com: ");//texto para imprimirmna mesmo linha a nome da rede
    Serial.println(ssid);           //nome da rede

    WiFi.begin(ssid, password);     //inicializa o WiFi colocando a rede e senha

    while (WiFi.status() != WL_CONNECTED) //Retorne o status da conexão se está conectado ou não
    {                                     //WL_CONNECTED atribuído quando conectado a uma rede WiFi. Nesse Caso a pergunta é se não foi conectado
        delay(500);                       //delay
        Serial.print(".");                //imprimir no monitor serial ponto enquanto repete o laçõ
    }

    Serial.println("");                   //pular linha
    Serial.println("WiFi Conectado!.");   //Texto
    Serial.print("IP address: ");         //texto endereço IP
    Serial.println(WiFi.localIP());       //numero do IP
    server.begin();                       //inicializa a função servidor
}

int value = 0;

void loop()
{
 WiFiClient client = server.available();   // WiFiClient inicia uma variável que confere se há algum cliente conectado

      if (client) 
      {                                      // Se consegiu um cliente
        Serial.println("New Client.");       // msg no monitor serial de novo cliente
        String currentLine = "";             // faça uma String(texto) para armazenar dados recebidos do cliente
        
        while (client.connected())           //enquanto cliente conectado
        {                                    // loop while the client's connected
                if (client.available())            // se o cliente estiver disponivel
                {                                 // se houver bytes para ler do cliente
                  char c = client.read();         // leia o byte
                  Serial.write(c);                // imprimir no monitor serial
                  
                  if (c == '\n') 
                  {                                  // se o byte for um caractere de nova linha
                           if (currentLine.length() == 0)  //lenght analisa se não tem mais nenhum dado para receber, e também responde isso ao cliente.
                             {                                 //comando para abrir uma pagina em html          
                                                            // Os cabeçalhos HTTP sempre começam com um código de resposta (e.g. HTTP/1.1 200 OK)
                                                            // e um tipo de conteúdo para que o cliente saiba o que está por vir, depois uma linha em branco:
                           
                //****************************************INICIO DA PAGINA HTML***********************************************
                            client.println("HTTP/1.1 200 OK");//abre o protocolo http para chamar uma pagina em html
                            client.println("Content-type:text/html");//conteudo a ser chamado é em html
                            client.println();//chamada do cliente para o servidor.
                
                            //o conteúdo da resposta HTTP segue o cabeçalho:
                            client.print(html);
                            
                //****************************************fim do html**********************************************************
                            client.println();// A resposta HTTP termina com outra linha em branco:
                            break;            //sair do loop while:
                          }   
                    
                      else
                      {                       
                        currentLine = "";     //se você tiver uma nova linha, limpe a linha atual
                      }
                  } 
                  
                  
                  else if (c != '\r') {       //se você tiver qualquer outra coisa além de um caractere de retorno de carro,
                    currentLine += c;         //adicione-o ao final da currentLine
                  }
          
                  // Check to see if the client request was "GET /H" or "GET /L":
          
                  
                  if (currentLine.endsWith("GET /H"))      //na linha atual pega o final, no caso H recebido e faz a comparação 
                      {
                       digitalWrite(2, HIGH);               // GET /H para ligar o LED
                      }
                  if (currentLine.endsWith("GET /L")) 
                      {
                      digitalWrite(2, LOW);                // GET /L para desligar o led
                      }
                }
        }
        
        client.stop();                        //finaliza-se a conexão com a função
        Serial.println("Client Disconnected.");
      }
}

//********************WiFi - WiFi.status()******************************
//WL_CONNECTED: atribuído quando conectado a uma rede WiFi;
//WL_NO_SHIELD: atribuído quando não há escudo WiFi presente;
//WL_IDLE_STATUS: é um status temporário atribuído quando WiFi.begin() é chamado e permanece ativo até que o número de tentativas expire (resultando em WL_CONNECT_FAILED) ou uma conexão seja estabelecida (resultando em WL_CONNECTED);
//WL_NO_SSID_AVAIL: atribuído quando nenhum SSID está disponível;
//WL_SCAN_COMPLETED: atribuído quando a varredura da rede é concluída;
//WL_CONNECT_FAILED: atribuído quando a conexão falha em todas as tentativas;
//WL_CONNECTION_LOST: atribuído quando a conexão é perdida;
//WL_DISCONNECTED: atribuído quando desconectado de uma rede;
