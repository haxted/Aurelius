global idtStubTable
global loadIdt
extern mainExceptionHandler

%macro isrErrStub 1
isrStub%+%1:
    pushad
    push dword %1
    push esp
    call mainExceptionHandler
    add esp, 4
    popad
    iretd
%endmacro

%macro isrNoErrStub 1
isrStub%+%1:
    push dword 0
    pushad
    push dword %1
    push esp
    call mainExceptionHandler
    add esp, 8
    popad
    iretd
%endmacro

isrNoErrStub 0
isrNoErrStub 1
isrNoErrStub 2
isrNoErrStub 3
isrNoErrStub 4
isrNoErrStub 5
isrNoErrStub 6
isrNoErrStub 7
isrErrStub 8
isrNoErrStub 9
isrErrStub 10
isrErrStub 11
isrErrStub 12
isrErrStub 13
isrErrStub 14
isrNoErrStub 15
isrNoErrStub 16
isrErrStub 17
isrNoErrStub 18
isrNoErrStub 19
isrNoErrStub 20
isrErrStub 21
isrNoErrStub 22
isrNoErrStub 23
isrNoErrStub 24
isrNoErrStub 25
isrNoErrStub 26
isrNoErrStub 27
isrNoErrStub 28
isrNoErrStub 29
isrErrStub 30
isrNoErrStub 31

idtStubTable:
%assign i 0
%rep 32
    dd isrStub%+i
%assign i i+1
%endrep



loadIdt:
    push ebp
    mov ebp, esp

    mov eax, [ebp+8]
    lidt [eax]
    sti 

    mov esp, ebp
    pop ebp
    ret