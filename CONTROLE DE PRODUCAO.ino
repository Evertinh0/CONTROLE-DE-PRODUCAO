/* SISTEMA DE RELATORIO - TEIU
   DATA DE CRIAÇÃO: 12/06/22
   AUTOR: EVERTON YAN DE JESUS SOUZA
*/

//---- DEFINIÇÃO DAS BIBLIOTECAS----//

#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
#include "TouchScreen.h"
MCUFRIEND_kbv tft;

// ------------------------
#define YP A1
#define XM A2
#define YM 7
#define XP 6
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// DEFINIR OS VALORES MINIMOS E MAXIMOS DOS EIXOS X E Y //

#define TS_LEFT 870 // Use 150 para o 9341
#define TS_RT 165 // Use 120 para o 9341
#define TS_TOP 870
#define TS_BOT 110
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);

//----------------------------------------|
// TFT Breakout  -- Arduino UNO / Mega2560 / OPEN-SMART UNO Black
// GND              -- GND
// 3V3               -- 3.3V
// CS                 -- A3
// RS                 -- A2
// WR                -- A1
// RD                 -- A0
// RST                -- RESET
// LED                -- GND
// DB0                -- 8
// DB1                -- 9
// DB2                -- 10
// DB3                -- 11
// DB4                -- 4
// DB5                -- 13
// DB6                -- 6
// DB7                -- 7

// Definição de cores hexadecimal:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 20
#define MAXPRESSURE 1000

// Variáveis Globais
int page = 0;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("SISTEMA -TEIU-");
  tft.reset();
  delay(500);
  tft.begin(0x7793);

  tft.setRotation(4);
  tft.setCursor(0, 0); //y e x
  tft.setTextColor(WHITE);
  tft.setTextSize(2);

  tft.println("Programa feito por: ");
  tft.println("Everton yan");
  tft.println("de jesus Souza");
  tft.println("www.youtube.com/c/EduArduino");

  delay(2000);
  tft.fillScreen(BLACK);
//  telainicia1();
  page = 0;

}

void loop()
{
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
  pinMode(YM, OUTPUT);
  digitalWrite(YM, LOW);
  pinMode(XP, OUTPUT);
  digitalWrite(XP, HIGH);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_LEFT, TS_RT, 0, tft.width());
    p.y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    Serial.print(" px: ");
    Serial.print(p.x);
    Serial.print("py: ");
    Serial.println(p.y);

/*    //============== PAGINA DESBLOQUEIO =====================
    if (page == 1) {

      if (p.x > 60 & p.x < 100 & p.y > 5 & p.y < 110)//DESBLOQUEIO
      {
        page = 1;
        telamenu ();
      }
    } //FECHA A PAGINA DESBLOQUEIO*/
    //================ dentro no menu  ==================
    //===================== PAGINA OP ===================
    if (page == 2) {

      if (p.x > 5 & p.x < 110 & p.y > 60 & p.y < 100)//OP
      {
        page = 1;
        opselect ();
        telaop();
      }
      //===================== PAGINA CEP ===================
      if (p.x > 130 & p.x < 105 & p.y > 60 & p.y < 100)//CEP
      {
        page = 2;
        cepselect ();
        telacep();
      }
      //===================== PAGINA PARADAS ===================
      if (p.x > 5 & p.x < 110 & p.y > 180 & p.y < 100)//PARADAS
      {
        page = 3;
        paradasselect ();
        telaparadas();
      }
      //===================== PAGINA SETTINGS ===================
      if (p.x > 130 & p.x < 105 & p.y > 180 & p.y < 100)//SETTINGS
      {
        page = 4;
        settingsselect ();
        telasettings();
      }
      //===================== PAGINA INFORMAÇÕES ===================
      if (p.x > 10 & p.x < 0 & p.y > 0 & p.y < 0)//INFORMAÇÕES
      {
        page = 5;
        informacoesselect ();
        telainformacoes();
      }
      
      } //FECHA A PAGINA MENU
//=============== 
else if(page==2){
if (p.x > 0 & p.x < 0 & p.y > 0 & p.y < 0)//botão voltar
      {
//        telainicial();
        page=0;         
      }





  }
}
void telainicia1() {
  tft.fillScreen(WHITE);
  tft.fillRoundRect(5, 270, 230, 60, 3, BLACK);
  tft.fillRoundRect(5, 270, 224, 54, 3, BLUE);
  tft.setCursor(55, 290);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("DESBLOQUEAR");
}

