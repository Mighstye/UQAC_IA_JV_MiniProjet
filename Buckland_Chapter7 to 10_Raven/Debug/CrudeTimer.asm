; Listing generated by Microsoft (R) Optimizing Compiler Version 19.14.26431.0 

	TITLE	D:\IA jeux vid�o\Projets\UQAC_IA_JV_MiniProjet\Common\Time\CrudeTimer.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMTD
INCLUDELIB OLDNAMES

PUBLIC	??0CrudeTimer@@AAE@XZ				; CrudeTimer::CrudeTimer
PUBLIC	?Instance@CrudeTimer@@SAPAV1@XZ			; CrudeTimer::Instance
PUBLIC	__real@3f50624dd2f1a9fc
PUBLIC	__xmm@41f00000000000000000000000000000
EXTRN	__Init_thread_header:PROC
EXTRN	__Init_thread_abort:PROC
EXTRN	__Init_thread_footer:PROC
EXTRN	__imp__timeGetTime@0:PROC
EXTRN	@__security_check_cookie@4:PROC
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_InitBase:PROC
EXTRN	__RTC_Shutdown:PROC
EXTRN	___CxxFrameHandler3:PROC
EXTRN	__Init_thread_epoch:DWORD
EXTRN	___security_cookie:DWORD
EXTRN	__fltused:DWORD
EXTRN	__tls_array:DWORD
EXTRN	__tls_index:DWORD
;	COMDAT ?instance@?1??Instance@CrudeTimer@@SAPAV2@XZ@4V2@A
_BSS	SEGMENT
?instance@?1??Instance@CrudeTimer@@SAPAV2@XZ@4V2@A DQ 01H DUP (?) ; `CrudeTimer::Instance'::`2'::instance
_BSS	ENDS
;	COMDAT ?$TSS0@?1??Instance@CrudeTimer@@SAPAV2@XZ@4HA
_BSS	SEGMENT
?$TSS0@?1??Instance@CrudeTimer@@SAPAV2@XZ@4HA DD 01H DUP (?) ; TSS0<`template-parameter-2',CrudeTimer::stance,CrudeTimer * * const volatile,void,int, ?? &>
_BSS	ENDS
;	COMDAT __xmm@41f00000000000000000000000000000
CONST	SEGMENT
__xmm@41f00000000000000000000000000000 DB 00H, 00H, 00H, 00H, 00H, 00H, 00H
	DB	00H, 00H, 00H, 00H, 00H, 00H, 00H, 0f0H, 'A'
CONST	ENDS
;	COMDAT __real@3f50624dd2f1a9fc
CONST	SEGMENT
__real@3f50624dd2f1a9fc DQ 03f50624dd2f1a9fcr	; 0.001
CONST	ENDS
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
rtc$IMZ	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
__unwindtable$?Instance@CrudeTimer@@SAPAV1@XZ DD 0ffffffffH
	DD	FLAT:__unwindfunclet$?Instance@CrudeTimer@@SAPAV1@XZ$0
__ehfuncinfo$?Instance@CrudeTimer@@SAPAV1@XZ DD 019930522H
	DD	01H
	DD	FLAT:__unwindtable$?Instance@CrudeTimer@@SAPAV1@XZ
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	DD	00H
	DD	01H
xdata$x	ENDS
; Function compile flags: /Odtp /RTCsu
; File d:\ia jeux vid�o\projets\uqac_ia_jv_miniprojet\common\time\crudetimer.cpp
;	COMDAT ?Instance@CrudeTimer@@SAPAV1@XZ
_TEXT	SEGMENT
__$EHRec$ = -12						; size = 12
?Instance@CrudeTimer@@SAPAV1@XZ PROC			; CrudeTimer::Instance, COMDAT

; 5    : {

	push	ebp
	mov	ebp, esp
	push	-1
	push	__ehhandler$?Instance@CrudeTimer@@SAPAV1@XZ
	mov	eax, DWORD PTR fs:0
	push	eax
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	push	eax
	lea	eax, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:0, eax

; 6    :   static CrudeTimer instance;

	mov	eax, DWORD PTR __tls_index
	mov	ecx, DWORD PTR fs:__tls_array
	mov	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR ?$TSS0@?1??Instance@CrudeTimer@@SAPAV2@XZ@4HA
	cmp	eax, DWORD PTR __Init_thread_epoch[edx]
	jle	SHORT $LN2@Instance
	push	OFFSET ?$TSS0@?1??Instance@CrudeTimer@@SAPAV2@XZ@4HA
	call	__Init_thread_header
	add	esp, 4
	cmp	DWORD PTR ?$TSS0@?1??Instance@CrudeTimer@@SAPAV2@XZ@4HA, -1
	jne	SHORT $LN2@Instance
	mov	DWORD PTR __$EHRec$[ebp+8], 0
	mov	ecx, OFFSET ?instance@?1??Instance@CrudeTimer@@SAPAV2@XZ@4V2@A
	call	??0CrudeTimer@@AAE@XZ			; CrudeTimer::CrudeTimer
	mov	DWORD PTR __$EHRec$[ebp+8], -1
	push	OFFSET ?$TSS0@?1??Instance@CrudeTimer@@SAPAV2@XZ@4HA
	call	__Init_thread_footer
	add	esp, 4
$LN2@Instance:

; 7    : 
; 8    :   return &instance;

	mov	eax, OFFSET ?instance@?1??Instance@CrudeTimer@@SAPAV2@XZ@4V2@A

; 9    : }

	mov	ecx, DWORD PTR __$EHRec$[ebp]
	mov	DWORD PTR fs:0, ecx
	pop	ecx
	add	esp, 12					; 0000000cH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
__unwindfunclet$?Instance@CrudeTimer@@SAPAV1@XZ$0:
	push	OFFSET ?$TSS0@?1??Instance@CrudeTimer@@SAPAV2@XZ@4HA
	call	__Init_thread_abort
	pop	ecx
	ret	0
__ehhandler$?Instance@CrudeTimer@@SAPAV1@XZ:
	mov	edx, DWORD PTR [esp+8]
	lea	eax, DWORD PTR [edx+12]
	mov	ecx, DWORD PTR [edx-4]
	xor	ecx, eax
	call	@__security_check_cookie@4
	mov	eax, OFFSET __ehfuncinfo$?Instance@CrudeTimer@@SAPAV1@XZ
	jmp	___CxxFrameHandler3
text$x	ENDS
?Instance@CrudeTimer@@SAPAV1@XZ ENDP			; CrudeTimer::Instance
; Function compile flags: /Odtp /RTCsu
; File d:\ia jeux vid�o\projets\uqac_ia_jv_miniprojet\common\time\crudetimer.h
;	COMDAT ??0CrudeTimer@@AAE@XZ
_TEXT	SEGMENT
tv71 = -8						; size = 4
_this$ = -4						; size = 4
??0CrudeTimer@@AAE@XZ PROC				; CrudeTimer::CrudeTimer, COMDAT
; _this$ = ecx

; 31   :   CrudeTimer(){m_dStartTime = timeGetTime() * 0.001;}

	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	esi
	mov	DWORD PTR [ebp-8], -858993460		; ccccccccH
	mov	DWORD PTR [ebp-4], -858993460		; ccccccccH
	mov	DWORD PTR _this$[ebp], ecx
	mov	esi, esp
	call	DWORD PTR __imp__timeGetTime@0
	cmp	esi, esp
	call	__RTC_CheckEsp
	mov	DWORD PTR tv71[ebp], eax
	cvtsi2sd xmm0, DWORD PTR tv71[ebp]
	mov	eax, DWORD PTR tv71[ebp]
	shr	eax, 31					; 0000001fH
	addsd	xmm0, QWORD PTR __xmm@41f00000000000000000000000000000[eax*8]
	mulsd	xmm0, QWORD PTR __real@3f50624dd2f1a9fc
	mov	ecx, DWORD PTR _this$[ebp]
	movsd	QWORD PTR [ecx], xmm0
	mov	eax, DWORD PTR _this$[ebp]
	pop	esi
	add	esp, 8
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
??0CrudeTimer@@AAE@XZ ENDP				; CrudeTimer::CrudeTimer
_TEXT	ENDS
END
