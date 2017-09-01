        SECTION "LoadAddress",CODE[$1BFF]
        DW      $1C01

        SECTION "BasicStub",CODE[$1C01]
        ; SYS 7200
        DB      $0B, $08, $0A, $00, $9E, $37, $32, $30, $30, $00, $00, $00

        SECTION "Code",CODE[$1C20]
        rts