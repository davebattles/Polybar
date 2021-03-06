[Variables]
Workspacemanager_x=52
;Left, Right or Center
Workspacemanager_Anchor=left
Maximum_Workspace = 4
Workspace_Dot_Gap = (#Font_Size#*22/14)
Workspace_Dot_Radius = (#Font_Size#*8/14)
Workspace_Current_Dot_Radius = (#Font_Size#*4/14)
;Self-generated, change Workspacemanager_Anchor instead.
WorkspaceAnchorPoint = 0

[Metadata]
Name=Papirus\\Workspace Manager
Author=reddit.com/u/khanhas
Description=Click at number to change to desired workspace. Middle click to create new workspace. Choose a windows then hold Shift + click at number to move that window to desired workspace.

[GetWorkspaceVariable]
Measure=PLugin
Plugin=RunCommand
Program=""#@#WorkspaceManager.exe" "#PROGRAMPATH#Rainmeter.exe" "Workspace_Total" "Workspace_Current" "#RootConfig#""

[WorkspaceWindowSendMessage]
Measure=Plugin
Plugin=WindowMessagePlugin
WindowName=#@#WorkspaceManager.exe

[WorkspaceAnchorPoint]
Measure=String
String = #Workspacemanager_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetVariable WorkspaceAnchorPoint "[*WorkspaceShape:W*]/2"]
IfMatch2 = Right|right
IfMatchAction2 = [!SetVariable WorkspaceAnchorPoint "[*WorkspaceShape:W*]"]

[WorkspacemanagereColor]
Measure=Script
SCriptFile=#ROOTCONFIGPATH#Themes\#Theme#\Additional_Comps_And_Scripts\Module_Color.lua
Color = #Color_Scheme3#
Color2= #Color_Scheme4#
;Color transition direction. Valid options: side to middle, middle to side, left to right, right to left.
Transition_Direction=side to middle
Position_Variable=Workspacemanager_X

[WorkspaceShape]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#-#WorkspaceAnchorPoint#)
Y=(#Bar_OffsetY#)
Shape = Rectangle 0,0,((#Workspace_Dot_Gap# + #Workspace_Dot_Radius#)*#Maximum_Workspace# + #Workspace_Dot_Gap#*1.5),#Bar_Height# | StrokeWidth 0 | Extend Color
Color = Fill Color [ColorMeasureScript:GetColor('#Color_Scheme3#', '#Color_Scheme4#', 'side to middle', #Workspacemanager_X#)]
DynamicVariables=1 
;Save current active windows
MouseOverAction=[!CommandMeasure WorkspaceWindowSendMessage "SendMessage 16687 5 1"]
;New desktop
MiddleMouseUpAction=[!CommandMeasure WorkspaceWindowSendMessage "SendMessage 16687 3 1"]

[WorkspaceScript]
Measure=Script
ScriptFile=#ROOTCONFIGPATH#Themes\#Theme#\Additional_Comps_And_Scripts\script_Workspace.lua

[WorkspaceActionTimer]
Measure=Plugin
Plugin=Actiontimer
ActionList1=Repeat ScriptAnimation,16,1000
ScriptAnimation=!CommandMeasure WorkspaceScript "ChangeWorkspaceAnimation()"

[StyleCircle]
Y=(#Bar_OffsetY#+#Bar_Height#/2)
Shape=Ellipse 0,0,#Workspace_Dot_Radius# | StrokeWidth 2 | Stroke Color #Color_Scheme2# | Fill Color 0,0,0,1
Hidden=1

[Workspace1]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle
DynamicVariables=1 
[Workspace2]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5 + (#Workspace_Dot_Gap#+#Workspace_Dot_Radius#)*1-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle
[Workspace3]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5 + (#Workspace_Dot_Gap#+#Workspace_Dot_Radius#)*2-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle
[Workspace4]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5 + (#Workspace_Dot_Gap#+#Workspace_Dot_Radius#)*3-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle
[Workspace5]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5 + (#Workspace_Dot_Gap#+#Workspace_Dot_Radius#)*4-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle
[Workspace6]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5 + (#Workspace_Dot_Gap#+#Workspace_Dot_Radius#)*5-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle
[Workspace7]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5 + (#Workspace_Dot_Gap#+#Workspace_Dot_Radius#)*6-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle
[Workspace8]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5 + (#Workspace_Dot_Gap#+#Workspace_Dot_Radius#)*7-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle
[Workspace9]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5 + (#Workspace_Dot_Gap#+#Workspace_Dot_Radius#)*8-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle
[Workspace10]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5 + (#Workspace_Dot_Gap#+#Workspace_Dot_Radius#)*9-#WorkspaceAnchorPoint#)
MeterStyle=StyleCircle

[WorkspaceCurrent]
Meter=Shape
X=(#Bar_OffsetX#+#workspacemanager_x#+#Workspace_Dot_Gap#*1.5-#WorkspaceAnchorPoint#)
Y=(#Bar_OffsetY#+#Bar_Height#/2)
Trait = StrokeWidth 0 | Fill Color #Color_Scheme2#
DynamicVariables=1
