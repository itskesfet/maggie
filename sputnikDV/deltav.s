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
;        Assembler:             NASM & GCC 
;								(Comment out as needed _start/main )
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

	opt1 		db "OPT 1. Orbit attainment feasibility?", 	10
	opt1_len 	equ $ - opt1
	opt2 		db "OPT 2. Required fuel mass?", 		10
	opt2_len 	equ $ - opt2
	opt3 		db "OPT 3. Engine efficiency level?", 		10
	opt3_len 	equ $ - opt3
	opt4 		db "OPT 4. Maximum mission range?", 		10
	opt4_len 	equ $ - opt4

	;OPT`s
	
	opt1_1		dq "Required Orbital Velocity:	",		10
	opt1_1_len	equ $ - opt1_1
	opt1_1_1	db "Not Feasible",				10
	opt1_1_1_len	equ $ - opt1_1_1
	opt1_1_2	db "Feasible With Margine:	",		10
	opt1_1_2_len	equ $ - opt1_1_2

	opt2_msg	db "OPT 2: Fuel required calculation", 10
	opt2_msg_len 	equ $ - opt2_msg



	;terminal clear
	clear_seq db 27, "[2J", 27, "[H"
	clear_len equ $ - clear_seq

	;wait key
	key_buf resb 1

section .bss
	input_buf   	resb   32
	del_velocity 	resq   1
	
	init_m   	resq   1
	final_m  	resq   1
	delta_v  	resq   1
	eff_exhaust_v 	resq   1
	spec_impulse    resq   1

	;usr opt
	disp_options 	resq   1
	
	;opt1
	required_dv	resq   1
	margine		resq   1

	;opt2
	fuel_required	resq   1
	
section .text 

global main
extern exp
;global _start

main:
;_start:

 ;init() 	equate del_v formula.
 init:
	;print_titel
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
	
	
	;TODO rem this bloack
	;calc Isp
	;mov rax, [eff_exhaust_v]
	;mov rbx, g
	;imul rax, rbx 
	;mov spec_inpulse , rax
	
	;calc ln of mi/mf
	movsd xmm0, [init_m]
	movsd xmm1, [final_m]
	divsd xmm0, xmm1
	
	extern log
	call log	; works with xmm0
	
	;TODO rem this
	;mulsd xmm0, [g]
	;TODO fixed
	mulsd xmm0, [eff_exhaust_v]
	movsd   [del_velocity],	xmm0
options:

    	mov rax, 1          
    	mov rdi, 1          
    	mov rsi, opt1
    	mov rdx, opt1_len
    	syscall

    	mov rax, 1
    	mov rdi, 1
    	mov rsi, opt2
    	mov rdx, opt2_len
    	syscall

    	mov rax, 1
    	mov rdi, 1
    	mov rsi, opt3
    	mov rdx, opt3_len
    	syscall

    	mov rax, 1
    	mov rdi, 1
    	mov rsi, opt4
    	mov rdx, opt4_len
    	syscall

	;read opt (either bw 1-4)
	mov rax,  0
	mov rdi,  0
	mov rsi,  disp_options 	
	mov rdx,  8
	syscall

	;TODO branch based on input
	


f_opt1:
	;OPT 1. Orbit attainment feasibility?
	mov rax,  1
	mov rdi,  1
	mov rsi,  opt1_1
	mov rdx,  opt1_1_len
	syscall

;	mov rax, 0
;	mov rdi, 0
;	mov rsi, input_buf
;	mov rdx, 32
;	syscall

;	mov rdi, input_buf
;	xor rsi, rsi

;	sub rsp, 8
;	call strtod
;	add rsp, 8

;	movsd [required_dv], xmm0

	movsd xmm0, [del_velocity]
	movsd xmm1, [required_dv]
	ucomisd xmm0, xmm1
	JAE f_opt1_ORBIT_FEASIBIL

	mov rax,  1
	mov rdi,  1
	mov rsi,  opt1_1_1
	mov rdx,  opt1_1_1_len
	syscall
	
	JMP options
	
	

f_opt1_ORBIT_FEASIBIL:
	mov rax,  1
	mov rdi,  1
	mov rsi,  opt1_1_2
	mov rdx,  opt1_1_2_len
	syscall
	
	mov rax,  1
	mov rdi,  1
	mov rsi,  opt1_1
	mov rdx,  opt1_1_len
	syscall
		
	movsd xmm0, [del_velocity]
	movsd xmm1, [required_dv]
	subsd xmm0, xmm1
	
	movsd [margine], xmm0
	
	;TODO print margin 
	;mov rax,  1
	;mov rdi,  1
	;mov rsi,  margine
	;mov rdx,  8
	;syscall


f_opt2:
   	 ; Print header
   	 mov rax, 1
   	 mov rdi, 1
   	 mov rsi, opt2_msg
   	 mov rdx, opt2_msg_len
   	 syscall
	

 	 movsd xmm0, [required_dv]
 	 movsd xmm1, [eff_exhaust_v]

 	 divsd xmm0, xmm1
 	 xorpd xmm2, xmm2
 	 subsd xmm2, xmm0   ; 0 - (dv/ve)   


	 movapd xmm0, xmm2
    	 sub 	rsp, 8
    	 call 	exp  		; exp xmm0               	 
	 add 	rsp, 8		; xmm0 e^(-dv/ve)
	 movsd  xmm1, [one]
   	 subsd  xmm1, xmm0	
   	 movsd  xmm0, [init_m]
   	 mulsd  xmm0, xmm1
    	 movsd  [fuel_required], xmm0
    	 jmp 	options


pgm_exit:	
	; exit
	mov rax, 60
    	xor rdi, rdi
    	syscall

clear_screen:
    mov rax, 1  
    mov rdi, 1 
    mov rsi, clear_seq
    mov rdx, clear_len
    syscall
    ret

wait_key:
    mov rax, 0
    mov rdi, 0
    mov rsi, key_buf
    mov rdx, 1      
	syscall
    ret
