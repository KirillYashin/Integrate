section .rodata
    float_two dd 2.0
    float_eight dd 8.0
    float_neg_five dd -5.0
    float_neg_two dd -2.0
    
    global f1
    global f2
    global f3
    
section .text
f1:
    push ebp
    mov ebp, esp
    sub esp, 8
    
    fld dword [ebp+8]
    fldl2e
    fmul
    fld st0
    frndint
    fsub st1, st0
    fxch st1
    f2xm1
    fld1
    fadd
    fscale
    fstp st1
    fld dword [float_two]
    faddp
    
    add esp, 8
    mov esp, ebp
    pop ebp
    ret

f2:
    push ebp
    mov ebp, esp
    sub esp, 8
    
    
    fld dword [float_neg_two]
    fld dword [ebp+8]
    fmulp
    fld dword [float_eight]
    faddp
    
    add esp, 8
    mov esp, ebp
    pop ebp
    ret
    
f3:
    push ebp
    mov ebp, esp
    sub esp, 8
    
    fld dword [float_neg_five]
    fld dword [ebp+8]
    fdivp
    
    add esp, 8
    mov esp, ebp
    pop ebp
    ret