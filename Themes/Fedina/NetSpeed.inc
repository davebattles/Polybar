[Variables]
NetSpeed_X=2261
;Left, Right or Middle
NetSpeed_Anchor=right
NetSpeed_Width=(#Font_Size#*19.5)

[Metadata]
Name=Fedina\\NetSpeed
Author=reddit.com/u/khanhas
Description=Display download and upload speed.

[NetSpeedAnchor]
Measure=String
String = #NetSpeed_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetOption NetSpeedShape X "(#Bar_OffsetX#+#*NetSpeed_X*#-#NetSpeed_Width#/2)"]
IfMatch2 = Right|right
IfMatchAction2 = [!SetOption NetSpeedShape X "(#Bar_OffsetX#+#*NetSpeed_X*#-#NetSpeed_Width#)"]

[NetSpeedShape]
Meter=Shape
X=(#Bar_OffsetX#+#NetSpeed_X#)
Y=#Bar_OffsetY#
Shape=Rectangle 0,0,#NetSpeed_Width#,#Bar_Height# | StrokeWidth 0 | Extend Color
Color = Fill Color [ColorMeasureScript:GetColor('#Color_Scheme3#', '#Color_Scheme4#', 'side to middle', #NetSpeed_X#)]
DynamicVariables=1

[NetSpeedInMeasure]
Measure=NetIn
Interface=Best
AverageSize=5
UpdateDivider=5

[NetSpeedInScale]
Measure=Script
;Desc: To maintain constant meter width, NetSpeedScaling_Common_Script scales
;      InputMeasure value by chosen unit's factor (1000 or 1024) but it always 
;      start to scale at 1000. It also appends unit to the result.
;Opts:
;      InputMeasure : NetIn or NetOut measure name.
;      NumOfNum: number of characters of output, has to be equal or larger
;                 than 3 (not including dot character).
;      Unit: Valid options:
;            db: Decimal multiples of bits (kb, Mb, Gb)
;            bb: Binary multiples of bits (Kibit, Mibit, Gibit)
;            dB: Decimal multiples of bytes (kB, MB, GB)
;            bB: Binary multiples of bytes (KiB, MiB, GiB)
;      More info about unit: https://en.wikipedia.org/wiki/Data_rate_units
ScriptFile=#@#Scripts\NetSpeedScaling_Common_Script.lua
InputMeasure=NetSpeedInMeasure
NumOfNum=4
Unit = dB
;Uncomment 2 lines below to have a space between value and unit.
;RegExpSubstitute=1
;Substitute="([^0-9\.]+)":" \1"

[NetSpeedOutMeasure]
Measure=NetOut
Interface=Best
AverageSize=5
UpdateDivider=5

[NetSpeedOutScale]
Measure=Script
ScriptFile=#@#Scripts\NetSpeedScaling_Common_Script.lua
InputMeasure=NetSpeedOutMeasure
NumOfNum=4
Unit = dB
;RegExpSubstitute=1
;Substitute="([^0-9\.]+)":" \1"

[NetSpeedInIcon]
Meter=String
Text=[\xF063]
FontFace=FontAwesome
FontSize=(#Font_Size#*15/14)
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=([NetSpeedShape:X] + [NetSpeedShape:W]/2 - ([NetSpeedInIcon:W] + [NetSpeedIn:W] + [NetSpeedOutIcon:W] + [NetSpeedOut:W] + 5*2 + 10)/2)
Y=(#Bar_OffsetY#+#Bar_Height#/2)
DynamicVariables=1

[NetSpeedIn]
Meter=String
MeasureName=NetSpeedInScale
Text=%1/s
FontFace=#Font_Face#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=5R
W=(#Font_Size#*90/14)
Y=r

[NetSpeedOutIcon]
Meter=String
MeterStyle=NetSpeedInIcon
Text=[\xF062]
X=10R

[NetSpeedOut]
Meter=String
MeterStyle=NetSpeedIn
MeasureName=NetSpeedOutScale
