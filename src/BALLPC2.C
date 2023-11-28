//---------------------------------------------------------------------------------------------
//                                      B A L L P C 2 . C
//
//        Funções de comunicação entre os dois PC's para processar o movimento da bola
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                            Funções locais da fonte BALLPC2.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: process_data           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Processa os dados enviados pelo PC 2, isto é, avalia o BYTE recebido e     ║
// ║               executa uma determinada tarefa (ou não) de acordo com o seu valor.         ║
// ║                                                                                          ║
// ║ Parâmetros:   cData é o BYTE recebido do PC2.                                            ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void process_data( BYTE cData )
{
    switch( cData )
    {
        case 0:                                             // Se recebeu um valor entre 0 e 5,
        case 1:                                             // significa que o PC 2 está a
        case 2:                                             // informar a direcção que a bola
        case 3:                                             // vai tomar. Este PC deve então
        case 4:                                             // transformar este valor visto que
        case 5:                                             // a bola vai descer e não subir
        {
            BOOLEAN dirOddity = ODD( Ball.dir );//Salva se a direcção anterior era ímpar ou par

            Ball.dir = cData + ( ODD( cData ) ? 5 : 7 );         // Transforma direcção da bola

            if( dirOddity && !ODD( Ball.dir ) )// Se direcção anterior era ímpar e a actual não
                Ball.dir++;                                              // Soma 1 e fica ímpar
            else if( !dirOddity && ODD( Ball.dir ) )//Se direcção anterior par e actual é ímpar
                Ball.dir--;                                             // Subtrai 1 e fica par

            break;
        }

        case BALL_LOSTED:                    // Recebeu BALL_LOSTED significa que o PC 2 perdeu
            v_putball(Ball.adr,PutDimX[MAX_PLANS-1],ImgDimY[MAX_PLANS-1],adrBall[MAX_PLANS-1]);
            s_lost_ball();                                         // Emite som - perdeu a bola

            Status.player1++;          // Atribui mais um ponto para o jogado 1 (paddle grande)
            Status.balls--;                                        // Menos uma bola para jogar

            game_status();  // Actualiza o status do jogo (nº de bolas para jogar e pontuações)

            if( Status.balls )                             // Se ainda existem bolas para jogar
            {
                cls_game_area();                         // Limpa o ecran antes de se ir embora
                start_lpad();       // Re-inicializa as variáveis da bola para o paddle pequeno
                init_paddles();                     // Coloca os paddles nas posições correctas
            }

            break;

        case 21:                                        // Se recebeu um valor entre 21 e 28
        case 22:                                        // quer dizer que recebeu um valor
        case 23:                                        // correspondente à velocidade (delay).
        case 24:                                        // Isto significa que o utilizador no
        case 25:                                        // PC2, abortou o seu jogo e voltou a
        case 26:                                        // entrar, ou seja, neste momento o PC2
        case 27:                                        // está "desesperadamente" a tentar
        case 28:                                        // sincronozar a velocidade do jogo.
            UserAborted = TRUE;     // Aborta - tem de voltar ao menu pois não devia estar aqui
            Status.balls = 0;     // 0 bolas para jogar - uma das condições para voltar ao menu
            break;

        default:
            break;
    }
}


