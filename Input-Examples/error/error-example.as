; error file
mov #2047,r1
; out of range number of 12 bits
mov #2048,r2
;unkonw label
mov #892,r9
L1: .data 8191
L1: mov #3,r5
;out of range number of 14 bits
L2: .data 8192
mov L1,r3
mov L2,r4

;reserved name
jmp: .data 43
;illegal name for label
.3L4: mov #2,r5
;reserved name for label
r4: add #3,r6
;unknon command
jump L1(#3,#4)
;bad jump args
jmp L1(#3)
jmp L1(#3,tt)
jmp L1()#3,L1
jmp L1(#3,L1)
mov LOOP,r1
    ;unknown directive
    .enrie L1
STR: .string "abcdef
    ;bad number
LENGTH: .data 6,-9,1e5
; lea cant take num a source
lea #3,r4
;or for destination
lea L1,#6
;clr cant be assign with jump
clr L1(#3,#4)
;lea cant take register a source
lea r1,r4
;too much params
stop r1
;too few params
lea L1
    ;no label
.extern
.entry
;to much labels
.extern e t
.entry y l
;missing params
LR: .string
LD: .data
;invalid label
Lr$r: .data 4
;onnly label
R:
R: extern. TT
;no ""
DD: .string abf
