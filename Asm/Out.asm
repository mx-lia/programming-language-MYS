.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/StaticLib.lib
ExitProcess PROTO :DWORD

EXTRN Link: proc
EXTRN Measure: proc
EXTRN Line: proc
EXTRN OutputInt: proc
EXTRN OutputStr: proc

.stack 4096

.const
	L1 SDWORD 1
	L2 SDWORD 0
	L3 BYTE "Fibonacci: 0 1 ", 0
	L4 SDWORD 3
	L5 BYTE " ", 0
	L6 SDWORD 1
	L7 SDWORD 0
	L8 BYTE "Hello ", 0
	L9 BYTE "world!", 0
	L10 BYTE "Error", 0
	L11 SDWORD 2
	L12 SDWORD 4
	L13 SDWORD 204
	L14 SDWORD 120
	L15 SDWORD 62
	L16 BYTE "Result is zero", 0
	L17 BYTE "Result is not zero", 0

.data
	buffer BYTE 256 dup(0)
	powresult SDWORD 0
	powcounter SDWORD 0
	fibonaccia SDWORD 0
	fibonaccib SDWORD 0
	fibonaccic SDWORD 0
	fibonaccii SDWORD 0
	checkzerofl SDWORD 0
	Mainstring DWORD ?
	Mainlength SDWORD 0
	Mainresult SDWORD 0
	Mainfl SDWORD 0

.code

pow PROC pownumber : SDWORD, powpower : SDWORD
	push L1
	pop powresult
	push L2
	pop powcounter
	mov eax, powcounter
	cmp eax, powpower
	jl cycle0
	jmp cyclenext0
cycle0:
	push powresult
	push pownumber
	pop eax
	pop ebx
	mul ebx
	push eax
	pop powresult
	push powcounter
	push L1
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop powcounter
	mov eax, powcounter
	cmp eax, powpower
	jl cycle0
cyclenext0:
	push powresult
	jmp local0
local0:
	pop eax
	ret
pow ENDP

fibonacci PROC fibonaccin : SDWORD
	push L2
	pop fibonaccia
	push L1
	pop fibonaccib
	push offset L3
	call OutputStr
	push L4
	pop fibonaccii
	push fibonaccin
	push L1
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop fibonaccin
	mov eax, fibonaccii
	cmp eax, fibonaccin
	jl cycle1
	jmp cyclenext1
cycle1:
	push fibonaccib
	pop fibonaccic
	push fibonaccia
	push fibonaccib
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop fibonaccib
	push fibonaccib
	call OutputInt
	push offset L5
	call OutputStr
	push fibonaccic
	pop fibonaccia
	push fibonaccii
	push L1
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop fibonaccii
	mov eax, fibonaccii
	cmp eax, fibonaccin
	jl cycle1
cyclenext1:
	ret
fibonacci ENDP

checkzero PROC checkzeron : SDWORD
	mov eax, checkzeron
	cmp eax, L2
	jz m0
	jnz m1
	je m1
m0:
	push L6
	pop checkzerofl
	jmp e0
m1:
	push L7
	pop checkzerofl
e0:
	push checkzerofl
	jmp local1
local1:
	pop eax
	ret
checkzero ENDP

main PROC
	push offset L8
	push offset L9
	pop edx
	pop edx
	push offset L9
	push offset L8
	push offset buffer
	call Link
	push eax
	pop Mainstring
	push Mainstring
	pop edx
	push Mainstring
	call Measure;
	push eax
	pop Mainlength
	mov eax, Mainlength
	cmp eax, L1
	jg m2
	jl m3
	je m3
m2:
	push Mainlength
	call fibonacci
	call Line
	jmp e1
m3:
	push offset L10
	call OutputStr
	call Line
e1:
	push pow
	push L11
	push L12
	pop edx
	pop edx
	push L12
	push L11
	call pow
	push eax
	push L13
	push L14
	push L15
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop ebx
	pop eax
	cdq
	idiv ebx
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop Mainresult
	push checkzero
	push Mainresult
	pop edx
	push Mainresult
	call checkzero
	push eax
	pop Mainfl
	mov eax, Mainfl
	cmp eax, 1
	jz m4
	jnz m5
	je m5
m4:
	push offset L16
	call OutputStr
	call Line
	jmp e2
m5:
	push offset L17
	call OutputStr
	call Line
e2:
	call ExitProcess
main ENDP
end main