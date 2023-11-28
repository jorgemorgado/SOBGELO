//---------------------------------------------------------------------------------------------
//                                        E R R O R . C
//
//                       Função de tratamento de erros do jogo Sob-Gelo
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                            Funções externas da fonte ERROR.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: exit_with_error        │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Abandonar o jogo Spb-Gelo e retornar ao DOS devido à ocorrência de um erro ║
// ║               fatal. A função repõe o modo de video e de teclado originais, exibe a      ║
// ║               respectiva mensagem de erro e finalmente regressa ao DOS.                  ║
// ║                                                                                          ║
// ║ Parâmetros:   nErrorCode é o código do erro que ocorreu. Consulte no manual do           ║
// ║               utilizador a lista completa dos códigos de erro.                           ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void exit_with_error( char *msgError )
{
    k_reset();                                            // Repõe a rotina de teclado original
    v_mode( 0x03 );                                          // Repõe o modo de texto - 80 x 25

    perror( msgError );                                  // Exibe a respectiva mensagem de erro
    exit( EXIT_FAILURE );                                // Regressa ao DOS - abandona com erro
}
