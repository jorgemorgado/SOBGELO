//---------------------------------------------------------------------------------------------
//                                         B A L L . C
//
//                 Todas as funções relacionadas com a bola e o seu movimento
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                                                   Constantes
//---------------------------------------------------------------------------------------------
#define MAX_PLANS       6                                 // Número máximo de planos existentes
#define MAX_DIRS        12                                        // Número máximo de direcções
#define MAX_LPP         27        // Número máximo de linhas que cada bola se desloca por plano
#define MAX_LPP_FAST    14     // Nº máx. de linhas por plano nas direcções rápidas (4,5,10,11)


//---------------------------------------------------------------------------------------------
//                                                            Variáveis globais da fonte BALL.C
//---------------------------------------------------------------------------------------------
// Deslocamentos (offsets) das 6 bolas dentro do ficheiro BALL.BIN (veja Manual do Programador)
static BYTE *adrBall[ MAX_PLANS ];

// Dimensão X das 6 bolas para utilizar como parâmetero quando chamamos a função v_putball()
static int PutDimX[ MAX_PLANS ] = {  9,  8,  7,  6,  5, 4 };

// Dimensão X e Y (em pixels) das 6 bolas
static int ImgDimX[ MAX_PLANS ] = { 18, 16, 14, 12, 10, 8 };
static int ImgDimY[ MAX_PLANS ] = {  7,  7,  7,  7,  7, 6 };

// Valores a somar para limpar as 1ª e 2º linhas por baixo da bola quando esta vai para cima
static int Cls1BtLin[ MAX_PLANS ] = { 1920, 1920, 1920, 1920, 1600, 1280 };
static int Cls2BtLin[ MAX_PLANS ] = { 1600, 1600, 1600, 1600, 1280,  960 };

// Valores a somar para limpar 1ª e 2º colunas à direita da bola quando esta vai para esquerda
static int Cls1RtLin[ MAX_PLANS ] = { 17, 15, 13, 11,  9, 7 };
static int Cls2RtLin[ MAX_PLANS ] = { 16, 14, 12, 10,  8, 6 };

// Número de pixels a avançar para ver se bola a vai bater na bancada direita
static int ReadPxlRt[ MAX_PLANS ] = { 20, 18, 16, 14, 12, 10 };

// É necessário somar estes valores devido a um bug dos deslocamentos 7 e 9
static int Cls2RtDir[ MAX_DIRS ] = { 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0 };


