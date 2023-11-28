//---------------------------------------------------------------------------------------------
//                                       S O B - G E L O
//
//                  Módulo principal - é aqui que tudo começa e tudo acaba...
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                                Livrarias utilizadas (header)
//---------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <io.h>
#include <string.h>
#include <time.h>


//---------------------------------------------------------------------------------------------
//                                                                                    Interface
//---------------------------------------------------------------------------------------------
#include "global.h"                                      // Arquivo header de variáveis globais
#include "execute.c"                                    // Procedimentos principais do programa
#include "video.c"                                         // Rotinas de video para o modo MCGA
#include "sound.c"                                                    // Rotinas de som do jogo
#include "keyboard.c"                                                     // Rotinas de teclado
#include "error.c"                                             // Rotina de tratamento de erros
#include "miscelan.c"                                      // Várias funções com várias tarefas
#include "menu.c"                                      // Menu: JOGAR, Adversário, TABELA, SAIR
#include "scores.c"                                            // Tudo sobre a tabela de scores
#include "play.c"                                           // Início do jogo propriamente dito
#include "levels.c"                 // Funções relacionadas com o nível de dificuladade do jogo
#include "rs232.c"                                          // Rotinas relacionadas com a RS232
#include "syncronz.c"                                  // Rotinas para sincronizar os dois PC's
#include "ball.c"                                  // Rotinas da bola (movimento, choque, etc.)
#include "ballpc2.c"                 // Rotinas da bola mas para comunicação entre os dois PC's
#include "bigpadle.c"                               // Funções relacionadas com o paddle grande
#include "litpadle.c"                              // Funções relacionadas com o paddle pequeno
#include "computer.c"           // Funções do paddle pequeno quando o adversário é o computador
#include "player2.c"  // Funções do paddle pequeno quando adversário é outra pessoa no mesmo PC


//---------------------------------------------------------------------------------------------
//                                                                                  Função main
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: main (Sob-Gelo)        │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Função principal (main) do jogo Sob-Gelo.                                  ║
// ║               É aqui que tudo começa e acaba.                                            ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void main( void )
{
    init_sob_gelo();                                                       // Inicializa o jogo
    menu_sob_gelo();                                                // Menu principal de opções
    exit_sob_gelo();                                               // Termina e regressa ao DOS
}
