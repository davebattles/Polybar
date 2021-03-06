[Variables]
StartMenu_X=0

[Metadata]
Name=Pratous\\Start Menu
Author=reddit.com/u/khanhas
Description=Click to show Windows's Start Menu

[StartMenuShape]
Meter=Shape
X=(#Bar_OffsetX#+#StartMenu_X#)
Y=#Bar_OffsetY#
Shape=Rectangle 0,0,([StartMenuButton:W]+#Bar_Height#),#Bar_Height#|StrokeWidth 0|Extend FillColor
FillColor=Fill Color 00000001
DynamicVariables=1

[StartMenuButton]
Meter=String
Text=
FontFace=Material Icons
FontSize=(#Font_Size#*16/13)
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=CenterCenter
X=([StartMenuButton:W]/2+#Bar_Height#/2)r
Y=(#Bar_Height#/2)r
SolidColor=00000001
MouseOverAction=[!SetOption StartMenuShape FillColor "Fill Color #Color_Scheme5#"][!UpdateMeter StartMenuShape][!Redraw]
MouseLeaveAction=[!SetOption StartMenuShape FillColor "Fill Color 00000001"][!UpdateMeter StartMenuShape][!Redraw]
LeftMouseUpAction =[!WriteKeyValue Variables Curr_X ([StartMenuShape:X]+#CURRENTCONFIGX#+round([StartMenuShape:X]/(#Bar_OffsetX#+#Bar_Width#))*([StartMenuShape:W]-580)) "#ROOTCONFIGPATH#\Themes\#Theme#\Additional_Comps_And_Scripts\AppLauncher.ini"][!WriteKeyValue Variables Curr_Y [SubSkinYPositionCalc] "#ROOTCONFIGPATH#\Themes\#Theme#\Additional_Comps_And_Scripts\AppLauncher.ini"][!WriteKeyValue Variables Dir [SubSkinDirectionCalc] "#ROOTCONFIGPATH#\Themes\#Theme#\Additional_Comps_And_Scripts\AppLauncher.ini"][!ToggleConfig "#ROOTCONFIG#\Themes\#Theme#\Additional_Comps_And_Scripts" "AppLauncher.ini"]
;LeftMouseDownAction=["#@#nircmd.exe" sendkeypress lwin]
DynamicVariables=1
