[Variables]
Awesome_X =0
;Left, Right or Center
Awesome_Anchor=middle

[Metadata]
Name=Gruvbox\\Awesome Command Center
Author=reddit.com/u/ibattlemonsters
Description=AwesomeWM inspired Command Center

[AwesomeShape]
Meter=Shape
X=(#Bar_OffsetX#+#Awesome_X#)
Y=#Bar_OffsetY#
Shape=Rectangle 0,0,([AwesomeButton:W]+#Bar_Height#),#Bar_Height#|StrokeWidth 0|Extend FillColor
FillColor=Fill Color 00000001
DynamicVariables=1

; [LauncherShape]
; Meter=Shape
; X=(#WORKAREAWIDTH#/2)
; Y=(#WORKAREAHEIGHT#/2)
; Shape=Rectangle 0,0,100,100 | Extend MyModifiers1
; MyModifiers1=Fill Color 191,237,239,255 | StrokeWidth 4 | Stroke Color 46,115,31,255

[AwesomeButton]
Meter=String
Text=
FontFace=Material Icons
FontSize=(#Font_Size#*16/13)
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=CenterCenter
X=([AwesomeButton:W]/2+#Bar_Height#/2)r
Y=(#Bar_Height#/2)r
SolidColor=00000001
MouseOverAction=[!SetOption AwesomeShape FillColor "Fill Color #Color_Scheme5#"][!UpdateMeter AwesomeShape][!Redraw]
MouseLeaveAction=[!SetOption AwesomeShape FillColor "Fill Color 00000001"][!UpdateMeter AwesomeShape][!Redraw]
; LeftMouseDownAction =[!SetOption LauncherShape FillColor "Fill Color 00000001"][!UpdateMeter LauncherShape][!Redraw]
;LeftMouseDownAction=["#@#nircmd.exe" sendkeypress lwin]
DynamicVariables=1

[AwesomeAnchor]
Measure=String
String = #Awesome_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetOption AwesomeIcon X "(#Bar_OffsetX#+#*Awesome_X*#-([*AwesomeIcon:W*]+[*Awesome:W*]+10)/2)"][!SetOption Awesome X 10R]
IfMatch2 = Right|right
IfMatchAction2 = [!SetOption Awesome StringAlign RightCenter][!SetOption AwesomeIcon X "([*Awesome:X*]-[*AwesomeIcon:W*]-10)"][!SetOption Awesome X "(#Bar_OffsetX#+#*Awesome_X*#)"]
