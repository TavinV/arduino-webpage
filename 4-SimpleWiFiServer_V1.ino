//https://lobodarobotica.com/blog/web-server-com-esp32-conexao-wifi/

#include <WiFi.h> // inclusão da biblioteca WiFi

const char* ssid     = "Teixeiras_NET";// SSID é o nome da rede a ser conectada
const char* password = "@Igor2530";      // senha da rede

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

                            int numerosPorSegundo = 1;
                            int valor = random(0,100);
                            
                            
                //****************************************INICIO DA PAGINA HTML***********************************************
                            client.println("HTTP/1.1 200 OK");//abre o protocolo http para chamar uma pagina em html
                            client.println("Content-type:text/html");//conteudo a ser chamado é em html
                            client.println();//chamada do cliente para o servidor.

                           String html ="<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <script src=\"https://kit.fontawesome.com/06a72cc7b8.js\" crossorigin=\"anonymous\"></script> <title>Esp Controller</title> </head> <body> <header> <h1> Esp Controller </h1> </header> <main> <div class=\"esp-info\"> <h2 class=\"title-espinfo\">Informações de conexão </h2> <br> Mac Address: <span class=\"info\">";
                            html += String(WiFi.macAddress());
                            html +="</span> <br> Endereço de IP: <span class=\"info\">";
                            html += String(WiFi.localIP());
                            html +="</span> </div> <div class=\"led-controller\"> <div class=\"led-buttons\"> <h2 class=\"title-controller\">Controlador do ESP32</h2> <br> <a class=\"link\" href=\"/H\\\"> <button class=\"button\"> Ligar o Led </button> </a> <br> <a class=\"link\" href=\"/L\\\"> <button class=\"button\"> Desigar o Led </button> </a> </div> </div> <div class=\"random-number\"> <h2 class=\"valor-aleatorio-title\">Valor aleatório</h2> <br> <div class=\"Numero-randomico\" > <h1 class=\"valor\">";
                            html += String(valor);
                            html +="</h1> </div> </div> </main> <footer> </footer> <style> @import url('https://fonts.googleapis.com/css2?family=Poppins:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&family=Rubik:ital,wght@0,300..900;1,300..900&display=swap'); @import url('https://fonts.cdnfonts.com/css/digital-numbers'); * { font-family: \"Rubik\", sans-serif; font-optical-sizing: auto; font-style: normal; font-weight: 350; margin: 0; padding: 0; } :root { --dark: #02023c; --white: #f8f8f8; --accent1: #ff4500; --accent2: #32cd32; --header_height: 10vh; --width_general: 80vw; } body { overflow-x: hidden; } header { position: fixed; top: 0px; left: 0px; display: flex; justify-content: center; align-items: center; width: 100vw; height: var(--header_height); background: var(--dark); color: var(--white); font-size: 5vw; font-weight: 500; font-family: 'Rosbed', sans-serif; } main { height: 100vh; width: 100vw; background-color: var(--white); margin-top: var(--header_height); padding-top: 50px; display: flex; justify-content: flex-start; align-items: center; flex-direction: column; gap: 30px; } .esp-info, .led-controller { background: var(--dark); color: var(--white); width: var(--width_general); padding-top: 2%; padding-left: 2%; padding-right: 2%; border-radius: 10px; } .random-number{ background: var(--dark); color: var(--white); width: var(--width_general); padding-top: 2%; padding-left: 2%; padding-right: 2%; border-radius: 30px; height: 12vh; display: flex; justify-content: flex-start; align-items: center; flex-direction: column; } .Numero-randomico{ background-color: var(--white); color: var(--dark); display: flex; justify-content: center; align-items: center; width: 50%; height: 40%; border-radius: 20px; } .valor { font-size: 9vw; font-family: 'Digital Numbers', sans-serif; text-align: center; margin-right: 10%; } .valor-aleatorio-title { font-size: 5vw; } .esp-info { background: var(--dark); color: var(--white); width: var(--width_general); height: 15vh; padding-top: 2%; padding-left: 2%; padding-right: 2%; border-radius: px; font-size: 4vw; } .info { color: var(--accent2); } .led-controller { display: flex; flex-direction: column; height: 20vh; } .link { display: flex; justify-content: center; align-items: center; text-decoration: none; cursor: default; width: 100%; } .button { outline: none; border: none; background: var(--white); color: var(--accent2); width: 100%; height: 5vh; font-size: 5vw; border-radius: 50px; } .button:active{ scale: 0.98; } .title-espinfo { font-size: 5vw; } .title-controller{ font-size: 5vw; margin-bottom: 1vh; } @media (max-width: 335px) { body { overflow-x: hidden; } } </style> </body> </html>";

                
                            //o conteúdo da resposta HTTP segue o cabeçalho:
                            client.print(html);
                            
                            delay(1000 / numerosPorSegundo);
                            client.print("<script> window.location.reload(); </script>");
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
