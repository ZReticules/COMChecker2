importlib uxtheme,\
	SetWindowTheme,\
	OpenThemeData,\
	CloseThemeData
importlib user32,\
	GetClassNameW

struct ColoredDialog DIALOGFORM
	bgBrush 	dptr ?
	textColor 	dd ?
	backColor	dd ?
ends

proc_noprologue

proc ColoredSpecial_paint uses psi pbx, lpForm, lpParams, lpControl, lpEventData
	@virtObj form:arg ColoredDialog at pbx from @arg1
	@virtObj control:arg CONTROL at psi from @arg3

	locals 
		ps 			PAINTSTRUCT 
		txSize		SIZE
		textBrush 	dptr ?
		textCoordX	dptr ?
	endl
	
	@call [BeginPaint]([control.hWnd], addr ps)
	@call [GetClientRect]([control.hWnd], addr ps.rcPaint)
	@call [FillRect]([ps.hdc], addr ps.rcPaint, [form.bgBrush])
	@call [textBrush] = [CreateSolidBrush]([form.textColor])
	with controlText:String(0)
		@call [GetTextExtentPoint32A]([ps.hdc], "P", 1, addr txSize)
		mov edx, [txSize.cy]
		shr edx, 1
		add [ps.rcPaint.top], edx
		@call [FrameRect]([ps.hdc], addr ps.rcPaint, [textBrush])
		sub [ps.rcPaint.top], edx
		mov eax, [txSize.cx]
		mov [textCoordX], pax

		@call control->getString(addr controlText)
		@call controlText->getLpChars()
		@call [GetTextExtentPoint32A]([ps.hdc], pax, [controlText.len], addr txSize)

		@call [SetBkColor]([ps.hdc], [form.backColor])
		@call [SetTextColor]([ps.hdc], [form.textColor])
		@call [GetWindowPtrA]([control.hWnd], GWL_EXSTYLE)
		and eax, WS_EX_RIGHT
		cmp eax, WS_EX_RIGHT
		jne @f
			mov eax, [txSize.cx]
			add [textCoordX], pax
			mov eax, [ps.rcPaint.right]
			sub [textCoordX], pax
			neg [textCoordX]
		@@:
		@call controlText->getLpChars()
		@call [TextOutA]([ps.hdc], [textCoordX], 0, pax, [controlText.len])
	end_with
	@call [DeleteObject]([textBrush])
	@call [EndPaint]([control.hWnd], addr ps)
	mov eax, 0	
	ret
endp

proc ColoredDialog_ctlColor uses pbx pdi, lpForm, lpParams, lpEventData
	@sarg @arg3
	@virtObj form:arg ColoredDialog at pbx from @arg1
	@virtObj _params:arg params at pdi from @arg2

	@call [SetBkColor]([_params.wParam], [form.backColor])
	@call [SetTextColor]([_params.wParam], [form.textColor])
	mov pax, [form.bgBrush] 
	ret
endp

proc ChangeThemeChilds uses psi, hWnd, vlThemeNames
	@sarg @arg1, @arg2
	@call [GetWindowPtrA](@arg1, GWL_USERDATA)
	test eax, eax
	jz .continue
		local className:rw 257, hThemeOld:POINTER, hThemeNew:POINTER
		@call [GetClassNameW]([hWnd], addr className, 257)
		@call [hThemeOld] = [OpenThemeData]([hWnd], addr className)
		mov psi, [vlThemeNames]
		@@:
			@call [SetWindowTheme]([hWnd], pointer[psi], NULL)
			@call [OpenThemeData]([hWnd], addr className)
			cmp pax, [hThemeOld]
			je .next
				@call [CloseThemeData](pax)
				@call [CloseThemeData]([hThemeOld])
				jmp .continue
			.next:
			@call [CloseThemeData](pax)
			add psi, pointer.size
		cmp pointer[psi], NULL
		jne @b
	.continue:
	mov eax, esp
	ret
endp

proc_resprologue
