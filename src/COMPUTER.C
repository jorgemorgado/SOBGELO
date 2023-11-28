//---------------------------------------------------------------------------------------------
//                                  C O M P U T E R . C
//
//        Funções relacionadas com o paddle pequeno quando o adversário é o computador
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                         Funções externas da fonte COMPUTER.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: computer_1             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Processa o movimento do paddle pequeno quando este é controlado pelo       ║
// ║               computador. A função processa tando a defesa como o ataque e em alguns     ║
// ║               casos insere um factor aleatório.                                          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ║                                                                                          ║
// ║ NOTA: Neste nível o computador falha a maioria das bolas com deslocamento 1.             ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void computer( void )
{
    if( Ball.dir > 5 )
    // Se a bola vai para baixo move o paddle pequeno para o meio
    {
        if( LitPaddle.adr > 3032 )
        // Se o paddle está do lado direito do ecran
            move_lpad( ( LitPaddle.adr > 2970 ) ? 1 : 2 );
        else if( LitPaddle.adr < 3032 )
        // Se o paddle está do lado esquerdo do ecran
            move_lpad( ( LitPaddle.adr < 3092 ) ? 0 : 2 );
    }
    else if( Ball.dir == 0 && Ball.adr / 320 > nComputerQI )
    // Supostamente a bola vai para o lado esquerdo do ecran
        move_lpad( ( LitPaddle.adr > 2970 ) ? 1 : 2 );
    else if( Ball.dir == 1 && Ball.adr / 320 > 100 )
    // Supostamente a bola vai para o lado direito do ecran
        move_lpad( ( LitPaddle.adr < 3092 ) ? 0 : 2 );
    else if( Ball.adr % 320 > ( LitPaddle.adr - 2 + random( 3 ) * 4 ) % 320 )
    //Acompanha a bola e introduz um factor aleatório no ataque: 5=meio; -2=esquerda; 8=direita
        move_lpad( ( LitPaddle.adr < 3092 ) ? 0 : 2 );
    else
    // Acompanha a bola e simplesmente defende-a
        move_lpad( ( LitPaddle.adr > 2970 ) ? 1 : 2 );
}
