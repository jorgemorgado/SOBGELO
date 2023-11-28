//---------------------------------------------------------------------------------------------
//                                         M E N U . C
//
//                 Menu inicial do jogo: "JOGAR", Adversário, "TABELA" e "SAIR"
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                               Funções locais da fonte MENU.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: menu_display           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Exibe o menu inicial, utilizando o apontador ptrMenu. Este apontador foi   ║
// ║               inicializado acima e aponta para a imagem do menu. O único promenor a      ║
// ║               referir, trata-se de que a tecla com o nome do adversário é exibida        ║
// ║               dependendo do oponente escolhido pelo utilizador. Os oponentes possíveis   ║
// ║               são o COMPUTADOR, um JOGADOR 2, ou finalmente um JOGADOR 2 (PC2); cada um  ║
// ║               destes adversários possui respectivamente o valor 0, 1 e 2, o qual é       ║
// ║               guardado na variável nOpponent (definida no módulo GLOBAL.C).              ║
// ║                                                                                          ║
// ║ Parâmetros:   nChoice é a opção seleccionada (imagem da tecla pressionada) quando esta   ║
// ║               função é chamada.                                                          ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void menu_display( int nChoice )
{
    int nKeyUp[] = { 0, 2340, 9360, 11700 };   // Posição das teclas libertas (somar a ptrMenu)

    nKeyUp[ nChoice - 1 ] += 1170;

    v_putimage( 139,  85,  42, 13, ptrMenu + 14040 );                 // Exibe a palavra "MENU"
    v_putimage( 115, 122,  58,  7, ptrMenu + 14586 );          // Exibe a palavra "Adversário:"

    v_putimage( 115, 105, 90, 13, ptrMenu + nKeyUp[ 0 ]  );                    // Tecla "JOGAR"
    v_putimage( 115, 131, 90, 13, ptrMenu + nKeyUp[ 1 ] + nOpponent * 2340 );//Tecla adversário
    v_putimage( 115, 148, 90, 13, ptrMenu + nKeyUp[ 2 ] );                    // Tecla "TABELA"
    v_putimage( 115, 165, 90, 13, ptrMenu + nKeyUp[ 3 ] );                      // Tecla "SAIR"
}


