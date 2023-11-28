//---------------------------------------------------------------------------------------------
//                                     L I T P A D L E . C
//
//                     Funções relacionadas com o movimento do paddle pequeno
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                         Funções externas da fonte LITPADLE.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: move_lpad              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Movimenta do paddle pequeno dependendo do valor de nDir.                   ║
// ║               Se nDir = 0 então o paddle pequeno desloca-se para a direita.              ║
// ║               Se nDir = 1 então o paddle pequeno desloca-se para a esquerda.             ║
// ║                                                                                          ║
// ║ Parâmetros:   nDir é o sentido do paddle pequeno: se 0 então o paddle será deslocado     ║
// ║               para a direita; se 1 será deslocado para a esquerda.                       ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void move_lpad( int nDir )
{
    switch( nDir )
    {
        case 0:                                          // Move o little paddle para a DIREITA
            v_putlitpad( ++LitPaddle.adr, LitPaddle.ptr );   // Desloca um pixel para a direita
            v_vlinelitpad( LitPaddle.adr + 319 );                              // Limpa o rasto
            break;
        case 1:                                         // Move o little paddle para a ESQUERDA
            v_putlitpad( --LitPaddle.adr, LitPaddle.ptr );  // Desloca um pixel para a esquerda
            v_vlinelitpad( LitPaddle.adr + 338 );                              // Limpa o rasto
            break;
    }
}
