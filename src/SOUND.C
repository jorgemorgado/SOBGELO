//---------------------------------------------------------------------------------------------
//                                        S O U N D . C
//
//                  Todas as funções relacionadas o som do jogo Sob-Gelo
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                            Funções externas da fonte SOUND.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: s_ball_hit_wall        │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Este é o som que se  houve quando a bola bate numa bancada.                ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void s_ball_hit_wall( void )
{
    sound( 500 );                                        // Emite um som de frequência = 400 Hz
    delay( 10 );                                                      // Durante 7 milisegundos
    nosound();                                                                // Cala o speaker
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: s_ball_hit_paddle      │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Este é o som que se houve quando a bola bate num dos paddles.              ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void s_ball_hit_paddle( void )
{
    sound( 400 );                                        // Emite um som de frequência = 400 Hz
    delay( 7 );                                                       // Durante 7 milisegundos
    nosound();                                                                // Cala o speaker
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: s_lost_ball            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Este é o som que houve quando a bola não é defendida por um dos paddles.   ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void s_lost_ball( void )
{
    int i;

    for( i = 60; i > 0; i-- )                                 // Ciclo - sound effect à maneira
    {
        sound( 200 * i );                                // Emite um som de frequência = 400 Hz
        delay( 7 );                                                   // Durante 7 milisegundos
        nosound();                                                            // Cala o speaker
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: s_out_of_range         │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Este é o som que houve quando o utilizador ultrapassa os limites da string ║
// ║               a introduzir. Por exemplo, quando está a inserir o seu nome no scores e    ║
// ║               tenta introduzir ou apagar para além dos limites do espaço para o nome.    ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void s_out_of_range( void )
{
    sound( 500 );                                        // Emite um som de frequência = 500 Hz
    delay( 30 );                                                     // Durante 30 milisegundos
    nosound();                                                                // Cala o speaker
}
