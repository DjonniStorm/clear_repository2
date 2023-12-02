// Lab_25.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab_25.h"
#include <windowsx.h>
#include <stdio.h>
#define MAX_LOADSTRING 100

int number = 0;
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB25, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB25));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB25));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB25);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
	char name[10] = { "lab" }; //обязательны двойные кавычки
	TCHAR nameT[10];
	OemToCharBuff(name, nameT, 10);
	static TCHAR szWindowTitle[] = _T("app");
   HWND hWnd = CreateWindow(szWindowClass, /*szTitle*//*(LPCWSTR) nameT*/ szWindowTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void Cross(HDC hdc, int cx, int cy, int size) {
	HPEN pen1 = CreatePen(PS_SOLID, 2, RGB(0, 200, 0));
	HBRUSH brush1 = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush1);
	SelectObject(hdc, pen1);

	MoveToEx(hdc, cx - size, cy, NULL);
	LineTo(hdc, cx + size, cy);
	MoveToEx(hdc, cx, cy - size, NULL);
	LineTo(hdc, cx, cy + size);
	DeleteObject(pen1);
	DeleteObject(brush1);

}
void Triangle(HDC hdc, int cx, int cy, int size) {
	HPEN pen2 = CreatePen(PS_SOLID, 2, RGB(0, 0, 200));
	HBRUSH brush2 = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush2);
	SelectObject(hdc, pen2);

	MoveToEx(hdc, cx, cy - size, NULL);
	LineTo(hdc, cx - size, cy + size);
	LineTo(hdc, cx + size, cy + size);
	LineTo(hdc, cx, cy - size);
	DeleteObject(pen2);
	DeleteObject(brush2);
}
void Circle(HDC hdc, int cx, int cy, int size) {
	HPEN pen3 = CreatePen(PS_SOLID, 2, RGB(200, 0, 0));
	HBRUSH brush3 = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush3);
	SelectObject(hdc, pen3);

	Ellipse(hdc, cx - size, cy - size, cx + size, cy + size);


	DeleteObject(pen3);
	DeleteObject(brush3);

}
void RecursiveCross(HDC hdc, int cx, int cy, int size) {
	Cross(hdc, cx, cy, size);
	if (size < 10) {
		return;
	}
	RecursiveCross(hdc, cx - size, cy, size / 2);
}
void RecursiveCross2(HDC hdc, int cx, int cy, int size) {
	
	Cross(hdc, cx, cy - size, size / 2);
	if (size < 10) {
		return;
	}
	RecursiveCross2(hdc, cx, cy - size, size / 2);
}
//треугольник
void RecursiveTriangleExample(HDC hdc, int cx, int cy, int size) {
	Triangle(hdc, cx, cy, size);
	if (size < 10) {
		return;
	}
	RecursiveTriangleExample(hdc, cx, cy - size, size / 2);
}
void Triangle2(HDC hdc, int cx, int cy, int size) {
	HPEN pen4 = CreatePen(PS_SOLID, 2, RGB(200, 0, 0));
	HBRUSH brush4 = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush4);
	SelectObject(hdc, pen4);

	MoveToEx(hdc, cx, cy + size, NULL);
	LineTo(hdc, cx + size, cy - size);
	LineTo(hdc, cx - size, cy - size);
	LineTo(hdc, cx, cy + size);

	DeleteObject(pen4);
	DeleteObject(brush4);

}
void RecursiveTriangle1(HDC hdc, int cx, int cy, int size) {
	Triangle2(hdc, cx, cy, size);
	if (size < 40) {
		return;
	}
	/*RecursiveTriangle1(hdc, cx, cy - size, size / 2);
	RecursiveTriangle1(hdc, cx - size, cy - size, size / 3);
	RecursiveTriangle1(hdc, cx + size, cy - size, size / 3);
	*/
	RecursiveTriangle1(hdc, cx + size, cy - size, size / 2);
	RecursiveTriangle1(hdc, cx - size, cy - size, size / 2);
}

