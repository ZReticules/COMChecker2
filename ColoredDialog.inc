importlib uxtheme,\
	SetWindowTheme,\
	OpenThemeData,\
	CloseThemeData
importlib user32,\
	GetClassNameW,\
	BeginPaint,\
	EndPaint,\
	GetUpdateRgn
importlib gdi32,\
	Rectangle,\
	CreateSolidBrush,\
	DeleteObject,\
	GetTextExtentPoint32A,\
	TextOutA,\
	CreateRectRgn,\
	SelectClipRgn

; du "DarkMode_Explorer", 0
; du "DarkMode_CFD", 0
; du "DarkMode_ItemsView", 0
; du "DarkMode_SearchBox", 0
; du "DarkMode_Immersive", 0
; du "DarkMode_Explorer", 0
irp themeName, DarkMode_Explorer, DarkMode_CFD, DarkMode_ItemsView,\ 
		DarkMode_SearchBox, DarkMode_Immersive{
	ColoredDialog.#themeName @const du `themeName, 0
	common
	macro _\{
		forward
		dptr ColoredDialog.#themeName
		common
		dptr ColoredDialog.#DarkMode_Explorer
		dptr NULL
	\}
	ColoredDialog.DarkThemes @const _
	purge _
}
.lightTheme 				@const du "Explorer", 0

ColoredDialog.LightThemes 	@const dptr .lightTheme, NULL
ColoredDialog.ChildThemes	@const dptr ColoredDialog.DarkThemes, ColoredDialog.LightThemes
ColoredDialog.darkText		@const db "Перейти на светлую тему", 0
ColoredDialog.lightText		@const db "Перейти на темную тему", 0
ColoredDialog.menuTexts		@const dptr ColoredDialog.darkText, ColoredDialog.lightText

struct ColoredDialog DIALOGFORM
	const ID_MENU_THEME = 1001
	
	WM_CTLCOLORDLG  	event ColoredDialog_ctlColor
	WM_CTLCOLOREDIT  	event ColoredDialog_ctlColor
	WM_CTLCOLORSTATIC  	event ColoredDialog_ctlColor
	WM_CTLCOLORLISTBOX 	event ColoredDialog_ctlColor
	WM_CTLCOLORBTN  	event ColoredDialog_ctlColor

	bgBrush 	dptr ?
	textColor 	dd ?
	backColor	dd ?
	hIcon  		dptr ?

	hSysMenu		dptr ?
	isLight			dd ?

	changeTheme		dm this	; (isLightTheme)
ends

proc_noprologue

proc ColoredDialog_paintGroup uses psi pbx, lpForm, lpParams, lpControl, lpEventData
	virtObj .form:arg ColoredDialog at pbx from @arg1
	virtObj .control:arg CONTROL at psi from @arg3

	locals 
		ps 			PAINTSTRUCT 
		txSize		SIZE
		textBrush 	dptr ?
		textCoordX	dptr ?
	endl
	
	@call [BeginPaint]([.control.hWnd], addr ps)
	@call [GetClientRect]([.control.hWnd], addr ps.rcPaint)
	; @call [FillRect]([ps.hdc], addr ps.rcPaint, [.form.bgBrush])
	@call [textBrush] = [CreateSolidBrush]([.form.textColor])
	with controlText:String(0)
		@call [GetTextExtentPoint32A]([ps.hdc], "P", 1, addr txSize)
		mov edx, [txSize.cy]
		shr edx, 1
		add [ps.rcPaint.top], edx
		@call [FrameRect]([ps.hdc], addr ps.rcPaint, [textBrush])
		sub [ps.rcPaint.top], edx
		mov eax, [txSize.cx]
		mov [textCoordX], pax

		@call .control->getString(addr controlText)
		@call controlText->getLpChars()
		@call [GetTextExtentPoint32A]([ps.hdc], pax, [controlText.len], addr txSize)

		@call [SetBkColor]([ps.hdc], [.form.backColor])
		@call [SetTextColor]([ps.hdc], [.form.textColor])
		@call [GetWindowPtrA]([.control.hWnd], GWL_EXSTYLE)
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
	; @call [SelectClipRgn]([ps.hdc], NULL)
	@call [DeleteObject]([textBrush])
	@call [EndPaint]([.control.hWnd], addr ps)
	mov eax, 0	
	ret
endp

proc ColoredDialog_ctlColor uses pbx pdi, lpForm, lpParams, lpEventData
	@sarg @arg3
	virtObj .form:arg ColoredDialog at pbx from @arg1
	virtObj .params:arg params at pdi from @arg2

	@call [SetBkColor]([.params.wParam], [.form.backColor])
	@call [SetTextColor]([.params.wParam], [.form.textColor])
	mov pax, [.form.bgBrush] 
	ret
endp

proc ColoredDialod.ChangeThemeChilds uses psi, hWnd, vlThemeNames
	@sarg @arg1, @arg2
	@call [GetWindowPtrA](@arg1, GWL_USERDATA)
	test eax, eax
	jz .continue
		local className:rw 257, hThemeOld:POINTER, hThemeNew:POINTER
		; @call [SetWindowTheme]([hWnd], L "Explorer", NULL)
		; @call .form.updCount->setTheme(L "DarkMode_Explorer")
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
			; @call c [printf]("%S:%d:%d\n", addr className, [hThemeOld], pax)
			@call [CloseThemeData](pax)
			add psi, pointer.size
		cmp pointer[psi], NULL
		jne @b
	.continue:
	mov eax, esp
	ret
endp

proc ColoredDialog.changeTheme c uses pbx, _this, isLight
	@virtObj this:arg ColoredDialog at pbx from @arg1
	@larg pdx, @arg2

	mov [this.isLight], edx

	.textColors 	@const dd 0xECECEC, 0x0
	.backColors 	@const dd WND.darkThemeColor, 0xECECEC

	mov eax, [.textColors + pdx * 4]
	mov [this.textColor], eax

	mov eax, [.backColors + pdx * 4]
	mov [this.backColor], eax

	@call [ModifyMenuA]([this.hSysMenu], ColoredDialog.ID_MENU_THEME,\ 
			MF_BYCOMMAND or MF_STRING, ColoredDialog.ID_MENU_THEME, pointer[ColoredDialog.menuTexts + pdx * pointer.size])
	@call this->setCaptionColor([this.backColor])
	cmp [this.bgBrush], NULL
	je @f
		@call [DeleteObject]([this.bgBrush])
	@@:
	@call [this.bgBrush] = [CreateSolidBrush]([this.backColor])
	mov eax, [this.isLight]
	@call [EnumChildWindows](\
		[this.hWnd], ColoredDialod.ChangeThemeChilds,\
		pointer[ColoredDialog.ChildThemes + pax * pointer.size]\
	)
	ret
endp

proc_resprologue
