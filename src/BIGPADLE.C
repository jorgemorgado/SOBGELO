//---------------------------------------------------------------------------------------------
//                                     B I G P A D L E . C
//
//                     Funções relacionadas com o movimento do paddle grande
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                           Funções locais da fonte BIGPADLE.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: move_bigpaddle         │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Movimenta do paddle grande dependendo do valor de nDir.                    ║
// ║               Se nDir = 0 então o paddle grande desloca-se para a direita.               ║
// ║               Se nDir = 1 então o paddle grande desloca-se para a esquerda.              ║
// ║                                                                                          ║
// ║ Parâmetros:   nDir é o sentido do paddle grande: se 0 então o paddle será deslocado para ║
// ║               a direita; se 1 será deslocado para a esquerda.                            ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void move_bpad( int nDir )
{
    switch( nDir )
    {
        case 0:                                             // Move o big paddle para a DIREITA
            v_putbigpad( BigPaddle.adr += 2, BigPaddle.ptr );  // Desloca 2 pixels para direita
            v_vlinebigpad( BigPaddle.adr + 319 );                              // Limpa o rasto
            v_vlinebigpad( BigPaddle.adr + 318 );                              // Limpa o rasto
            break;
        case 1:                                            // Move o big paddle para a ESQUERDA
            v_putbigpad( BigPaddle.adr -= 2, BigPaddle.ptr ); // Desloca 2 pixels para esquerda
            v_vlinebigpad( BigPaddle.adr + 350 );                              // Limpa o rasto
            v_vlinebigpad( BigPaddle.adr + 351 );                              // Limpa o rasto
            break;
    }
}


//---------------------------------------------------------------------------------------------
//                                                         Funções externas da fonte BIGPADLE.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: palyer_1               │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Processa o movimento do paddle grande atrvés do teclado. É esta função que ║
// ║               verifica se o big paddle pode andar (isto é, se ainda não bateu nas        ║
// ║               bancadas esquerda ou direita), e depois desloca o paddle se o utilizador   ║
// ║               estiver a carregar nas teclas "arrow-key left" ou "arrow-key right".       ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ║                                                                                          ║
// ║ NOTA: O paddle só será deslocado se o utilizador estiver a carregar nas teclas. Se tal   ║
// ║       não suceder o paddle grande permanecerá estático (daí o nome desta função ser      ║
// ║       easy - fácil).                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void player_1( void )
{
    if( KEY_RIGHT && BigPaddle.adr < 58205 )
        move_bpad( 0 );                                         // Move o paddle para a DIREITA
    else if( KEY_LEFT && BigPaddle.adr > 57925 )
        move_bpad( 1 );                                        // Move o paddle para a ESQUERDA
}