//---------------------------------------------------------------------------------------------
//                                                             Funções externas da fonte MENU.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: load_menu              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Inicializa o apontador para a imagem do menu. A imagem do menu contém as   ║
// ║               várias teclas ON/OFF do menu, assim com, as palavras "MENU" e              ║
// ║               "Adversário:". Consulte o manual do programador.                           ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void load_menu( void )
{
    ptrMenu = getfile( "MENU.BIN", O_BINARY );           // Carrega a imagem do menu na memória
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: menu_process           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta função está encarregue de gerir o menu inicial. A função faz o        ║
// ║               processamento do teclado e retorna a opção seleccionada. As teclas válidas ║
// ║               são: arrow keys up/down, <ENTER> e <ESCAPE>.                               ║
// ║               Como se sabe o menu do jogo foi pensado para simular as teclas no ecran.   ║
// ║               Quando o utilizador de movimenta dentro do menu essas teclas vão sendo ora ║
// ║               pressionadas, ora libertadas. Por exemplo, se o utilizador pretende ver a  ║
// ║               tabela dos high-scores, ele deve colocar-se sobre a tecla "TABELA", e aí   ║
// ║               carregar na tecla └-> (<ENTER>) do seu keyboard. Neste caso, é óbvio que   ║
// ║               devem existir duas imagens de cada uma das teclas do menu - a imagem da    ║
// ║               tecla pressionada e outra imagem da mesma tecla, mas liberta.              ║
// ║               Por outro lado, como já foi referido acima, as imagens das teclas do menu  ║
// ║               podem ser fácilmente acedidas através do apontador ptrMenu (veja no manual ║
// ║               do programador como estão organizadas as imagens das teclas dentro do      ║
// ║               ficheiro MENU.000).                                                        ║
// ║               Assim, basta-nos definir um array com as 4 posições das 4 teclas libertas, ║
// ║               e somar cada uma dessas posições com ptrMenu para obter a imagem da tecla  ║
// ║               liberta correspondente à posição somada. Por exemplo, se adicionarmos a    ║
// ║               ptrMenu o valor da 4ª posição do array vamos obter a imagem da tecla       ║
// ║               "SAIR" (liberta). Depois para obter a imagem da mesma tecla, mas           ║
// ║               pressionada teremos ainda de somar 1170, que é a dimensão de cada uma das  ║
// ║               teclas (90 pixels de largura x 13 pixels de altura = 1170).                ║
// ║               Deste modo, embora as imagem da teclas ocupem mais espaço do que           ║
// ║               desejariamos, conseguimos um código bastante mais rápido e compacto.       ║
// ║               Apesar de tudo , o ideal seria uma rotina de processamento de menus o mais ║
// ║               genérica possível. No entanto, tal não foi possível, por três simples      ║
// ║               razões. A primeira prende-se com a falta de tempo de que dispunha para     ║
// ║               terminar este programa, onde o menu não é de certeza o mais importante.    ║
// ║               Quanto à segunda razão tem a ver com o facto de o menu a implementar ser   ║
// ║               pouco versátil, ou seja, só trabalha com imagens préviamente carregadas em ║
// ║               memória, e para além disso possui uma tecla estáctica (a tecla que indica  ║
// ║               o tipo de adversário). Finalmente a terceira razão está directamente       ║
// ║               relacionada com o teclado. Como se sabe este programa utiliza uma rotina   ║
// ║               de atendimento de teclado elaboraba por mim e adequada ao tipo de jogo que ║
// ║               se trata. Assim como o menu também deve ser controlado através do teclado, ║
// ║               se por acaso existisse uma rotina de processamento de menus genérica, ela  ║
// ║               teria de contar com a rotina de teclado (que nem sempre estaria activa, e  ║
// ║               como tal a rotina deixava de ser genérica).                                ║
// ║                                                                                          ║
// ║ Parâmetros:   nChoice é a opção (tecla) do menu actualmente pressionada. Por exemplo, se ║
// ║               a função recebe nChoice = 3 o menu será exibido com a tecla "TABELA" em    ║
// ║               baixo. Isto é-nos bastante vantajoso uma vez que sempre que o menu é       ║
// ║               exibido a tecla pressionada é a última opção seleccionada pelo utilizador. ║
// ║                                                                                          ║
// ║ Retorna:      Retorna a opção seleccionada, que depois será novamente enviada para esta  ║
// ║               função através do parâmetero nChoice. Os valores retornados pode ser:      ║
// ║               1 = escolheu a opção "JOGAR" (o jogo vai começar);                         ║
// ║               3 = escolheu a opção "TABELA" (exibir o quadro dos high-scores);           ║
// ║               4 = escolheu a opção "SAIR" (abandonar a regressar ao DOS).                ║
// ║               Note-se que a opção 2 nunca é retornada uma vez que corresponde ao tipo de ║
// ║               adversário com que se pretende jogar. A própria função está encarregue de  ║
// ║               definir a variável nOpponent de acordo com o tipo de adversário escolhido. ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
BYTE menu_process( BYTE nChoice )
{
    int nY[]     = {  105,  131,   148,   165 };          // Coordenadas Y das 4 teclas do menu
    int nKeyUp[] = {    0, 2340,  9360, 11700 };//Posição das teclas libertas (somar a ptrMenu)
    BYTE bExitMenu = FALSE;             // Variável booleana que indica quando abandonar o menu

    menu_display( nChoice );           // Exibe o menu (teclas e frases "MENU" e "Adversário:")

    while( KEYPRESSED )              // Espera enquanto estiver a pressionar uma tecla qualquer
        back_letters();                              // As letras em rodapé não param de passar

    do
    {
        if( KEYPRESSED )                                        // Se foi pressionada uma tecla
        {
            v_putimage( 115, nY[ nChoice - 1 ], 90, 13,                // Repõe a tecla liberta
            ptrMenu + nKeyUp[ nChoice - 1 ] +
            ( ( nChoice == 2 ) ? nOpponent * 2340 : 0 ) );

            if( KEY_ESCAPE )                                     // Pressionou a tecla <ESCAPE>
                nChoice = 4;                         // Avança directamente para a tecla "SAIR"
            else if( KEY_ENTER )                                  // Pressionou a tecla <ENTER>
            {
                if( nChoice != 2 )// Pressionou <ENTER> sobre uma tecla que não a "Adversário:"
                    bExitMenu = 1;     // Vai abandonar o ciclo e retornar a opção seleccionada
                else if( nOpponent++ == 2 )   // Pressionou <ENTER> sobre a tecla "Adversário:"
                    nOpponent = 0;                               // Define o tipo de adversário
            }
            else if( KEY_UP && nChoice-- == 1 )                      // Pressionou arrow-key up
                nChoice = 4;
            else if( KEY_DOWN && nChoice++ == 4 )                  // Pressionou arrow-key down
                nChoice = 1;

            v_putimage( 115, nY[ nChoice - 1 ], 90, 13,           // Exibe a nova tecla do menu
            ptrMenu + nKeyUp[ nChoice - 1 ] + 1170 +
            ( ( nChoice == 2 ) ? nOpponent * 2340 : 0 ) );

            do
                back_letters();                      // As letras em rodapé não param de passar
            while( KEYPRESSED );     // Repete enquanto estiver a pressionar uma tecla qualquer
        }

        back_letters();                              // As letras em rodapé não param de passar
    }
    while( !bExitMenu );      // Ciclo até que opção do menu seja seleccionada (exepto opção 2)

    return( nChoice );                                          // Retorna a opção seleccionada
}