//---------------------------------------------------------------------------------------------
//                                                               Funções locais da fonte BALL.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_0                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 0 - para cima +/- 30°.                              ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_0( void )
{
    v_hlineball( Ball.adr + Cls1BtLin[ Ball.plan ], ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr,                          ImgDimY[ Ball.plan ] );
    v_vlineball( Ball.adr + 1,                      ImgDimY[ Ball.plan ] );

    if( ++Ball.line == MAX_LPP )
    {
        Ball.line = 0;
        Ball.plan++;
    }

    Ball.adr -= 318;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_1                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 1 - para cima +/- 120°.                             ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_1( void )
{
    v_hlineball( Ball.adr + Cls1BtLin[ Ball.plan ], ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr + Cls1RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );
    v_vlineball( Ball.adr + Cls2RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );

    if( ++Ball.line == MAX_LPP )
    {
        Ball.line = 0;
        Ball.plan++;
        Ball.adr -= 320;
    }
    else
        Ball.adr -=322;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_2                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 2 - para cima +/- 45°.                              ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_2( void )
{
    v_hlineball( Ball.adr + Cls1BtLin[ Ball.plan ], ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr,                          ImgDimY[ Ball.plan ] );

    if( ++Ball.line == MAX_LPP )
    {
        Ball.line = 0;
        v_vlineball( Ball.adr + Cls1RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );
        Ball.plan++;
    }

    Ball.adr -= 319;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_3                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 3 - para cima +/- 135°.                             ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_3( void )
{
    v_hlineball( Ball.adr + Cls1BtLin[ Ball.plan ], ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr + Cls1RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );

    if( ++Ball.line == MAX_LPP )
    {
        Ball.line = 0;
        v_vlineball( Ball.adr, ImgDimY[ Ball.plan ] );
        Ball.plan++;
        Ball.adr -= 319;
    }
    else
        Ball.adr -= 321;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_4                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 4 - para cima +/- 60°.                              ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_4( void )
{
    v_hlineball( Ball.adr + Cls1BtLin[ Ball.plan ], ImgDimX[ Ball.plan ] );
    v_hlineball( Ball.adr + Cls2BtLin[ Ball.plan ], ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr,                          ImgDimY[ Ball.plan ] );

    if( ++Ball.line > MAX_LPP_FAST )  // Nº de linhas por plano (este é um deslocamento rápido)
    {
        Ball.line = 0;
        v_vlineball( Ball.adr + Cls1RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );
        Ball.plan++;
    }

    Ball.adr -= 639;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_5                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 5 - para cima +/- 150°.                             ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_5( void )
{
    v_hlineball( Ball.adr + Cls1BtLin[ Ball.plan ], ImgDimX[ Ball.plan ] );
    v_hlineball( Ball.adr + Cls2BtLin[ Ball.plan ], ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr + Cls1RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );

    if( ++Ball.line > MAX_LPP_FAST )  // Nº de linhas por plano (este é um deslocamento rápido)
    {
        Ball.line = 0;
        v_vlineball( Ball.adr, ImgDimY[ Ball.plan ] );
        Ball.plan++;
        Ball.adr -= 639;
    }
    else
        Ball.adr -= 641;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_6                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 6 - para baixo +/- 120°.                            ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_6( void )
{
    v_hlineball( Ball.adr,     ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr,     ImgDimY[ Ball.plan ] );
    v_vlineball( Ball.adr + 1, ImgDimY[ Ball.plan ] );

    if( ++Ball.line == MAX_LPP )
    {
        Ball.line = 0;
        Ball.plan--;
    }

    Ball.adr += 322;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_7                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 7 - para baixo +/- 30°.                             ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_7( void )
{
    v_hlineball( Ball.adr,                          ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr + Cls1RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );
    v_vlineball( Ball.adr + Cls2RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );

    if( ++Ball.line == MAX_LPP )
    {
        Ball.line = 0;
        Ball.plan--;
        Ball.adr += 316;
    }
    else
        Ball.adr += 318;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_8                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 8 - para baixo +/- 135°.                            ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_8( void )
{
    v_hlineball( Ball.adr, ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr, ImgDimY[ Ball.plan ] );

    if( ++Ball.line == MAX_LPP )
    {
        Ball.line = 0;
        Ball.plan--;
    }

    Ball.adr += 321;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_9                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 9 - para baixo +/- 45°.                             ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_9( void )
{
    v_hlineball( Ball.adr,                          ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr + Cls1RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );

    if( ++Ball.line == MAX_LPP )
    {
        Ball.line = 0;
        Ball.plan--;
        Ball.adr += 317;
    }
    else
        Ball.adr += 319;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_10                 │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 10 - para baixo +/- 150°.                           ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_10( void )
{
    v_hlineball( Ball.adr,       ImgDimX[ Ball.plan ] );
    v_hlineball( Ball.adr + 320, ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr,       ImgDimY[ Ball.plan ] );

    if( ++Ball.line > MAX_LPP_FAST )  // Nº de linhas por plano (este é um deslocamento rápido)
    {
        Ball.line = 0;
        Ball.plan--;
    }

    Ball.adr += 641;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: dir_11                 │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Executa o deslocamento 11 - para baixo +/- 60°.                            ║
// ║               Consulte o manual do programador para mais detalhe.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void dir_11( void )
{
    v_hlineball( Ball.adr,                          ImgDimX[ Ball.plan ] );
    v_hlineball( Ball.adr + 320,                    ImgDimX[ Ball.plan ] );
    v_vlineball( Ball.adr + Cls1RtLin[ Ball.plan ], ImgDimY[ Ball.plan ] );

    if( ++Ball.line > MAX_LPP_FAST )  // Nº de linhas por plano (este é um deslocamento rápido)
    {
        Ball.line = 0;
        Ball.plan--;
        Ball.adr += 637;
    }
    else
        Ball.adr += 639;
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: lost_ball              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta é a função é chamada sempre que um jogador não consegue defender a    ║
// ║               bola, ou seja, sempre que se perde uma bola. A função repõe no ecran a     ║
// ║               bola não defendida e em seguida emite o som correspondente a perder uma    ║
// ║               bola. Depois a função actualiza o status, ou seja, atribui um ponto ao     ║
// ║               jogador que ganhou a bola e decrementa a variável Status.balls que guarda  ║
// ║               o número de bolas ainda para jogar. Finalmente aguarda por uma tecla.      ║
// ║                                                                                          ║
// ║ Parâmetros:   adrVideo é o endereço do ecran onde a bola deve ser colocada;              ║
// ║               nPlan é o plano da bola exibida, ou seja, se foi o jogador 1 quem perdeu a ║
// ║               bola, então o plano deve ser 0. Se o foi o jogador 2 então o plano deve    ║
// ║               ser o 6.                                                                   ║
// ║               Note ainda que a função limpa o ecran antes de terminar, visto que se um   ║
// ║               jogador perdeu a bola, então vai jogar outra bola (se ainda houver bolas   ║
// ║               para jogar), ou vai regressar ao menu (se já não houver bolas para jogar). ║
// ║                                                                                          ║
// ║ Retorna:      A função retorna um valor booleano:                                        ║
// ║               - 0 se já não existem mais bolas para jogar;                               ║
// ║               - 1 se ainda existem mais bolas para jogar;                                ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static int lost_ball( WORD adrVideo, int nPlan )
{
    v_putball( adrVideo, PutDimX[ nPlan ], ImgDimY[ nPlan ], adrBall[ nPlan ] );  // Exibe bola
    s_lost_ball();                                                 // Emite som - perdeu a bola

    if( nPlan )                        // Se o plano não é 0, então quem perdeu foi o jogador 2
        Status.player1++;              // Atribui mais um ponto para o jogado 1 (paddle grande)
    else                           // Senão, então o plano é 0 logo quem perdeu foi o jogador 1
        Status.player2++;            // Atribui mais um ponto para o jogador 2 (paddle pequeno)

    Status.balls--;                                                // Menos uma bola para jogar
    game_status();          // Actualiza o status do jogo (nº de bolas para jogar e pontuações)

    if( nOpponent == 2 )                                         // Se o adversário está no PC2
        report_pc2( BALL_LOSTED );     // Informa o PC2 que a bola não foi defendida deste lado

    if( nOpponent != 2 || Status.balls )              // Caso especial para o adversário no PC2
    {
        while( KEYPRESSED );               // Aguarda - enquanto estiver a pressionar uma tecla
        while( !KEYPRESSED );               // Aguarda - enquanto não for pressionada uma tecla

        cls_game_area();                                 // Limpa o ecran antes de se ir embora
    }

    return( ( Status.balls > 0 ) ? TRUE : FALSE );   // Retorna .T. se existem bolas para jogar
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: ball_goes_up           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta é a função que re-inicializa as variáveis da bola cada vez que ela    ║
// ║               atinge o big paddle e vai voltar para cima.                                ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void ball_goes_up( void )
{
    Ball.adr  = 55680 + ( Ball.adr % 320 ) + Cls2RtDir[ Ball.dir ];    // Bola na posição certa
    Ball.line = 0;                             // Re-inicializa Ball.line para voltar para cima
    Ball.plan = 0;                                // A bola vai subir logo Ball.plan deve ser 0

    s_ball_hit_paddle();                                        // Som - a bola bateu no paddle
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: lp_hitball             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Verifica se o little paddle defendeu a bola e age em conformidade. Assim   ║
// ║               se a bola foi defendida a função verifica com que zona do paddle foi feita ║
// ║               a defesa e determina a direcção que a bola irá todar no regresso. Se o     ║
// ║               little paddle não defendeu a bola é chamada uma outra função que se        ║
// ║               encarrega de processar a morte do little paddle.                           ║
// ║               É ainda nesta função que se define o movimento da bola em caso de teste.   ║
// ║               Se a directiva (para o compilador) TEST = 1 for definida a bola nunca será ║
// ║               perdida mesmo que não seja apanhada pelo little paddle.                    ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ║                                                                                          ║
// ║ NOTA: No fundo esta função executa exactamente o mesmo trabalho que a função bp_hitball, ║
// ║       só que em relação ao little paddle. Neste caso, vem de baixo e caso seja defendida ║
// ║       irá voltar para baixo. Como tal, grande parte das verificações e atribuições, são  ║
// ║       executadas ao contrário.                                                           ║
// ║       Consulte o manual do programador sobre os deslocamentos descendentes da bola.      ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void lp_hitball( void )
{
#ifndef TEST

    BYTE *ptrBallLf = ( BYTE * )MK_FP( VIDEO, Ball.adr - 320 );         // Lê um pixel do ecran
    BYTE *ptrBallRt = ( BYTE * )MK_FP( VIDEO, Ball.adr - 313 );         // Lê um pixel do ecran

    if( *ptrBallLf && *ptrBallRt )
    // A bola bateu no meio do little paddle - retorna com o mesmo ângulo
    {
        ball_goes_dn();              // A bola vai para baixo - re-inicializa as suas variáveis
        Ball.dir += 6;                              // Muda a direcção da bola: (MAX_PLANS - 1)
    }
    else if( *ptrBallLf )
    // A bola bateu do lado esquerdo do big paddle
    {
        ball_goes_dn();              // A bola vai para baixo - re-inicializa as suas variáveis

        if( ODD( Ball.dir ) )                                        // A bola vinha da direita
            Ball.dir += ( Ball.dir == 1 ) ? 10 : 4;                          // Muda a direcção
        else                                                        // A bola vinha da esquerda
            Ball.dir += ( Ball.dir == 4 ) ?  2 : 8;                          // Muda a direcção
    }
    else if( *ptrBallRt )
    // A bola bateu do lado direito do big paddle
    {
        ball_goes_dn();              // A bola vai para baixo - re-inicializa as suas variáveis

        if( ODD( Ball.dir ) )                                        // A bola vinha da direita
            Ball.dir += ( Ball.dir == 5 ) ? 2 : 8;                           // Muda a direcção
        else                                                        // A bola vinha da esquerda
            Ball.dir += ( Ball.dir == 0 ) ? 10 : 4;                          // Muda a direcção
    }
    else if( lost_ball( Ball.adr, MAX_PLANS - 1 ) )
    // A bola não bateu no little paddle - o computador/jogador2/jogador2pc2 perdeu
    {
        start_lpad();               // Re-inicializa as variáveis da bola para o paddle pequeno
        init_paddles();                             // Coloca os paddles nas posições correctas
        wait_for_SPACE();             // Aguarda - enquanto não for pressionada a tecla <SPACE>
    }

#else                  // TEST=1  Directiva para o compilador para testar os movimentos da bola

    ball_goes_dn();                  // A bola vai para baixo - re-inicializa as suas variáveis
    Ball.dir = ( ODD( Ball.dir ) ) ? random( 3 ) * 2 + 7 : random( 3 ) * 2 + 6;// Muda direcção

#endif
}


//---------------------------------------------------------------------------------------------
//                                                             Funções externas da fonte BALL.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: ball_goes_dn           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta é a função que re-inicializa as variáveis da bola cada vez que ela    ║
// ║               atinge o little paddle e vai voltar para baixo.                            ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void ball_goes_dn( void )
{
    Ball.adr  = 4160 + ( Ball.adr % 320 );                        // Coloca bola na linha certa
    Ball.line = 0;                            // Re-inicializa Ball.line para voltar para baixo
    Ball.plan = MAX_PLANS - 1;                   // A bola vai descer logo Ball.plan deve ser 5

    s_ball_hit_paddle();                                        // Som - a bola bateu no paddle
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: bp_hitball             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Verifica se o big paddle defendeu a bola e age em conformidade. Assim se   ║
// ║               a bola foi defendida a função verifica com que zona do paddle foi feita a  ║
// ║               defesa e determina a direcção que a bola irá todar no regresso. Se o big   ║
// ║               paddle não defendeu a bola é chamada uma outra função que se encarrega de  ║
// ║               processar a morte o big paddle.                                            ║
// ║               É ainda nesta função que se define o movimento da bola em caso de teste.   ║
// ║               Se a directiva (para o compilador) TEST = 1 for definida a bola nunca será ║
// ║               perdida mesmo que não seja apanhada pelo big paddle.                       ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ║                                                                                          ║
// ║ NOTA: Neste caso existe um erro, ou seja, quando a bola vem do lado direito com um       ║
// ║       deslocamento igual a 7 ou 9, as suas duas colunas direitas não são apagadas quando ║
// ║       bate no big paddle. Como tal é necessário apagá-las de outra forma - à unha.  O    ║
// ║       método utilizado é pouco versátil mas funciona eficazmente e, acima de tudo foi o  ║
// ║       mais rápido que encontrei. É assim: no início foi definido um array chamado        ║
// ║       Cls2RtDir[ 12 ], que significa "limpa o ecran 2 colunas à direita da bola          ║
// ║       dependendo da direcção".  Como se pode ver o array tem 12 posições, uma vez que,   ║
// ║       existem 12 direcções (deslocamentos) diferentes.  Apesar de tudo, o ecran não é    ║
// ║       limpo no verdadeiro sentido da palavra.  A técnica utilizada é outra: a próxima    ║
// ║       bola é colocada 2 colunas mais à direita, de tal forma que ela irá limpar o rasto  ║
// ║       deixado pela bola anterior.  Ora, para deslocar uma imagem qualquer 2 pixels à     ║
// ║       direita basta somar 2 ao seu endereço de ecran (memória video).  Como este         ║
// ║       problema só ocorre nos deslocamentos 7 e 9, vem que tais posições no array         ║
// ║       Cls2RtDir[] contém o valor 2 (todas as outras estão a zero).  Deste modo quando a  ║
// ║       bola se deslocar nas direcções 7 e 9 o seu endereço será incrementado de 2 ao      ║
// ║       bater no big paddle; nos outros casos o incremento será 0 (zero). PERCEBIDO ???    ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void bp_hitball( void )
{
#ifndef TEST

    BYTE *ptrBallLf = ( BYTE * )MK_FP( VIDEO, Ball.adr + 2240 );        // Lê um pixel do ecran
    BYTE *ptrBallRt = ( BYTE * )MK_FP( VIDEO, Ball.adr + 2258 );        // Lê um pixel do ecran

    if( *ptrBallLf && *ptrBallRt )
    // A bola bateu no meio do big paddle - retorna com o mesmo ângulo
    {
        ball_goes_up();               // A bola vai para cima - re-inicializa as suas variáveis
        Ball.dir -= 6;                              // Muda a direcção da bola: (MAX_PLANS - 1)
    }
    else if( *ptrBallLf )
    // A bola bateu do lado esquerdo do big paddle
    {
        ball_goes_up();               // A bola vai para cima - re-inicializa as suas variáveis

        if( ODD( Ball.dir ) )                                     // Se a bola vinha da direita
            Ball.dir -= ( Ball.dir == 11 ) ? 10 : 4;                         // Muda a direcção
        else                                                     // Se a bola vinha da esquerda
            Ball.dir -= ( Ball.dir ==  6 ) ?  2 : 8;                         // Muda a direcção
    }
    else if( *ptrBallRt )
    // A bola bateu do lado direito do big paddle
    {
        ball_goes_up();               // A bola vai para cima - re-inicializa as suas variáveis

        if( ODD( Ball.dir ) )                                     // Se a bola vinha da direita
            Ball.dir -= ( Ball.dir ==  7 ) ? 2 :  8;                         // Muda a direcção
        else                                                     // Se a bola vinha da esquerda
            Ball.dir -= ( Ball.dir == 10 ) ? 10 : 4;                         // Muda a direcção
    }
    else if( lost_ball( Ball.adr + Cls2RtDir[ Ball.dir ], 0 ) )
    // A bola não bateu no big paddle - o jogador 1 perdeu
    {
        start_bpad();                // Re-inicializa as variáveis da bola para o paddle grande
        init_paddles();                             // Coloca os paddles nas posições correctas
        wait_for_SPACE();             // Aguarda - enquanto não for pressionada a tecla <SPACE>
    }

#else                  // TEST=1  Directiva para o compilador para testar os movimentos da bola

    ball_goes_up();                   // A bola vai para cima - re-inicializa as suas variáveis
    Ball.dir = ( ODD( Ball.dir ) ) ? random( 3 ) * 2 + 1 : random( 3 ) * 2;  // Muda a direcção

#endif
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: load_ball              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Inicializa o array adrBall. Este array tem 6 posições, sendo que cada uma  ║
// ║               é o endereço da imagem de uma bola.                                        ║
// ║               Ou seja, como se sabe existem 6 imagens da bola (desde a maior, até à mais ║
// ║               pequena). Cada uma dessas imagens pode ser acedida através de um apontador ║
// ║               para a memória. Assim, por forma a tornar esse acesso o mais rápido        ║
// ║               possível, inicialmente foi definido um array de apontadores com 6 (seis)   ║
// ║               posições. Por exemplo, para exibir a imagem da bola 4, basta mandar exibir ║
// ║               a imagem apontada por adrBall[ 3 ] (lembre-se que em linguagem C os arrays ║
// ║               iniciam em zero).                                                          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void load_ball( void )
{
    int i;                                                           // Contador para ciclo for
    int Ball[ MAX_PLANS ] = { 0, 126, 238, 336, 420, 490 };              // Dimensões das bolas

    adrBall[ 0 ] = getfile( "BALLS.BIN", O_BINARY );                // Carrega imagem das bolas

    for( i = 1; i < MAX_PLANS; i++ )                              // Define o endereço efectivo
        adrBall[ i ] = adrBall[ 0 ] + Ball[ i ];                   // para cada uma das 7 bolas
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: start_bpad             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta função inicializa as variáveis da bola. É chamada em duas situações:  ║
// ║               - quando um novo jogo vai começar e a bola sai do jogador 1 (big paddle);  ║
// ║               - quando um jogador 1 (big paddle) sofre um golo.                          ║
// ║               Já agora, convém explicar o que é isto de inicalizar as variáveis da bola. ║
// ║               No que refere à bola, existem quatro variáveis que lhe estão directamente  ║
// ║               relacionadas. São elas, Ball.adr (endreço da bola no ecran - memória       ║
// ║               video), Ball.dir (direcção da bola = [0,11]), Ball.plan (plano da bola =   ║
// ║               = [0,6]), e finalmente Ball.line (número da linha dentro do plano actual). ║
// ║               Quando um jogo começa ou o jogador 1 (big paddle) sofre um golo, a bola    ║
// ║               deve ser colocada sobre o paddle do jogador 1, já que é dele que a bola    ║
// ║               sai ou foi ele que sofreu um golo. Assim todas estas variáveis devem ser   ║
// ║               reinicializadas (consulte o Manual do Programador para mais informaçoes).  ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void start_bpad( void )
{
    Ball.plan = 0;                                                  // O plano inicial é o zero
    Ball.adr  = 55831;                               // A bola começa no meio do ecran em baixo
    Ball.dir  = random( 4 ) + 2;        // A bola começa com uma direcção aleatória (para cima)
    Ball.line = 0;                       // Inicializa variável estática no início de cada bola

    v_putball( Ball.adr, PutDimX[ Ball.plan ], ImgDimY[ Ball.plan ], adrBall[ Ball.plan ] );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: start_lpad             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta função inicializa as variáveis da bola. É chamada em duas situações:  ║
// ║               - quando um novo jogo vai começar e a bola sai do jogador 2 (lit. paddle); ║
// ║               - quando um jogador 2 (little paddle) sofre um golo.                       ║
// ║               Já agora, convém explicar o que é isto de inicalizar as variáveis da bola. ║
// ║               No que refere à bola, existem quatro variáveis que lhe estão directamente  ║
// ║               relacionadas. São elas, Ball.adr (endreço da bola no ecran - memória       ║
// ║               video), Ball.dir (direcção da bola = [0,11]), Ball.plan (plano da bola =   ║
// ║               = [0,6]), e finalmente Ball.line (número da linha dentro do plano actual). ║
// ║               Quando um jogo começa ou o jogador 2 (little paddle) sofre um golo, a bola ║
// ║               deve ser colocada sobre o paddle do jogador 2, já que é dele que a bola    ║
// ║               sai ou foi ele que sofreu um golo. Assim todas estas variáveis devem ser   ║
// ║               reinicializadas (consulte o Manual do Programador para mais informaçoes).  ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void start_lpad( void )
{
    Ball.plan = MAX_PLANS - 1;                                     // O plano inicial é o cinco
    Ball.adr  = 4316;                                 // A bola começa no meio do ecran em cima
    Ball.dir  = random( 6 ) + 6;       // A bola começa com uma direcção aleatória (para baixo)
    Ball.line = 0;                       // Inicializa variável estática no início de cada bola

    v_putball( Ball.adr, PutDimX[ Ball.plan ], ImgDimY[ Ball.plan ], adrBall[ Ball.plan ] );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: eval_balldir           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Avalia a direção da bola e desloca-a nesse sentido. A bola pode            ║
// ║               deslocar-se em 12 direcções (sentidos) diferentes.                         ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void eval_balldir( void )
{
    switch( Ball.dir )
    {
        case  0:  dir_0(); break;                      // Deslocamento  0 - para cima  +/-  30°
        case  1:  dir_1(); break;                      // Deslocamento  1 - para cima  +/- 120°
        case  2:  dir_2(); break;                      // Deslocamento  2 - para cima  +/-  45°
        case  3:  dir_3(); break;                      // Deslocamento  3 - para cima  +/- 135°
        case  4:  dir_4(); break;                      // Deslocamento  4 - para cima  +/-  60°
        case  5:  dir_5(); break;                      // Deslocamento  5 - para cima  +/- 150°
        case  6:  dir_6(); break;                      // Deslocamento  6 - para baixo +/- 120°
        case  7:  dir_7(); break;                      // Deslocamento  7 - para baixo +/-  30°
        case  8:  dir_8(); break;                      // Deslocamento  8 - para baixo +/- 135°
        case  9:  dir_9(); break;                      // Deslocamento  9 - para baixo +/-  45°
        case 10: dir_10(); break;                      // Deslocamento 10 - para baixo +/- 150°
        case 11: dir_11(); break;                      // Deslocamento 11 - para baixo +/-  60°
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: ball_hit_wall          │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Verifica se a bola atingiu alguma das bancadas esquerda ou direita. Se sim ║
// ║               então a direcção da bola será alterada de acordo com a direcção anterior.  ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void ball_hit_wall( void )
{
    if( ODD( Ball.dir ) )
    // Se Ball.dir é ímpar então a bola vinha da direita
    {
        if( *( BYTE * )MK_FP( VIDEO, Ball.adr - 3 ) )
        // Lê um pixel do ecran à esquerda da bola
        {
            Ball.dir--;                                                     // Muda de direcção
            s_ball_hit_wall();                                     // Bateu na bancada esquerda
        }
    }
    else if( *( BYTE * )MK_FP( VIDEO, Ball.adr + ReadPxlRt[ Ball.plan ] ) )
    // Senão, a bola vinha da esquerda, logo lê um pixel do ecran à direita da bola
    {
        Ball.dir++;                                                         // Muda de direcção
        s_ball_hit_wall();                                          // Bateu na bancada direita
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: move_ball_01           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Função que determina o movimento da bola quanado os adversários são ou o   ║
// ║               computador, ou outro jogador no mesmo. Isto é, quando a variável nOpponent ║
// ║               é igual a 0 ou 1. A função encarrega-se ainda de verificar se a bola terá  ║
// ║               chegado ao topo ou ao fundo do ecran (pois pode ter sido defendida).       ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void move_ball_01( void )
{
    eval_balldir();                                   // Desloca a bola na direcção de Ball.dir

    if( Ball.adr > 56000 )
    // Bateu na base - vamos verificar se o big paddle defende a bola
        bp_hitball();
    else if( Ball.adr < 4160 )
    // Bateu no topo - vamos verificar se o little paddle defende a bola
        lp_hitball();
    else
    // Caso contrário coloca a bola na sua nova posição
        v_putball(Ball.adr, PutDimX[ Ball.plan ], ImgDimY[ Ball.plan ], adrBall[ Ball.plan ]);

    ball_hit_wall();     // Verifica se a bola bateu numa das bancadas - se sim muda a direcção
}
