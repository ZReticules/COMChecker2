struct MainForm ColoredDialog
	const MAIN_COLOR 	= WND.darkThemeColor; xor 0xFFFFFF

	WM_INITDIALOG 		event MainForm_init
	WM_CTLCOLORDLG  	event ColoredDialog_ctlColor
	WM_CTLCOLOREDIT  	event ColoredDialog_ctlColor
	WM_CTLCOLORSTATIC  	event ColoredDialog_ctlColor
	WM_CTLCOLORBTN  	event ColoredDialog_ctlColor
	WM_CLOSE 			event MainForm_close
	; @on_scaling

	const _font equ "Segoe UI Variable"
	const _cx = 125
	const _cy = 150
	$layout _cx: MainForm._cx,\
			_cy: MainForm._cy,\
			_position: absolute,\
			_orientation: vertical,\
			_align: start

		$layout _orientation: vertical,\
				_padding_right: 5,\
				_padding_left: 5,\
				_padding_bottom: 5

			$layout _orientation: horizontal,\
					_cy: content,\
					_padding_top:6,\
					_padding_bottom: 1,\
					_space_between: 5,\
					_padding: 4

				$control ColoredGroup,\
					_text: "Порт",\
					_position: background,\
					_style: WS_VISIBLE or BS_GROUPBOX,\
					_style_ex: WS_EX_RIGHT,\
					_initvals: ColoredSpecial_paint
				$control COMBOBOX,\
					_name: comboPorts,\
					_style: WS_VISIBLE or WS_TABSTOP or CBS_DROPDOWNLIST or CBS_SORT,\
					_cy: 13
				$control PushButton,\
					_text: "Открыть",\ 
					_style: WS_VISIBLE or BS_DEFPUSHBUTTON or WS_TABSTOP,\
					_initvals: PushButton_сlicked
			$endl

			$layout _orientation: vertical,\
					_padding: 4,\
					_padding_top:6,\
					_padding_bottom: 1

				$control ColoredGroup,\
					_position: background,\
					_style: WS_VISIBLE or BS_GROUPBOX,\
					_style_ex: WS_EX_RIGHT,\
					_text: "Сведения",\
					_initvals: ColoredSpecial_paint
				$control STATIC,\
					_cy: PortForm._pointsize,\
					_text: "Описание"
				$control EDIT,\
					_name: edDesc,\
					_style: WS_VISIBLE or WS_VSCROLL or ES_READONLY or ES_MULTILINE,\
					_style_ex: WS_EX_STATICEDGE
				$control STATIC,\
					_name: stCreator,\
					_cy: PortForm._pointsize,\
					_text: "Производитель"
				$control EDIT,\
					_cy: PortForm._pointsize + 1,\
					_style: WS_VISIBLE or ES_READONLY,\
					_style_ex: WS_EX_STATICEDGE
				$control STATIC,\
					_cy: PortForm._pointsize,\
					_text: "Физ. имя"
				$control EDIT,\
					_cy: PortForm._pointsize + 1,\
					_style: WS_VISIBLE or ES_READONLY,\
					_style_ex: WS_EX_STATICEDGE
				$control STATIC,\
					_cy: PortForm._pointsize,\
					_text: "Служба"
				$control EDIT,\
					_cy: PortForm._pointsize + 1,\
					_style: WS_VISIBLE or ES_READONLY,\
					_style_ex: WS_EX_STATICEDGE
			$endl
		$endl
	$endl
ends

ShblDialog_Mem MainForm, "COMCheker",  WS_VISIBLE or WS_SYSMENU or WS_MINIMIZEBOX or DS_CENTER or DS_SETFONT; or WS_SIZEBOX or WS_MAXIMIZEBOX

include "MainForm.fasm"