// ==================== TELA MENU (CRIA O MENU VISUAL )=============
void telamenu() {
  // Inicio - Texto e botoes
  tft.fillScreen(WHITE);
  tft.fillRoundRect(5, 60, 110, 100, 5, BLACK);
  tft.fillRoundRect(5, 60, 106, 96, 5, BLUE);
  tft.setCursor(42, 96);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("OP");

  tft.fillScreen(WHITE);
  tft.fillRoundRect(130, 60, 105, 100, 5, BLACK);
  tft.fillRoundRect(130, 60, 101, 96, 5, BLUE);
  tft.setCursor(155, 96);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("CEP");

  tft.fillScreen(WHITE);
  tft.fillRoundRect(5, 180, 110, 100, 5, BLACK);
  tft.fillRoundRect(5, 176, 106, 96, 5, BLUE);
  tft.setCursor(16, 220);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("PARADAS");

  tft.fillScreen(WHITE);
  tft.fillRoundRect(130, 180, 105, 100, 5, BLACK);
  tft.fillRoundRect(130, 176, 101, 96, 5, BLUE);
  tft.setCursor(134, 220);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("SETTINGS");

  tft.fillScreen(WHITE);
  tft.fillRoundRect(10, 320, 217, 70, 5, BLACK);
  tft.fillRoundRect(10, 320, 217, 70, 5, BLUE);
  tft.setCursor(20, 345);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("INFORMACOES");
}
//================= TELA SELECT( CRIA UM EFEITO DE CLICK AO ABERTA) ==============
  void opselect() {
    tft.fillRoundRect(5, 60, 110, 100, 5, BLACK);
    tft.fillRoundRect(5, 60, 106, 96, 5, BLUE);
    tft.setCursor(42, 96);
    tft.setTextColor(WHITE);  
    tft.setTextSize(3);
    tft.print("OP");   
  }
  void cepselect() {
    tft.fillRoundRect(130, 60, 105, 100, 5, BLACK);
    tft.fillRoundRect(130, 60, 101, 96, 5, BLUE);
    tft.setCursor(155, 96);
    tft.setTextColor(WHITE);  
    tft.setTextSize(3);
    tft.print("CEP");   
  }
    void paradasselect() {
    tft.fillRoundRect(5, 180, 110, 100, 5, BLACK);
    tft.fillRoundRect(5, 176, 106, 96, 5, BLUE);
    tft.setCursor(16, 220);
    tft.setTextColor(WHITE);  
    tft.setTextSize(2);
    tft.print("PARADAS");   
  }
    void settingsselect() {
    tft.fillRoundRect(130, 180, 105, 100, 5, BLACK);
    tft.fillRoundRect(130, 176, 101, 96, 5, BLUE);
    tft.setCursor(134, 220);
    tft.setTextColor(WHITE);  
    tft.setTextSize(2);
    tft.print("SETTINGS");   
  }
    void informacoesselect() {
    tft.fillRoundRect(10, 320, 217, 70, 5, BLACK);
    tft.fillRoundRect(10, 320, 217, 70, 5, BLUE);;
    tft.setCursor(20, 345);
    tft.setTextColor(WHITE);  
    tft.setTextSize(3);
    tft.print("INFORMACOES");   
  } 
//====== TELA MENU DE DENTRO DAS OPÇÕES = OP, CEP, PARADAS, SETTINGS E INFORMACOES ===================
//=========== TELA DO MENU OP ===========
    void telaop() {
    
    tft.fillScreen(WHITE);
    tft.fillRoundRect(0,0,240,5,0,WHITE);
    tft.fillRoundRect(0,13,240,52,0,BLACK);
    tft.fillRoundRect(2,15,236,48,0,BLUE);
    tft.setCursor(70,20);
    tft.setTextColor(WHITE);  
    tft.setTextSize(2);
    tft.print("ORDEM DE");
    tft.setCursor(70,40);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("PRODUCAO");
     //BOTÃO DE VOLTAR
    tft.fillTriangle(50,20,50,55,15,37,GREY);
    
    tft.fillRoundRect(5,130,232,34,0,BLACK);
    tft.fillRoundRect(7,132,228,30,0,BLUE);
    tft.setCursor(50,110);
    tft.setTextColor(BLACK);  
    tft.setTextSize(2);
    tft.print("DIGITE A OP:");

    tft.fillRoundRect(5,210,232,34,0,BLACK);
    tft.fillRoundRect(7,212,228,30,0,BLUE);
    tft.setCursor(25,190);
    tft.setTextColor(BLACK);  
    tft.setTextSize(2);
    tft.print("COD. DO OPERADOR:");

    tft.fillRoundRect(70,320,104,69,0,BLACK);
    tft.fillRoundRect(72,322,100,65,0,BLUE);
    tft.setCursor(80,345);
    tft.setTextColor(WHITE);  
    tft.setTextSize(2);
    tft.print("INICIAR");
  
  }