//---------------------------------------------------------------------------------------------
//                                                          Funções externas da fonte BALLPC2.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: report_pc2             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Envia um byte para o outro PC, via RS232. Depois de a função enviar um     ║
// ║               valor para o PC 2, espera que este lhe retorne o mesmo valor e termina.    ║
// ║               Este método é necessário para que este PC tenha a certeza de o PC 2        ║
// ║               recebeu o dados correctamente.                                             ║
// ║               No entanto, a função poderá terminar antes de executar o processo referido ║
// ║               acima, caso a variável UserAborted seja colocada a TRUE - lembre-se que    ║
// ║               esta variável será TRUE quando o utilizador interromper a comunicação.     ║
// ║                                                                                          ║
// ║ Parâmetros:   cData é o byte a enviar para o outro PC.                                   ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void report_pc2( BYTE cData )
{
    do
    {
        do
        {
            write_RS232( cData );                                // Envia a direcção para o PC2
            wait_for_data();                            // Agurda que o PC2 envie o que recebeu
        }
        while( !UserAborted && TimeOut );        // Repete se ainda não abortou ou fim de tempo
    }
    while( !UserAborted && read_RS232() != cData );            // Verifica se o PC2 recebeu bem
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: receive_pc2            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Recebe dados do PC 2 e encaminha-os para a função process_data(), para     ║
// ║               que sejam processados. Depois de recebidos os dados e caso a comunicação   ║
// ║               não tenha sido abortada pelo utilizador, a função enviará o que recebeu    ║
// ║               de volta para o PC 2. Este método é necessário para que o PC 2 tenha a     ║
// ║               certeza de que os dados que enviou foram bem recebidos deste lado.         ║
// ║               Se tudo correu bem, então o PC 2 começará a enviar caracteres de SYN e     ║
// ║               a função termina.                                                          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void receive_pc2( void )
{
    do
    {
        do
            wait_for_data();                                    // Espera que o PC2 envie dados
            while( !UserAborted && TimeOut );    // Repete se ainda não abortou ou fim de tempo

            if( !UserAborted )                     // Se o utilizador não abortou a comunicação
            {
                BYTE cData = read_RS232();                             // Lê os dados recebidos

                process_data( cData );                           // Processa os dados recebidos

                if( !UserAborted )                         // Se o utilizador ainda não abortou
                {
                    do
                    {
                        write_RS232( cData );        // Envia aquilo que rebeceu para confirmar
                        wait_for_data();                   // Espera por uma confirmação de OK!
                    }
                    while(!UserAborted && TimeOut);//Repete se ainda não abortou ou fim de tempo
                }
            }
    }
    while( !UserAborted && read_RS232() != SYN );       // Repete se ainda não há "sincronismo"
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: move_ball_2            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Função que determina o movimento da bola quanado os adversários estão em   ║
// ║               PC's separados. Isto é, quando a variável nOpponent é igual a 2. A função  ║
// ║               encarrega-se ainda de verificar se a bola terá chegado ao topo ou ao fundo ║
// ║               do ecran (pois pode ter sido defendida).                                   ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void move_ball_2( void )
{
    eval_balldir();                                   // Desloca a bola na direcção de Ball.dir

    if( SENDER )
    // Se sou emissor então a bola vai para cima
    {
        if( Ball.adr < 4160 )
        // Verifica se a bola atingiu o topo do ecran
        {
            SENDER = FALSE;                 // Passa a ser o receptor porque vai receber a bola

            ball_goes_dn();                      // Actualiza as variáveis da bola - vai descer
            receive_pc2();                                    // Recebe a nova direcção da bola
        }
        else
        // Senão, então a bola ainda vai a subir
        {
            v_putball( Ball.adr, PutDimX[Ball.plan], ImgDimY[Ball.plan], adrBall[Ball.plan]);
            write_RS232( SYN );                              // Envia caracteres de sincronismo
        }
    }
    else
    // Senão, então sou o receptor, logo a bola vem a descer
    {
        if( Ball.adr > 56000 )
        // Verifica se a bola atingiu a base
        {
            SENDER = TRUE;                     // Passa a ser o receptor pois vai enviar a bola
            bp_hitball();                           // Verifica se o big paddle defendeu a bola

            if( Status.balls )     // Se ainda há bolas para jogar, i.e., se o jogador defendeu
                report_pc2( Ball.dir );                        // Envia a nova direcção da bola
            }
        else
            // Senão, então a bola ainda vem a descer
            v_putball( Ball.adr, PutDimX[Ball.plan], ImgDimY[Ball.plan], adrBall[Ball.plan]);
    }

    if( Status.balls )
    // Se ainda há bolas para jogar
        ball_hit_wall(); // Verifica se a bola bateu numa das bancadas - se sim muda a direcção
    else
    // Senão, então o jogo terminou
    {
        if( !UserAborted )                                 // Se o utilizador ainda não abortou
        {
            while( KEYPRESSED )            // Aguarda - enquanto estiver a pressionar uma tecla
                if( SENDER )                    // Se sou o emissor (fui eu quem perdeu a bola)
                    write_RS232( SYN );                      // Envia caracteres de sincronismo

            while( !KEYPRESSED )            // Aguarda - enquanto não for pressionada uma tecla
                if( SENDER )                      // Se sou emissor (fui eu quem perdeu a bola)
                   write_RS232( SYN );                       // Envia caracteres de sincronismo
        }

        cls_game_area();                                 // Limpa o ecran antes de se ir embora
    }
}
