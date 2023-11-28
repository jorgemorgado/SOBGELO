//---------------------------------------------------------------------------------------------
//                                     M I S C E L A N . C
//
//                     Miscelanea de funções utilizadas no jogo "SUB-GELO"
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                         Funções externas da fonte MISCELAN.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: load_letters           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Inicializa o apontador para a imagem das letras, números, etc. (enfim,     ║
// ║               todos os caracters necessários e utilizados no jogo).                      ║
// ║               Consulte o manual do programador.                                          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void load_letters( void )
{
   ptrLetters = getfile( "CHARS.BIN", O_BINARY );           // Carrega as letras, números, etc.
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: load_name              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Inicializa o apontador para a imagem do nome do jogo.                      ║
// ║               Consulte o manual do programador.                                          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void load_name( void )
{
   ptrName = getfile( "SOB-GELO.BIN", O_BINARY );     // Carrega a imagem "SOB-GELO" na memória
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: back_letters           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Processa o rodapé no início do jogo. Esta função é chamada de vários       ║
// ║               locais, como por exemplo da fonte MENU.C ou ainda da fonte SCORES.C        ║
// ║               Daí que ela possui variáveis estácticas (que conservam os seus valores),   ║
// ║               para que o rodapé seja exibido contínuamente.                              ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void back_letters( void )
{
    static int i, j, nIdx = 0, k = 0;                                             // Contadores
    static BYTE far *ptrX, far *ptrY;               // Apontadores para o ecran (memória video)
    static BYTE *text = "SPOOLER^SOB=GELO?^AUTOR:^JORGE^ALEXANDRE^CABRITA^MORGADO^>>>>^SOB=GELO\
^=^MADE^IN^BARREIRO^=^PORTUGAL^>>>>>^";

    ptrX = ( BYTE far * )MK_FP( VIDEO, 61440 );  // Define apontador para última linha do ecran

    for( j = 0; j < 319; j++, ptrX++ )                                        // Este pedaço de
    {                                                                         // código copia a
        ptrY = ptrX;                                                          // última linha
                                                                              // do ecran, e
        for( i = 0; i < 8; i++, ptrY += 320 )                                 // desloca-a um
        *ptrY = *( ptrY + 1 );                                                // pixel para a
    }                                                                         // esquerda

    for( i = 0; i < 8; i++ )                         // Escreve nova coluna de pixels do rodapé
        v_pixel(319, 192 + i, *( ptrLetters + ( ( *(text + nIdx) - 48 ) * 64 ) + i * 8 + k ));

    if( ++k > 7 )
    {
        k = 0;

        if( ++nIdx > 106 )            // 106 é o número de caracteres do rodapé - quando chegar
            nIdx = 0;                 // ao final, volta a zero, e recomeça tudo outra vez
    }

    delay( 5 );                                                      // Até os miúdos podem ler
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: cls_game_area          │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Limpa a área do jogo, isto é, toda a zona de movimento quer da bola, quer  ║
// ║               dos paddles grande e pequeno.                                              ║
// ║               Esta função é chamada, fundamentalmente quando inicia ou termina um jogo,  ║
// ║               ou quando uma bola não é defendida e ainda existem bolas para jogar.       ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void cls_game_area( void )
{
    int nX, nY, nSize;

    for( nY = 0; nY < 11; nY++ )
        v_hline( 89, nY, 230, 0 );

    for( nX = 89, nSize = 142; nY < 190; nX--, nY++, nSize += 2 )
    {
        v_hline( nX,   nY, nX + nSize, 0 );
        v_hline( nX, ++nY, nX + nSize, 0 );
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: cls_bottom_line        │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Limpa a última linha do ecran. Note que é nesta linha que aparecem a maior ║
// ║               parte das mensagens do jogo.                                               ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void cls_bottom_line( void )
{
    v_clswin( 0, 192, 319, 199, 0 );              // Limpa toda a zona do rodapé (última linha)
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: write_str              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Escreve a partir da posição (nX,nY) a frase apontada por ptrStr.           ║
// ║                                                                                          ║
// ║ Parâmetros:   nX e nY são as cooredenadas (em pixels) da frase a escrever;               ║
// ║               ptrStr é a frase a escrever - como se saber, em linguagem C, as strings    ║
// ║               são definidas por um apontador para um conjunto de caracteres.             ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void write_str( int nX, int nY, char *ptrStr )
{
    while( *ptrStr )             // Enquanto não apanhar o caracter fim de string ('\0' = NULL)
    {
        v_putimage( nX, nY, 8, 8, ptrLetters + ( *ptrStr - 48 ) * 64 );    // Escreve uma letra
        ptrStr++;                                            // Avança para o próximo caractere
        nX += 8;                                     // Avança 8 pixels (largura de cada letra)
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: getfile                │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Abre e carrega na memória um ficheiro do tipo nType. Em caso de erro exibe ║
// ║               a respectiva mensagem.                                                     ║
// ║                                                                                          ║
// ║ Parâmetros:   ptrFileName é o nome do ficheiro a abrir e carregar em memória;            ║
// ║               nType é o tipo do ficheiro a abrir. Por exemplo, se deseja abrir um        ║
// ║               ficheiro do tipo binário então nType deve ser igual a O_BINARY; do mesmo   ║
// ║               modo se deseja abrir um ficheiro de texto nType deve ser O_TEXT (veja      ║
// ║               a livraria FCNTL.H para mais informações).                                 ║
// ║                                                                                          ║
// ║ Retorna:      A função retorna um apontador para o início da informação do ficheiro      ║
// ║               carregado em memória.                                                      ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
BYTE *getfile( char *ptrFileName, const int nType )
{
    int nHandle;                                                          // Handle do ficheiro
    WORD nFlen;                                                      // Comprimento do ficheiro
    BYTE *ptrBuf;                           // Apontador para o conteúdo do ficheiro em memória

    if( ( nHandle = open( ptrFileName, nType ) ) < 0 )        // Se ocorreu um erro na abertura
        exit_with_error( ptrFileName );                     // Informa o erro e regressa ao DOS

    nFlen = filelength( nHandle );                           // Obtém o comprimento do ficheiro

    if( ( ptrBuf = ( BYTE * )malloc( nFlen ) ) == NULL )// Se houve erro na alocação de memória
        exit_with_error( "Memória" );                       // Informa o erro e regressa ao DOS

    read( nHandle, ptrBuf, nFlen );          // Lê o ficheiro para a memória (apontador ptrBuf)
    close( nHandle );                                                       // Fecha o ficheiro

    return ( ptrBuf );          // Retorna um apontador para o início da informação do ficheiro
}