//===================== TELA MENU CEP ===========================
    void telacep() {
    
    tft.fillScreen(WHITE);
    tft.fillRoundRect(0,0,240,5,0,WHITE);
    tft.fillRoundRect(0,13,240,52,0,BLACK);
    tft.fillRoundRect(2,15,236,48,0,BLUE);
    tft.setCursor(70,30);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("CONTROLE ESTATICO");
    tft.setCursor(100,50);
    tft.setTextColor(WHITE);
    tft.setTextSize(1);
    tft.print("DE PESO");
     //BOTÃO DE VOLTAR
    tft.fillTriangle(50,20,50,55,15,37,GREY);

    tft.fillRoundRect(128,68,104,24,0,BLACK);
    tft.fillRoundRect(130,70,100,20,0,BLUE);
    tft.setCursor(142,72);
    tft.setTextColor(WHITE);  
    tft.setTextSize(2);
    tft.print("LIMPAR");
    
//========= QUANTIDADE DE AMOSTRAS PESADAS 1-30 8HORAS ==========  
  
    tft.fillRoundRect(5,100,50,20,0,BLACK);
    tft.fillRoundRect(20,100,50,20,0,BLUE);
    tft.setCursor(9,105);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("1");
    
    tft.fillRoundRect(5,130,50,20,0,BLACK);
    tft.fillRoundRect(20,130,50,20,0,BLUE);
    tft.setCursor(9,135);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("2");
    
    tft.fillRoundRect(5,160,50,20,0,BLACK);
    tft.fillRoundRect(20,160,50,20,0,BLUE);
    tft.setCursor(9,165);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("3");

    tft.fillRoundRect(5,190,50,20,0,BLACK);
    tft.fillRoundRect(20,190,50,20,0,BLUE);
    tft.setCursor(9,195);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("4");

    tft.fillRoundRect(5,220,50,20,0,BLACK);
    tft.fillRoundRect(20,220,50,20,0,BLUE);
    tft.setCursor(9,225);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("5");

    tft.fillRoundRect(5,250,50,20,0,BLACK);
    tft.fillRoundRect(20,250,50,20,0,BLUE);
    tft.setCursor(9,255);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("6");

    tft.fillRoundRect(5,280,50,20,0,BLACK);
    tft.fillRoundRect(20,280,50,20,0,BLUE);
    tft.setCursor(9,285);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("7");

    tft.fillRoundRect(5,310,50,20,0,BLACK);
    tft.fillRoundRect(20,310,50,20,0,BLUE);
    tft.setCursor(9,315);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("8");

    tft.fillRoundRect(5,340,50,20,0,BLACK);
    tft.fillRoundRect(20,340,50,20,0,BLUE);
    tft.setCursor(9,345);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("9");

    tft.fillRoundRect(5,370,50,20,0,BLACK);
    tft.fillRoundRect(20,370,50,20,0,BLUE);
    tft.setCursor(6,375);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("10");

    tft.fillRoundRect(85,100,50,20,0,BLACK);
    tft.fillRoundRect(100,100,50,20,0,BLUE);
    tft.setCursor(87,105);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("11");

    tft.fillRoundRect(85,130,50,20,0,BLACK);
    tft.fillRoundRect(100,130,50,20,0,BLUE);
    tft.setCursor(87,135);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("12");

    tft.fillRoundRect(85,160,50,20,0,BLACK);
    tft.fillRoundRect(100,160,50,20,0,BLUE);
    tft.setCursor(87,165);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("13");

    tft.fillRoundRect(85,190,50,20,0,BLACK);
    tft.fillRoundRect(100,190,50,20,0,BLUE);
    tft.setCursor(87,195);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("14");

    tft.fillRoundRect(85,220,50,20,0,BLACK);
    tft.fillRoundRect(100,220,50,20,0,BLUE);
    tft.setCursor(87,225);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("15");

    tft.fillRoundRect(85,250,50,20,0,BLACK);
    tft.fillRoundRect(100,250,50,20,0,BLUE);
    tft.setCursor(87,255);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("16");

    tft.fillRoundRect(85,280,50,20,0,BLACK);
    tft.fillRoundRect(100,280,50,20,0,BLUE);
    tft.setCursor(87,285);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("17");

    tft.fillRoundRect(85,310,50,20,0,BLACK);
    tft.fillRoundRect(100,310,50,20,0,BLUE);
    tft.setCursor(87,315);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("18");

    tft.fillRoundRect(85,340,50,20,0,BLACK);
    tft.fillRoundRect(100,340,50,20,0,BLUE);
    tft.setCursor(87,345);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("19");

    tft.fillRoundRect(85,370,50,20,0,BLACK);
    tft.fillRoundRect(100,370,50,20,0,BLUE);
    tft.setCursor(87,375);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("20");
    
    tft.fillRoundRect(165,100,50,20,0,BLACK);
    tft.fillRoundRect(180,100,50,20,0,BLUE);
    tft.setCursor(168,105);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("21");

    tft.fillRoundRect(165,130,50,20,0,BLACK);
    tft.fillRoundRect(180,130,50,20,0,BLUE);
    tft.setCursor(168,135);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("22");

    tft.fillRoundRect(165,160,50,20,0,BLACK);
    tft.fillRoundRect(180,160,50,20,0,BLUE);
    tft.setCursor(168,165);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("23");

    tft.fillRoundRect(165,190,50,20,0,BLACK);
    tft.fillRoundRect(180,190,50,20,0,BLUE);
    tft.setCursor(168,195);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("24");

    tft.fillRoundRect(165,220,50,20,0,BLACK);
    tft.fillRoundRect(180,220,50,20,0,BLUE);
    tft.setCursor(168,225);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("25");

    tft.fillRoundRect(165,250,50,20,0,BLACK);
    tft.fillRoundRect(180,250,50,20,0,BLUE);
    tft.setCursor(168,255);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("26");

    tft.fillRoundRect(165,280,50,20,0,BLACK);
    tft.fillRoundRect(180,280,50,20,0,BLUE);
    tft.setCursor(168,285);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("27");

    tft.fillRoundRect(165,310,50,20,0,BLACK);
    tft.fillRoundRect(180,310,50,20,0,BLUE);
    tft.setCursor(168,315);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("28");

    tft.fillRoundRect(165,340,50,20,0,BLACK);
    tft.fillRoundRect(180,340,50,20,0,BLUE);
    tft.setCursor(168,345);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("29");

    tft.fillRoundRect(165,370,50,20,0,BLACK);
    tft.fillRoundRect(180,370,50,20,0,BLUE);
    tft.setCursor(168,375);
    tft.setTextColor(WHITE);  
    tft.setTextSize(1);
    tft.print("30");

    }
