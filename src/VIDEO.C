//---------------------------------------------------------------------------------------------
//                                        V I D E O . C
//
//Várias rotinas para uso do video no modo MCGA (Multi Color Graphics Adapter - 320x200 pixels)
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                            Funções externas da fonte VIDEO.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_fadein               │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Faz o fade in de uma imagem de (nH x nV) para o ecran. O fade da imagem é  ║
// ║               feito pixel por pixel, numa sequência definida pelo array FadeSeq.         ║
// ║                                                                                          ║
// ║ Parâmetros:   nH e nV são as dimensões da imagem (largura x altura);                     ║
// ║               adr é o endereço da memória video (ecran) onde colocar a imagem;           ║
// ║               ptrImg é o apontador para a imagem;                                        ║
// ║               FadeSeq é um array de nH valores e é utilizado para exibir a imagem no     ║
// ║               ecran. Por exemplo, se FadeSeq é { 0, 1, 2, ..., nH-1, nH } então a imagem ║
// ║               será exibida com um efeito de "abertura". Outra possibilidade, será por    ║
// ║               exemplo, FadeSeq ser um array de valores aleatórios, isto é, { 0, 4, 1, 6, ║
// ║               nH, 12, 5, ... }: neste caso a imagem será exibida com um efeito aleatório.║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_fadein( int nH, int nV, WORD adr, char *ptrImg, int *FadeSeq )
{
    BYTE far *pointer;
    char x, y, j, t;

    pointer = ( BYTE far * )MK_FP( VIDEO, adr );

    for( x = 0; x < nH; x++ )
    {
        y = FadeSeq[ x ];

        for( j = 0; j < nV; j++, y = ++y % nH )
        {
            *( pointer + j * 320 + FadeSeq[ y ] ) = *( ptrImg + j * nH + FadeSeq[ y ] );

            for( t = 0; t < 100; t++ );                                    // Provoca uma pausa
        }
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_imgup                │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Move uma imagem apontada por ptrImg, com tamanho (nH,nV), colocada em      ║
// ║               (nX,nY), nMoves para cima, deixando a cor bColor.                          ║
// ║                                                                                          ║
// ║ Parâmetros:   nX e nY são as coordenadas do ecran onde está colocada a imagem a mover;   ║
// ║               nH e nV são as dimensões da imagem (largura x altura);                     ║
// ║               nMoves é o número de pixels que a imagem deve ser deslocada para cima;     ║
// ║               ptrImg é o apontador para a imagem;                                        ║
// ║               bColor é a cor do rasto deixado pela imagem quando está a subir.           ║
// ║                                                                                          ║
// ║ NOTA: Poderiamos ter utilizado a função v_winup() para obter o mesmo efeito. No entanto, ║
// ║       como possuimos a imagem que pretendemos deslocar está carregada em memória, é      ║
// ║       preferível utilizar esta função uma vez que o deslocamento será bastante mais      ║
// ║       rápido.                                                                            ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_imgup( int nX, int nY, int nH, int nV, int nMoves, BYTE *ptrImg, BYTE bColor )
{
    while( nMoves-- > 0 )
    {
        v_hline( nX, nY + nV, nX + nH, bColor );
        v_putimage( nX, --nY, nH, nV, ptrImg );
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_winup                │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Move uma janela com tamanho (nH,nV), colocada em (nX,nY), nMoves para      ║
// ║               cima, deixando a cor bColor.                                               ║
// ║                                                                                          ║
// ║ Parâmetros:   nX e nY são as coordenadas do ecran onde está colocada a janela a mover;   ║
// ║               nH e nV são as dimensões da janela (largura x altura);                     ║
// ║               nMoves é o número de pixels que a janela deve ser deslocada para cima;     ║
// ║               ptrImg é o apontador para a imagem;                                        ║
// ║               bColor é a cor do rasto deixado pela janela quando está a subir.           ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_winup( int nX, int nY, int nH, int nV, int nMoves, BYTE bColor )
{
    BYTE far *ptrVideo;
    int i, j;

    while( nMoves-- > 0 )
    {
        ptrVideo = ( BYTE far * )MK_FP( VIDEO, nX + 320 * --nY );

        for( j = 0; j < nV; j++, ptrVideo += 320 )
            for( i = 0; i < nH; i++ )
                *( ptrVideo + i ) = *( ptrVideo + i + 320 );

        v_hline( nX, nY + nV, nX + nH, bColor );
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_clswin               │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Limpa uma janela definida por (nH1,nV1,nH2,nV2) na cor bColor.             ║
// ║                                                                                          ║
// ║ Parâmetros:   nH1 é a coordenada X do canto superior esquerdo da janela;                 ║
// ║               nV1 é a coordenada Y do canto superior esquerdo da janela;                 ║
// ║               nH2 é a coordenada X do canto inferior direito da janela;                  ║
// ║               nV2 é a coordenada Y do canto inferior direito da janela;                  ║
// ║               bColor é a cor em que a janela deve ser limpa.                             ║
// ║                                                                                          ║
// ║ NOTA: Esta função pode servir também para pintar uma caixa no ecran numa determinada cor.║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_clswin( int nH1, int nV1, int nH2, int nV2, BYTE bColor )
{
    for( ; nV1 <= nV2; nV1++ )
        v_hline( nH1, nV1, nH2, bColor );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_curtain              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Limpa com efeito de cortina, uma janela definida por (nH1,nV1,nH2,nV2) na  ║
// ║               cor bColor.                                                                ║
// ║                                                                                          ║
// ║ Parâmetros:   nH1 é a coordenada X do canto superior esquerdo da janela;                 ║
// ║               nV1 é a coordenada Y do canto superior esquerdo da janela;                 ║
// ║               nH2 é a coordenada X do canto inferior direito da janela;                  ║
// ║               nV2 é a coordenada Y do canto inferior direito da janela;                  ║
// ║               bColor é a cor em que a janela deve ser limpa.                             ║
// ║               nSeg é o número de cortinas a correr quando é a função executada.          ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_curtain( int nH1, int nV1, int nH2, int nV2, BYTE bColor, int nSeg )
{
    int nDist = ( nH2 - nH1 + 1 ) / nSeg;
    int i, j;

    for( i = 0; i < nDist; i++ )
        for( j = 0; j < nSeg; j++ )
        {
            v_vline( nH1 + j * nDist + i, nV1, nV2, bColor );
            delay( 2 );
        }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_putbigpad            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Coloca na posição adr do ecran (memória video) a imagem do paddle grande.  ║
// ║               Lembra-se que a dimensão do paddle grande é de 30x8 pixels.                ║
// ║                                                                                          ║
// ║ Parâmetros:   adr é o endereço da memória video (ecran) onde colocar a imagem do paddle; ║
// ║               ptrImg é o apontador para a imagem do paddle grande.                       ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_putbigpad( WORD adr, BYTE *ptrImg )
{
    __emit__( 0x1E );
    _ES = VIDEO;
    _DS = FP_SEG( ptrImg );
    _DI = adr;
    _SI = FP_OFF( ptrImg );
    _DX = 15;
    _BX = 8;
    __emit__( 0x89, 0xD1, 0xF3, 0xA5, 0x81, 0xC7, 0x40, 0x01, 0x29, 0xD7, 0x29, 0xD7, 0x4B,
        0x75, 0xF1, 0x1F );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_vlinebigpad          │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Desenha uma linha vertical de 6 pixels em preto. É utilizada para limpar o ║
// ║               rasto deixado do paddle grande quando este vai para a esquerda ou direita. ║
// ║                                                                                          ║
// ║ Parâmetros:   adr é o endereço da memória video (ecran) onde colocar a imagem do paddle. ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_vlinebigpad( WORD adr )
{
    _ES = VIDEO;
    _DI = adr;
    _BX = 6;
    _AL = 0;                                                   // Define a cor 0 (zero = preto)
    __emit__( 0x26, 0x88, 0x05, 0x81, 0xC7, 0x40, 0x01, 0x4B, 0x75, 0xF6 );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_putlitpad            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Coloca na posição adr do ecran (memória video) a imagem do paddle pequeno. ║
// ║               Lembra-se que a dimensão do paddle pequeno é de 16x4 pixels.               ║
// ║                                                                                          ║
// ║ Parâmetros:   adr é o endereço da memória video (ecran) onde colocar a imagem do paddle; ║
// ║               ptrImg é o apontador para a imagem do paddle pequeno.                      ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_putlitpad( WORD adr, BYTE *ptrImg )
{
    __emit__( 0x1E );
    _ES = VIDEO;
    _DS = FP_SEG( ptrImg );
    _DI = adr;
    _SI = FP_OFF( ptrImg );
    _DX = 9;
    _BX = 4;
    __emit__( 0x89, 0xD1, 0xF3, 0xA5, 0x81, 0xC7, 0x40, 0x01, 0x29, 0xD7, 0x29, 0xD7, 0x4B,
        0x75, 0xF1, 0x1F );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_vlinelitpad          │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Desenha uma linha vertical de 2 pixels em preto. É utilizada para limpar o ║
// ║               rasto deixado do paddle pequeno quando este vai para a esquerda ou direita.║
// ║                                                                                          ║
// ║ Parâmetros:   adr é o endereço da memória video (ecran) onde colocar a imagem do paddle. ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_vlinelitpad( WORD adr )
{
    _ES = VIDEO;
    _DI = adr;
    _BX = 2;
    _AL = 0;                                                    // Define a cor 0 (zero = preto)
    __emit__( 0x26, 0x88, 0x05, 0x81, 0xC7, 0x40, 0x01, 0x4B, 0x75, 0xF6 );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_putball              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Coloca no endereço adr do ecran (memória video) uma bola de dimensões      ║
// ║               ((2*nX) x nY), apontada por ptrBuf.                                        ║
// ║                                                                                          ║
// ║ Parâmetros:   adr é o endereço da memória video (ecran) onde colocar o desenho da bola;  ║
// ║               nX é metade da largura da bola, ou seja, se por exemplo a bola tem 16      ║
// ║               pixels de largura, então nX deve ser igual a 8;                            ║
// ║               ptrBuf é o apontador para a imagem da bola.                                ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_putball( WORD adr, int nX, int nY, BYTE *ptrBuf )
{
    __emit__( 0x1E );
    _ES = VIDEO;
    _DS = FP_SEG( ptrBuf );
    _DI = adr;
    _SI = FP_OFF( ptrBuf );
    _DX = nX;
    _BX = nY;
    __emit__( 0x89, 0xD1, 0xF3, 0xA5, 0x81, 0xC7, 0x40, 0x01, 0x29, 0xD7, 0x29,
        0xD7, 0x4B, 0x75, 0xF1, 0x1F);
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_hlineball            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Desenha uma linha horizontal em preto. É utilzada para limpar o rasto      ║
// ║               deixado pela bola quando esta vai para cima ou para baixo.                 ║
// ║                                                                                          ║
// ║ Parâmetros:   adr é o endereço da memória video (ecran) onde colocar a linha horizontal; ║
// ║               dim é o tamanho da linha em pixels.                                        ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_hlineball( WORD adr, int dim )
{
    _ES = VIDEO;
    _DI = adr;
    _CX = dim;
    _AL = 0;                                                   // Define a cor 0 (zero = preto)
    __emit__( 0xF3, 0xAA );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_vlineball            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Desenha uma linha vertical em preto. É utilizada para limpar o rasto       ║
// ║               deixado pela bola quando esta vai para a esquerda ou para a direita.       ║
// ║                                                                                          ║
// ║ Parâmetros:   adr é o endereço da memória video (ecran) onde colocar a linha vertical;   ║
// ║               dim é o tamanho da linha em pixels.                                        ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_vlineball( WORD adr, int dim )
{
    _ES = VIDEO;
    _DI = adr;
    _BX = dim;
    _AL = 0;                                                   // Define a cor 0 (zero = preto)
    __emit__( 0x26, 0x88, 0x05, 0x81, 0xC7, 0x40, 0x01, 0x4B, 0x75, 0xF6 );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_mode                 │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Activa o modo de video especificado em Mode.                               ║
// ║                                                                                          ║
// ║ Parâmetros:   Mode é o modo de video a activar (para maiores detalhes consulte o manual  ║
// ║               do seu computador ou um livro de interrupções IBMPC ou compatível).        ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_mode( char Mode )
{
    _AH = 0;
    _AL = Mode;
    __int__( 0x10 );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_putpal               │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Escreve na palette os valores de um buffer fornecido como parâmetero.      ║
// ║                                                                                          ║
// ║ Parâmetros:   ptrBuf é um apontador para o buffer onde que contém as cores da palette;   ║
// ║               nStart o número da primeira cor da palette a ser escrita;                  ║
// ║               nLen é o comprimento a escrever a partir de nStart.                        ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_putpal( char *ptrBuf, int nStart, int nLen )
{
    __emit__( 0x1E, 0xFA );
    _DS = FP_SEG( ptrBuf );
    _SI = FP_OFF( ptrBuf );
    _CX = nLen;
    __emit__( 0xBA, 0xC8, 0x03 );
    _AL = nStart;
    __emit__( 0xEE, 0x42, 0xAC, 0xEE, 0xAC, 0xEE, 0xAC, 0xEE, 0xE2, 0xF8, 0xFB, 0x1F );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_getpal               │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Lê a palette de 256 cores para um buffer fornecido como parâmetero.        ║
// ║                                                                                          ║
// ║ Parâmetros:   ptrBuf é um apontador para o buffer onde colocar os valores da palette;    ║
// ║               nStart o número da primeira cor a guardar;                                 ║
// ║               nLen é o comprimento a guardar a partir de nStart.                         ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_getpal( char *ptrBuf, int nStart, int nLen )
{
    __emit__( 0x06 );
    _ES = FP_SEG( ptrBuf );
    _BX = nStart;
    _CX = nLen;
    _DX = FP_OFF( ptrBuf );
    _AX = 0x1017;
    __int__( 0x10 );
    __emit__( 0x07 );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_paloff               │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Apaga os valores da palette, ou seja, produz um efeito como que a          ║
// ║               escurecer o ecran.                                                         ║
// ║                                                                                          ║
// ║ Parâmetros:   bHalf é uma variável booleana qua indica quando o ecran deve ser           ║
// ║               escurecido integralmente, ou apenas uma parte (mais ou menu metade).       ║
// ║               Assim temos:  se bHalf = 0 o ecran será totalmente escurecido;             ║
// ║                             se bHalf = 1 apenas "metade" do efeito será realizado.       ║
// ║                                                                                          ║
// ║               Um bom exemplo de como isto funciona é o jogo Sob-Gelo onde a opção "Sair" ║
// ║               realiza um fade off total (bHalf = 0), e a tecla de pausa <P> realiza      ║
// ║               metade do fade off.                                                        ║
// ║                                                                                          ║
// ║ NOTA: Esta função não funciona convenientemente com qualquer palette, mas apenas com a   ║
// ║       palette definida, por exemplo no jogo Sob-Gelo.                                    ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_paloff( BYTE bHalf )
{
    int i;
    char k = 1, buf[ 768 ];

    v_getpal( buf, 0, 256 );

    while( ( !bHalf && k ) || ( bHalf && k < 10 ) )
    {
        if( !bHalf )
        k = 0;

        for( i = 0; i < 768; i++ )
        {
            if( !buf[ i ] )
            ;
            else if( buf[ i ] > 48 )
            {
                buf[ i ] -= 3;
                k++;
            }
            else if( buf[ i ] < 24 )
            {
                buf[ i ]--;
                k++;
            }
            else
            {
                buf[ i ] -= 2;
                k++;
            }
        }

        v_putpal( buf, 0, 256 );
        delay( 25 );
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_palon                │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Acende os valores da palette, ou seja, produz um efeito como que a         ║
// ║               iluminar o ecran.                                                          ║
// ║                                                                                          ║
// ║ Parâmetros:   bHalf é uma variável booleana qua indica quando o ecran deve ser           ║
// ║               iluminado integralmente, ou apenas uma parte (mais ou menu metade).        ║
// ║               Assim temos:  se bHalf = 0 o ecran será totalmente iluminado;              ║
// ║                             se bHalf = 1 apenas "metade" do efeito será realizado.       ║
// ║                                                                                          ║
// ║               Um bom exemplo de como isto funciona é o jogo Sob-Gelo onde a tecla de     ║
// ║               <P> realiza metade do fade on.                                             ║
// ║                                                                                          ║
// ║ NOTA: Esta função não funciona convenientemente com qualquer palette, mas apenas com a   ║
// ║       palette definida, por exemplo no jogo Sob-Gelo.                                    ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_palon( BYTE bHalf )
{
    int i;
    char k = 1, buf[ 768 ];

    if( bHalf )
        v_getpal( buf, 0, 256 );
    else
        for( i = 0; i < 768; i++ )
            buf[ i ] = 0;

    while( ( !bHalf && k ) || ( bHalf && k < 10 ) )
    {
        if( !bHalf )
        k = 0;

        for( i = 0; i < 768; i++ )
        {
            if( buf[ i ] < palette[ i ] )
            {
                buf[ i ] += ( palette[ i ] / 12 + 1 );
                k++;

                if( buf[ i ] > palette[ i ] )
                    buf[ i ] = palette[ i ];
            }
        }

        v_putpal( buf, 0, 256 );
        delay( 25 );
    }
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_putimage             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Coloca uma imagem de dimensão (nH x nV), apontada por ptrBuf, nas          ║
// ║               coordenadas (nX,nY) do ecran.                                              ║
// ║                                                                                          ║
// ║ Parâmetros:   nX e nY são as coordenadas do ecran onde a imagem deve ser colocada;       ║
// ║               nH e nV são as dimensões da imagem em pixels (largura x altura);           ║
// ║               ptrImg é o apontador para a imagem;                                        ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_putimage( int nX, int nY, int nH, int nV, BYTE *ptrBuf )
{
    __emit__( 0x1E );
    nH /= 2;
    _ES = VIDEO;
    _DS = FP_SEG( ptrBuf );
    _DI = nY * 320 + nX;
    _SI = FP_OFF( ptrBuf );
    _DX = nH;
    _BX = nV;
    __emit__( 0x89, 0xD1, 0xF3, 0xA5, 0x81, 0xC7, 0x40, 0x01, 0x29, 0xD7, 0x29, 0xD7, 0x4B,
        0x75, 0xF1, 0x1F);
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_hline                │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Desenha uma linha horizontal na cor bCorlor.                               ║
// ║                                                                                          ║
// ║ Parâmetros:   nH1 é a coordenada inicial X da linha a desenhar;                          ║
// ║               nV é a coordenada Y da linha a desenhar;                                   ║
// ║               nH2 é a coordenada final X da linha a desenhar;                            ║
// ║               bColor é a cor da linha.                                                   ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_hline( int nH1, int nV, int nH2, BYTE bColor )
{
    _ES = VIDEO;
    _DI = nV * 320 + nH1;
    _CX = nH2 - nH1 + 1;
    _AL = bColor;
    __emit__( 0xF3, 0xAA );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_vline                │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Desenha uma linha vertical na cor bColor.                                  ║
// ║                                                                                          ║
// ║ Parâmetros:   nH é a coordenada X da linha a desenhar;                                   ║
// ║               nV1 é a coordenada inicial Y da linha a desenhar;                          ║
// ║               nV2 é a coordenada final Y da linha a desenhar;                            ║
// ║               bColor é a cor da linha.                                                   ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_vline( int nH, int nV1, int nV2, BYTE bColor )
{
    _ES = VIDEO;
    _DI = nV1 * 320 + nH;
    _BX = nV2 - nV1 + 1;
    _AL = bColor;
    __emit__( 0x26, 0x88, 0x05, 0x81, 0xC7, 0x40, 0x01, 0x4B, 0x75, 0xF6 );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_box                  │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Desenha um rectângulo vazio no ecran na cor bColor.                        ║
// ║                                                                                          ║
// ║ Parâmetros:   nH1 é a coordenada X do canto superior esquerdo do rectângulo;             ║
// ║               nV1 é a coordenada Y do canto superior esquerdo do rectângulo;             ║
// ║               nH2 é a coordenada X do canto inferior direito do rectângulo;              ║
// ║               nV2 é a coordenada Y do canto inferior direito do rectângulo;              ║
// ║               bColor é a cor das linhas do rectângulo.                                   ║
// ║                                                                                          ║
// ║ NOTA: Esta função não pinta o rectângulo desenhado - para isso utilize antes a função    ║
// ║       v_clswin().                                                                        ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_box( int nH1, int nV1, int nH2, int nV2, BYTE bColor )
{
    v_hline( nH1, nV1, nH2, bColor );
    v_hline( nH1, nV2, nH2, bColor );
    v_vline( nH1, nV1, nV2, bColor );
    v_vline( nH2, nV1, nV2, bColor );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_pixel                │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Coloca um ponto na posição (nX,nY) no ecran, na cor bColor.                ║
// ║                                                                                          ║
// ║ Parâmetros:   nX é a coordenada X do ponto a exibir;                                     ║
// ║               nY é a coordenada Y do ponto a exibir;                                     ║
// ║               bColor é acor do ponto a exibir.                                           ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_pixel( int nX, int nY, char bColor )
{
    __emit__( 0xBF, 0x00, 0xA0, 0x8E, 0xC7 );
    _DI = nY * 320 + nX;
    _AL = bColor;
    __emit__( 0x26, 0x88, 0x05 );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: v_getwin               │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Move um bloco de imagem do ecran para um buffer.                           ║
// ║                                                                                          ║
// ║ Parâmetros:   nH1 é a coordenada X do canto superior esquerdo da imagem a guardar;       ║
// ║               nV1 é a coordenada Y do canto superior esquerdo da imagem a guardar;       ║
// ║               nH2 é a coordenada X do canto inferior direito da imagem a guardar;        ║
// ║               nV2 é a coordenada Y do canto inferior direito da imagem a guardar;        ║
// ║               ptrBuf é um apontador para a zona de memória (buffer) onde a imagem será   ║
// ║               guardada.                                                                  ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void v_getwin( int nH1, int nV1, int nH2, int nV2, char *ptrBuf )
{
    __emit__( 0x1E );
    _ES = FP_SEG( ptrBuf );
    _DS = VIDEO;
    _SI = nV1 * 320 + nH1;
    _DI = FP_OFF( ptrBuf );
    _DX = nH2 - nH1 + 1;
    _BX = nV2 - nV1 + 1;
    __emit__( 0x89, 0xD1, 0xF3, 0xA4, 0x81, 0xC6, 0x40, 0x01, 0x29, 0xD6, 0x4B, 0x75, 0xF3,
        0x1F );
}
