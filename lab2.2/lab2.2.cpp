#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("lab2.2");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("lab2.2"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

BOOLEAN f = 0;
HDC hdc;
int count = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HGDIOBJ pen;
	HWND win1;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	switch (message)		 // Обработчик сообщений
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		if (f)
		{
			pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
			SelectObject(hdc, pen);
			Rectangle(hdc, 100, 150, 200, 300);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_RBUTTONUP:
		win1 = FindWindow(TEXT("lab2.1"), NULL);
		if (!win1) {
			TCHAR czCommandLine[] = TEXT("");
			CreateProcess(L"C:\\Users\\Егор\\source\\repos\\lab2\\lab2.1\\Debug\\lab2.1.exe",
				czCommandLine,
				NULL,
				NULL,
				FALSE,
				NULL,
				NULL,
				NULL,
				&si,
				&pi);


		}
		break;
	case WM_USER + 3:
		PostMessage(hWnd, WM_DESTROY, 0, 0);
		break;
	case WM_USER + 1:
		if (count < 1) {
			MessageBox(hWnd, TEXT("Message accept"), TEXT("Mirza"), NULL);
		}
		else {
			f = 1;
		}
		count++;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
