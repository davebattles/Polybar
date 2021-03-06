[Variables]
Weather_X =2937
;Left, Right or Center
Weather_Anchor=middle
;C or F
Weather_Unit = F

[Metadata]
Name=Pratous\\Weather
Author=reddit.com/u/khanhas
Description=Display current weather and temperature. Hover mouse on text for more information.

[WeatherAnchor]
Measure=String
String = #Weather_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetOption WeatherIcon X "(#Bar_OffsetX#+#*Weather_X*#-([*WeatherIcon:W*]+[*Weather:W*]+10)/2)"][!SetOption Weather X 10R]
IfMatch2 = Right|right
IfMatchAction2 = [!SetOption Weather StringAlign RightCenter][!SetOption WeatherIcon X "([*Weather:X*]-[*WeatherIcon:W*]-10)"][!SetOption Weather X "(#Bar_OffsetX#+#*Weather_X*#)"]

[WeatherMeasure]
Measure=Plugin
Plugin=Webparser
URL=https://www.yahoo.com/news/weather
;Your location is automatically located. If it's incorrect or you want a custom place, access to https://www.yahoo.com/news/weather
;Click "Change Location", type in then choose where you want. After that, copy new webpage link and replace it with this measure URL. And refresh skin!
RegExp=(?siU)<h1 class="city.*data-reactid="7">(.*)</h1>.*<div class="My\(2px\).*60x60\/(.*)@2x.png.*data-reactid="26">(.*)<.*<span class="Va\(t\)" data-reactid="37">(.*)</span>.*
UpdateRate=60

[Stock1Parse]
Measure=Plugin
Plugin=Webparser
URL=[WeatherMeasure]
StringIndex=1
DynamicVariables=1


[WeatherLocation]
Measure=Plugin
Plugin=Webparser
URL=[WeatherMeasure]
StringIndex=1
DynamicVariables=1
[WeatherMeasureIcon]
Measure=Plugin
Plugin=Webparser
URL=[WeatherMeasure]
StringIndex=2
DynamicVariables=1
Substitute="rain_day_night":"rain","scattered_showers_day_night":"rain","windy_day_night":"wind","mostly_cloudy_day_night":"cloudy","partly_cloudy_night":"cloudy","partly_cloudy_day":"cloudy","cloudy_day_night":"cloudy","snow_rain_mix_day_night":"sleet","fair_day":"clear_day","fair_night":"clear_night","flurries_day_night":"snow","snow_day_night":"snow","thundershowers_day_night":"storm","fog_day_night":"fog"
OnChangeAction=[!SetOption WeatherIcon ImageName "#ROOTCONFIGPATH#Themes\#Theme#\Additional_Comps_And_Scripts\[WeatherMeasureIcon]"][!UpdateMeter WeatherIcon]
[WeatherDes]
Measure=Plugin
Plugin=Webparser
URL=[WeatherMeasure]
StringIndex=3
DynamicVariables=1
[WeatherTempF]
Measure=Plugin
Plugin=Webparser
URL=[WeatherMeasure]
StringIndex=4
DynamicVariables=1
[WeatherTempC]
Measure=Calc
Formula=Round((WeatherTempF-32)*5/9)

[WeatherIcon]
Meter=Image
ImageName=
ImageTint=#Color_Scheme2#
W=(#Font_Size#*16/13)
X=(#Bar_OffsetX#+#Weather_X#)
Y=(#Bar_OffsetY#+(#Bar_Height#-[WeatherIcon:H])/2)
DynamicVariables=1
ToolTipText=Today is [WeatherDes]#CRLF#Location: [WeatherLocation]

[Weather]
Meter=String
MeasureName=WeatherTemp#Weather_Unit#
Text=%1°#Weather_Unit#
FontFace=#Font_Face#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=10R
Y=(#Bar_OffsetY#+#Bar_Height#/2)
DynamicVariables=1
ToolTipText=Today is [WeatherDes]#CRLF#Location: [WeatherLocation]
