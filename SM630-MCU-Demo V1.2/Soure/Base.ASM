;11.0592M 

	name   Sample

Sample_prog   SEGMENT CODE

	rseg Sample_prog

	public _DelayNuS
	public _DelayNmS



;
;
;--------------------------------------
_DelayNuS:;6+2*R7
	;
	PUSH	PSW;2

	;MOV	WDTCR,#00110000B;Feed Dog

	;
LoopD2:
	DJNZ	R7,LoopD2;R7*2

	;
	POP	PSW;2
	
	RET;2

;
;--------------------------------------
_Delay1mS:
	PUSH	PSW
	PUSH	06H;PUSH	R6
	PUSH	07H
	MOV	R6,#05H
LOOPms:
	MOV	R7,#100
	ACALL	_DelayNus
	DJNZ	R6,LOOPms

	POP	07H
	POP	06H;POP	R6
	POP	PSW
	RET

;
;--------------------------------------
_DelayNmS:
	PUSH	PSW
LOOPnms:
	ACALL	_Delay1mS
	DJNZ	R7,LOOPnms

	POP	PSW
	RET




	end
