[Variables]
Tray_X=3147

[Metadata]
Name=Papirus\\Tray
Author=reddit.com/u/khanhas
Description=Click to show tray

[TrayShape]
Meter=Shape
X=#Tray_X#
Y=(#Bar_OffsetY#+#Bar_Height#/2-#Section_Height#/2)
Shape=Rectangle 0,0,(#Section_Height#),(#Section_Height#) | StrokeWidth 0 | Fill Color #Color_Scheme1#
DynamicVariables=1
LeftMouseDownAction=["#@#ActivateTray.exe" "[TrayXPos]" "[SubSkinYPositionCalc]" "[SubSkinDirectionCalc]"]

[TrayXPos]
Measure=Calc
Formula=#CURRENTCONFIGX#+[TrayButton:X]+[TrayButton:W]/2
DynamicVariables=1

[TrayButton]
Meter=Image
ImageName=#ROOTCONFIGPATH#Themes\#Theme#\Additional_Comps_And_Scripts\traymenu.png
ImageRotate=(180*(1-[SubSkinDirectionCalc]))
ImageTint=#Color_Scheme2#
W=(#Font_Size#)
X=(#Section_Height#/2 - [TrayButton:W]/2)r
Y=(#Bar_OffsetY#+#Bar_Height#/2-[TrayButton:H]/2)
DynamicVariables=1
AntiAlias=1