void RecursiveTriangle2(HDC hdc, int cx, int cy, int size) { //???????????????
	Triangle2(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveTriangle2(hdc, cx - size, cy - size, size / 2);
	RecursiveTriangle2(hdc, cx, cy + size, size / 2);
	//RecursiveTriangle3(hdc, cx + size, cy - size, size / 2);
}
void RecursiveTriangle3(HDC hdc, int cx, int cy, int size) { //1_3
	Triangle2(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveTriangle3(hdc, cx - size, cy - size, size / 2);
	RecursiveTriangle3(hdc, cx, cy + size, size / 2);
	RecursiveTriangle3(hdc, cx + size, cy - size, size / 2);
}

void RecursiveTriangle4(HDC hdc, int cx, int cy, int size) {
	Triangle2(hdc, cx, cy, size);
	if (size < 1) {
		return;
	}

	RecursiveTriangle4(hdc, cx, cy - size, size / 2);
}

void RecursiveTriangle5(HDC hdc, int cx, int cy, int size) {
	Triangle2(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveTriangle5(hdc, cx + size, cy, size / 2);
}

void RecursiveTriangle6(HDC hdc, int cx, int cy, int size) {
	Triangle2(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveTriangle6(hdc, cx - size, cy, size / 2);
}

void RecursiveTriangle7(HDC hdc, int cx, int cy, int size) {
	Triangle2(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveTriangle7(hdc, cx, cy - size, size / 2);
	RecursiveTriangle7(hdc, cx - size, cy, size / 2);
	RecursiveTriangle7(hdc, cx + size, cy, size / 2);
}
//номер 2

void Image2(HDC hdc, int cx, int cy, int size) {
	int x1 = cx - size / 2;
	int y1 = cy - size;
	int x2 = cx + size / 2;
	int y2 = cy - size;
	int x3 = cx - size;
	int y3 = cy + size;
	int x4 = cx + size;
	int y4 = cy + size;

	HPEN pen5 = CreatePen(PS_SOLID, 2, RGB(200, 0, 0));
	HBRUSH brush5 = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush5);
	SelectObject(hdc, pen5);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);
	LineTo(hdc, x4, y4);
	LineTo(hdc, x1, y1);
	DeleteObject(pen5);
	DeleteObject(brush5);

}

void RecursiveImage2_1(HDC hdc, int cx, int cy, int size) {
	Image2(hdc, cx, cy, size);
	if (size < 5) {
		return;
	}

	RecursiveImage2_1(hdc, cx - size, cy + size, size / 2);
}

void RecursiveImage2_2(HDC hdc, int cx, int cy, int size) {
	Image2(hdc, cx, cy, size);
	if (size < 5) {
		return;
	}

	RecursiveImage2_2(hdc, cx - size, cy - size, size / 2);
}

void RecursiveImage2_3(HDC hdc, int cx, int cy, int size) {
	Image2(hdc, cx, cy, size);
	if (size < 5) {
		return;
	}

	RecursiveImage2_3(hdc, cx - size / 2, cy - size, size / 2);
	RecursiveImage2_3(hdc, cx + size / 2, cy - size, size / 2);
}

void RecursiveImage2_4(HDC hdc, int cx, int cy, int size) {
	Image2(hdc, cx, cy, size);
	if (size < 5) {
		return;
	}

	RecursiveImage2_4(hdc, cx - size, cy + size, size / 2);
	RecursiveImage2_4(hdc, cx + size, cy + size, size / 2);
}

void RecursiveImage2_5(HDC hdc, int cx, int cy, int size) {
	Image2(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveImage2_5(hdc, cx - size / 2, cy - size, size / 2);
	RecursiveImage2_5(hdc, cx + size / 2, cy - size, size / 2);
	RecursiveImage2_5(hdc, cx - size, cy + size, size / 2);
	RecursiveImage2_5(hdc, cx + size, cy + size, size / 2);
}

void RecursiveImage2_6(HDC hdc, int cx, int cy, int size) {
	Image2(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveImage2_6(hdc, cx - size, cy, size / 2);
}

void RecursiveImage2_7(HDC hdc, int cx, int cy, int size) {
	Image2(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveImage2_7(hdc, cx + size, cy, size / 2);
}

void RecursiveImage2_8(HDC hdc, int cx, int cy, int size) {
	Image2(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveImage2_8(hdc, cx - size, cy, size / 2);
	RecursiveImage2_8(hdc, cx + size, cy, size / 2);
}

void Image3(HDC hdc, int cx, int cy, int size) {
	int x1 = cx;
	int y1 = cy - size;

	int x2 = cx + size;
	int y2 = cy;

	int x3 = cx;
	int y3 = cy + size;

	int x4 = cx - size;
	int y4 = cy;

	HPEN pen6 = CreatePen(PS_SOLID, 2, RGB(200, 0, 0));
	HBRUSH brush6 = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush6);
	SelectObject(hdc, pen6);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);
	LineTo(hdc, x4, y4);
	LineTo(hdc, x1, y1);
	DeleteObject(pen6);
	DeleteObject(brush6);


}

void RecursiveImage3_1(HDC hdc, int cx, int cy, int size) {
	Image3(hdc, cx, cy, size);
	if (size < 30) {
		return;
	}
	RecursiveImage3_1(hdc, cx - size, cy, size / 2);
	RecursiveImage3_1(hdc, cx + size, cy, size / 2);

}

void RecursiveImage3_2(HDC hdc, int cx, int cy, int size) {
	Image3(hdc, cx, cy, size);
	if (size < 30) {
		return;
	}
	RecursiveImage3_2(hdc, cx - size, cy, size / 2);
	RecursiveImage3_2(hdc, cx + size, cy, size / 2);
	RecursiveImage3_2(hdc, cx, cy + size, size / 2);

}

void RecursiveImage3_3(HDC hdc, int cx, int cy, int size) {
	Image3(hdc, cx, cy, size);
	if (size < 10) {
		return;
	}
	RecursiveImage3_3(hdc, cx - size, cy, size / 2);
	RecursiveImage3_3(hdc, cx + size, cy, size / 2);
	RecursiveImage3_3(hdc, cx, cy - size, size / 2);

}

void RecursiveImage3_4(HDC hdc, int cx, int cy, int size) {
	Image3(hdc, cx, cy, size);
	if (size < 10) {
		return;
	}
	RecursiveImage3_4(hdc, cx - size, cy, size / 2);
	RecursiveImage3_4(hdc, cx + size, cy, size / 2);
	RecursiveImage3_4(hdc, cx, cy - size, size / 2);
	RecursiveImage3_4(hdc, cx, cy + size, size / 2);

}
//как я понял произвольные 
void RecursiveImage3_5(HDC hdc, int cx, int cy, int size) {
	Image3(hdc, cx, cy, size);
	if (size < 10) {
		return;
	}
	RecursiveImage3_5(hdc, cx - size, cy, size / 2);
	RecursiveImage3_5(hdc, cx + size, cy, size / 2);
	RecursiveImage3_5(hdc, cx, cy, size / 2);

}

void RecursiveImage3_6(HDC hdc, int cx, int cy, int size) {
	Image3(hdc, cx, cy, size);
	if (size < 10) {
		return;
	}
	RecursiveImage3_6(hdc, cx - size, cy - size, size / 2);
	RecursiveImage3_6(hdc, cx + size, cy + size, size / 2);
	RecursiveImage3_6(hdc, cx, cy, size / 2);

}

void RecursiveImage3_7(HDC hdc, int cx, int cy, int size) {
	Image3(hdc, cx, cy, size);
	if (size < 10) {
		return;
	}
	RecursiveImage3_7(hdc, cx - size, cy / 2, size / 2);
	RecursiveImage3_7(hdc, cx + size, cy / 2, size / 2);
	RecursiveImage3_7(hdc, cx, cy - size, size / 2);
	RecursiveImage3_7(hdc, cx, cy + size, size / 2);

}
void Image4(HDC hdc, int cx, int cy, int size) {
	int x1 = cx;
	int y1 = cy - size;

	int x2 = cx + size / 4;
	int y2 = cy - size / 4;

	int x3 = cx + size;
	int y3 = cy;

	int x4 = cx + size / 4;
	int y4 = cy + size / 4;
	
	int x5 = cx;
	int y5 = cy + size;
	
	int x6 = cx - size / 4;
	int y6 = cy + size / 4;
	
	int x7 = cx - size;
	int y7 = cy;
	
	int x8 = cx - size / 4;
	int y8 = cy - size / 4;

	HPEN pen7 = CreatePen(PS_SOLID, 2, RGB(200, 0, 0));
	HBRUSH brush7 = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush7);
	SelectObject(hdc, pen7);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);
	LineTo(hdc, x4, y4);
	LineTo(hdc, x5, y5);
	LineTo(hdc, x6, y6);
	LineTo(hdc, x7, y7);
	LineTo(hdc, x8, y8);
	LineTo(hdc, x1, y1);
	DeleteObject(pen7);
	DeleteObject(brush7);

}

void RecursiveImage4_1(HDC hdc, int cx, int cy, int size) {
	Image4(hdc, cx, cy, size);
	if (size < 1) {
		return;
	}
	RecursiveImage4_1(hdc, cx - size, cy, size / 2);
	RecursiveImage4_1(hdc, cx + size, cy, size / 2);


}

void RecursiveImage4_2(HDC hdc, int cx, int cy, int size) {
	Image4(hdc, cx, cy, size);
	if (size < 1) {
		return;
	}
	RecursiveImage4_2(hdc, cx, cy - size, size / 2);
	RecursiveImage4_2(hdc, cx, cy + size, size / 2);


}

void RecursiveImage4_3(HDC hdc, int cx, int cy, int size) {
	Image4(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveImage4_3(hdc, cx - size, cy, size / 2);
	RecursiveImage4_3(hdc, cx, cy + size, size / 2);
	RecursiveImage4_3(hdc, cx, cy - size, size / 2);


}

void RecursiveImage4_4(HDC hdc, int cx, int cy, int size) {
	Image4(hdc, cx, cy, size);
	if (size < 20) {
		return;
	}
	RecursiveImage4_4(hdc, cx - size, cy - size, size / 2);
	RecursiveImage4_4(hdc, cx + size, cy + size, size / 2);
	RecursiveImage4_4(hdc, cx - size, cy + size, size / 2);
	RecursiveImage4_4(hdc, cx + size, cy - size, size / 2);


}

void Diamond(HDC hdc, int cx, int cy, int size) {
	int x1 = cx;
	int y1 = cy + size;

	int x2 = cx + size;
	int y2 = cy - size / 2;

	int x3 = cx + size / 2;
	int y3 = cy - size;

	int x4 = cx - size / 2;
	int y4 = cy - size;
	
	int x5 = cx - size;
	int y5 = cy - size / 2;
	

	HPEN pen8 = CreatePen(PS_SOLID, 2, RGB(0, 0, 200));
	HBRUSH brush8 = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush8);
	SelectObject(hdc, pen8);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);
	LineTo(hdc, x4, y4);
	LineTo(hdc, x5, y5);
	LineTo(hdc, x1, y1);

	DeleteObject(pen8);
	DeleteObject(brush8);

}
void RecursiveDiamond1(HDC hdc, int cx, int cy, int size) {
	Diamond(hdc, cx, cy, size);
	if (size < 10) {
		return;
	}
	RecursiveDiamond1(hdc, cx - size, cy - size, size / 2);
	RecursiveDiamond1(hdc, cx + size, cy - size, size / 2);
	RecursiveDiamond1(hdc, cx - size, cy + size, size / 2);
	RecursiveDiamond1(hdc, cx + size, cy + size, size / 2);
}

void RecursiveDiamond2(HDC hdc, int cx, int cy, int size) {
	Diamond(hdc, cx, cy, size);
	if (size < 1) {
		return;
	}
	RecursiveDiamond2(hdc, cx, cy - size, size / 2);
	RecursiveDiamond2(hdc, cx, cy + size, size / 2);
	

}

void RecursiveDiamond3(HDC hdc, int cx, int cy, int size) {
	Diamond(hdc, cx, cy, size);
	if (size < 1) {
		return;
	}
	RecursiveDiamond3(hdc, cx - size, cy, size / 2);
	RecursiveDiamond3(hdc, cx + size, cy, size / 2);


}

void chtoto(HDC hdc, int cx, int cy, int size) {
	int x1 = cx - size / 2;
	int y1 = cy - size;

	int x2 = cx + size / 2;
	int y2 = cy - size;

	int x3 = cx + size;
	int y3 = cy;

	int x4 = cx + size / 2;
	int y4 = cy + size;

	int x5 = cx - size / 2;
	int y5 = cy + size;
	
	int x6 = cx - size;
	int y6 = cy;


	HPEN pen9 = CreatePen(PS_SOLID, 2, RGB(0, 0, 200));
	HBRUSH brush9 = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush9);
	SelectObject(hdc, pen9);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);
	LineTo(hdc, x4, y4);
	LineTo(hdc, x5, y5);
	LineTo(hdc, x6, y6);
	LineTo(hdc, x1, y1);

	DeleteObject(pen9);
	DeleteObject(brush9);

}

