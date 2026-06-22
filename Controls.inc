@module Controls

struct PushButton BUTTON
	BN_CLICKED event ?
ends

struct ColoredGroup BUTTON
	WM_PAINT hook ?
ends

struct SelChangeCombo COMBOBOX
	CBN_SELCHANGE event ?
ends

struct DropDownEdit EDIT
	WM_DROPFILES 	hook ?
	WM_GETDLGCODE	hook ?
ends

struct LoseBlueListBox LISTBOX
	const SELCHANGED = WM_USER + 1

	LBN_KILLFOCUS 				event LoseBlueListBox_killFocus
	LBN_SETFOCUS 				event LoseBlueListBox_takeFocus
	WM_GETDLGCODE				hook LoseBlueListBox_getDlgCode
	LoseBlueListBox.SELCHANGED 	event NULL

	lastSelected rd 1
ends

.proc_frame_mode_static

.proc stdcall LoseBlueListBox_killFocus(.p_form, .p_params, .p_control, .p_eventData) uses pbx psi
	@sarg @arg1
	virtObj .listBox LoseBlueListBox at pbx from @arg3
	
	mov esi, [.listBox.lastSelected]
	$call [.listBox.lastSelected] = .listBox::getSelected()
	$call .listBox::setSelected()
	
	cmp esi, [.listBox.lastSelected]
		je .return

	movzx edx, word[.listBox.ID]
	or edx, LoseBlueListBox.SELCHANGED shl 16

	mov pcx, [.p_form]
	$call [SendMessageA]([pcx + DIALOGFORM.hWnd], WM_COMMAND, edx, [.listBox.hWnd])
	.return: ret
.endp

.proc stdcall LoseBlueListBox_takeFocus(.p_form, .p_params, .p_control, .p_eventData)
	virtObj .listBox LoseBlueListBox at pcx from @arg3
	$call .listBox::setSelected([.listBox.lastSelected])
	ret
.endp

.proc stdcall LoseBlueListBox_getDlgCode(.p_form, .p_params, .p_control, .p_eventData)
	@sarg @arg1, @arg2
	virtObj .params Params at pcx from @arg2
	virtObj .msg MSG at pdx from [.params.lParam]
	cmp [.params.wParam], VK_RETURN
	@block jne @fb
		cmp [.msg.message], WM_KEYDOWN
			jne @fb

		.local .saveBx:POINTER
		mov [.saveBx], pbx
		virtObj .listBox LoseBlueListBox at pbx from @arg3
		$call .listBox::getSelected()
		cmp eax, [.listBox.lastSelected]
			cmove pbx, [.saveBx]
			cmove pcx, [.p_params]
			je @fb

		mov [.listBox.lastSelected], eax

		movzx edx, word[.listBox.ID]
		or edx, LoseBlueListBox.SELCHANGED shl 16

		mov pcx, [.p_form]
		$call [SendMessageA]([pcx + DIALOGFORM.hWnd], WM_COMMAND, edx, [.listBox.hWnd])

		mov pbx, [.saveBx]
		mov pcx, [.p_params]
	@endb
	$call [DefSubclassProc]([.params.hWnd], [.params.uMsg], [.params.wParam], [.params.lParam])
	ret
.endp

.proc_frame_mode_previous

@endm
