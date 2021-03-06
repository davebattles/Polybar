[Variables]
Stock_X =2529
;Left, Right or Center
Stock_Anchor=middle

[Metadata]
Name=Gruvbox\\Stock
Author=reddit.com/u/ibattlemonsters
Description=Display current Stock Ticker from marketwatch

[StockAnchor]
Measure=String
String = #Stock_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetOption StockIcon X "(#Bar_OffsetX#+#*Stock_X*#-([*StockIcon:W*]+[*Stock:W*]+10)/2)"][!SetOption Stock X 10R]
IfMatch2 = Right|right
IfMatchAction2 = [!SetOption Stock StringAlign RightCenter][!SetOption StockIcon X "([*Stock:X*]-[*StockIcon:W*]-10)"][!SetOption Stock X "(#Bar_OffsetX#+#*Stock_X*#)"]

[StockMeasure]
Measure=Plugin
Plugin=Webparser
;Local austin Stock report and regex
URL=https://stocktwits.com/symbol/AAPL
RegExp=(?siU)<span class="st_3zYaKAL">(.*)</span>.*<svg class="st_3tVBpgr" height="100%" viewBox="0 0 512 512" width="100%"><path d="(.*)"></path></svg>.*<span class="st_17sIB4J">(.*)</span>.*<span class="st_17sIB4J">(.*)</span>.*<span class="st_17sIB4J">(.*)</span>.*<span class="st_17sIB4J">(.*)</span>
UpdateRate=720

; Find the stock price
[Stock1Parse]
Measure=Plugin
Plugin=Webparser
URL=[StockMeasure]
StringIndex=1
DynamicVariables=1

; Determines if the SVG next to the Stock price is an up arrow or a down arrow and subsitutes the SVG points with Font Awesome up or down arrows.
[Stock2Parse]
Measure=Plugin
Plugin=Webparser
URL=[StockMeasure]
StringIndex=2
DynamicVariables=1
Substitute="M 219.09704,338.21059 V 18.27301 c 0,-10.08005 7.93604,-18.27209 17.76009,-18.27209 h 38.27219 c 9.82405,0 17.76008,8.19204 17.76008,18.27209 v 320.00158 l 49.85625,-68.92834 0.096,-0.096 a 21.824108,21.824108 0 0 1 29.63215,-4.96003 l 34.49617,23.36012 c 9.56804,6.49603 11.90406,19.20009 5.21602,28.44814 l -42.0802,58.17629 -78.33639,118.72058 a 41.792206,41.792206 0 0 1 -13.05607,12.57606 c -19.84009,12.16006 -46.11222,6.56004 -58.78429,-12.48006 L 133.27262,362.37071 99.800452,316.09848 a 19.968098,19.968098 0 0 1 5.216028,-28.41614 l 34.49617,-23.36012 a 21.824108,21.824108 0 0 1 29.72814,5.02403 l 49.85625,68.92834 z":"","m 219.11393,173.74781 -49.85324,68.86017 a 21.822786,21.822786 0 0 1 -29.72634,5.05572 L 105.04027,224.305 A 19.96689,19.96689 0 0 1 99.824556,195.85858 L 133.2947,149.58916 219.94588,18.90842 c 12.6713,-19.03894 38.97383,-24.63863 58.78073,-12.4793 5.24771,3.19982 9.69546,7.51958 13.05528,12.5753 l 78.33164,118.7134 42.07766,58.17276 a 19.96689,19.96689 0 0 1 -5.21571,28.41442 l -34.49408,23.3587 a 21.822786,21.822786 0 0 1 -29.63036,-4.92772 l -0.096,-0.096 -49.85323,-68.89217 V 493.73002 A 18.270984,18.270984 0 0 1 274.63084,512.001 h -37.24593 a 18.270984,18.270984 0 0 1 -18.27098,-18.27098 z":""

[52LowParse]
Measure=Plugin
Plugin=Webparser
URL=[StockMeasure]
StringIndex=3
DynamicVariables=1

[52HighParse]
Measure=Plugin
Plugin=Webparser
URL=[StockMeasure]
StringIndex=4
DynamicVariables=1

[MrkCapParse]
Measure=Plugin
Plugin=Webparser
URL=[StockMeasure]
StringIndex=5
DynamicVariables=1
Substitute="m":" million","b":" billion","t":" trillion"

[VolumeParse]
Measure=Plugin
Plugin=Webparser
URL=[StockMeasure]
StringIndex=6
DynamicVariables=1
Substitute="m":" million","b":" billion","t":" trillion"

[StockDetailsMeter]
Meter=String
MeasureName=Stock1Parse
Text= AAPL %1 [Stock2Parse]
FontFace=#Font_Face2#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=(#Bar_OffsetX#+#Stock_X#)
Y=(#Bar_OffsetY#+#Bar_Height#/2)
DynamicVariables=1
ToolTipText=    ---Overview---#CRLF#52 Week Low : [52LowParse]#CRLF#52 Week High : [52HighParse]#CRLF#Market Cap : [MrkCapParse]#CRLF#Volume : [VolumeParse]
