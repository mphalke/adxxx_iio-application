;/*
;THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES INC. ``AS IS'' AND ANY EXPRESS OR
;IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
;MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT, ARE
;DISCLAIMED. IN NO EVENT SHALL ANALOG DEVICES INC. BE LIABLE FOR ANY DIRECT,
;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
;ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;POSSIBILITY OF SUCH DAMAGE.
;
;YOU ASSUME ANY AND ALL RISK FROM THE USE OF THIS CODE OR SUPPORT FILE.
;
;IT IS THE RESPONSIBILITY OF THE PERSON INTEGRATING THIS CODE INTO AN APPLICATION
;TO ENSURE THAT THE RESULTING APPLICATION PERFORMS AS REQUIRED AND IS SAFE.
;
;    Module       : startup_ADuCM320.s
;    Description  : Cortex-M3 startup file - ADuCM320 - EWARM Version
;    Date         : Monday January 04 2016 16:29
;    Version      : v0.3
;*/



         MODULE  ?cstartup
         
         #define USER_SRAM_MODE 0
         //#define USER_SRAM_MODE 1
         //#define USER_SRAM_MODE 2
         //#define USER_SRAM_MODE 3

         #define SRAMCON_ADDR   0x40065000
         #define USERKEY_ADDR   0x40002134
         #define USERKEY        0x8D5F9FEC
         #define CACHESETUP_ADDR        0x40044004
         #define CACHE_KEY       0xF123F456
         #define CACHE_KEY_ADDR  0x40044008
         #define CACHE_STATUS_ADDR    0x40044000

         ;; Forward declaration of sections.
         SECTION CSTACK:DATA:NOROOT(3)

         SECTION .intvec:CODE:ROOT(2)

         EXTERN  __iar_program_start
         EXTERN  SystemInit
         PUBLIC  __vector_table
         

         DATA
