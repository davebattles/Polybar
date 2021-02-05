#NoEnv
#NoTrayIcon

hVirtualDesktopAccessor := DllCall("LoadLibrary", "Str", A_ScriptDir . "\virtual-desktop-accessor.dll", "Ptr")
global GoToDesktopNumberProc := DllCall("GetProcAddress", Ptr, hVirtualDesktopAccessor, AStr, "GoToDesktopNumber", "Ptr")
global GetCurrentDesktopNumberProc := DllCall("GetProcAddress", Ptr, hVirtualDesktopAccessor, AStr, "GetCurrentDesktopNumber", "Ptr")
global GetDesktopCountProc := DllCall("GetProcAddress", Ptr, hVirtualDesktopAccessor, AStr, "GetDesktopCount", "Ptr")
global IsWindowOnDesktopNumberProc := DllCall("GetProcAddress", Ptr, hVirtualDesktopAccessor, AStr, "IsWindowOnDesktopNumber", "Ptr")
global MoveWindowToDesktopNumberProc := DllCall("GetProcAddress", Ptr, hVirtualDesktopAccessor, AStr, "MoveWindowToDesktopNumber", "Ptr")

_GetNumberOfDesktops() {
		return DllCall(GetDesktopCountProc)
}

_GetCurrentDesktopNumber() {
		return DllCall(GetCurrentDesktopNumberProc) + 1
}

_ChangeDesktop(n:=1) {
		DllCall(GoToDesktopNumberProc, Int, n-1)
}

_MoveCurrentWindowToDesktop(n:=1) {
		activeHwnd := _GetCurrentWindowID()
		DllCall(MoveWindowToDesktopNumberProc, UInt, activeHwnd, UInt, n-1)
}

_GetCurrentWindowID() {
		WinGet, activeHwnd, ID, A
		return activeHwnd
}

newDesktop() {
		Send ^#d
		return
}

Global mouseOverSaveLastActiveHwnd = 0

OnMessage(16687, "RainmeterWindowMessage")

RainmeterWindowMessage(wParam, lParam) { 
	If (wParam = 2) {
		current := _GetCurrentDesktopNumber()
		direction := lParam-current
		state := GetKeyState("Shift")
		if (state = 1) {
			DllCall(MoveWindowToDesktopNumberProc, UInt, mouseOverSaveLastActiveHwnd, UInt, lParam-1)
			_ChangeDesktop(lParam)
			WinActivate, ahk_id %mouseOverSaveLastActiveHwnd%
			return
		}
		If (lParam=1)
			Send #1
		Else If (lParam=2)
			Send #2
		Else If (lParam=3)
			Send #3
		Else If (lParam=4)
			Send #4
		Else If (lParam=5)
			Send #5
		Else If (lParam=6)
			Send #6
		Else If (lParam=7)
			Send #7
		Else If (lParam=8)
			Send #8
		Else If (lParam=9)
			Send #9
		Else
			Send #0
		_ChangeDesktop(lParam)
	}
	If (wParam = 3) {
		newDesktop()
	}
	If (wParam = 5) {
		mouseOverSaveLastActiveHwnd := WinExist("A")
	}
	return
}

ProgramPath = %1%
MaxDesktopVariableName = %2%
CurrentDesktopVariableName = %3%
ConfigName = %4%


global OldIndex=0
global OldMax=0

loop
{
	Sleep, 100
	IfWinNotExist, ahk_exe rainmeter.exe
		ExitApp
	currentDesktopIndex := _GetCurrentDesktopNumber()
	maxVD := _GetNumberOfDesktops()
	If (OldMax <> maxVD) {
		Run, "%ProgramPath%" !SetVariable "%MaxDesktopVariableName%" "%maxVD%" "%ConfigName%"
		OldMax := maxVD
	}
	If (OldIndex <> currentDesktopIndex) {
		Run, "%ProgramPath%" !SetVariable "%CurrentDesktopVariableName%" "%currentDesktopIndex%" "%ConfigName%"
		OldIndex := currentDesktopIndex
	}
}