//---------------------------------------------------------------------------------------------
//                                       L E V E L S . C
//
//             Todas as funções relacionadas com os níveis de dificuldade do jogo
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                             Funções locais da fonte LEVELS.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dificulty_box          │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta é a função que processa o quadro da "Dificuldade". Este quadro é      ║
// ║               exibido no início de cada jogo, mas somente quando o adversário escolhido  ║
// ║               é o computador. É nesta fase que o utilizador poderá definir o Q.I. do     ║
// ║               computador, isto é, se ele deve ser bom ou mau a apanhar as bolas.         ║
// ║                                                                                          ║
// ║ Parâmetros:   *ptrDificulty é um apontador para endereço de memória que contém o actual  ║
// ║               valor de QI. O facto de utilizarmos um apontador, prende-se com a          ║
// ║               necessidade de retornar (re-actualizar) o valor apontado.                  ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dificulty_box( BYTE *ptrDificulty )
{
    if( KEY_UP && *ptrDificulty > 0 )                                           // Arrow-key up
        (*ptrDificulty)--;
    else if( KEY_DOWN && *ptrDificulty < 47 )                                 // Arrow-key down
        (*ptrDificulty)++;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: velocity_box           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta é a função que processa o quadro da "Velocidade". Este quadro é       ║
// ║               exibido no início de cada jogo. É aqui que o utilizador poderá definir a   ║
// ║               velocidade do jogo.                                                        ║
// ║                                                                                          ║
// ║ Parâmetros:   *ptrVelocity é um apontador para endereço de memória que contém o actual   ║
// ║               valor da velocidade. O facto de utilizarmos um apontador, prende-se com a  ║
// ║               necessidade de retornar (re-actualizar) o valor apontado.                  ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void velocity_box( BYTE *ptrVelocity )
{
    if( *ptrVelocity > 0 && ( KEY_LEFT || ( KEY_Z && nOpponent == 1 ) ) )     // Arrow-key left
        (*ptrVelocity)--;
    else if( *ptrVelocity < 73 && ( KEY_RIGHT || ( KEY_C && nOpponent == 1 ) ) )// Arrkey right
        (*ptrVelocity)++;
}


//---------------------------------------------------------------------------------------------
//                                                           Funções externas da fonte LEVELS.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: load_levels            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Inicializa os apontador para a imagem dos quadros "Velocidade" e           ║
// ║               "Dificuldade". Estas imagens são utilizadas quando um novo jogo vai        ║
// ║               começar - aí o utilizador deve escolher a dificuldade do jogo (caso tenha  ║
// ║               como adversário o computador), e escolher a velocidade do jogo.            ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void load_levels( void )
{
    ptrDifiBox  = getfile( "LEVELS.BIN", O_BINARY );  // Carrega e aponta p/ imagem dos quadros
    ptrVeloBox  = ptrDifiBox + 8856;          // Aponta para a imagem do quadro da "Velocidade"
    ptrDifiCurs = ptrDifiBox + 12420;        // Aponta para o cursor do quadro da "Dificuldade"
    ptrVeloCurs = ptrDifiBox + 12490;         // Aponta para o cursor do quadro da "Velocidade"
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: define_level           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Definir o nível de dificuldade do jogo. É nesta função que se define os    ║
// ║               parâmeteros para o nível de dificuldade e para a velocidade do jogo.       ║
// ║                                                                                          ║
// ║ Parâmetros:   *ptrVelo é um apontador para a velocidade (o valor contido neste endereço  ║
// ║               será retornado);                                                           ║
// ║               *ptrDifi é um apontador para o nível de dificuldade do computador, isto é, ║
// ║               um valor que determina se o computador joga melhor ou pior (o valor        ║
// ║               contido neste endereço será retornado).                                    ║
// ║                                                                                          ║
// ║ Retorna:      A função retorna um valor booleano que tem o seguinte significado:         ║
// ║               TRUE  = significa que tudo se precessou normalmente - jogo deve continuar  ║
// ║               FALSE = significa que o utilizador abandonou a função com <ESCAPE>         ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
BOOLEAN define_level( BYTE *ptrVelo, BYTE *ptrDifi )
{
    int nVeloY = ( !nOpponent ) ? 130 : 84;           // Coordenada Y do quadro da "Velocidade"
    static BYTE nDifi = 24;               // Parâmetero para o nível da dificuldade - [ 0, 47 ]
    static BYTE nVelo = 37;                         // Parâmetero para a velocidade - [ 0, 73 ]

    while( KEYPRESSED );                             // Aguarda qua qualquer tecla seja liberta

    if( !nOpponent )                                        // Se o adversário for o computador
    {
        v_putimage( 106,  40, 108, 82, ptrDifiBox );            // Exibe o quadro "Dificuldade"
        v_putimage( 192, 56 + nDifi, 10, 7, ptrDifiCurs );     // Exibe cursor do potenciómetro
    }

    v_putimage( 106, nVeloY, 108, 33, ptrVeloBox );              // Exibe o quadro "Velocidade"
    v_putimage( 119 + nVelo, nVeloY + 14,  8, 9, ptrVeloCurs );// Exibe cursor do potenciómetro

    do
    {
        if( KEYPRESSED )                                   // Se alguma tecla foi pressionda...
        {
            if( KEY_ESCAPE )                                              // Se teclou <ESCAPE>
                return( FALSE );                                        // Abandona agora mesmo

            if( !nOpponent )                                // Se o adversário for o computador
            {
                dificulty_box( &nDifi );                      // Escolher a dificuldade do jogo
                v_putimage(192, 56 + nDifi, 10, 7, ptrDifiCurs);// Cursor potenciómetro Dificul
            }

            velocity_box( &nVelo );                            // Escolher a velocidade do jogo
            v_putimage( 119 + nVelo, nVeloY + 14,  8, 9, ptrVeloCurs );//Cursor potencióm. Velo

            delay( 3 );                       // Atrasa pois a rotina de teclado é muito rápida
        }
    }
    while( !KEY_ENTER );                      // Ciclo até que seja pressionada a tecla <ENTER>

    cls_game_area();                                     // Limpa o ecran antes de se ir embora

    *ptrVelo = MAX_DELAY - nVelo / 10;                   // Define a velocidade (delay) do jogo
    *ptrDifi = -nDifi / 2 + 85;                          // Define a inteligência do computador

    return( TRUE );                             // Retorna TRUE - tudo se precessou normalmente
}