__vector_table
         DCD     sfe(CSTACK)                       ; Top of Stack
         DCD     Reset_Handler               ; Reset Handler

         DCD     Nmi_Handler                       ; The NMI handler
         DCD     HardFault_Handler                  ; The hard fault handler
         DCD     MemManage_Handler                 ; The MPU fault handler
         DCD     BusFault_Handler                  ; The bus fault handler
         DCD     UsageFault_Handler                ; The usage fault handler
         DCD     0                                 ; Reserved
         DCD     0                                 ; Reserved
         DCD     0                                 ; Reserved
         DCD     0                                 ; Reserved
         DCD     SVC_Handler                       ; SVCall handler
         DCD     DebugMon_Handler                  ; Debug monitor handler
         DCD     0                                 ; Reserved
         DCD     PendSV_Handler                    ; The PendSV handler
         DCD     SysTick_Handler                   ; The SysTick handler

         ; External Interrupts
         DCD     WakeUp_Int_Handler        ; Wakeup Timer Interrupt        [ 0]
         DCD     Ext_Int0_Handler          ; External Interrupt 0          [ 1]
         DCD     Ext_Int1_Handler          ; External Interrupt 1          [ 2]
         DCD     Ext_Int2_Handler          ; External Interrupt 2          [ 3]
         DCD     Ext_Int3_Handler          ; External Interrupt 3          [ 4]
         DCD     Ext_Int4_Handler          ; External Interrupt 4          [ 5]
         DCD     Ext_Int5_Handler          ; External Interrupt 5          [ 6]
         DCD     Ext_Int6_Handler          ; External Interrupt 6          [ 7]
         DCD     Ext_Int7_Handler          ; External Interrupt 7          [ 8]
         DCD     Ext_Int8_Handler          ; External Interrupt 8          [ 9]
         DCD     Ext_Int9_Handler          ; External Interrupt 8          [10]
         DCD     WDog_Tmr_Int_Handler      ; Watchdog Timer Interrupt      [11]
         DCD     GP_Tmr0_Int_Handler       ; Timer0 Interrupt              [12]
         DCD     GP_Tmr1_Int_Handler       ; Timer1 Interrupt              [13]
         DCD     GP_Tmr2_Int_Handler       ; Timer2 Interrupt              [14]
         DCD     GP_Tmr3_Int_Handler       ; Timer3 Interrupt              [15]
         DCD     GP_Tmr4_Int_Handler       ; Timer4 Interrupt              [16]
         DCD     MDIO_Int_Handler          ; MDIO Interrupt                [17]
         DCD     Flsh_Int_Handler          ; Flash Memory Interrupt        [18]
         DCD     UART0_Int_Handler         ; UART0 Interrupt               [19]
         DCD     UART1_Int_Handler         ; UART1 Interrupt               [20]
         DCD     SPI0_Int_Handler          ; SPI0 Interrupt                [21]
         DCD     SPI1_Int_Handler          ; SPI1 Interrupt                [22]
         DCD     SPI2_Int_Handler          ; SPI2 Interrupt                [23]
         DCD     I2C0_Slave_Int_Handler    ; I2C0 Slave Interrupt          [24]
         DCD     I2C0_Master_Int_Handler   ; I2C0 Master Interrupt         [25]
         DCD     I2C1_Slave_Int_Handler    ; I2C1 Slave Interrupt          [26]
         DCD     I2C1_Master_Int_Handler   ; I2C1 Master Interrupt         [27]
         DCD     I2C2_Slave_Int_Handler    ; I2C2 Slave Interrupt          [28]
         DCD     I2C2_Master_Int_Handler   ; I2C2 Master Interrupt         [29]
         DCD     PLA0_Int_Handler          ; PLA0 Interrupt                [30]
         DCD     PLA1_Int_Handler          ; PLA1 Interrupt                [31]
         DCD     PLA2_Int_Handler          ; PLA2 Interrupt                [32]
         DCD     PLA3_Int_Handler          ; PLA3 Interrupt                [33]
         DCD     PWMTrip_Int_Handler       ; PWM TRIP Interrupt            [34]
         DCD     PWM0_Int_Handler          ; PWM Channel Pair 0 interrupt  [35]
         DCD     PWM1_Int_Handler          ; PWM Channel Pair 1 interrupt  [36]
         DCD     PWM2_Int_Handler          ; PWM Channel Pair 2 interrupt  [37]
         DCD     PWM3_Int_Handler          ; PWM Channel Pair 3 interrupt  [38]
         DCD     SRAM_Err_Int_Handler      ; SRAM interrupt                [39]
         DCD     DMA_Err_Int_Handler       ; DMA Error Interrupt           [40]
         DCD     DMA_SPI0_TX_Int_Handler   ; DMA SPI0 TX Interrupt         [41]
         DCD     DMA_SPI0_RX_Int_Handler   ; DMA SPI0 RX Interrupt         [42]
         DCD     DMA_SPI1_TX_Int_Handler   ; DMA SPI1 TX Interrupt         [43]
         DCD     DMA_SPI1_RX_Int_Handler   ; DMA SPI1 RX Interrupt         [44]
         DCD     DMA_SPI2_TX_Int_Handler   ; DMA SPI2 TX Interrupt         [45]
         DCD     DMA_SPI2_RX_Int_Handler   ; DMA SPI2 RX Interrupt         [46]
         DCD     DMA_UART0_TX_Int_Handler  ; DMA UART0 TX Interrupt        [47]
         DCD     DMA_UART0_RX_Int_Handler  ; DMA UART0 RX Interrupt        [48]
         DCD     DMA_UART1_TX_Int_Handler  ; DMA UART1 TX Interrupt        [49]
         DCD     DMA_UART1_RX_Int_Handler  ; DMA UART1 RX Interrupt        [50]
         DCD     DMA_I2C0_STX_Int_Handler  ; DMA I2C0 Slave TX Interrupt   [51]
         DCD     DMA_I2C0_SRX_Int_Handler  ; DMA I2C0 Slave RX Interrupt   [52]
         DCD     DMA_I2C0_MTX_Int_Handler  ; DMA I2C0 Master Interrupt     [53]
         DCD     DMA_I2C1_STX_Int_Handler  ; DMA I2C1 Slave TX Interrupt   [54]
         DCD     DMA_I2C1_SRX_Int_Handler  ; DMA I2C1 Slave RX Interrupt   [55]
         DCD     DMA_I2C1_MTX_Int_Handler  ; DMA I2C1 Master Interrupt     [56]
         DCD     DMA_I2C2_STX_Int_Handler  ; DMA I2C2 Slave TX Interrupt   [57]
         DCD     DMA_I2C2_SRX_Int_Handler  ; DMA I2C2 Slave RX Interrupt   [58]
         DCD     DMA_I2C2_MTX_Int_Handler  ; DMA I2C2 Master Interrupt     [59]
         DCD     DMA_MDIO_TX_Int_Handler   ; DMA MDIO Tx Interrupt         [60]
         DCD     DMA_MDIO_RX_Int_Handler   ; DMA MDIO Rx Interrupt         [61]
         DCD     DMA_Flsh_Int_Handler      ; DMA Flash Interrupt           [62]
         DCD     DMA_ADC_Int_Handler       ; DMA ADC Interrupt             [63]
         DCD     PLL_Int_Handler           ; TBD                           [64]
         DCD     HFOSC_Int_Handler         ; TBD                           [65]
         DCD     ADC_Int_Handler           ; TBD                           [66]
         DCD     SEQ_Int_Handler           ; TBD                           [67]
         DCD     COMP0_Int_Handler         ; TBD                           [68]
         DCD     COMP1_Int_Handler         ; TBD                           [69]
         DCD     COMP2_Int_Handler         ; TBD                           [70]
         DCD     COMP3_Int_Handler         ; TBD                           [71]
         DCD     VDAC_Int_Handler          ; TBD                           [72]
         DCD     LVDIE_Int_Handler         ; TBD                           [73]
         DCD     HVDIE_Int_Handler         ; TBD                           [74]
         DCD     SPI_LVD2D_Int_Handler     ; TBD                           [75]
         DCD     SPI_HVD2D_Int_Handler     ; TBD                           [76]
         DCD     SPI_LV_TX_Int_Handler     ; TBD                           [77]
         DCD     SPI_LV_RX_Int_Handler     ; TBD                           [78]
         DCD     SPI_HV_TX_Int_Handler     ; TBD                           [79]
         DCD     SPI_HV_RX_Int_Handler     ; TBD                           [80]
         DCD     DMA_TRIG0_Int_Handler     ; TBD                           [81]
         DCD     DMA_TRIG1_Int_Handler     ; TBD                           [82]
         DCD     DMA_SW0_Int_Handler       ; TBD                           [83]
         DCD     DMA_SW1_Int_Handler       ; TBD                           [84]
         DCD     DMA_CACHE_Int_Handler     ; TBD                           [85]
         DCD     DMA_DIGCOMP_Int_Handler   ; TBD                           [86]
         DCD     UnUsed_Handler            ; TBD                           [87]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
         PUBWEAK Nmi_Handler
         PUBWEAK HardFault_Handler
         PUBWEAK MemManage_Handler
         PUBWEAK BusFault_Handler
         PUBWEAK UsageFault_Handler
         PUBWEAK SVC_Handler
         PUBWEAK DebugMon_Handler
         PUBWEAK PendSV_Handler
         PUBWEAK SysTick_Handler
         PUBWEAK WakeUp_Int_Handler
         PUBWEAK Ext_Int0_Handler
         PUBWEAK Ext_Int1_Handler
         PUBWEAK Ext_Int2_Handler
         PUBWEAK Ext_Int3_Handler
         PUBWEAK Ext_Int4_Handler
         PUBWEAK Ext_Int5_Handler
         PUBWEAK Ext_Int6_Handler
         PUBWEAK Ext_Int7_Handler
         PUBWEAK Ext_Int8_Handler
         PUBWEAK Ext_Int9_Handler
         PUBWEAK WDog_Tmr_Int_Handler
         PUBWEAK GP_Tmr0_Int_Handler
         PUBWEAK GP_Tmr1_Int_Handler
         PUBWEAK GP_Tmr2_Int_Handler
         PUBWEAK GP_Tmr3_Int_Handler
         PUBWEAK GP_Tmr4_Int_Handler
         PUBWEAK MDIO_Int_Handler
         PUBWEAK Flsh_Int_Handler
         PUBWEAK UART0_Int_Handler
         PUBWEAK UART1_Int_Handler
         PUBWEAK SPI0_Int_Handler
         PUBWEAK SPI1_Int_Handler
         PUBWEAK SPI2_Int_Handler
         PUBWEAK I2C0_Slave_Int_Handler
         PUBWEAK I2C0_Master_Int_Handler
         PUBWEAK I2C1_Slave_Int_Handler
         PUBWEAK I2C1_Master_Int_Handler
         PUBWEAK I2C2_Slave_Int_Handler
         PUBWEAK I2C2_Master_Int_Handler
         PUBWEAK PLA0_Int_Handler
         PUBWEAK PLA1_Int_Handler
         PUBWEAK PLA2_Int_Handler
         PUBWEAK PLA3_Int_Handler
         PUBWEAK PWMTrip_Int_Handler
         PUBWEAK PWM0_Int_Handler
         PUBWEAK PWM1_Int_Handler
         PUBWEAK PWM2_Int_Handler
         PUBWEAK PWM3_Int_Handler
         PUBWEAK SRAM_Err_Int_Handler
         PUBWEAK DMA_Err_Int_Handler
         PUBWEAK DMA_SPI0_TX_Int_Handler
         PUBWEAK DMA_SPI0_RX_Int_Handler
         PUBWEAK DMA_SPI1_TX_Int_Handler
         PUBWEAK DMA_SPI1_RX_Int_Handler
         PUBWEAK DMA_SPI2_TX_Int_Handler
         PUBWEAK DMA_SPI2_RX_Int_Handler
         PUBWEAK DMA_UART0_TX_Int_Handler
         PUBWEAK DMA_UART0_RX_Int_Handler
         PUBWEAK DMA_UART1_TX_Int_Handler
         PUBWEAK DMA_UART1_RX_Int_Handler
         PUBWEAK DMA_I2C0_STX_Int_Handler
         PUBWEAK DMA_I2C0_SRX_Int_Handler
         PUBWEAK DMA_I2C0_MTX_Int_Handler
         PUBWEAK DMA_I2C1_STX_Int_Handler
         PUBWEAK DMA_I2C1_SRX_Int_Handler
         PUBWEAK DMA_I2C1_MTX_Int_Handler
         PUBWEAK DMA_I2C2_STX_Int_Handler
         PUBWEAK DMA_I2C2_SRX_Int_Handler
         PUBWEAK DMA_I2C2_MTX_Int_Handler
         PUBWEAK DMA_MDIO_TX_Int_Handler
         PUBWEAK DMA_MDIO_RX_Int_Handler
         PUBWEAK DMA_Flsh_Int_Handler
         PUBWEAK DMA_ADC_Int_Handler
         PUBWEAK PLL_Int_Handler
         PUBWEAK HFOSC_Int_Handler
         PUBWEAK ADC_Int_Handler
         PUBWEAK SEQ_Int_Handler
         PUBWEAK COMP0_Int_Handler
         PUBWEAK COMP1_Int_Handler
         PUBWEAK COMP2_Int_Handler
         PUBWEAK COMP3_Int_Handler
         PUBWEAK VDAC_Int_Handler
         PUBWEAK LVDIE_Int_Handler
         PUBWEAK HVDIE_Int_Handler
         PUBWEAK SPI_LVD2D_Int_Handler
         PUBWEAK SPI_HVD2D_Int_Handler
         PUBWEAK SPI_LV_TX_Int_Handler
         PUBWEAK SPI_LV_RX_Int_Handler
         PUBWEAK SPI_HV_TX_Int_Handler
         PUBWEAK SPI_HV_RX_Int_Handler
         PUBWEAK DMA_TRIG0_Int_Handler  
         PUBWEAK DMA_TRIG1_Int_Handler  
         PUBWEAK DMA_SW0_Int_Handler    
         PUBWEAK DMA_SW1_Int_Handler    
         PUBWEAK DMA_CACHE_Int_Handler  
         PUBWEAK DMA_DIGCOMP_Int_Handler
         PUBWEAK UnUsed_Handler

         THUMB
         SECTION .text:CODE:REORDER:ROOT(2)

