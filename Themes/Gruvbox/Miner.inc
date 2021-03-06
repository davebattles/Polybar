[Variables]
Miner_X =1255
;Left, Right or Center
Miner_Anchor=middle

[Metadata]
Name=Gruvbox\\Miner
Author=reddit.com/u/ibattlemonsters
Description=Display current hash rate from Bitfly Ethermine.org

[MinerAnchor]
Measure=String
String = #Miner_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetOption MinerIcon X "(#Bar_OffsetX#+#*Miner_X*#-([*MinerIcon:W*]+[*Miner:W*]+10)/2)"][!SetOption Miner X 10R]
IfMatch2 = Right|right
IfMatchAction2 = [!SetOption Miner StringAlign RightCenter][!SetOption MinerIcon X "([*Miner:X*]-[*MinerIcon:W*]-10)"][!SetOption Miner X "(#Bar_OffsetX#+#*Miner_X*#)"]

[MinerMeasure]
Measure=Plugin
Plugin=Webparser
; URL of Ethermine Dashboard
URL=https://ethermine.org/miners/f81AB2a27510ba095c38B3c5f8e7007C79eCb394/dashboard
RegExp=(?siU)<span style="margin-right: 0.3rem;" class="current-balance" data-v-3d27ca50="" data-v-72139ea6="">(.*)</span>
UpdateRate=60

; Find the Crypto price
[MinerRateParse]
Measure=Plugin
Plugin=Webparser
URL=[MinerMeasure]
StringIndex=1


; [MinerHashParse]
; Measure=Plugin
; Plugin=Webparser
; URL=[MinerMeasure]
; StringIndex=2
; DynamicVariables=1

[MinerDetailsMeter]
Meter=String
MeasureName=MinerRateParse
;Condiction to create a up or down arrow to represent price change
Text= %1 
FontFace=#Font_Face2#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=(#Bar_OffsetX#+#Miner_X#)
Y=(#Bar_OffsetY#+#Bar_Height#/2)
DynamicVariables=1
ToolTipText= -----Overview-----#CRLF#
