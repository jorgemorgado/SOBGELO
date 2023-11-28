//---------------------------------------------------------------------------------------------
//                                        R S 2 3 2 . C
//
//   Funções relacionadas com a porta série RS232 (funções de escrita, leitura, ststus, etc.)
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                                                                   Constantes
//---------------------------------------------------------------------------------------------
#define COMPORT           1                                              // Porto RS232 - COM 2
#define WAITING_TIME      0.1                              // Tempo de espera por dados do PC 2


//---------------------------------------------------------------------------------------------
//                                                              Funções locais da fonte RS232.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: status_RS232           │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Verifica o status do porto de comunicações RS232.                          ║
// ║                                                                                          ║
// ║ Parâmetros:   R é o registador AH (acomulator high) retornado depois de efectuada a      ║
// ║               inicialização da RS232. Cada um dos 8 bits tem o seguinte significado:     ║
// ║                 bit 7 = Timed-out                                                        ║
// ║                 bit 6 = Transmission shift register empty                                ║
// ║                 bit 5 = Transmission hold register empty                                 ║
// ║                 bit 4 = Break detected                                                   ║
// ║                 bit 3 = Framing error                                                    ║
// ║                 bit 2 = Parity error                                                     ║
// ║                 bit 1 = Overrun error                                                    ║
// ║                 bit 0 = Data ready                                                       ║
// ║                                                                                          ║
// ║ Retorna:      TRUE se os bits 7, 4, 3, 2 e 1 estiverem a 0 (zero);                       ║
// ║               FALSE se qualquer um bits 7, 4, 3, 2 ou 1 estiver a 1 (um). Se algum       ║
// ║               destes bits estiver a 1 (on), significa que existe "lixo" na porta série.  ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
static BOOLEAN status_RS232( BYTE R )
{
    return( !( (R & 0x80) || (R & 0x10) || (R & 0x08) || (R & 0x04) || (R & 0x02) ) );
}


//---------------------------------------------------------------------------------------------
//                                                            Funções externas da fonte RS232.C
//---------------------------------------------------------------------------------------------

// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: init_RS232             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Inicializa a RS232. A função executa um ciclo (inicializando a RS232)      ║
// ║               enquanto houver "lixo" no porto, ou enquanto o utilizador não pressionar   ║
// ║               a tecla <ESCAPE>.                                                          ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void init_RS232( void )
{
    union REGS regs;

    do
    {
        regs.h.ah = 0x00;
        regs.h.al = 0xEB;                                     // 9600 Baud, Odd, 1 Stop, 8 Bits
        regs.x.dx = COMPORT;
        int86( 0x14, &regs, &regs );
    }
    while( !( KEY_ESCAPE || status_RS232( regs.h.ah ) ) );// Até pressionar ESCAPE ou status OK

    UserAborted = FALSE;                // No início o utilizador ainda abortou nenhum processo
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: wait_for_data          │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Esta função aguarda por dados na RS232 durante o tempo de espera, o qual é ║
// ║               definido pela constante WAITING_TIME. Depois de atingido este tempo        ║
// ║               significa que durante a espera não foram recebidos nenhuns dados pela      ║
// ║               RS232. Assim, a função terminará, colocando a variável TimeOut a TRUE.     ║
// ║               No entanto, a espera de dados pode também ser interrompida pressionado a   ║
// ║               tecla <ESCAPE>, e neste caso a variável UserAborted será actualizada para  ║
// ║               TRUE.                                                                      ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void wait_for_data( void )
{
    clock_t start = clock();                                        // Guarda o tempo de início

    TimeOut = FALSE;                       // Inicialmente ainda não terminou o tempo de espera

    while( !(UserAborted || data_ready() || TimeOut) ) // Espera: <ESCAPE>, dados, fim de tempo
        if( KEY_ESCAPE )                                     // O utilizador perdeu a paciência
            UserAborted = TRUE;                                     // Vai sair no próximo loop
        else if( ( clock() - start ) / CLK_TCK > WAITING_TIME )   // Verifica se acabou o tempo
            TimeOut = TRUE;                                         // Vai sair no próximo loop
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: write_RS232            │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Escreve um byte na RS232.                                                  ║
// ║                                                                                          ║
// ║ Parâmetros:   Ch é o byte a esctever no porto I/O RS232.                                 ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
void write_RS232( BYTE Ch )
{
    union REGS regs;

    regs.h.ah = 0x01;
    regs.h.al = Ch;
    regs.x.dx = COMPORT;
    int86( 0x14, &regs, &regs );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: read_RS232             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Lê um byte do porto i/o RS232.                                             ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ║                                                                                          ║
// ║ Retorna:      A função retorna o byte lido.                                              ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
BYTE read_RS232( void )
{
    union REGS regs;

    regs.h.ah = 0x02;
    regs.x.dx = COMPORT;
    int86( 0x14, &regs, &regs );

    return( ( regs.h.ah & 0x80 ) ? 32 : regs.h.al );
}


// ╔══════════════════════════════╤═══════════════════════════════════════════════════════════╗
// ║ Nome: data_ready             │                   Autor: Jorge Morgado (Fev/Mar/Abr 1994) ║
// ╟──────────────────────────────┴───────────────────────────────────────────────────────────╢
// ║ Objectivo:    Verifica se existem dados a ler na RS232.                                  ║
// ║                                                                                          ║
// ║ Parâmetros:   Nenhum                                                                     ║
// ║                                                                                          ║
// ║ Retorna:      TRUE se existem dados a ler na RS232;                                      ║
// ║               FALSE se a RS232 não tem nada para ser lido.                               ║
// ╚══════════════════════════════════════════════════════════════════════════════════════════╝
BOOLEAN data_ready( void )
{
    union REGS regs;

    regs.h.ah = 0x03;
    regs.x.dx = COMPORT;
    int86( 0x14, &regs, &regs );

    return( ( regs.h.ah & 0x01 ) ? TRUE : FALSE );
}