Reset_Handler:
        /* Reset the main stack pointer from the first entry in the 
           vector table (First entry contains the stack pointer) */
        LDR     R0, =__vector_table
        LDR     R0, [R0, #0]
        MSR     MSP, R0

        /*SRAM setup, default SRAM MODE = 0*/
        LDR     R4, =USERKEY_ADDR
        LDR     R5, =USERKEY
        STR     R5, [R4]        //write user key
        LDR     R6, =SRAMCON_ADDR
#if   (USER_SRAM_MODE == 1)
        BL      Disable_Cache
        STR     R5, [R4]     //write user key
        MOV     R2, #2       //SRAM0 as code SRAM, cache as SRAM
        STR     R2, [R6]
#elif (USER_SRAM_MODE == 2)
        BL      Enable_Cache
        STR     R5, [R4]     //write user key
        MOV     R2, #1      //SRAM0 as sytem sram, cache
        STR     R2, [R6]
#elif (USER_SRAM_MODE == 3)
        BL      Disable_Cache
        STR     R5, [R4]     //write user key
        MOV     R2, #3       //SRAM0 as system sram, cache as SRAM
        STR     R2, [R6]
#else
        BL      Enable_Cache
        STR     R5, [R4]     //write user key
        MOV     R2, #0       //SRAM0 as code sram, cache 
        STR     R2, [R6]
#endif   
        MOV     R2, #0
        STR     R2, [R4]        //LOCK
        MOV     R1, #0
        MOV     R3, #0
        MOV     R4, #0
        MOV     R5, #0
        MOV     R6, #0
        
        /* Call system init */
        LDR     R0, =SystemInit
        BLX     R0
     
        /* Hand over to IAR */
        LDR     R0, =__iar_program_start
        BX      R0
        
Disable_Cache:
      LDR   R0, =CACHESETUP_ADDR
      LDR   R1, [R0]
      UBFX  R2, R1, #0, #1 //get current bit0 value
      CMP   R2, #0
      BEQ   CacheWapDone   // cache already disabled.
      BFC   R1, #0, #1  //clear bit0
      LDR   R7, = CACHE_KEY_ADDR
      LDR   R8, = CACHE_KEY
      STR   R8, [R7]     //write cache key
      STR   R1, [R0]
      LDR   R7, = CACHE_STATUS_ADDR
CacheWip
		LDR   R8, [R7]	;read cache status
		UBFX  R0, R8, #3, #1	;BIT3 of cache status register ind
		CMP   R0, #1
		BNE   CacheWip  	; Cache is wapping
CacheWapDone
		LDR   R8, [R7]	;read cache status
		UBFX  R0, R8, #3, #1	;BIT3 of cache status register ind
		CMP   R0, #0
		BNE   CacheWapDone  	; Cache wapping done		
      MOV   R7, #0
      MOV   R8, #0
      BX    LR
      
Enable_Cache:
      LDR   R0, =CACHESETUP_ADDR
      LDR   R1, [R0]
      MOV   R7, #1
      BFI   R1, R7, #0, #1  //SET bit0
      LDR   R7, = CACHE_KEY_ADDR
      LDR   R8, = CACHE_KEY
      STR   R8, [R7]     //write cache key
      STR   R1, [R0]
      MOV   R7, #0
      MOV   R8, #0
      BX    LR

Reset_Loop:
       B    Reset_Loop

Nmi_Handler
HardFault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler
WakeUp_Int_Handler
Ext_Int0_Handler
Ext_Int1_Handler
Ext_Int2_Handler
Ext_Int3_Handler
Ext_Int4_Handler
Ext_Int5_Handler
Ext_Int6_Handler
Ext_Int7_Handler
Ext_Int8_Handler
Ext_Int9_Handler
WDog_Tmr_Int_Handler
GP_Tmr0_Int_Handler
GP_Tmr1_Int_Handler
GP_Tmr2_Int_Handler
GP_Tmr3_Int_Handler
GP_Tmr4_Int_Handler
MDIO_Int_Handler
Flsh_Int_Handler
UART0_Int_Handler
UART1_Int_Handler
SPI0_Int_Handler
SPI1_Int_Handler
SPI2_Int_Handler
I2C0_Slave_Int_Handler
I2C0_Master_Int_Handler
I2C1_Slave_Int_Handler
I2C1_Master_Int_Handler
I2C2_Slave_Int_Handler
I2C2_Master_Int_Handler
PLA0_Int_Handler
PLA1_Int_Handler
PLA2_Int_Handler
PLA3_Int_Handler
PWMTrip_Int_Handler
PWM0_Int_Handler
PWM1_Int_Handler
PWM2_Int_Handler
PWM3_Int_Handler
SRAM_Err_Int_Handler
DMA_Err_Int_Handler
DMA_SPI0_TX_Int_Handler
DMA_SPI0_RX_Int_Handler
DMA_SPI1_TX_Int_Handler
DMA_SPI1_RX_Int_Handler
DMA_SPI2_TX_Int_Handler
DMA_SPI2_RX_Int_Handler
DMA_UART0_TX_Int_Handler
DMA_UART0_RX_Int_Handler
DMA_UART1_TX_Int_Handler
DMA_UART1_RX_Int_Handler
DMA_I2C0_STX_Int_Handler
DMA_I2C0_SRX_Int_Handler
DMA_I2C0_MTX_Int_Handler
DMA_I2C1_STX_Int_Handler
DMA_I2C1_SRX_Int_Handler
DMA_I2C1_MTX_Int_Handler
DMA_I2C2_STX_Int_Handler
DMA_I2C2_SRX_Int_Handler
DMA_I2C2_MTX_Int_Handler
DMA_MDIO_TX_Int_Handler
DMA_MDIO_RX_Int_Handler
DMA_Flsh_Int_Handler
DMA_ADC_Int_Handler
PLL_Int_Handler
HFOSC_Int_Handler
ADC_Int_Handler
SEQ_Int_Handler
COMP0_Int_Handler
COMP1_Int_Handler
COMP2_Int_Handler
COMP3_Int_Handler
VDAC_Int_Handler
LVDIE_Int_Handler
HVDIE_Int_Handler
SPI_LVD2D_Int_Handler
SPI_HVD2D_Int_Handler
SPI_LV_TX_Int_Handler
SPI_LV_RX_Int_Handler
SPI_HV_TX_Int_Handler
SPI_HV_RX_Int_Handler
DMA_TRIG0_Int_Handler  
DMA_TRIG1_Int_Handler  
DMA_SW0_Int_Handler    
DMA_SW1_Int_Handler    
DMA_CACHE_Int_Handler  
DMA_DIGCOMP_Int_Handler
UnUsed_Handler

         B UnUsed_Handler

         END


