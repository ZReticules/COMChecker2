struct PushButton BUTTON
	BN_CLICKED event ?
ends

struct ColoredGroup BUTTON
	WM_PAINT hook ?
ends

struct SelChangeCombo COMBOBOX
	CBN_SELCHANGE event ?
ends

struct LoseBlueListBox LISTBOX
	LBN_KILLFOCUS event LoseBlueListBox_killFocus

	lastSelected dd ?
ends

proc LoseBlueListBox_killFocus uses pbx, lpForm, lpParams, lpControl, lpEventData
	@virtObj listBox:arg LoseBlueListBox at pbx from @arg3
	@call listBox->getSelected()
	mov [listBox.lastSelected], eax
	@call c [printf]("%d\n", pax)
	@call listBox->setSelected()
	ret
endp
