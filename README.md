# COMChecker2
COMChecker2.0, обновление кода и рефакторинг  
# Описание
- Полностью поддерживает функционал оригинала
- Исправлены проблемы с безопасностью и надежностью, повышена безопасность при работе с потоками
- Добавлен бесконечный скроллинг вывода путем удаления начала при переполнении в EDIT
- Добавлены параметры задержки(ожидания между отправками пакетов) и буфера памяти(набирается чтением с порта до конца задержки или переполнения)
- Добавлено автомасштабирование формы чтения с порта
- Drag&drop файлов в поле ввода
- Отправка данных на порт по ctrl+enter
- Переключение темы(светлая/темная, по умолчанию используется как в системе)
- Выбор форматов ввода и вывода(ASCII/HEX, для HEX пробел допустим как разделитель)  

# Скриншоты

<figure>
<figcaption>Стартовая форма</figcaption>  
	<div>
		<img src="screenshots/main_dark.png" alt="Image not found" />
		<img src="screenshots/main_light.png" alt="Image not found" />
	</div>
</figure> 

<figure>
<figcaption>Смена темы</figcaption>  
	<img src="screenshots/change_theme.png" alt="Image not found" />
</figure>  

<figure>
	<figcaption>Форма порта</figcaption> 
	<div>
		<img src="screenshots/port_dark.png" alt="Image not found" />
		<img src="screenshots/port_light.png" alt="Image not found" />
	</div> 
</figure> 

# Компиляция из исходников
Для компиляции сначала клонируйте репозиторий с подмодулями  
`git clone --recurse-submodules https://github.com/ZReticules/COMChecker2`  
Затем в командной строке используя FASM со всеми пакетами макросов по умолчанию  
`fasm -m 999999 COMChecker2.fasm COMChecker2.exe`  
Для выбора архитектуры x86 в файле COMChecker2.fasm замените  
`include "FASM_OOP\x64.inc"`  
на  
`include "FASM_OOP\x86.inc"` 
