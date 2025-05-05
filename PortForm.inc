struct PortForm ColoredDialog
	const MAIN_COLOR 	= WND.darkThemeColor; xor 0xFFFFFF

	WM_INITDIALOG 		event PortForm_init
	WM_CTLCOLORDLG  	event ColoredDialog_ctlColor
	WM_CTLCOLOREDIT  	event ColoredDialog_ctlColor
	WM_CTLCOLORSTATIC  	event ColoredDialog_ctlColor
	WM_CTLCOLORBTN  	event ColoredDialog_ctlColor
	WM_CLOSE 			event PortForm_close
	@on_scaling
	@set_min_max_sizes PortForm._cx + 10, PortForm._cy

	const _font equ "Segoe UI Variable"
	const _cx 			= 255
	const _cy  			= 200
	$layout _cx: PortForm._cx,\
			_cy: PortForm._cy,\
			_position: absolute,\
			_orientation: vertical,\
			_align: start

		$layout _orientation: vertical,\
				_cy: 25 %,\
				_padding_right: 5,\
				_padding_left: 5,\
				_y_sticker: 1,\
				_cy_sticker: 1

			$layout _orientation: horizontal,\
					_padding: 4,\
					_padding_top:4,\
					_x_sticker: 1,\
					_cx_sticker: 2

				$control ColoredGroup,\
					_text: "Параметры",\
					_position: background,\
					_style: WS_VISIBLE or BS_GROUPBOX,\
					_style_ex: WS_EX_RIGHT,\
					_initvals: ColoredSpecial_paint

				$layout _orientation: horizontal,\
						_space_between: 5,\
						_x_sticker: 0,\
						_cx_sticker: 6

					$layout _orientation: vertical
						$control STATIC,\
							_cy: PortForm._pointsize,\
							_text: "Бит в секунду"
						$control COMBOBOX,\
							_style: WS_VISIBLE or WS_TABSTOP or CBS_DROPDOWNLIST or CBS_SORT
					$endl

					$layout _orientation: vertical
						$control STATIC,\
							_cy: PortForm._pointsize,\
							_text: "Биты данных"
						$control COMBOBOX,\
							_style: WS_VISIBLE or WS_TABSTOP or CBS_DROPDOWNLIST or CBS_SORT
					$endl

					$layout _orientation: vertical
						$control STATIC,\
							_cy: PortForm._pointsize,\
							_text: "Чётность"
						$control COMBOBOX,\
							_style: WS_VISIBLE or WS_TABSTOP or CBS_DROPDOWNLIST or CBS_SORT
					$endl

					$layout _orientation: vertical
						$control STATIC,\
							_cy: PortForm._pointsize,\
							_text: "Стоповые биты"
						$control COMBOBOX,\
							_style: WS_VISIBLE or WS_TABSTOP or CBS_DROPDOWNLIST or CBS_SORT,\
							_cy: 13
						$control PushButton,\
							_padding_top: 1,\
							_text: "Применить",\ 
							_style: WS_VISIBLE or WS_TABSTOP,\
							_initvals: PushButton_сlicked
					$endl
				$endl
			$endl
		$endl

		$layout _orientation: vertical,\
				_padding_right: 5,\
				_padding_left: 5,\
				_cy_sticker: 2,\
				_y_sticker: 1

			$layout _orientation: vertical,\
					_padding: 4,\
					_padding_top:6,\
					_padding_bottom: 1,\
					_x_sticker: 1,\
					_cx_sticker: 2

				$control ColoredGroup,\
					_text: "Вывод",\
					_position: background,\
					_style: WS_VISIBLE or BS_GROUPBOX,\
					_style_ex: WS_EX_RIGHT,\
					_initvals: ColoredSpecial_paint
				$control EDIT,\
					_style: WS_VISIBLE or WS_VSCROLL or ES_READONLY or ES_MULTILINE,\
					_style_ex: WS_EX_STATICEDGE

				$layout _orientation: horizontal,\
						_align: evenly,\
						_cy: 25 %,\
						_padding_top: 4,\
						_y_sticker: 2

					$control PushButton,\
						_text: "Стоп",\ 
						_style: WS_VISIBLE or WS_TABSTOP,\
						_initvals: PushButton_сlicked,\
						_cx: 25 %,\
						_padding_right: 5,\
						_x_sticker: 1,\
						_cx_sticker: 4
					$control PushButton,\
						_text: "Очистить",\ 
						_style: WS_VISIBLE or WS_TABSTOP,\
						_initvals: PushButton_сlicked,\
						_cx: 25 %,\
						_padding_left: 5,\
						_x_sticker: 5,\
						_cx_sticker: 2
				$endl
			$endl
		$endl

		$layout _orientation: vertical,\
				_cy: 30 %,\
				_padding_right: 5,\
				_padding_left: 5,\
				_padding_bottom: 5,\
				_cy_sticker: 2,\
				_y_sticker: 2,\
				_x_sticker: 1,\
				_cx_sticker: 2

			$layout _orientation: horizontal,\
					_padding: 4,\
					_padding_top:6,\
					_padding_bottom: 1

				$control ColoredGroup,\
					_text: "Ввод",\
					_position: background,\
					_style: WS_VISIBLE or BS_GROUPBOX,\
					_style_ex: WS_EX_RIGHT,\
					_initvals: ColoredSpecial_paint
				$control EDIT,\
					_style: WS_VISIBLE or WS_TABSTOP or WS_VSCROLL or WS_TABSTOP or ES_MULTILINE,\
					_style_ex: WS_EX_STATICEDGE

				$layout _orientation: vertical,\
					_cx: 25 %,\
					_align: center

					$control PushButton,\
						_cy: 34 %,\
						_padding_left: 5,\
						_text: "Отправить",\ 
						_style: WS_VISIBLE or BS_DEFPUSHBUTTON or WS_TABSTOP,\
						_initvals: PushButton_сlicked,\
						_x_sticker: 2
				$endl
			$endl
		$endl
	$endl
ends

ShblDialog_Mem PortForm, "PortViewer",  WS_VISIBLE or WS_SYSMENU or WS_MINIMIZEBOX or DS_CENTER or DS_SETFONT or WS_SIZEBOX or WS_MAXIMIZEBOX

include "PortForm.fasm"
