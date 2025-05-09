@module PortForm

	; @bss_alloc PortForm.LpMemIndex rptr 1

	; @at_start @call [PortForm.LpMemIndex] = [TlsAlloc]()
	; @at_end @call [TlsFree]([PortForm.LpMemIndex])

	struct COMReadThreadParams
		hWnd	dptr ?
		hCOM	dptr ?
		union
			struct
				hStopEvent		dptr ?
				hPauseEvent		dptr ?
				hCOMEvent 		dptr ?
				hPausedEvent	dptr ?
			ends
			_events rptr 4
		ends
		delay	dd ?
		sizeBuf	dd ?
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
		WM_CLOSE 			event PortForm_close

		@on_scaling
		@set_min_max_sizes PortForm._cx + 10, PortForm._cy, 1920, 1080

		lpParent 			dptr ?
		portName			db "COM"
		portIndex 			rb 5
		hThread 			dptr ?
		isPaused			dd ?
		threadParams 		COMReadThreadParams
		overlapped 			OVERLAPPED
		comIface 			COMIface
		strBuf  			String
		hDeviceNotify		dptr ?

		switchThread 		dm this

		include "PortForm_markup.inc"
	ends

	ShblDialog_Mem_Ex PortForm, "",  WS_VISIBLE or WS_SYSMENU or WS_MINIMIZEBOX or DS_CENTER or DS_SETFONT or WS_SIZEBOX or WS_MAXIMIZEBOX

	include "PortForm.fasm"
@endm
