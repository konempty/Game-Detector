#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <psapi.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

bool detected();
void loadimage();
bool isShow();
TCHAR **List;
size_t len;
unsigned int count, Timer = 600000;
int main()
{
	// Get the list of process identifiers.
	unsigned int i;
	char tmp[100];
	FILE * file = fopen("list.txt", "r+");
	FreeConsole();
	if (file == NULL)
		return 1;
	fscanf(file, "%d", &count);
	fgets(tmp, 99, file);
	List = (TCHAR**)malloc(sizeof(TCHAR*)*count);

	for (i = 0; i < count; i++) {
		List[i] = (TCHAR*)malloc(sizeof(TCHAR) * 201);
		fgetws(List[i], 200, file);
		len = _tcslen(List[i]) - 1;
		if (List[i][len] == '\n')
			List[i][len] = 0;
	}
	srand(time(NULL));
	fclose(file);
	while (1) {
		// Print the name and process identifier for each process.
		if (detected()) {
			loadimage();
		}

		Sleep(Timer);
		Timer = 600000;

	}

	return 0;
}

bool detected() {
	unsigned int i;
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	// Get a handle to the process.
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
	}

	HANDLE   hProcess = NULL,hHandle;
	PROCESSENTRY32 pe32 = { 0 };
	DWORD dwExitCode = 0;

	hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcess, &pe32))
	{
		do
		{
			_tcscpy(szProcessName, pe32.szExeFile);
			//_tprintf(_T("%s\n"), pe32.szExeFile);
			for (unsigned int j = 0; j < count; j++) {

				if (!_tcscmp(szProcessName, List[j])) {
					hHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pe32.th32ProcessID);
					if (TerminateProcess(hHandle, 0))
						GetExitCodeProcess(hHandle, &dwExitCode);
					CloseHandle(hProcess);
					return true;
				}
			}
		} while (Process32Next(hProcess, &pe32));
	}

	CloseHandle(hProcess);
	
	return false;
}

void loadimage() {

	IplImage* image = cvLoadImage("a.jpg", CV_LOAD_IMAGE_UNCHANGED);//이미지 불러오기
	char str[100];
	int i;
	cvDestroyAllWindows();
	/*cvNamedWindow("게임하지마세요", CV_WINDOW_NORMAL);
	cvSetWindowProperty("게임하지마세요", CV_WND_PROP_FULLSCREEN, CV_WINDOW_NORMAL);
	cvShowImage("게임하지마세요", image);//이미지 윈도우에 출력*/

	for (i = 0; i < 80; i++) {
		sprintf(str, "게임하지마세요%d", i);
		cvNamedWindow(str, CV_WINDOW_AUTOSIZE);

		moveWindow(str, rand() % 800, rand() % 800);
		cvShowImage(str, image);//이미지 윈도우에 출력
		HWND hwnd = (HWND)cvGetWindowHandle(str);
		hwnd = GetParent(hwnd);
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

		waitKey(50);

	}
	cvReleaseImage(&image);
	while (isShow() && Timer>10) {
		waitKey(10);
		Timer -= 10;
	}
	if (isShow())
		cvDestroyAllWindows();

}

bool isShow() {
	HWND hwnd;

	char str[100];
	for (int i = 0; i < 80; i++) {
		sprintf(str, "게임하지마세요%d", i);
		hwnd = (HWND)cvGetWindowHandle(str);
		if (IsWindowVisible(hwnd))
			return true;
	}
	return false;
}
