FR_40           EQU     2       ; offset to 40 column ROM functions

DefBIOS:        MACRO
FR_\1           EQU     \2
FR_\1_40        EQU     \2+FR_40
                ENDM

        DefBIOS WrChar,$00      ; D=char auto advance
        DefBIOS CursorPos,$04   ; B=row, C=column
        DefBIOS CursorUp,$08
        DefBIOS CursorDown,$0C
        DefBIOS CursorLeft,$10
        DefBIOS CursorRt,$14
        DefBIOS DoCr,$18
        DefBIOS CEL,$1C
        DefBIOS CES,$20
        DefBIOS CharIns,$24
        DefBIOS CharDel,$28
        DefBIOS LineIns,$2C
        DefBIOS LineDel,$30
        DefBIOS Color,$34       ; B=color
        DefBIOS Attr,$38        ; B=bit to set/clear, C=bit value
        DefBIOS RdChrAtr,$3C    ; in  D=row, E=col
                                ; out H=row, L=col, B=char, C=attr(real)
        DefBIOS WrChrAtr,$40    ; in  D=row, E=col, B=char, C=attr(real)
                                ; out H=row, L=col
        DefBIOS RdColor,$44
        DefBIOS WrColor,$48

FR_TrkSect      EQU     $50
FR_CheckCBM     EQU     $52
FR_Bell         EQU     $54

FR_Trk40        EQU     $60
FR_SetCur40     EQU     $62
FR_LinePaint    EQU     $64
FR_ScreenPaint  EQU     $66
FR_PrtMsgBoth   EQU     $68
FR_PrtDeBoth    EQU     $6A
FR_UpdateIt     EQU     $6C

FR_ASCIIToPet   EQU     $70
FR_CurAdr40     EQU     $72
FR_CurAdr80     EQU     $74
FR_LookColor    EQU     $76

FR_BlkFill      EQU     $7A     ; HL passed on the stack
FR_BlkMove      EQU     $7C     ; "
FR_CharInst     EQU     $7E     ; "

BCALL:  MACRO
        ld      l,FR_\1
        rst     $28
        ENDM

BIOS_CmpHlDe        EQU     $100-6
BIOS_WriteMemory    EQU     $180+0
BIOS_ReadMemory     EQU     $180+3
BIOS_SetUpdateAdr   EQU     $180+6
BIOS_Wait           EQU     $180+9
BIOS_PrintText      EQU     $534
BIOS_InitCharset    EQU     $5BD

BIOS_LDIR_RET           EQU     $0A8B
BIOS_8502               EQU     $0D22
BIOS_8502_Size          EQU     $1C3
BIOS_CPUSwitch          EQU     $0EE5
BIOS_CPUSwitch_Size     EQU     31
BIOS_MMUConfig          EQU     $0FAA
BIOS_MMUConfig_Size     EQU     11
BIOS_MMUConfig_Last     EQU     BIOS_MMUConfig+BIOS_MMUConfig_Size-1

