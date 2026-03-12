@module PortForm

include "FASM_OOP\COMPort.inc"

include "Controls.inc"
include "ColoredDialog.inc"

struct COMReadThreadParams
	hWnd	rptr 1
	hCOM	rptr 1
	union
		struct
			hStopEvent		rptr 1
			hPauseEvent		rptr 1
			hCOMEvent 		rptr 1
			hPausedEvent	rptr 1
		ends
		_events rptr 4
	ends
	delay	rd 1
	sizeBuf	rd 1
ends

struct PortForm DIALOGFORM
	const WM_COMM 		= WM_USER + 5
	const COM_BUF_SIZE 	= 4096
	const UPDATE_DELAY	= 20
	const BAUD_MAX 		= 128000
	const WIN_BUF_SIZE	= PortForm.COM_BUF_SIZE * 2

	WM_INITDIALOG 		event PortForm_init
	WM_CTLCOLORDLG  	event PortForm_ctlColor
	WM_CTLCOLOREDIT  	event PortForm_ctlColor
	WM_CTLCOLORSTATIC  	event PortForm_ctlColor
	WM_CTLCOLORLISTBOX 	event PortForm_ctlColor
	WM_CTLCOLORBTN  	event PortForm_ctlColor
	PortForm.WM_COMM	event PortForm_COMIn
	WM_DEVICECHANGE		event PortForm_deviceChange
	WM_LBUTTONDOWN 		event PortForm_mouseButtonDown
	WM_RBUTTONDOWN 		event PortForm_mouseButtonDown
	WM_SYSCOMMAND 		event PortForm_sysCommand
	; WM_VKEYTOITEM		event PortForm_itemKey
	WM_EXITSIZEMOVE 	event PortForm_exitSizeMove
	WM_CLOSE 			event PortForm_close

	@on_scaling
	@set_min_max_sizes PortForm._cx + 10, PortForm._cy, 1920, 1080

	lpParent 			rptr 1
	hSysMenu  			rptr 1
	portName			db "COM"
	portIndex 			rb 5
	hThread 			rptr 1
	isPaused			rd 1
	threadParams 		COMReadThreadParams
	overlapped 			OVERLAPPED
	comIface 			COMIface
	strBuf  			String
	hDeviceNotify		rptr 1

	switchThread 		dm this

	include "PortForm_markup.inc"
ends

ShblDialog_Mem_Ex PortForm, "",  WS_VISIBLE or WS_SYSMENU or WS_MINIMIZEBOX or DS_CENTER or DS_SETFONT or WS_SIZEBOX or WS_MAXIMIZEBOX

include "PortForm.fasm"

@endm
