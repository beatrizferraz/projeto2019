#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.c>
#include <time.h>
#include <ctype.h>

int li=21, co=4; int pontos=0; int tempo=120;
int cen[81][26];

//------------------------------------------------------------------------------------------------------------------------------------
void arquivo_cenario(){
     int x,y;
     
     FILE *file;
     file = fopen("cenariojogo.txt","r");
         if (file == NULL){
             printf("Arquivo nao encontrado.");
             getchar();
             exit(0);
         }

     for (x=0;x<25;x++)
        for (y=0;y<80;y++)
            fscanf(file,"%i ",&cen[y][x]);
            fclose(file);
}

//-----------------------------------------------------------------------------------------------------------------------------------
void cenario(){
     int l,c;

     for (l=0;l<25;l++)
         for (c=0;c<80;c++){  
           printf("%c",cen[c][l]);
         }  
}

//------------------------------------------------------------------------------------------------------------------------------------
void colisao_barreira(int C, int L){ 
     
     if((cen[C+2][L]!=32 && cen[C+2][L]!=79) || (cen[C+2][L+1]!=32 && cen[C+2][L+1]!=79) ){  
              co--;       //barreira a direita
     }    
     
     if((cen[C-1][L]!=32 && cen[C-1][L]!=79)||(cen[C-1][L+1]!=32 && cen[C-1][L+1]!=79)){
              co++;       //barreira esquerda            
     }
     
     if((cen[C][L-1]!=32 && cen[C][L-1]!=79)||(cen[C+1][L-1]!=32 && cen[C+1][L-1]!=79)){
              li++;   //barreira de cima      
     } 
     
     if(cen[C][L+1]!=32 && cen[C][L+1]!=79){
              li--;       //barreira de baixo
     } 
  
  //(cen[C-1][L]!=32 && cen[C-1][L]!=79)        
} 

//------------------------------------------------------------------------------------------------------------------------------------
void correcao_dir(int colu,int linha){

        if(cen[colu-1][linha]==32||cen[colu-1][linha]==79){ 
           gotoxy(colu-1,linha);printf("%c",32);
        }
        if(cen[colu-2][linha+1]==32||cen[colu-2][linha+1]==79){
           gotoxy(colu-1,linha+1);printf("%c",32);
           gotoxy(colu-1,linha+2);printf("%c",32);
        }
        
        colisao_barreira(co,li);
     
}
//-----------------------------------------------------------------------------------------------------------------------------------
void correcao_esq(int COLU, int LINHA){

         if(cen[COLU+1][LINHA]==32||cen[COLU+1][LINHA]==79){
            gotoxy(COLU+1,LINHA);printf("%c",32);
         } 
         if(cen[COLU+3][LINHA+1]==32||cen[COLU+3][LINHA+1]==79){
            gotoxy(COLU+3,LINHA+1);printf("%c",32);
            gotoxy(COLU+3,LINHA+2);printf("%c",32);
         }

         colisao_barreira(co,li);
}
//-----------------------------------------------------------------------------------------------------------------------------------
void correcao_cima(int Coluna, int Linha ){
  
        if(cen[Coluna][Linha+2]==32||cen[Coluna+2][Linha+2]==79){
           gotoxy(Coluna,Linha+3);printf("%c",32);
        } //perna esq

        if(cen[Coluna+2][Linha+2]==32||cen[Coluna+2][Linha+2]==79){
           gotoxy(Coluna+2,Linha+3);printf("%c",32);
        } //perna direita
        
        colisao_barreira(co,li); 
        
}
//-----------------------------------------------------------------------------------------------------------------------------------
void correcao_baixo(int colunA, int linhA){
     
       if(cen[colunA+1][linhA-2]==32||cen[colunA+1][linhA-2]==79){
          gotoxy(colunA+1,linhA-1);printf("%c",32);
       }
       
       colisao_barreira(co,li);
}
//-----------------------------------------------------------------------------------------------------------------------------------
void carinha(int i,int j){    
         
     textcolor(11); 
     gotoxy(i,j);  printf(" o ");
     gotoxy(i,j+1);printf("/|\\"); 
     gotoxy(i,j+2);printf("/ \\"); 
     
}
//------------------------------------------------------------------------------------------------------------------------------------
void pega_moeda(int COL, int LIN){
     
     if(cen[COL+2][LIN]==79 || cen[COL+2][LIN+1]==79){         
           pontos=pontos+10;
           gotoxy(4,1);printf("PONTOS: %d",pontos);
           if(cen[COL+2][LIN]==79)
             cen[COL+2][LIN]=32;
           
           if(cen[COL+2][LIN+1]==79)
             cen[COL+2][LIN+1]=32;  
     }
}     
//------------------------------------------------------------------------------------------------------------------------------------
void gravidade(int lin, int col,int tec){       
     
     tec=getch();
     
     if (cen[col][lin+2]==32||cen[col][lin+2]==79){
         do{
           li++;
           Sleep(1000);
           
           
         }while(lin<=22||(cen[col][lin+2]==32&&cen[col][lin+2]==79)||tec==0);  
         
     } 
     
     correcao_baixo(co,li);   
} 
//------------------------------------------------------------------------------------------------------------------------------------
void cronometro(){
     
     while(tempo >=0){
       tempo--;      
       /*gotoxy(15,1);    
       printf("TEMPO: %d",tempo);*/
	   Sleep(1000);
    }
}    
//------------------------------------------------------------------------------------------------------------------------------------
void creditos(){
   gotoxy(22,12);printf("Autora:  Beatriz Ferraz\n");
   gotoxy(22,13);printf("Curso:   Engenharia de Sofware");
   gotoxy(22,14);printf("         2o semestre, Unicesumar, 2019");
   gotoxy(22,15);printf("\n");
   gotoxy(22,16);printf("Contato: aferrazbeatriz@gmail.com");
}
//------------------------------------------------------------------------------------------------------------------------------------
void movimenta(){
     int tecla=0;
       
     arquivo_cenario();  
     cenario();
     
     carinha(co,li);
     
       do{  
            
         if (kbhit()) { 
            tecla = getch();
            if (tecla==224|| tecla==0){
               tecla=getch();
             
            switch (tecla){
              case 13: //enter
    	        break;
    
    	      case 32: //espaco
    	        if (li-2>=1) 
                  li=li-2;  
    	        break;
    
              case 72: //cima
                if (li-1>=1){ 
                  li--; 
                  correcao_cima(co,li);   
                } 
                break;
       
              case 80: //baixo
    	        if (li+1<=21){ 
                  li++;
                  correcao_baixo(co,li);
                  }
                break;
         
              case 75: //esq
    	        if (co-1>=3){
    	           co--;
    	           correcao_esq(co,li);
                }   
                
                break;
         
              case 77: //dir
                if (co+1<=75){ 
                  co++;   
                  correcao_dir(co,li);               
                }
                break;
            }
            colisao_barreira(co,li); 
            carinha(co,li);
            //gravidade(li,co,tecla);
            pega_moeda(co,li);
            
           } 
         }
       } 
       while(tecla!=27);
}
//------------------------------------------------------------------------------------------------------------------------------------
void gameover(){
     gotoxy(30,12); 
     printf(" G A M E   O V E R "); 
     gotoxy(34,18);
     printf("Pontos: %d",pontos);  
     Sleep(10000);   
}
//-----------------------------------------------------------------------------------------------------------------------------------
int main(){
     
     creditos();
     getch();
     system("cls");
     
     movimenta();

     getch();
     return 0;
}
