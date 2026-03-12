@module ColoredDialog

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
irp themeName, DarkMode_Explorer, DarkMode_CFD, DarkMode_ItemsView, DarkMode_SearchBox, DarkMode_Immersive\{
	ColoredDialog.\#themeName @const du \`themeName, 0
	\common
	macro _\\{
		\forward
		dptr ColoredDialog.\#themeName
		\common
		dptr ColoredDialog.#DarkMode_Explorer
		dptr NULL
	\\}
	ColoredDialog.DarkThemes @const _
	purge _
\}
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

	bgBrush 		rptr 1
	textColor 		rd 1
	backColor		rd 1
	hIcon  			rptr 1

	hSysMenu		rptr 1
	isLight			rd 1

	changeTheme		dm this	; (isLightTheme)
ends

.proc_frame_mode_static

.proc stdcall ColoredDialog_paintGroup(.p_form, .p_params, .p_control, .p_eventData) uses psi pbx
	virtObj .form ColoredDialog at pbx from @arg1
	virtObj .control CONTROL at psi from @arg3

	.locals 
		.ps 		PAINTSTRUCT 
		.txSize		SIZE
		.textBrush 	rptr 1
		.textCoordX	rptr 1
	.endl
	
	$call [BeginPaint]([.control.hWnd], &.ps)
	$call [GetClientRect]([.control.hWnd], &.ps.rcPaint)
	; $call [FillRect]([.ps.hdc], &.ps.rcPaint, [.form.bgBrush])
	$call [.textBrush] = [CreateSolidBrush]([.form.textColor])
	.with .controlText:String(0)
		$call [GetTextExtentPoint32A]([.ps.hdc], "P", 1, &.txSize)
		mov edx, [.txSize.cy]
		shr edx, 1
		add [.ps.rcPaint.top], edx
		$call [FrameRect]([.ps.hdc], &.ps.rcPaint, [.textBrush])
		sub [.ps.rcPaint.top], edx
		mov eax, [.txSize.cx]
		mov [.textCoordX], pax

		$call .control::getString(&.controlText)
		$call .controlText::getLpChars()
		$call [GetTextExtentPoint32A]([.ps.hdc], pax, [.controlText.len], &.txSize)

		$call [SetBkColor]([.ps.hdc], [.form.backColor])
		$call [SetTextColor]([.ps.hdc], [.form.textColor])
		$call [GetWindowPtrA]([.control.hWnd], GWL_EXSTYLE)
		and eax, WS_EX_RIGHT
		cmp eax, WS_EX_RIGHT
		jne @f
			mov eax, [.txSize.cx]
			add [.textCoordX], pax
			mov eax, [.ps.rcPaint.right]
			sub [.textCoordX], pax
			neg [.textCoordX]
		@@:
		$call .controlText::getLpChars()
		$call [TextOutA]([.ps.hdc], [.textCoordX], 0, pax, [.controlText.len])
	.end_with
	; $call [SelectClipRgn]([.ps.hdc], NULL)
	$call [DeleteObject]([.textBrush])
	$call [EndPaint]([.control.hWnd], &.ps)
	$return 0
.endp

.proc stdcall ColoredDialog_ctlColor(.p_form, .p_params, .p_eventData) uses pbx pdi
	virtObj .form ColoredDialog at pbx from @arg1
	; virtObj .params params at pdi from @arg2
	@larg pdx, @arg2
	mov pdi, [pdx + params.wParam]

	$call [SetBkColor](pdi, [.form.backColor])
	$call [SetTextColor](pdi, [.form.textColor])
	$return [.form.bgBrush] 
.endp

.proc stdcall ColoredDialod.ChangeThemeChilds(.hWnd, .vlThemeNames) uses psi
	@sarg @arg1, @arg2
	$call DLG|getPtr(@arg1)
	test eax, eax
	jz .continue
		.local .className[272]:WORD, .hThemeOld:POINTER
		$call [GetClassNameW]([.hWnd], &.className, 272)
		$call [.hThemeOld] = [OpenThemeData]([.hWnd], &.className)		
		mov psi, [.vlThemeNames]
		@@:
			$call [SetWindowTheme]([.hWnd], pointer[psi], NULL)
			$call [OpenThemeData]([.hWnd], &.className)
			cmp pax, [.hThemeOld]
			je .next
				$call [CloseThemeData](pax)
				$call [CloseThemeData]([.hThemeOld])
				jmp .continue
			.next:
			$call [CloseThemeData](pax)
			add psi, pointer.size
		cmp pointer[psi], NULL
		jne @b
	.continue:
	mov eax, esp
	ret
.endp

.proc cdecl ColoredDialog.changeTheme(.pthis, .isLight) uses pbx
	.textColors @const dd 0xECECEC, 0x0
	.backColors @const dd WND.darkThemeColor, 0xECECEC

	virtObj .this ColoredDialog at pbx from @arg1
	@larg pdx, @arg2

	mov [.this.isLight], edx


	mov eax, [.textColors + pdx * 4]
	mov [.this.textColor], eax

	mov eax, [.backColors + pdx * 4]
	mov [.this.backColor], eax

	$call [ModifyMenuA]([.this.hSysMenu], ColoredDialog.ID_MENU_THEME,\ 
			MF_BYCOMMAND or MF_STRING, ColoredDialog.ID_MENU_THEME, pointer[ColoredDialog.menuTexts + pdx * pointer.size])
	$call .this::setCaptionColor([.this.backColor])
	cmp [.this.bgBrush], NULL
	je @f
		$call [DeleteObject]([.this.bgBrush])
	@@:
	$call [.this.bgBrush] = [CreateSolidBrush]([.this.backColor])
	mov eax, [.this.isLight]
	$call [EnumChildWindows](\
		[.this.hWnd], ColoredDialod.ChangeThemeChilds,\
		pointer[ColoredDialog.ChildThemes + pax * pointer.size]\
	)
	ret
.endp

.proc_frame_mode_previous

@endm
