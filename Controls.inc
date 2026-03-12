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
	LBN_KILLFOCUS 	event LoseBlueListBox_killFocus
	LBN_SETFOCUS 	event LoseBlueListBox_takeFocus
	WM_GETDLGCODE	hook LoseBlueListBox_keyDown

	lastSelected rd 1
ends

.proc_frame_mode_static

.proc stdcall LoseBlueListBox_killFocus(.p_form, .p_params, .p_control, .p_eventData) uses pbx
	virtObj .listBox LoseBlueListBox at pbx from @arg3
	$call .listBox::getSelected()
	mov [.listBox.lastSelected], eax
	$call .listBox::setSelected()
	ret
.endp

.proc stdcall LoseBlueListBox_takeFocus(.p_form, .p_params, .p_control, .p_eventData)
	virtObj .listBox LoseBlueListBox at pcx from @arg3
	$call .listBox::setSelected([.listBox.lastSelected])
	ret
.endp

.proc stdcall LoseBlueListBox_keyDown(.p_form, .p_params, .p_control, .p_eventData) uses psi
	virtObj .params params at pcx from @arg2
	switch [.params.wParam]
		case VK_RETURN
			@sarg @arg2

			.local .saveBx:POINTER
			mov [.saveBx], pbx
			virtObj .listBox LoseBlueListBox at pbx from @arg3
			$call .listBox::getSelected()
			mov [.listBox.lastSelected], eax
			mov pbx, [.saveBx]

			mov pcx, [.p_params]
		case_default
			$call [DefSubclassProc]([.params.hWnd], [.params.uMsg], [.params.wParam], [.params.lParam])
	end_switch
	ret
.endp

.proc_frame_mode_previous

@endm