void Recursivechtoto(HDC hdc, int cx, int cy, int size) {
	chtoto(hdc, cx, cy, size);
	if (size < 10) {
		return;
	}
	Recursivechtoto(hdc, cx, cy - size, size / 2);
	Recursivechtoto(hdc, cx, cy + size, size / 2);
	Recursivechtoto(hdc, cx - size, cy, size / 2);
	Recursivechtoto(hdc, cx + size, cy, size / 2);


}

void chtoto2(HDC hdc, int cx, int cy, int size, int angle) {
	int x1 = cx - size;
	int y1 = cy - size;

	int x2 = cx + size;
	int y2 = cy - size;

	int x3 = cx + size;
	int y3 = cy + size;

	int x4 = cx - size;
	int y4 = cy + size;


	HPEN pen = CreatePen(PS_SOLID, 2, RGB(200, 0, 0));
	HBRUSH brush = GetStockBrush(NULL_BRUSH);
	SelectObject(hdc, brush);
	SelectObject(hdc, pen);


	MoveToEx(hdc, x1 + angle / 10, y1 + angle / 5, NULL);
	LineTo(hdc, x2 - angle / 10, y2 + angle / 5);
	LineTo(hdc, x3 - angle / 10, y3 - angle / 5);
	LineTo(hdc, x4 + angle / 10, y4 - angle / 5);
	LineTo(hdc, x1 + angle / 10, y1 + angle / 5);
	
	DeleteObject(brush); DeleteObject(pen);
}

