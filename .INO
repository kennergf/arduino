/*********************************************  SMART CAR  ********************************************
*                                                                                                     *
*Placa: Arduino UNO R3                                                                                *
*Autor: Aline Siqueira, Aline Xavier, Kenner Gonçalves                                                *
*                                                                                                     *
*Descrição:  Projeto do Smart Car criado com o arduino UNO R3 ponte H e dois motores DC e um          *
*            modulo bluetooth que utiliza o software "arduino bluetooth rc car" para enviar comandos  *
*            via bluetooth para o arduino.                                                            *
*                                                                                                     *
*  Pinos usados para o Módulo Bluetooth:                                                              *
*    1(TX) -> RXD do bluetooth  (Desconectar o bluetooth do arduino quando for fazer o upload)        *
*    0(RX) -> TXD do bluetooth  (Desconectar o bluetooth do arduino quando for fazer o upload)        *
*    Você deve alimentar o módulo bluetooth: Ligue VCC ao Pino 5V e o GND ao GND                      *
*******************************************************************************************************/
char dataIn = 'S'; //Recebe dados vindos do telefone.
//Variaveis de controle dos motores/pino ponte H/pino arduino
int inA1 = 5;
int inA2 = 6;
int inA3 = 10;
int inA4 = 11;
//Variaveis de controle de farois(Não usados nesse projeto devido ao tipo formula um do carro)
int pinfrontLights = 4;    //Pin que ativa as luzes da frente.
int pinbackLights = 7;    //Pin que ativa as luzes traseiras.
//Variaveis de controle
char determinant;         //Usado na função de verificação, armazena o caráter recebido do telefone.
char det;                 //Usado na função loop, armazena o caráter recebido do telefone.
int velocity = 0;    //Armazena a velocidade baseado no character enviada pelo telefone.

void setup()
{       
  //************* NOTA: Se estiver usando Bluetooth Mate Silver usar 115200 btu
  //Se estiver usando MDFLY Bluetooth Module uso 9600 btu
  Serial.begin(9600);  //Inicializar a comunicação serial com o módulo Bluetooth em 9600 btu.
  set_motors(0,0,0,0);

  pinMode(pinfrontLights , OUTPUT);
  pinMode(pinbackLights , OUTPUT);
}

void loop()
{
    det = check();
      while (det == 'F')   //Se os dados de entrada é um F, mover para frente
      {
        set_motors(velocity,0,0,0);
        det = check();          
      }  
      while (det == 'B')   //se os dados de entrada é um B, voltar (move back)
      {
        set_motors(0,velocity,0,0);
        det = check();          
      }
      while (det == 'L')   //se os dados de entrada for um L, rodas se movem para a esquerda (move wheels left)
      {
        set_motors(0,0,255,0);      
        det = check();          
      }
      while (det == 'R')   //se os dados de entrada for um R,rodas se movem para direita (move wheels right)
      {
        set_motors(0,0,0,255);      
        det = check();          
      }
      while (det == 'I')   //se os dados de entrada é um I, vire à direita e para a frente
      {
        set_motors(velocity,0,0,255);                  
        det = check();          
      }  
      while (det == 'J')   //se os dados de entrada é um J, vire à direita para trás
      {
        set_motors(0,velocity,0,255);       
        det = check();          
      }          
      while (det == 'G')   //se os dados de entrada é um G, vire à esquerda e para a frente
      {
        set_motors(velocity,0,255,0);         
        det = check();          
      }    
      while (det == 'H')   //se os dados de entrada é um H, vire à esquerda e para trás
      {
        set_motors(0,velocity,255,0);        
        det = check();                                              
      }   
      while (det == 'S')   //se os dados de entrada é a S, parar
      {
        set_motors(0,0,0,0);      
        det = check();
      }
      while (det == 'U')   //se os dados de entrada é um U, ligar luzes dianteiras
      {
        digitalWrite(pinfrontLights, HIGH);          
        det = check();
      }
      while (det == 'u')   //se os dados de entrada é um u, desligar as luzes dianteiras
      {
        digitalWrite(pinfrontLights, LOW);          
        det = check();
      }
      while (det == 'W')   //se os dados de entrada é um W, ligar luzes traseiras
      {
        digitalWrite(pinbackLights, HIGH);          
        det = check();
      }
      while (det == 'w')   //se os dados de entrada é um w, desligar as luzes traseiras
      {
        digitalWrite(pinbackLights, LOW);
        det = check();
      }
}
int check()//função que verifica os valores passado pelo bluetooth
{
  if (Serial.available() > 0) //Verifica se a porta serial esta disponivel
  {   
    dataIn = Serial.read();  //Obtem o caractere enviado pelo telefone e armazená-lo em 'dataIn'.
        if (dataIn == 'F')
        {     
          determinant = 'F';
        }  
        else if (dataIn == 'B')
        {
          determinant = 'B';
        }
        else if (dataIn == 'L')  
        {
          determinant = 'L';
        }
        else if (dataIn == 'R')  
        {
          determinant = 'R';
        }
        else if (dataIn == 'I')  
        {
          determinant = 'I';
        }  
        else if (dataIn == 'J')  
        {  
          determinant = 'J';
        }          
        else if (dataIn == 'G')
        {
          determinant = 'G';
        }    
        else if (dataIn == 'H')  
        {
          determinant = 'H';
        }   
        else if (dataIn == 'S')
        {
          determinant = 'S';
        }
        else if (dataIn == '0')
        {
          velocity = 0;//"velocidade" não precisa ser devolvido.
        }
        else if (dataIn == '1')
        {
          velocity = 25;
        }
        else if (dataIn == '2')
        {
          velocity = 50;
        }
        else if (dataIn == '3')
        {
          velocity = 75;
        }
        else if (dataIn == '4')
        {
          velocity = 100;
        }
        else if (dataIn == '5')
        {
          velocity = 125;
        }
        else if (dataIn == '6')
        {
          velocity = 150;
        }
        else if (dataIn == '7')
        {
          velocity = 175;
        }
        else if (dataIn == '8')
        {
          velocity = 200;
        }
        else if (dataIn == '9')
        {
          velocity = 225;
        }
        else if (dataIn == 'q')
        {
          velocity = 255;
        }
        else if (dataIn == 'U')
        {
          determinant = 'U';
        }
        else if (dataIn == 'u')
        {
          determinant = 'u';
        }
        else if (dataIn == 'W')
        {
          determinant = 'W';
        }
        else if (dataIn == 'w')
        {
          determinant = 'w';
        }
  }
  return determinant;
}
/*Fução que define direção e velocidade para os motores, asegure-se de nunca ligar
*motorA1 e motorA2 ou motorB1 e motorB2 ao mesmo tempo*/
void set_motors(int motorA1, int motorA2, int motorB1, int motorB2){
  analogWrite(inA1, motorA1);
  analogWrite(inA2, motorA2);
  analogWrite(inA3, motorB1);
  analogWrite(inA4, motorB2);
}//fim set_motors
