[Variables]
StartMenu_X=15

[Metadata]
Name=Papirus\\Start Menu
Author=reddit.com/u/khanhas
Description=Click to show Windows's Start Menu

[StartMenuShape]
Meter=Shape
X=#StartMenu_X#
Y=(#Bar_OffsetY#+#Bar_Height#/2-#Section_Height#/2)
Shape=Rectangle 0,0,(#Section_Height#),(#Section_Height#),5 | StrokeWidth 0 | Fill Color #Color_Scheme1#
DynamicVariables=1
Hidden=1

[StartMenuButton]
Meter=Image
ImageName=#ROOTCONFIGPATH#Themes\#Theme#\Additional_Comps_And_Scripts\appdrawer.png
W=(#Font_Size#*20/14)
X=(#Section_Height#/2 - [StartMenuButton:W]/2)r
Y=(#Bar_OffsetY#+#Bar_Height#/2-[StartMenuButton:H]/2)
SolidColor=0,0,0,1
MouseOverAction=[!ShowMeter StartMenuShape][!UpdateMeter StartMenuButton][!Redraw]
MouseLeaveAction=[!HideMeter StartMenuShape][!UpdateMeter StartMenuButton][!Redraw]
LeftMouseDownAction=["#@#nircmd.exe" sendkeypress lwin]
DynamicVariables=1
