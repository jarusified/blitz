#include<windows.h>

LRESULT CALLBACK MainWindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam){
  LRESULT result=0;
  switch (message) {
    case WM_SIZE:{
      OutputDebugStringA("SIZE\n");
    } break;
    case WM_DESTROY:{
      OutputDebugStringA("DESTROY\n");
    } break;
    case WM_CLOSE:{
      OutputDebugStringA("CLOSE\n");
    } break;
    case WM_ACTIVATEAPP:{
      OutputDebugStringA("ACTIVATE\n");
    } break;
    case WM_PAINT:{
      PAINTSTRUCT paint;
      HDC deviceContext = BeginPaint(window,&paint);
      int X = paint.rcPaint.left;
      int Y = paint.rcPaint.right;
      int height = paint.rcPaint.bottom - paint.rcPaint.top;
      int width  = paint.rcPaint.right - paint.rcPaint.left;
      PatBlt(deviceContext,X,Y,width,height,WHITENESS);
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
   	WindowClass.lpfnWndProc=MainWindowCallback;
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
        		for(;;){
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
