[Variables]
Crypto_X =2268
;Left, Right or Center
Crypto_Anchor=middle

[Metadata]
Name=Gruvbox\\Crypto ETH
Author=reddit.com/u/ibattlemonsters
Description=Display current Etherium Price

[CryptoAnchor]
Measure=String
String = #Crypto_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetOption CryptoIcon X "(#Bar_OffsetX#+#*Crypto_X*#-([*CryptoIcon:W*]+[*Crypto:W*]+10)/2)"][!SetOption Crypto X 10R]
IfMatch2 = Right|right
IfMatchAction2 = [!SetOption Crypto StringAlign RightCenter][!SetOption CryptoIcon X "([*Crypto:X*]-[*CryptoIcon:W*]-10)"][!SetOption Crypto X "(#Bar_OffsetX#+#*Crypto_X*#)"]

[CryptoMeasure]
Measure=Plugin
Plugin=Webparser
URL=https://ethereumprice.org/
RegExp=(?siU)<div class="headline flash" id="coin-price">.*<span class="currency-symbol">.*</span><span class="value">(.*)</span>.*<span class="abs" id="coin-change">(.*)</span>.*<span class="percent" id="coin-changePercent">(.*)</span>
UpdateRate=720

; Find the Crypto price
[Crypto1Parse]
Measure=Plugin
Plugin=Webparser
URL=[CryptoMeasure]
StringIndex=1
DynamicVariables=1

;Find Daily Change
[CryptoChangeParse]
Measure=Plugin
Plugin=Webparser
URL=[CryptoMeasure]
StringIndex=2
DynamicVariables=1

;Find Percent Change
[CryptoPercentParse]
Measure=Plugin
Plugin=Webparser
URL=[CryptoMeasure]
StringIndex=3
DynamicVariables=1

[MeterCPU]
Meter=String
X=(#Bar_OffsetX#+#Crypto_X#+145)
Y=(#Bar_OffsetY#+#Bar_Height#/2-6)
FontColor=#Color_Scheme2#
FontFace=#Font_Face2#
FontSize=#Font_Size#
AntiAlias=1
Text= 

[MeasureCPU]
Measure=Plugin
Plugin=Webparser
URL=[CryptoMeasure]
StringIndex=2
DynamicVariables=1
IfCondition=MeasureCPU < 0
IfTrueAction=[!SetOption MeterCPU Text ""]
IfCondition2=MeasureCPU > 0
IfTrueAction2=[!SetOption MeterCPU Text ""]
OnUpdateAction=[!UpdateMeter MeterCPU][!Redraw]

[CryptoDetailsMeter]
Meter=String
MeasureName=Crypto1Parse
;Condiction to create a up or down arrow to represent price change
ArrowString=HEY
Text= ETH %1 [CryptoPercentParse]
FontFace=#Font_Face2#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=(#Bar_OffsetX#+#Crypto_X#)
Y=(#Bar_OffsetY#+#Bar_Height#/2)
DynamicVariables=1
ToolTipText= -----Overview----- #CRLF# https://ethereumprice.org/
