[Variables]
Allergy_X =2701
;Left, Right or Center


[Metadata]
Name=Gruvbox//Allergy Scraper
Author=reddit.com/u/ibattlemonsters
Description=Display current Allergy and Air Quality in Austin Texas

[AllergyAnchor]
Measure=String
String = #Allergy_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetOption AllergyIcon X "(#Bar_OffsetX#+#*Allergy_X*#-([*AllergyIcon:W*]+[*Allergy:W*]+10)/2)"][!SetOption Allergy X 10R]
IfMatch2 = Right|right
IfMatchAction2 = [!SetOption Allergy StringAlign RightCenter][!SetOption AllergyIcon X "([*Allergy:X*]-[*AllergyIcon:W*]-10)"][!SetOption Allergy X "(#Bar_OffsetX#+#*Allergy_X*#)"]

[AirQualityMeasure]
Measure=Plugin
Plugin=Webparser
;Local austin allergy report and regex
URL=https://www.austinallergist.com/resources/allergy-report/
RegExp=(?siU)<li><strong>Overall Air Quality:</strong>(.*)</li>.*<li><strong>Grass:</strong>(.*)</li>.*<li><strong>Mold:</strong>(.*)</li>.*<li><strong>Tree:</strong>(.*)</li>.*<li><strong>Ragweed:</strong>(.*)</li>
UpdateRate=1480

[AirParse]
Measure=Plugin
Plugin=Webparser
URL=[AirQualityMeasure]
StringIndex=1
DynamicVariables=1

[GrassParse]
Measure=Plugin
Plugin=Webparser
URL=[AirQualityMeasure]
StringIndex=2
DynamicVariables=1

[MoldParse]
Measure=Plugin
Plugin=Webparser
URL=[AirQualityMeasure]
StringIndex=3
DynamicVariables=1

[TreeParse]
Measure=Plugin
Plugin=Webparser
URL=[AirQualityMeasure]
StringIndex=4
DynamicVariables=1

[RagweedParse]
Measure=Plugin
Plugin=Webparser
URL=[AirQualityMeasure]
StringIndex=5
DynamicVariables=1

[AllergyMeter]
Meter=String
MeasureName=AirParse
Text= %1 Air Quality
FontFace=#Font_Face2#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=(#Bar_OffsetX#+#Allergy_X#)
Y=(#Bar_OffsetY#+#Bar_Height#/2)
DynamicVariables=1
ToolTipText= Grass : [GrassParse]#CRLF#Mold : [MoldParse]#CRLF#Tree Pollen: [TreeParse]#CRLF#Ragweed : [RagweedParse]
