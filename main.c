#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

/* Os dados no arquivo txt estão salvos na seguinte ordem:
  1º vitoris Par
  2º vitorias Impar
  3º vitorias do usuario
  4º vitorias do usuario com PAR
  5º vitorias do usuario com IMAPR
  6º utima opcao do usuario
  7º quantas vezes escolheu IMPAR
  8º quantas vezes escolheu PAR
  9º partidas jogadas */

typedef struct stDados{
  int vitPar;
  int vitImp;
  int vitUser;
  int userPar;
  int userImp;
  int userOpt;
  int optImp;
  int optPar;
  int partidas;
}dado;

dado dados;

int zerarDados(){
  dados.vitPar = 0;
  dados.vitImp = 0;
  dados.vitUser = 0;
  dados.userPar = 0;
  dados.userImp = 0;
  dados.userOpt = 0;
  dados.optImp = 0;
  dados.optPar = 0;
  dados.partidas = 0;
}

//gera um valor que determina se o pc é impar ou par
int escolhaPc(){
  srand(time(NULL));
  int x = rand()%2;
  if(x%2 == 0){
    x = 0;
  }else{
    x = 1;
  }
  return x;
}

// gera o valor que o pc vai jogar
int valorPc(){
  srand(time(NULL));
  int x = rand()%11;
  return x;
}

// calcula se o valor da soma é impar ou par
int vencedor(int valor1, int valor2){
  int resultado = valor1 + valor2;
  if(resultado%2 == 0){
    resultado = 0;
  }else{
    resultado = 1;
  }
  return resultado;
}

// verifica o vencendor nas opções validas
int verficVenc(int resultado){
  if(resultado == 0 && dados.userOpt == 0){
    printf("\n O USUÁRIO VENCEU!");
    dados.vitPar++;
    dados.vitUser++;
    dados.userPar++;
    dados.partidas++;
  }else if(resultado == 0 && dados.userOpt==1){
    printf("\n O PC VENCEU!");
    dados.partidas++;
    dados.vitPar++;
  }else if(resultado == 1 && dados.userOpt==1){
    printf("\n O USUÁRIO VENCEU!");
    dados.vitImp++;
    dados.vitUser++;
    dados.userImp++;
    dados.partidas++;
  }else if(resultado == 1 && dados.userOpt==0){
    printf("\n O PC VENCEU!");
    dados.partidas++;
    dados.vitImp++;
  }
}

//verifica se foi digitado um valor válido
int verificao(){
  int x=0;
  int valor;
  while(x == 0){
    printf("\n Digite um valor entre 0 e 10: ");
    scanf("%d", &valor);
    if(valor>10 || valor<0){
    printf("\n Opção invalida, digite novamente!");
   }else{
      x=1;
   }
  }
  return valor;
}

//verifica se foi digitado um valor válido
int repetir(){
  int opcao, x=0;
  while(x==0){
    printf("\n Deseja jogar novamente? sim = 0 / não = 1: ");
    scanf("%d", &opcao);
    if(opcao<0 || opcao>1){
      printf("\n Opção invalida, digite novamente!");
    }
    else{
      x=1;
    }
  }
  return opcao;
}

int main(void) {
  setlocale(LC_ALL, " ");
  FILE *file;
  int pc, valUser, valPc, resultado, vitPc, play = 0;
  file = fopen("Dados.txt", "a");
  fclose(file);
  while(play == 0){
    if(dados.partidas<0){
      //zera os dados se necessario para evitar algum erro
      zerarDados();
    }else{
      //carrega os valores do arquivo txt
      file = fopen("Dados.txt", "r");
      fscanf(file, "%d", &dados.vitPar);
      fscanf(file, "%d", &dados.vitImp);
      fscanf(file, "%d", &dados.vitUser);
      fscanf(file, "%d", &dados.userPar);
      fscanf(file, "%d", &dados.userImp);
      fscanf(file, "%d", &dados.userOpt);
      fscanf(file, "%d", &dados.optImp);
      fscanf(file, "%d", &dados.optPar);
      fscanf(file, "%d", &dados.partidas);   
      fclose(file);
    }

    //verifica o número de partidas para determina a opção do pc
    if(dados.partidas >= 5){
      if(dados.vitPar > dados.vitImp){
        pc = 0;
      }else{
        pc=1;
      }
    }else{
      pc = escolhaPc();
    }

    //exibe qual a opção do usuário, seja impar ou par
   if(pc==0){
      printf("\n USUÁRIO JOGA COM IMPAR");
      dados.userOpt = 1;
      dados.optImp++;
    }else{
      printf("\n USUÁRIO JOGA COM PAR");
      dados.userOpt = 0;
      dados.optPar++;
    }
    
    printf("\n");

    //pega o valor gerado para o pc e o digitado pelo usuario e verifica quem é o vencedor
    valUser = verificao();
    valPc = valorPc();
    printf("\n Valor usuario: %d \n Valor PC: %d", valUser, valPc);
    resultado = vencedor(valUser, valPc);
    verficVenc(resultado);

    //exibe dados na tela
    printf("\n");
    printf("\n --------------------------------------------");
    printf("\n");
    printf("\n VITORIAS DO USUÁRIO");
    printf("\n");
    printf("\n Vitorias com usuário sendo IMPAR: %d", dados.userImp);
    printf("\n Vitorias com usuário sendo PAR: %d", dados.userPar);  

    //salva os dados atualizados
    file = fopen("Dados.txt", "w");
    fprintf(file, "\n%d", dados.vitPar);
    fprintf(file, "\n%d", dados.vitImp);
    fprintf(file, "\n%d", dados.vitUser);
    fprintf(file, "\n%d", dados.userPar);
    fprintf(file, "\n%d", dados.userImp);
    fprintf(file, "\n%d", dados.userOpt);
    fprintf(file, "\n%d", dados.optImp);
    fprintf(file, "\n%d", dados.optPar);
    fprintf(file, "\n%d", dados.partidas);
    fclose(file);

    play = repetir();
    system("clear");
  }
  printf("\n Saindo...");
  return 0;
}