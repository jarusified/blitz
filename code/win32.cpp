#include<windows.h>
#include<stdint.h>
#define internal static
#define local_persist static
#define global_variable static

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

global_variable bool running;
global_variable BITMAPINFO bitmapInfo;
global_variable void *bitmapMemory;
global_variable int bitmapWidth;
global_variable int bitmapHeight;

internal void win32ResizeDIBSection(int width, int height){
    if(bitmapMemory){
        VirtualFree(bitmapMemory,0,MEM_RELEASE);
    }
    bitmapWidth = width;
    bitmapHeight = height;
	bitmapInfo.bmiHeader.biSize= sizeof(bitmapInfo.bmiHeader);
	bitmapInfo.bmiHeader.biWidth = bitmapWidth;
	bitmapInfo.bmiHeader.biHeight = -bitmapHeight;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
    
    int bytePerPixel = 4;
    int bitmapMemorySize = (width*height)*bytePerPixel;    
    bitmapMemory = VirtualAlloc(0,bitmapMemorySize,MEM_COMMIT, PAGE_READWRITE);
    int pitch = width*bytePerPixel;
    uint8 *row = (uint8 *)bitmapMemory;
    for(int y=0; y<bitmapHeight; y++){
        uint8 *pixel = (uint8 *)row; 
        for(int x=0;x<bitmapWidth;x++){
            *pixel = (uint8)x;
            ++pixel;
            *pixel = (uint8)y;
            ++pixel;
            *pixel = 0;
            ++pixel;
            *pixel = 0;
            ++pixel;
        }
        row+= pitch;
    }
}


internal void win32UpdateWindow(HDC deviceContext,RECT *windowRect, int x,int y, int width,int height){
	int windowWidth = windowRect->right - windowRect->left;
    int windowHeight= windowRect->bottom - windowRect->top;

    StretchDIBits(deviceContext,0,0,bitmapWidth,bitmapHeight,0,0,windowWidth,windowHeight,bitmapMemory,&bitmapInfo,DIB_RGB_COLORS,SRCCOPY);
}

LRESULT CALLBACK win32MainWindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam){
  LRESULT result=0;
  switch (message) {
    case WM_SIZE:{
	RECT clientRect;   
      	GetClientRect(window,&clientRect);
      	int height =  clientRect.right - clientRect.left;
      	int width  =  clientRect.bottom - clientRect.top;
	win32ResizeDIBSection(width,height);
	OutputDebugStringA("SIZE\n");
    } break;
    case WM_DESTROY:{
	running = false;
	OutputDebugStringA("DESTROY\n");
    } break;
    case WM_CLOSE:{
	running = false;
	OutputDebugStringA("CLOSE\n");
    } break;
    case WM_ACTIVATEAPP:{
      	OutputDebugStringA("ACTIVATE\n");
    } break;
    case WM_PAINT:{
	// we are using gdi ( a windows specific library)
	
     	PAINTSTRUCT paint;
     	HDC deviceContext = BeginPaint(window,&paint);
      	int X = paint.rcPaint.left;
      	int Y = paint.rcPaint.right;
      	int height = paint.rcPaint.bottom - paint.rcPaint.top;
      	int width  = paint.rcPaint.right - paint.rcPaint.left;
	    RECT clientRect;
        GetClientRect(window,&clientRect);
        win32UpdateWindow(deviceContext,&clientRect,X,Y,width,height);
	    EndPaint(window,&paint);
    }
    default:{
    //  OutputDebugStringA("DEFAULT\n");
    	result = DefWindowProc(window,message,wParam,lParam);
    } break;
  }
  return result;
}

int CALLBACK WinMain(HINSTANCE instance,HINSTANCE prevInstance,LPSTR commandLine,int showCode){
	WNDCLASS WindowClass={};
   	WindowClass.style=CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
   	WindowClass.lpfnWndProc=win32MainWindowCallback;
    	WindowClass.hInstance=instance;
    	//WindowClass.hIcon;
   	WindowClass.lpszClassName="blitz";
   	if(RegisterClass(&WindowClass)){
      		HWND windowHandle = CreateWindowEx( 0,
                                          WindowClass.lpszClassName,
                                          "Blitz",
                                          WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                          CW_USEDEFAULT,
                                          CW_USEDEFAULT,
                                          CW_USEDEFAULT,
                                          CW_USEDEFAULT,
                                          0,
                                          0,
                                          instance,
                                          0);
      		if(windowHandle){
        		MSG message;
			running = true;
        		while(running) {
         			BOOL messageResult = GetMessage(&message,0,0,0);
          			if(messageResult>0){
            				TranslateMessage(&message);
            				DispatchMessage(&message);
          			}
          			else{
            				break;
          			}
        		}
      		}
	      	else{	
	
      		}	
    	}
    	else{	

    	}		
	return 0;
}