//================= TELA MENU PARADAS ==================    
 
    void telaparadas() {
    
    tft.fillScreen(WHITE);
    tft.fillRoundRect(5,5,310,30,0,BLACK);
    tft.fillRoundRect(7,7,306,26,0,BLUE);
    tft.setCursor(120, 10);
    tft.setTextColor(WHITE);  
    tft.setTextSize(3);
    tft.print("PARADAS");
     //Avança e retrocede botões
    tft.fillTriangle(270,10,270,30,290,20,GREY);
    
    }
//=========== TELA MENU SETTIGS ==============
    void telasettings() {
    
    tft.fillScreen(WHITE);
    tft.fillRoundRect(5,5,310,30,0,BLACK);
    tft.fillRoundRect(7,7,306,26,0,BLUE);
    tft.setCursor(120, 10);
    tft.setTextColor(WHITE);  
    tft.setTextSize(3);
    tft.print("SETTINGS");
     //Avança e retrocede botões
    tft.fillTriangle(270,10,270,30,290,20,GREY);
    
    }
//=========== TELA MENU INFORMAÇOES ==============    
    void telainformacoes() {
    
    tft.fillScreen(WHITE);
    tft.fillRoundRect(5,5,310,30,0,BLACK);
    tft.fillRoundRect(7,7,306,26,0,BLUE);
    tft.setCursor(120, 10);
    tft.setTextColor(WHITE);  
    tft.setTextSize(3);
    tft.print("INFORMACOES");
     //Avança e retrocede botões
    tft.fillTriangle(270,10,270,30,290,20,GREY);
    
    }
}
    