void Recursivechtoto2(HDC hdc, int cx, int cy, int size, int angle) {
	chtoto2(hdc, cx, cy, size, angle);
	if (size < 1) {
		return;
	}
	Recursivechtoto2(hdc, cx, cy, size / 2, angle / 2);
}

void status(HDC hdc) {
	SetBkColor(hdc, RGB(255, 204, 229));
	HFONT hFont = CreateFont(16, 10, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET | RUSSIAN_CHARSET, 0, 0, 0, 0, L"Roboto");
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 128));
	char str[180];
	sprintf_s(str, "picture num = %d", number);
	//sprintf_s(str2, "gold = %d", gold);
	TCHAR strT[180];
	OemToCharBuff(str, strT, 180);
	TextOut(hdc, 400, 10, (LPCWSTR)strT, _tcslen(strT));
	//TextOut(hdc, 20, 440, (LPCWSTR)strT2, _tcslen(strT2));
	DeleteObject(hFont);
}
//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			number++;
			if (number > 41)
				number = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_LEFT:
			number--;
			if (number < 0)
				number = 41;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
			switch (number)
			{
			case 0:
				Cross(hdc, 200, 160, 80);
				break;
			case 1:
				Triangle(hdc, 200, 160, 80);
				break;
			case 2:
				Circle(hdc, 200, 160, 80);
				break;
			case 3:
				RecursiveCross(hdc, 200, 160, 80);
				break;
			case 4:
				RecursiveCross2(hdc, 200, 160, 80);
				break;
			case 5:
				RecursiveTriangleExample(hdc, 200, 160, 80);
				break;
			case 6:
				Triangle2(hdc, 200, 160, 80);
				break;
			case 7:
				RecursiveTriangle1(hdc, 200, 160, 80);
				break;
			case 8:
				RecursiveTriangle2(hdc, 200, 160, 80);
				break;
			case 9:
				RecursiveTriangle3(hdc, 200, 160, 80);
				break;
			case 10:
				RecursiveTriangle4(hdc, 200, 160, 80);
				break;
			case 11:
				RecursiveTriangle5(hdc, 200, 160, 80);
				break;
			case 12:
				RecursiveTriangle6(hdc, 200, 160, 80);
				break;
			case 13:
				RecursiveTriangle7(hdc, 200, 160, 80);
				break;
			case 14:
				Image2(hdc, 200, 160, 80);
				break;
			case 15:
				RecursiveImage2_1(hdc, 200, 160, 80);
				break;
			case 16:
				RecursiveImage2_2(hdc, 200, 160, 80);
				break;
			case 17:
				RecursiveImage2_3(hdc, 200, 160, 80);
				break;
			case 18:
				RecursiveImage2_4(hdc, 200, 160, 80);
				break;
			case 19:
				RecursiveImage2_5(hdc, 200, 160, 80);
				break;
			case 20:
				RecursiveImage2_6(hdc, 200, 160, 80);
				break;
			case 21:
				RecursiveImage2_7(hdc, 200, 160, 80);
				break;
			case 22:
				RecursiveImage2_8(hdc, 200, 160, 80);
				break;
			case 23:
				Image3(hdc, 200, 160, 80);
				break;
			case 24:
				RecursiveImage3_1(hdc, 200, 160, 80);
				break;
			case 25:
				RecursiveImage3_2(hdc, 200, 160, 80);
				break;
			case 26:
				RecursiveImage3_3(hdc, 200, 160, 80);
				break;
			case 27:
				RecursiveImage3_4(hdc, 200, 160, 80);
				break;
			case 28:
				RecursiveImage3_5(hdc, 200, 160, 80);
				break;
			case 29:
				RecursiveImage3_6(hdc, 200, 160, 80);
				break;
			case 30:
				RecursiveImage3_7(hdc, 200, 160, 80);
				break;
			case 31:
				Image4(hdc, 200, 160, 80);
				break;
			case 32:
				RecursiveImage4_1(hdc, 200, 160, 80);
				break;
			case 33:
				RecursiveImage4_2(hdc, 200, 160, 80);
				break;
			case 34:
				RecursiveImage4_3(hdc, 200, 160, 80);
				break;
			case 35:
				RecursiveImage4_4(hdc, 200, 160, 80);
				break;
			case 36:
				Diamond(hdc, 200, 160, 80);
				break;
			case 37:
				RecursiveDiamond1(hdc, 200, 160, 80);
				break;
			case 38:
				RecursiveDiamond2(hdc, 200, 160, 80);
				break;
			case 39:
				RecursiveDiamond3(hdc, 200, 160, 80);
				break;
			case 40:
				chtoto(hdc, 200, 160, 80);
				break;
			case 41:
				Recursivechtoto(hdc, 200, 160, 80);
				break;
			}
			status(hdc);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
