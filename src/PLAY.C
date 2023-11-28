//---------------------------------------------------------------------------------------------
//                                         P L A Y . C
//
//                   Início da jogo propriamente dito - agora vamos ter acção
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                            Variáveis globais da fonte PLAY.C
//---------------------------------------------------------------------------------------------
static BYTE nComputerQI;   // Inteligência do computador - define o nível de jogo do computador
static BYTE nDelay;                   // Velocidade - quanto mais pequeno, mais rápido é o jogo


//---------------------------------------------------------------------------------------------
//                                                               Funções locais da fonte PLAY.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: init_status_line       │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Inicializa a linha de status do jogo, ou seja, o número de bolas a jogar,  ║
// ║               o atraso (delay), jogadores, etc.                                          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void init_status_line( void )
{
    Status.balls   = 7;                              // Inicialmente existem 7 bolas para jogar
    Status.player1 = 0;                            // Pontuação do "player 1" no início do jogo
    Status.player2 = 0;                            // Pontuação do "player 2" no início do jogo

    cls_bottom_line();                            // Limpa toda a zona do rodapé (última linha)
    write_str( 132, 192, "BOLAS:" );

    if( !nOpponent )                                          // Se o adversário é o computador
    {
        write_str(   8, 192, ":COMPUTADOR" );
        write_str( 248, 192, "JOGADOR:" );
    }
    else                                            // Senão, então o adversário é outra pessoa
    {
        write_str(   8, 192, ":JOGADOR^2" );
        write_str( 232, 192, "JOGADOR^1:" );
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: game_paused            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta é a função que interrompe o jogo em caso de "pausa" (tecla <P>).      ║
// ║               O jogo permanecerá interrompido até que a tecla <P> seja novamente         ║
// ║               pressionada.                                                               ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void game_paused( void )
{
    v_paloff( 1 );                            // Escurece as cores da palette apenas até metade

    while(  KEY_PAUSE );                          // Aguarda até que a tecla <P> esteja liberta
    while( !KEY_PAUSE );                      // Aguarda até que <P> seja novamente pressionado
    while(  KEY_PAUSE );                          // Aguarda até que a tecla <P> esteja liberta

    v_palon( 1 );     // Repõe as cores originais da palette (o ecran estava metade escurecido)
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: start_game             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Início do jogo. BOA SORTE!!!                                               ║
// ║                                                                                          ║
// ║ Parâmetros:   (*player_1)() é um apontador para a função que processa o movimento do     ║
// ║               paddles grande. Por exemplo, as hipóteses podem ser:                       ║
// ║                 - se (*player_1)() aponta para a função easy_player_1() então o paddle   ║
// ║                   grande só se movimentará quando enquanto o jogador carregar nas teclas;║
// ║               (*opponente)() é um apontador para a função que processa o movimento do    ║
// ║               paddles do adversário (paddle pequeno). Assim, algumas hipóteses são:      ║
// ║                 - se (*opponent)() aponta para a função computer_1() então o adversário  ║
// ║                   é o computador no nível de dificuldade 1;                              ║
// ║                 - se (*opponent)() aponta para a função player_2() então o adversário    ║
// ║                   escolhido é o jogador 2 no mesmo computador do jogador 1;              ║
// ║               (*move_ball)() é um apontador para a função que processa o movimento da    ║
// ║               bola. As hipóteses podem ser:                                              ║
// ║                 - se (*move_ball)() aponta para a função move_ball_01() então a          ║
// ║                   variável nOpponent é 0 ou 1, isto é, o adversário é o computador ou    ║
// ║                   outro jogador no mesmo PC;                                             ║
// ║                 - se (*move_ball)() aponta para a função move_ball_2() significa que a   ║
// ║                   variável nOpponent é igual a 2, ou seja, que o adversário é outro      ║
// ║                   jogador localizado noutro PC.                                          ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void start_game( void (*player_1)(void), void (*opponent)(void), void(*move_ball)(void))
{
    if( ( nOpponent != 2 ) || ( nOpponent == 2 && SENDER ) )
       wait_for_SPACE();                        // Aguarda que seja pressionada a tecla <SPACE>

    while( Status.balls )          // Loop até final do jogo - enquanto houver bolas para jogar
        if( KEY_ESCAPE )                                          // Carregou na tecla <ESCAPE>
            break;                                                           // Abandona o jogo
        else if( KEY_PAUSE )                                   // Carregou na tecla <P> = PAUSE
            game_paused();                                      // Rotina que interrompe o jogo
        else
        {
            delay( nDelay );                                   // Menos delay = mais velocidade

            (*player_1)();                              // Rotina que movimenta o paddle grande
            (*opponent)();                             // Rotina que movimenta o paddle pequeno
            (*move_ball)();                                      // Rotina que movimenta a bola
        }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: choose_player          │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta é a função que inicia o realmente o jogo, dependendo do adversário    ║
// ║               préviamente escolhido pelo utilizador.                                     ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void choose_player( void )
{
    void player_1( void );             // Função que processa o movimento o paddle do jogador 1
    void computer( void );            // Função que processa o movimento o paddle do computador
    void player_2( void );             // Função que processa o movimento o paddle do jogador 2
    void player_2_pc2( void ); // Função que processa o movimento do paddle do jogador 2 no PC2
    void move_ball_01( void );         // Função que movimenta a bola quando nOppenent é 0 ou 1
    void move_ball_2( void );               // Função que movimenta a bola quando nOppenent é 2

    if( !define_level( &nDelay, &nComputerQI ) )                        // Define nível do jogo
        return;                                    // Retorna pois o utilizador teclou <ESCAPE>

    if( nOpponent == 2 )                      // Se o adversário é um jogador noutro computador
    {
        init_RS232();                                                     // Inicializa a RS232

        if( !sincronize() )                                            // Sincronização com PC2
            return;                 // Ocorreu um erro durante a sincronização com PC2 - aborta
    }

    if( ( nOpponent != 2 && random( 2 ) ) || ( nOpponent == 2 && SENDER ) )
        start_bpad();                         // Começa o paddle grande - exibe a bola em baixo
    else
        start_lpad();                         // Começa o paddle pequeno - exibe a bola em cima

    init_paddles();            // Coloca os paddles nas posições correctas e actualiza o status
    init_status_line();                                // Informação inicial da linha de status
    game_status();          // Actualiza o status do jogo (nº de bolas para jogar e pontuações)

    switch( nOpponent )                 // Verifica quem é o adversário antes de começar o jogo
    {
        case 0:                                                  // O adversário é o computador
            start_game( player_1, computer, move_ball_01 );                   // Início do jogo

            if(!Status.balls && Status.player1 > Status.player2)// jogo acabou E jogador ganhou
                get_a_highscore( Status.player1 * (MAX_DELAY-nDelay+1) * nComputerQI );// Score

            break;
        case 1:                                     // O adversário é outra pessoa no mesmo PC
            start_game( player_1, player_2, move_ball_01 );                   // Início do jogo
            break;
        case 2:                                        // O adversário é outra pessoa noutro PC
            if( SENDER )                                                 // Se a bola sai minha
               report_pc2( Ball.dir );         // Informa o PC2 qual a direcção inicial da bola
            else                                // Senão, então a bola sai do adversário no PC2
               receive_pc2();                     // Recebe a direcção da bola enviada pelo PC2

            start_game( player_1, player_2_pc2, move_ball_2 );                // Início do jogo
            break;
    }
}


//---------------------------------------------------------------------------------------------
//                                                             Funções externas da fonte PLAY.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: load_play              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Carrega as imagens dos paddles grande (big) e pequeno (little).            ║
// ║               As imagens são carregadas em memória e podem ser acedidas através dos      ║
// ║               apontadores ptrBigPaddle para o paddle grande e ptrLitPaddle para o paddle ║
// ║               pequeno.                                                                   ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void load_play( void )
{
    randomize();      // Inicializa o gerador de números (o jogo possui parâmeteros aleatórios)

    BigPaddle.ptr = getfile( "PADDLES.BIN", O_BINARY );        // Carrega os paddles em memória
    LitPaddle.ptr = BigPaddle.ptr + 240;                        // Aponta para o paddle pequeno
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: play_sob_gelo          │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Prepara o ínicio do jogo propriamente dito. Antes do jogo começar, esta    ║
// ║               função executa várias tarefas, como por exemplo limpar o ecran, limpar o   ║
// ║               rodapé, etc.                                                               ║
// ║               Chamo a atenção para o facto de a função antes de limpar o rodapé, salvar  ║
// ║               o seu estado actual, para que quando regresse ao menu reponha o rodapé no  ║
// ║               ponto onde tinha deixado.                                                  ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void play_sob_gelo( void )
{
    BYTE *ptrBuf;                            // Apontador para salvar a imagem actual do rodapé

    if( ( ptrBuf = ( BYTE * )malloc( 2560 ) ) == NULL ) // Se houve erro na alocação de memória
        exit_with_error( "Memória" );                   // Informa o erro e regressa para o DOS

    v_getwin( 0, 192, 319, 199, ptrBuf );                    // Salva a imagem actual do rodapé

    v_curtain( 100, 0, 219, 177, 0, 15 ); // Limpa a zona central do ecran com efeito "cortina"
    v_clswin( 0, 192, 319, 199, 0 );              // Limpa toda a zona do rodapé (última linha)

    choose_player();                      // Inicia o jogo de acordo com o adversário escolhido

    v_putimage( 0, 192, 320, 8, ptrBuf );         // O jogo terminou - repõe a imagem do rodapé
    free( ptrBuf );                // Liberta o espaço alocado para a imagem anterior do rodapé
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: wait_for_SPACE         │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Espera que o utilizador pressione a tecla <SPACE>. É utilizada para dar    ║
// ║               início ao jogo. No entanto, a função aceita também a tecla <ESCAPE>, de    ║
// ║               modo que se esta tecla for pressionada o jogo abortará depois de começar.  ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void wait_for_SPACE( void )
{
    while( KEY_SPACE );                 // Aguarda - enquanto não for libertada a tecla <SPACE>
    while( !( KEY_ESCAPE || KEY_SPACE ) );  // Enquanto não premidas teclas <SPACE> ou <ESCAPE>
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: init_paddles           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta função é chamada antes de se começar a jogar uma bola, ou seja,       ║
// ║               quando um novo jogo começa, ou quando se perde uma bola mas ainda existem  ║
// ║               bolas para jogar. A função coloca os paddles grande e pequeno nas posições ║
// ║               iniciais.                                                                  ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void init_paddles( void )
{
    BigPaddle.adr = 58065;                     // O big paddle começa em baixo no meio do ecran
    v_putbigpad( BigPaddle.adr, BigPaddle.ptr );                          // Exibe o big paddle

    if( nOpponent != 2 )            // Só exibe o little paddle se o adversário não está no PC2
    {
        LitPaddle.adr = 3031;                // O little paddle começa em cima no meio do ecran
        v_putlitpad( LitPaddle.adr, LitPaddle.ptr );                   // Exibe o little paddle
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: game_status            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Actualiza o status do jogo, isto é, pontuações dos jogadores e número de   ║
// ║               bolas ainda para jogar.                                                    ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void game_status( void )
{
    char cNrBalls[ 2 ];       // Array do tipo char que aponta o valor da variável Status.balls
    char cScorePl1[ 2 ];    // Array do tipo char que aponta o valor da variável Status.player1
    char cScorePl2[ 2 ];    // Array do tipo char que aponta o valor da variável Status.player2

    itoa( Status.balls,   cNrBalls,  10 );              // Converte Status.balls para caractere
    itoa( Status.player1, cScorePl1, 10 );            // Converte Status.player1 para caractere
    itoa( Status.player2, cScorePl2, 10 );            // Converte Status.player2 para caractere

    write_str( 180, 192, cNrBalls );              // Escreve o número de bolas ainda para jogar
    write_str( 312, 192, cScorePl1 );                       // Escreve a pontuação do jogador 1
    write_str(   0, 192, cScorePl2 );                       // Escreve a pontuação do jogador 2
}
