struct PushButton BUTTON
	BN_CLICKED event ?
ends

struct ColoredGroup BUTTON
	WM_PAINT hook ?
ends

struct SelChangeCombo COMBOBOX
	; CBN_DROPDOWN	event comboOpen
	CBN_SELCHANGE event ?
ends
