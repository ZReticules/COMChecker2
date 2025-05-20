proc_noprologue

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

	lastSelected dd ?
ends

proc LoseBlueListBox_killFocus uses pbx, lpForm, lpParams, lpControl, lpEventData
	virtObj .listBox:arg LoseBlueListBox at pbx from @arg3
	@call .listBox->getSelected()
	mov [.listBox.lastSelected], eax
	@call .listBox->setSelected()
	ret
endp

proc LoseBlueListBox_takeFocus, lpForm, lpParams, lpControl, lpEventData
	virtObj .listBox:arg LoseBlueListBox at pcx from @arg3
	; @call listBox->getSelected()
	; mov [listBox.lastSelected], eax
	; @call c [printf]("%d\n", pax)
	@call .listBox->setSelected([.listBox.lastSelected])
	ret
endp

proc LoseBlueListBox_keyDown uses psi, lpForm, lpParams, lpControl, lpEventData
	virtObj .params params at pcx from @arg2
	; @call c [printf]("%d, %d\n", [.params.wParam], VK_RETURN)
	switch [.params.wParam]
		case VK_RETURN
			@sarg @arg2

			local saveBx:POINTER
			mov [saveBx], pbx
			virtObj .listBox:arg LoseBlueListBox at pbx from @arg3
			@call .listBox->getSelected()
			mov [.listBox.lastSelected], eax
			mov pbx, [saveBx]

			mov pcx, [lpParams]
		case_default
			@call [DefSubclassProc]([.params.hWnd], [.params.uMsg], [.params.wParam], [.params.lParam])
	end_switch
	ret
endp

proc_resprologue
