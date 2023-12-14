; ************************************************************************************************
; ************************************************************************************************
;
;		Name:		str.asm
;		Purpose:	Convert string to number
;		Created:	6th December 2003
;		Reviewed: 	No
;		Author:		Paul Robson (paul@robsons.org.uk)
;
; ************************************************************************************************
; ************************************************************************************************

		.section code

; ************************************************************************************************
;
; 										STR$() function
;
; ************************************************************************************************

StrUnary: ;; [str$(]	
		lda 	#24 						; allocate space
		jsr 	StringTempAllocate

		inx
		jsr 	EXPEvalNumber				; get value into next slot up.
		jsr 	ERRCheckRParen

		lda 	XSNumber0-1,x
		sta 	ControlParameters+4		
		lda 	XSNumber1-1,x
		sta 	ControlParameters+5

		lda 	#34 						; convert number to string
		jsr 	DoMathCommand
		dex

		rts

		.send code

; ************************************************************************************************
;
;									Changes and Updates
;
; ************************************************************************************************
;
;		Date			Notes
;		==== 			=====
;
; ************************************************************************************************
