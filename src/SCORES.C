//---------------------------------------------------------------------------------------------
//                                       S C O R E S . C
//
//                  Tudo sobre a tabela de scores - exibir, alterar, gravar...
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                                                   Constantes
//---------------------------------------------------------------------------------------------
#define BOX_COLOR          241        // Cor da caixa que rodeia as letras no quadro "PARABÉNS"


//---------------------------------------------------------------------------------------------
//                                                          Variáveis globais da fonte SCORES.C
//---------------------------------------------------------------------------------------------
// Player é um array de 10 estruturas. Isto é, são 10 posições (pois "OS MELHORES SOB-GELO" é
// um top 10), em que cada uma possui um campo name para o nome do jogador, e um campo score
// para a respectiva pontuação
static struct {
    char *name;                                             // Apontador para o nome do jogador
    int score;                                             // Variável inteira para a pontuação
} Player[ 10 ];                                                 // Máximo = 10 jogadores no top


//---------------------------------------------------------------------------------------------
//                                                             Funções locais da fonte SCORES.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: insert_your_name       │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Rotina utilizada para inserir o nome do jogador caso tenha sido alcançado  ║
// ║               um novo high-score. A função exibe o quadro das letras no ecran e executa  ║
// ║               o processamento de teclado. Será exibida uma caixa magenta (cor 241) em    ║
// ║               volta da letra actualmente seleccionada. O utilizador poderá então mover   ║
// ║               essa mesma caixa (isto é, seleccionar outra letra) utilizando as quatro    ║
// ║               arrow-keys. Pode ainda, abandonar a introdução teclando <ESCAPE> ou        ║
// ║               seleccionado a palavra "FIM" - no primeiro caso a função retornará o       ║
// ║               último nome introduzido pelo jogador; no segundo caso a função não retorna ║
// ║               nome nenhum (retorna um string vazia - "" ou '\0').                        ║
// ║               Tome especial atenção às teclas <RETURN>, <ENTER>) ou <SPACE>: elas são    ║
// ║               utilizada para seleccionar o actual conteúdo da caixa, e tem algumas       ║
// ║               particulariedades, especialmente quando esse conteúdo é " " (SPACE),       ║
// ║               "<-" (BACKSPACE), "FIM", ou ainda a tentativa de introduzir uma letra que  ║
// ║               já não cabe na range (cujo máximo é de 12 caracteres).                     ║
// ║                                                                                          ║
// ║ Parâmetros:   ptrName é o endereço de início do nome introduzido (e que será retornado). ║
// ║                                                                                          ║
// ║ Retorna:      A função retorna um apontador para o início nome introduzido pelo jogador. ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static char *insert_your_name( char *ptrName )
{
    BOOLEAN bExitInsert = FALSE;              // Controla o final (saida) da introdução do nome
    static char oldName[ 13 ] = "";                    // Buffer para o último nome introduzido
    char bufName[ 13 ] = "";                                 // Buffer para o nome a introduzir
    int n = 0;                                             // Contador para o apontador bufName
    int nX = 0, nY = 0;                 // Posição (nX,nY) nas matrizes de coordenadas da caixa
    int nLeft[ 5 ][ 6 ]  = { { 113, 129, 145, 161, 177, 193 },                   // Coordenadas
                             { 113, 129, 145, 161, 177, 193 },                   // X do canto
                             { 113, 129, 145, 161, 177, 193 },                   // esquerdo da
                             { 113, 129, 145, 161, 177, 193 },                   // caixa.
                             { 113, 129, 145, 161, 177, 177 }
                           };
    int nRight[ 5 ][ 6 ] = { { 125, 141, 157, 173, 189, 205 },                   // Coordenadas
                             { 125, 141, 157, 173, 189, 205 },                   // X do canto
                             { 125, 141, 157, 173, 189, 205 },                   // direito da
                             { 125, 141, 157, 173, 189, 205 },                   // caixa.
                             { 125, 141, 157, 173, 205, 205 }
                           };
    int nTop[ 5 ]        = { 50, 66, 82,  98, 114 };          // Coordenadas Y do topo da caixa
    int nBottom[ 5 ] = { 62, 78, 94, 110, 126 };             // Coordenadas Y do fundo da caixa

    v_putimage( 97, 35, 126, 122, ptrNewScore );         // Exibe a imagem do quadro "PARABÉNS"

    write_str( 112, 139, "????????????" );            // Exibe a range para o nome a introduzir

    v_box( nLeft[ nY ][ nX ], nTop[ nY ], nRight[ nY ][ nX ], nBottom[ nY ], BOX_COLOR ); // Cx

    while( KEYPRESSED );                          // Aguarda que todas as teclas estejam soltas

    do
    {
        if( KEYPRESSED )                                     // Se alguma tecla foi pressionada
        {
            v_box(nLeft[ nY ][ nX ], nTop[ nY ], nRight[ nY ][ nX ], nBottom[ nY ], 0); //Caixa

            if( KEY_ESCAPE )                                                  // Tecla <ESCAPE>
            {
               bExitInsert = TRUE;                                 // Abandona no próximo ciclo
               strcpy( bufName, oldName);                   // Assume o último nome introduzido
            }
            else if( KEY_ENTER || KEY_SPACE )         // Se pressionou a tecla <ENTER> sobre...
            {
               if( nY == 4 && nX >= 4 && nX <= 5 )                    // Se <ENTER> sobre "FIM"
                  bExitInsert = TRUE;
               else if( n > 0 && nX == 3 && nY == 4 )                  // Se <ENTER> sobre "<-"
                  write_str( 112 + 8 * --n, 139, "?" );        // Apaga a letra e recua valor n
               else if( n > 11 || ( n == 0 && nX==3 && nY==4 ) ) // Se exedeu range para + ou -
                  s_out_of_range();                           // Som - tentou agir fora a range
               else if( nX == 2 && nY == 4 )                            // Se <ENTER> sobre " "
                  *(bufName + n++) = '^';                           // Insere um espaço no nome
               else                                               // Se <ENTER> sobre uma letra
                  *(bufName + n++) = 'A' + nX + nY * 6;             // Insere a letra escolhida

               *(bufName + n) = '\0';                                 // Insere final de string
               write_str( 112, 139, bufName );                   // Exibe o nome já introduzido
            }
            else if( KEY_RIGHT && ( ( nX == 4 && nY == 4 ) || ++nX > 5 ) )   // Arrow-key right
               nX = 0;
            else if( KEY_LEFT  && nX == 5 && nY == 4 )            // Arrow-key left sobre "FIM"
               nX -= 2;
            else if( KEY_LEFT  && --nX < 0 )                  // Arrow-key left sobre uma letra
               nX = 5;
            else if( KEY_DOWN  && ++nY > 4 )                                  // Arrow-key down
               nY = 0;
            else if( KEY_UP    && --nY < 0 )                                    // Arrow-key up
               nY = 4;

            v_box(nLeft[ nY ][ nX ], nTop[ nY ], nRight[ nY ][ nX ], nBottom[ nY ], BOX_COLOR);

            while( KEYPRESSED );                          // Aguarda que a tecla seja libertada
        }
    }
    while( !bExitInsert );                              // Ciclo - enquanto a "saida" for FALSE

    if( ( ptrName = ( char * )realloc( ptrName, strlen( bufName ) + 1 ) ) == NULL ) // Re-aloca
       exit_with_error( "Re-alocação de memória" );         // Informa o erro e regressa ao DOS

    strcpy( ptrName, bufName );                  // Copia o conteúdo do buffer para o apontador
    strcpy( oldName, bufName );                          // Actualiza o último nome introduzido

    cls_game_area();                                       // Limpa o ecran de jogo (tabuleiro)

    return( ptrName );                      // Retorna o endereço de início do nome introduzido
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: scores_quicksort       │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Ordena as pontuções decrescentemente, bem como, os respectivos nomes.      ║
// ║               Para efectuar esta ordenação eu recorri ao método QUICKSORT, daí que não   ║
// ║               vale a pena perder tempo com explicações, pois parto do princípio que você ║
// ║               conhece este algoritmo.                                                    ║
// ║               No entanto, só uma nota: a ordenação é decrescente uma vez que quem tem    ║
// ║               maior pontuação deve surgir em primeiro lugar na tabela.                   ║
// ║                                                                                          ║
// ║ Parâmetros:   left e right são os limites do segmento a ordenar.                         ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void scores_quicksort( int left, int right )
{
    int media, ndx1, ndx2, i;
    int troca;                                   // Variável temporária para a troca dos scores
    char *temp;                                   // Variável temporária para a troca dos names

    media = Player[ ( left + right ) / 2 ].score;
    ndx1 = left;
    ndx2 = right;

    do
    {
        while( Player[ ndx1 ].score > media )
            ndx1++;                                           // Aproxima-se da média por baixo

        while( media > Player[ ndx2 ].score )
            ndx2--;                                            // Aproxima-se da média por cima

        if( ndx1 <= ndx2 )                                        // Neste caso vai haver troca
        {
            temp = Player[ ndx1 ].name;                                                // Troca
            Player[ ndx1 ].name = Player[ ndx2 ].name;                                 // os
            Player[ ndx2 ].name = temp;                                                // nomes

            troca = Player[ ndx1 ].score;                                             // Troca
            Player[ ndx1++ ].score = Player[ ndx2 ].score;                            // os
            Player[ ndx2-- ].score = troca;                                           // scores
        }
    }
    while( ndx1 <= ndx2 );

    if( left < ndx2 ) scores_quicksort( left, ndx2 );                      // Recursividade com
    if( ndx1 < right ) scores_quicksort( ndx1, right );                    // um novo segmento
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: save_scores            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Grava a tabela d' "OS MELHORES SOB-GELO" no ficheiro SCORES.SG.            ║
// ║               Veja no manual do programador como está organizada a informação da tabela  ║
// ║               dentro do ficheiro SCORES.SG.                                              ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void save_scores( void )
{
    char tmpScore[ 5 ];                                // Apontador temporário para a pontuação
    int nTotal;                      // Total de nomes existentes na tabela dos scores (max.10)
    int nHandle;                                             // Handle do ficheiro "SCORES.TXT"

    if((nHandle = open("SCORES.SG", O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE) ) == -1)
    // Se ocorreu um erro na abertura do ficheiro "SCORES.SG"
        exit_with_error( "Erro na abertura de SCORES.SG:" ); // Exibe a mensagem e volta ao DOS

    for( nTotal = 0; nTotal < 10 && Player[ nTotal ].score; nTotal++ )// Ciclo - corre a tabela
        if(write( nHandle, Player[ nTotal ].name, strlen( Player[ nTotal ].name ) + 1 ) == -1)
            // Se ocorreu um erro na escrita dos nomes no ficheiro "SCORES.SG"
            exit_with_error("Erro escrevendo em SCORES.SG:");// Exibe a mensagem e volta ao DOS

    if( write( nHandle, "\n", 1 ) == -1 )
    // Se ocorreu um erro escrevendo o caracter nova-linha no ficheiro "SCORES.SG"
        exit_with_error( "Erro escrevendo em SCORES.SG:" );  // Exibe a mensagem e volta ao DOS

    for( nTotal = 0; nTotal < 10 && Player[ nTotal ].score; nTotal++ )// Ciclo - corre a tabela
    {
        itoa( Player[ nTotal ].score, tmpScore, 10 );         // Converte os scores para string

        if( write( nHandle, tmpScore, strlen( tmpScore ) + 1 ) == -1 )
        // Se ocorreu um erro naescrita dos scores no ficheiro "SCORES.SG"
            exit_with_error("Erro escrevendo em SCORES.SG:");// Exibe a mensagem e volta ao DOS
    }
}


//---------------------------------------------------------------------------------------------
//                                                           Funções externas da fonte SCORES.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: load_scores            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Inicializa ptrScores (apontador para a imagem da tabela dos scores).       ║
// ║               A função está ainda encarregue de inicializar as 10 estruturas de Player.  ║
// ║               Isso é feito abrindo o ficheiro SCORES.SG que contém a tabela desde a      ║
// ║               a última vez que o jogo foi carregado e algum record foi alcançado.        ║
// ║               Se por exemplo só existirem 5 nomes e respectivas pontuações no ficheiro   ║
// ║               SCORES.SG, somente as 5 primeiras estruturas de Player[ 10 ] serão         ║
// ║               inicializadas.                                                             ║
// ║               Veja no manual do programador com está organizada a informação da tabela   ║
// ║               dentro do ficheiro SCORES.SG.                                              ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void load_scores( void )
{
    char *ptrFile;                                     // Apontador para o ficheiro "SCORES.SG"
    int nTotal;                      // Total de nomes existentes na tabela dos scores (max.10)
    int i;                                                           // Contador para ciclo for

    ptrScores   = getfile( "SCORES.BIN",   O_BINARY );   // Carrega imagem da tabela na memória
    ptrNewScore = getfile( "NEWSCORE.BIN", O_BINARY ); // Carrega a imagem do quadro "PARABÉNS"
    ptrFile     = getfile( "SCORES.SG",    O_TEXT );  // Carrega os scores da tabela na memória

    for( nTotal = 0; nTotal < 10 && *ptrFile != '\n'; nTotal++ )
    {
        Player[ nTotal ].name = ( char * )calloc( strlen( ptrFile ) + 1, sizeof( char ) );
        strcpy( Player[ nTotal ].name, ptrFile );                 // Apontadores para cada nome
        ptrFile += strlen( Player[ nTotal ].name ) + 1;           // Avança para o próximo nome
    }

    ptrFile++;  // Salta o caracter '\n' que indica o final dos nomes - agora vêm as pontuações

    for( i = 0; i < nTotal; i++ )
    {
        Player[ i ].score = atoi( ptrFile );                   // Apontador para cada pontuação
        ptrFile += strlen( ptrFile ) + 1;                    // Avança para a próxima pontuação
    }

    for( ; nTotal < 10; nTotal++ )             // Se a tabela dos scores ainda não tem 10 nomes
    {
        Player[ nTotal ].name = NULL;        // Coloca o resto dos pointers a apontar para nada
        Player[ nTotal ].score = 0;                     // Coloca o resto das pontuações a zero
    }

    scores_quicksort( 0, 9 );          // Ordena a tabela pois o ficheiro pode estar corrompido
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: scores_display         │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Exibe a tabela dos high-scores no ecran.                                   ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void scores_display( void )
{
    char tmpScore[ 5 ];                                // Apontador temporário para a pontuação
    int i;                                                           // Contador para ciclo for

    v_putimage( 70, 76, 180, 114, ptrScores );                      // Exibe a imagem da tabela

    for( i = 0; i < 10 && Player[ i ].score; i++ ) // Enquanto houver scores (maiores que zero)
    {
        write_str( 93, 99 + i * 8, Player[ i ].name );                 // Exibe nome do jogador

        itoa( Player[ i ].score, tmpScore, 10 );                  // Converte score para string
        write_str( 237 - strlen( tmpScore ) * 8, 99 + i * 8, tmpScore );     // Escreve o score
    }

    while( KEY_ENTER )            // Espera enquanto não libertar a tecla <ENTER> (ou <RETURN>)
        back_letters();                                  // Enquanto isso vai correndo o rodapé

    while( !KEYPRESSED )              // Espera enquanto não for pressionada uma tecla qualquer
        back_letters();                                  // Enquanto isso vai correndo o rodapé

    v_clswin( 70, 76, 250, 190, 0 );                                  // Limpa a zona da tabela
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: get_a_highscore        │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Verifica se o jogador merece entrar na tabela "OS MELHORES SOB-GELO".      ║
// ║               Se sim, substitui o último da tabela pelo actual jogador, bem como, a sua  ║
// ║               pontuação. No final re-ordena todos os elementos da tabela.                ║
// ║                                                                                          ║
// ║ Parâmetros:   nHighScore é a pontuação alcançada pelo jogador candidato a um lugar na    ║
// ║               tabela.                                                                    ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void get_a_highscore( int nHighScore )
{
    if( nHighScore > Player[ 9 ].score ) // Se o score alcançado é superior ao último da tabela
    {
        Player[ 9 ].name = insert_your_name( Player[ 9 ].name );//Introdução do nome do jogador
        Player[ 9 ].score = nHighScore;                         //Coloca o novo score na tabela

        scores_quicksort( 0, 9 );                 // Re-ordena os scores e os respectivos nomes
        save_scores();                              // Salva a tabela d' "OS MELHORES SOB-GELO"
    }
}
