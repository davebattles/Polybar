[Variables]
Crypto2_X =1988
;Left, Right or Center
Crypto2_Anchor=middle

[Metadata]
Name=Gruvbox\\Crypto2 DOGECOIN
Author=reddit.com/u/ibattlemonsters
Description=Display current Etherium Price

[Crypto2Anchor]
Measure=String
String = #Crypto2_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetOption Crypto2Icon X "(#Bar_OffsetX#+#*Crypto2_X*#-([*Crypto2Icon:W*]+[*Crypto2:W*]+10)/2)"][!SetOption Crypto2 X 10R]
IfMatch2 = Right|right
IfMatchAction2 = [!SetOption Crypto2 StringAlign RightCenter][!SetOption Crypto2Icon X "([*Crypto2:X*]-[*Crypto2Icon:W*]-10)"][!SetOption Crypto2 X "(#Bar_OffsetX#+#*Crypto2_X*#)"]

[Crypto2Measure]
Measure=Plugin
Plugin=Webparser
URL=https://coinmarketcap.com/currencies/dogecoin/
RegExp=(?siU)<div class="sc-16r8icm-0 kXPxnI priceTitle___1cXUG"><div class="priceValue___11gHJ">(.*)</div><span style="font-size:14px;font-weight:600;padding:5px 10px" class="sc-1v2ivon-0 iQVSWO"><span class="(.*)"></span>(.*)<!-- -->%</span></div>
UpdateRate=60

; Find the Crypto price
[Crypto2Parse]
Measure=Plugin
Plugin=Webparser
URL=[Crypto2Measure]
StringIndex=1
DynamicVariables=1

;Find the Trend arrow
[Crypto2Parse2]
Measure=Plugin
Plugin=Webparser
URL=[Crypto2Measure]
StringIndex=2
DynamicVariables=1
Substitute="icon-Caret-up":"","icon-Caret-down":""

; Find the Crypto percentage change
[Crypto2Parse3]
Measure=Plugin
Plugin=Webparser
URL=[Crypto2Measure]
StringIndex=3
DynamicVariables=1

[Crypto2DetailsMeter]
Meter=String
MeasureName=Crypto2Parse 
;Condiction to create a up or down arrow to represent price change
ArrowString=HEY
Text= DOGE [Crypto2Parse2] %1   [Crypto2Parse3]%
FontFace=#Font_Face2#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=(#Bar_OffsetX#+#Crypto2_X#)
Y=(#Bar_OffsetY#+#Bar_Height#/2)
DynamicVariables=1
ToolTipText= -----Overview-----#CRLF#🚀 TO THE MOON 🚀
