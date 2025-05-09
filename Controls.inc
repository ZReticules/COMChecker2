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
	WM_KILLFOCUS event ?

	lastSelected dd ?
ends

proc LoseBlueListBox_killFocus, lpForm, lpParams, lpControl, lpEventData
	@virtObj listBox:arg LoseBlueListBox at pbx from @arg1
	ret
endp
