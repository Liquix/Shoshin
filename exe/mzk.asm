; Listing generated by Microsoft (R) Optimizing Compiler Version 19.00.24215.1 

	TITLE	\\ahs\ahsfiles\Users\AHS-CO\Steven.Ulfelder\Personal Projects\Shoshin\Shoshin\src\mzk.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?mzk_init@@YIXPAF@Z				; mzk_init
PUBLIC	__real@3d8062d7
PUBLIC	__real@3dab5dc4
PUBLIC	__real@46fffe00
EXTRN	__fltused:DWORD
;	COMDAT __real@46fffe00
CONST	SEGMENT
__real@46fffe00 DD 046fffe00r			; 32767
CONST	ENDS
;	COMDAT __real@3dab5dc4
CONST	SEGMENT
__real@3dab5dc4 DD 03dab5dc4r			; 0.0836749
CONST	ENDS
;	COMDAT __real@3d8062d7
CONST	SEGMENT
__real@3d8062d7 DD 03d8062d7r			; 0.0626885
CONST	ENDS
; Function compile flags: /Ogspy
; File \\ahs\ahsfiles\users\ahs-co\steven.ulfelder\personal projects\shoshin\shoshin\src\mzk.cpp
;	COMDAT ?mzk_init@@YIXPAF@Z
mzkinit	SEGMENT
tv231 = -20						; size = 8
tv236 = -12						; size = 8
_i$1 = -4						; size = 4
?mzk_init@@YIXPAF@Z PROC				; mzk_init, COMDAT
; _buffer$ = ecx

; 6    : {

	push	ebp
	mov	ebp, esp
	sub	esp, 20					; 00000014H

; 7    :     for( int i=0; i<MZK_NUMSAMPLES; i++ ) 

	fld	DWORD PTR __real@3d8062d7
	xor	edx, edx
	fld	DWORD PTR __real@46fffe00
	fld	DWORD PTR __real@3dab5dc4
	mov	DWORD PTR _i$1[ebp], edx
$LN4@mzk_init:

; 8    :     {
; 9    :         const float fl = sinf( 6.2831f*440.0f * (float)i/(float)MZK_RATE );

	fild	DWORD PTR _i$1[ebp]
	fld	ST(0)
	fmul	ST(0), ST(4)
	fsin

; 10   :         const float fr = sinf( 6.2831f*587.3f * (float)i/(float)MZK_RATE );
; 11   : 
; 12   :         buffer[2*i+0] = fl*32767.0f;

	fmul	ST(0), ST(3)
	fistp	QWORD PTR tv236[ebp]
	mov	ax, WORD PTR tv236[ebp]
	mov	WORD PTR [ecx+edx*4], ax
	fmul	ST(0), ST(1)
	fsin

; 13   :         buffer[2*i+1] = fr*32767.0f;

	fmul	ST(0), ST(2)
	fistp	QWORD PTR tv231[ebp]
	mov	ax, WORD PTR tv231[ebp]
	mov	WORD PTR [ecx+edx*4+2], ax
	inc	edx
	mov	DWORD PTR _i$1[ebp], edx
	cmp	edx, 4586400				; 0045fba0H
	jl	SHORT $LN4@mzk_init
	fstp	ST(1)
	fstp	ST(1)
	fstp	ST(0)

; 14   :     }
; 15   : }

	mov	esp, ebp
	pop	ebp
	ret	0
?mzk_init@@YIXPAF@Z ENDP				; mzk_init
mzkinit	ENDS
; Function compile flags: /Ogspy
; File c:\program files (x86)\windows kits\10\include\10.0.10240.0\ucrt\math.h
;	COMDAT _sinf
_TEXT	SEGMENT
__X$ = 8						; size = 4
_sinf	PROC						; COMDAT

; 736  :         return (float)sin(_X);

	fld	DWORD PTR __X$[esp-4]
	fsin

; 737  :     }

	ret	0
_sinf	ENDP
_TEXT	ENDS
END