//---------------------------------------------------------------------------------------------
//                                   P L A Y E R 2 . C
//
// Funções relacionadas com o paddle pequeno quando o adversário é o outra pessoa no mesmo PC
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                          Funções externas da fonte PLAYER2.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: player_2               │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Processa o movimento do paddle pequeno quando este é controlado por        ║
// ║               outra pessoa a jogar no mesmo PC.                                          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void player_2( void )
{
    if( KEY_C && LitPaddle.adr < 3092 )  // Se está carregar na tecla <C> e o paddle pode andar
        move_lpad( 0 );                                 // Move o paddle pequeno para a direita
    else if( KEY_Z && LitPaddle.adr > 2970 )//Se está carregar na tecla <Z> e paddle pode andar
        move_lpad( 1 );                                // Move o paddle pequeno para a esquerda
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: player_2_pc2           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Não faz absolutamente nada. Lembre-se que quando o adversário é outra      ║
// ║               pessoa noutro PC não é exibido o paddle pequeno. A função é necessária     ║
// ║               apenas porque é chamada pela função start_game() na fonte PLAY.C.          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void player_2_pc2( void )
{
}
