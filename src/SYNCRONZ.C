//---------------------------------------------------------------------------------------------
//                                     S Y N C R O N Z . C
//
//       Várias funções utilizadas antes do início do jogo para sincronizar os dois PC's
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                        Variáveis globais da fonte SYNCRONZ.C
//---------------------------------------------------------------------------------------------
static BYTE nDelayPC2;                                   // Guarda a velocidade definida no PC2
static BYTE nRnd, nRndPC2;                 // Números aleatórios gerados por este PC e pelo PC2


//---------------------------------------------------------------------------------------------
//                                                           Funções locais da fonte SYNCRONZ.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: diff_delay             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Compara as velocidades definidas em ambos os PC's e retorna TRUE ou FALSE  ║
// ║               dependendo do resultado do teste. No entanto, a função também retorna      ║
// ║               FALSE caso o utilizador aborte a comunicação (teclando <ESCAPE>).          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ║                                                                                          ║
// ║ Retorna:      TRUE se o valor das velocidades definidas nos dois PC's é diferente;       ║
// ║               FALSE se o valor das velocidades é igual ou se o utilizador simplesmente   ║
// ║               abortou teclando <ESCAPE>.                                                 ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static BOOLEAN diff_delay( void )
{
   do
   {
      write_RS232( nDelay + 20 );                     // Envia para o PC2 a velocidade definida
      wait_for_data();                              // Aguarda que o PC2 envie a sua velocidade
   }
   while( !UserAborted && TimeOut );   // Repete outra vez se ainda não abortou ou fim de tempo

   if( UserAborted )                                         // Se o utilizador teclou <ESCAPE>
      return( FALSE );                                    // Aborta a sincronização agora mesmo

   nDelayPC2 = read_RS232() - 20;                  // Lê o valor da velocidade enviada pelo PC2

   return( nDelay != nDelayPC2 );    // Compara as velocidades - retorna TRUE se são diferentes
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: set_delay              │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Acerta a velocidade do jogo. Como se sabe o delay definido no outro PC     ║
// ║               foi guardado na variável nDelayPC2. Por outro lado, se esta função foi     ║
// ║               chamada então as velocidades definidas em ambos os são diferentes          ║
// ║               (lembre-se que a comparação das velocidades foi efectuada na função        ║
// ║               diff_delay(). Assim, neste momento a tarefa é muito simplesmente aceitar a ║
// ║               maior das velocidades definidas, mas apenas se a velocidade definida no    ║
// ║               PC2 estiver entro os valores permitidos para o delay (intervalo [1,8]) -   ║
// ║               - isto é necessário porque podemos ter recebido do outro PC uma velocidade ║
// ║               errada devido a um qualquer erro de transmissão.                           ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void set_delay( void )
{
   // Verifica se valor recebido está entre os valores permitidos para a velocidade do jogo,
   // e se o valor da velocidade é maior que a velocidade definida pelo utilizador neste PC
   if( nDelayPC2 >= 1 && nDelayPC2 <= 8 && nDelayPC2 > nDelay )
      nDelay = nDelayPC2;                                      // Se sim actualiza a velocidade
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: same_beginner          │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    A função gera um número aleatório e compara-o com o número gerado pelo     ║
// ║               PC2. Se por acaso os números forem iguais (só por muito azar), serão       ║
// ║               gerados novos números. Esta tarefa repetir-se-á até que os números seja    ║
// ║               diferentes, ou até que o utilizador perca a paciência e pressione a tecla  ║
// ║               <ESCAPE>. Neste último caso, a variável UserAborted será colocada a TRUE,  ║
// ║               o que significa que o programa vai retornar ao menu principal.             ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void same_beginner( void )
{
    do
    {
        nRnd = ( BYTE )random( 49 ) + 1;               // Gera um número aleatório entre 1 e 49

        do
        {
            write_RS232( nRnd + 50 );                       // Envia o número gerado para o PC2
            wait_for_data();                      // Aguarda que o PC2 envie o número que gerou
        }
        while( !UserAborted && TimeOut );        // Repete se ainda não abortou ou fim de tempo

        if( UserAborted )                                    // Se o utilizador teclou <ESCAPE>
            return;                                       // Aborta a sincronização agora mesmo

        nRndPC2 = read_RS232() - 50;                   // Lê o número aleatório gerado pelo PC2
    }
    while( nRnd == nRndPC2 );                 // Ciclo enquanto os números gerados forem iguais
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: set_beginner           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Se o jogo já chegou a este ponto significa que já temos dois números       ║
// ║               aleatórios diferentes - um gerado por este mesmo PC, e o outro gerado pelo ║
// ║               PC2. Agora basta-nos comparar estes dois números e determinar de quem sai  ║
// ║               a bola, isto é, a bola sairá do computador que gerou o número maior.       ║
// ║               Depois é só atribuir o resultado do teste à variável SENDER.               ║
// ║               Esta variável determina qual o PC emissor (SENDER=TRUE) e qual o PC        ║
// ║               receptor (SENDER=FALSE): por uma questão de facilidade lembre-se que o PC  ║
// ║               emissor é sempre aquele que detém a bola; quando esta atingir o paddle do  ║
// ║               adversário o esquema será invertido, isto é, o emissor passará a receptor  ║
// ║               e vice-versa.                                                              ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static void set_beginner( void )
{
    SENDER = ( nRndPC2 > nRnd );      // Será TRUE se o PC2 gerou um número maior; FALSE se não
}


//---------------------------------------------------------------------------------------------
//                                                         Funções externas da fonte SYNCRONZ.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: sincronize             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta função é chamada exactamente após a inicialização da RS232 e o seu    ║
// ║               principal objectivo é tornar simultâneos os movimentos dos 2 PC's que      ║
// ║               estão a comunicar. Isto é, definir qual a verdadeira velocidade do jogo,   ║
// ║               assim como, determinar de quem sai a bola: se do jogador localizado no     ║
// ║               PC1, ou do jogador localizado no PC 2.                                     ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ║                                                                                          ║
// ║ Retorna:      TRUE se a sincronização decorreu sem problemas (o jogo já pode começar);   ║
// ║               FALSE se o utilizador teclou <ESCAPE> e como tal abortou a sincronização.  ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
BOOLEAN sincronize( void )
{
    cls_bottom_line();                            // Limpa toda a zona do rodapé (última linha)
    write_str( 7, 192, "SINCRONIZANDO^>^AGUARDE^>^ESC^TERMINAR" );

    /***
    * Sincronização da velocidade (delay)
    */
    while( !UserAborted && diff_delay() )      // Enquanto não abortar e velocidades diferentes
        set_delay();                               // Acerta a velocidade do jogo entre os PC's

    /***
    *    Definição de quem sai a bola
    */
    if( !UserAborted )                                     // Enquanto o utilizador não abortar
        same_beginner();                      // Gera um número aleatório e compara-o com o PC2

    if( !UserAborted )                                     // Enquanto o utilizador não abortar
        set_beginner();                       // Acerta os PC's para definir de quem sai a bola

    /***
    * Finalmente terminou a sincronização
    */
    return( !UserAborted );                            // Se o utilizador abortou retorna FALSE
}
