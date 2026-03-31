;        [] Developing 
:
;                                        Tsiolkovsky Engine - DELTA V - LIB - V0
;==================================================================================================================================+
;        DELTA VEL Tool Uing The Tsiolkovsky Engine Calc. Program, Written on x86 64 assembly
;        For Spacecraft Mission Calculations. Delta Velocity For Mission Control , Orbit Transfers , Spacecraft Navigation ...
;        
;        READ readme.md For Further Detials And Implimentations.
;        
;        
;        Architecture:          x86 - 64 (Linux)
;        Assembler:             NASM
;        Linker:                ld
;        Libs:                  libm (Maths Library)
;        Build Instructions:    Check /sputnikDV/build.sh
;==================================================================================================================================+
;
;
;


section .data
	g	  dq 9.81
	welcom_msg 	db "DELTA V - LIB ",  10
	wel_len    	equ $ - welcom_msg
	
	e_init_m	db "INITIAL MASS OF CAR", 	10
	e_init_m_len    equ $ - e_init_m 
	
	e_fin_m		db "FINAL MASS OF CAR", 	10
	e_fin_m_len    	equ $ - e_fin_m
	
	e_exaust_v	db "EXHAUST VELOCITY", 		10
	e_exaust_v_len  equ $ - e_exaust_v

section .bss
	;velocity 	resq 1
	init_m   	resq   1
	final_m  	resq   1
	delta_v  	resq   1
	eff_exhaust_v 	resq   1
	spec_impulse    resq   1

section .text 
    	
	global _start

_start:
	; print_titel
	mov rax,  1
	mov rdi,  1
	mov rsi, welcom_msg
	mov rdx, wel_len
	syscall

	;print_
	mov rax,  1
	mov rdi,  1
	mov rsi, e_init_m
	mov rdx, e_init_m_len
	syscall
	
	; read
	mov rax,  0
	mov rdi,  0
	mov rsi,  init_m
	mov rdx,  8
	syscall
	
	; print_titel
	mov rax,  1
	mov rdi,  1
	mov rsi, e_fin_m
	mov rdx, e_fin_m_len
	syscall
		; read
	mov rax,  0
	mov rdi,  0
	mov rsi,  final_m
	mov rdx,  8
	syscall
	
	; print_titel
	mov rax,  1
	mov rdi,  1
	mov rsi, e_exaust_v
	mov rdx, e_exaust_v_len
	syscall
	
	; read
	mov rax,  0
	mov rdi,  0
	mov rsi,  eff_exhaust_v
	mov rdx,  8
	syscall

	;//TODO :g Is Pointless ATP 
        
	;calc Isp
	mov rax, [eff_exhaust_v]
	mov rbx, g
	imul rax, rbx 
	mov spec_inpulse , rax
	
	;calc ln of mi/mf
	movsd xmm0, [init_m]
	movsd xmm1, [final_m]
	divsd xmm0, xmm1
	
	extern log
	call log	; works with xmm0

	mulsd xmm0, [g]
	mulsd xmm0, [spec_impulse]

	; exit
	mov rax, 60
    	xor rdi, rdi
    	syscall

