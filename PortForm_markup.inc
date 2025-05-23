const _font equ "Segoe UI Variable"
const _cx 	= 255
const _cy  	= 200
$layout _cx: PortForm._cx,\
		_cy: PortForm._cy,\
		_position: absolute,\
		_orientation: vertical,\
		_align: start

	$layout _orientation: vertical,\
			_cy: content,\
			_padding_right: 5,\
			_padding_left: 5,\
			_y_sticker: EScaleMode.saveStart,\
			_cy_sticker: EScaleMode.saveStart

		$layout _orientation: horizontal,\
				_cy: content,\
				_padding: 4,\
				_padding_top:4,\
				_x_sticker: EScaleMode.saveStart,\
				_cx_sticker: EScaleMode.saveEnd

			$control ColoredGroup,\
				_text: "���������",\
				_position: background,\
				_style: WS_VISIBLE or BS_GROUPBOX,\
				_style_ex: WS_EX_RIGHT,\
				_initvals: PortForm_paintGroup

			$layout _orientation: horizontal,\
					_cy: content,\
					_space_between: 5,\
					_x_sticker: EScaleMode.simple,\
					_cx_sticker: EScaleMode.centerScale

				$layout _orientation: vertical,\
						_cy: content
					$control STATIC,\
						_cy: PortForm._pointsize,\
						_text: "��� � �������"
					$control COMBOBOX,\
						_name: comboBaud,\
						_cy: 13,\
						_style: WS_VISIBLE or WS_TABSTOP or CBS_DROPDOWNLIST
					$control STATIC,\
						_cy: PortForm._pointsize,\
						_text: "��������, ��"
					$control EDIT,\
						_name: editDelay,\
						_cy: PortForm._pointsize,\
						_style: WS_VISIBLE or WS_TABSTOP or ES_NUMBER,\
						_style_ex: WS_EX_STATICEDGE,\
						_text: "20"

					; $layout _orientation: horizontal,\
					; 		_cy: PortForm._pointsize

					; 	$control EDIT,\
					; 		_style_ex: WS_EX_STATICEDGE
					; 	$control UPDOWN,\
					; 		_cx: PortForm._pointsize,\
					; 		_style: WS_VISIBLE or UDS_AUTOBUDDY or UDS_SETBUDDYINT or UDS_ALIGNRIGHT or UDS_ARROWKEYS or UDS_NOTHOUSANDS
					; $endl
				$endl

				$layout _orientation: vertical,\
						_cy: content
					$control STATIC,\
						_cy: PortForm._pointsize,\
						_text: "���� ������"
					$control COMBOBOX,\
						_name: comboByteSize,\
						_cy: 13,\
						_style: WS_VISIBLE or WS_TABSTOP or CBS_DROPDOWNLIST or CBS_SORT
					$control STATIC,\
						_cy: PortForm._pointsize,\
						_text: "������ ������"
					$control EDIT,\
						_name: editBufSize,\
						_cy: PortForm._pointsize,\
						_style: WS_VISIBLE or WS_TABSTOP or ES_NUMBER,\
						_style_ex: WS_EX_STATICEDGE,\
						_text: "4096"

					; $layout _orientation: horizontal,\
					; 		_cy: PortForm._pointsize

					; 	$control EDIT,\
					; 		_style_ex: WS_EX_STATICEDGE
					; 	$control UPDOWN,\
					; 		_cx: PortForm._pointsize,\
					; 		_style: WS_VISIBLE or UDS_AUTOBUDDY or UDS_SETBUDDYINT or UDS_ALIGNRIGHT or UDS_ARROWKEYS or UDS_NOTHOUSANDS
					; $endl
				$endl

				$layout _orientation: vertical,\
						_cy: content
					$control STATIC,\
						_cy: PortForm._pointsize,\
						_text: "׸������"
					$control COMBOBOX,\
						_name: comboParity,\
						_cy: 13,\
						_style: WS_VISIBLE or WS_TABSTOP or CBS_DROPDOWNLIST
				$endl

				$layout _orientation: vertical
					$control STATIC,\
						_cy: PortForm._pointsize,\
						_text: "�������� ����"
					$control COMBOBOX,\
						_name: comboStopBits,\
						_cy: 13,\
						_style: WS_VISIBLE or WS_TABSTOP or CBS_DROPDOWNLIST or CBS_SORT
					$control PushButton,\
						_padding_top: 7,\
						_text: "���������",\ 
						_style: WS_VISIBLE or WS_TABSTOP,\
						_initvals: PortForm.SetupButton_clicked
				$endl
			$endl
		$endl
	$endl

	$layout _orientation: vertical,\
			_padding_right: 5,\
			_padding_left: 5,\
			_cy_sticker: EScaleMode.saveEnd,\
			_y_sticker: EScaleMode.saveStart

		$layout _orientation: vertical,\
				_padding: 4,\
				_padding_top:6,\
				_padding_bottom: 1,\
				_x_sticker: EScaleMode.saveStart,\
				_cx_sticker: EScaleMode.saveEnd

			$control ColoredGroup,\
				_text: "�����",\
				_position: background,\
				_style: WS_VISIBLE or BS_GROUPBOX,\
				_style_ex: WS_EX_RIGHT,\
				_initvals: PortForm_paintGroup
			$control EDIT,\
				_name: editIn,\
				_style: WS_VISIBLE or WS_VSCROLL or ES_READONLY or ES_MULTILINE,\
				_style_ex: WS_EX_STATICEDGE

			$layout _orientation: horizontal,\
					_align: evenly,\
					_cy: 25 %,\
					_padding_top: 4,\
					_y_sticker: EScaleMode.saveEnd,\
					_x_sticker: EScaleMode.simple,\
					_cx_sticker: EScaleMode.centerScale

				$control PushButton,\
					_name: buttonPause,\
					_cx: 25 %,\
					_padding_right: 5,\
					_x_sticker: EScaleMode.saveStart,\
					_cx_sticker: EScaleMode.saveSizeLeft,\
					_text: "����",\ 
					_style: WS_VISIBLE or WS_TABSTOP,\
					_initvals: PortForm.PauseButton_click
				$control LoseBlueListBox,\
					_cx: 20,\
					_padding_top: 2,\
					_name: listBoxOutFormat,\ 
					_style: WS_VISIBLE or WS_TABSTOP; or LBS_NOTIFY or LBS_WANTKEYBOARDINPUT 
				; $control BUTTON,\
				; 	_style: WS_VISIBLE or WS_GROUP or WS_TABSTOP or BS_AUTORADIOBUTTON,\
				; 	_text: "HEX"
				; $control BUTTON,\
				; 	_name: radioASCII,\
				; 	_style: WS_VISIBLE or WS_TABSTOP or BS_AUTORADIOBUTTON,\
				; 	_text: "ASCII"
				$control PushButton,\
					_cx: 25 %,\
					_padding_left: 5,\
					_x_sticker: EScaleMode.saveSizeRight,\
					_cx_sticker: EScaleMode.saveEnd,\
					_text: "��������",\ 
					_style: WS_VISIBLE or WS_TABSTOP or WS_GROUP,\
					_initvals: PortForm.ClearButton_click
			$endl
		$endl
	$endl

	$layout _orientation: vertical,\
			_cy: 30 %,\
			_padding_right: 5,\
			_padding_left: 5,\
			_padding_bottom: 5,\
			_cy_sticker: EScaleMode.saveEnd,\
			_y_sticker: EScaleMode.saveEnd,\
			_x_sticker: EScaleMode.saveStart,\
			_cx_sticker: EScaleMode.saveEnd

		$layout _orientation: horizontal,\
				_padding: 4,\
				_padding_top:6,\
				_padding_bottom: 1

			$control ColoredGroup,\
				_text: "����",\
				_position: background,\
				_style: WS_VISIBLE or BS_GROUPBOX,\
				_style_ex: WS_EX_RIGHT,\
				_initvals: PortForm_paintGroup
			$control DropDownEdit,\
				_name: editOut,\
				_text: "�� ������ ���������� ����� ����",\
				_style: WS_VISIBLE or WS_TABSTOP or WS_VSCROLL or ES_MULTILINE or ES_WANTRETURN,\
				_style_ex: WS_EX_STATICEDGE or WS_EX_ACCEPTFILES,\
				<_initvals: PortForm.OutEdit_drop, PortForm.OutEdit_keyDown>

			$layout _orientation: vertical,\
				_cx: 25 %,\
				_x_sticker: EScaleMode.saveEnd,\
				_padding_left: 5

				$control LoseBlueListBox,\
					_name: listBoxInFormat,\ 
					_cy: 33 %,\
					_style: WS_VISIBLE or WS_TABSTOP; or LBS_NOTIFY or LBS_WANTKEYBOARDINPUT 

				$control PushButton,\
					_name: buttonSend,\
					_cy: 34 %,\
					_text: "���������",\ 
					_style: WS_VISIBLE or BS_PUSHBUTTON or WS_TABSTOP,\
					_initvals: PortForm.SendButton_click
			$endl
		$endl
	$endl
$endl
