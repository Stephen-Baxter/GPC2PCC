# GPC2PCC

Game Pad Controls To Personal Computer Controls (GPC2PCC) is an application that allows
up to two game pads to be used as a keyboard and mouse on a computer.

# Settings
GPC2PCC will create a two files named "default.G2Pconfig" and ".G2PconfigList" on first start up
"default.G2Pconfig" contains the defualt setings (If GPC2PCC cannot find the specified .G2Pconfig file at top of the list in ".G2PconfigList" than it will create a new one if one does not already exists)
".G2PconfigList" contains a list that custom config files can be added to, to be use (if it can not find it in the same directory as "GPC2PCC.exe" than it will create a new one)

# Key Codes
all key codes are in hexadecimal and can b found at https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

# Mapping Keys To Tumb Stick
GPC2PCC allows the Thumb stick that is not being used for mouse movement to be use as a directional
pad that can emulate five different keys.
Keys one through four are emulated by moving the thumb stick in a direction within an angular range (Angular Range is 135.00 degrees by defalt)
(examples: if THUMB_STICK_ANGULER_RANGE is set to 135.00 degrees then each direction will overlap
evenly with direction next to it by 45.00 degrees, or if it is set 90.00 degrees or less than none of the directions will
overlap)
The fifth key is emulated when the thumb stick is moved in any direction past a shift point (SHIFT_POINT is 0.90 by default)
(this is great for a game that require a second key to be pressed to make the player run)(note: if SHIFT_POINT is 
less than zero then the fifth key will always be emulated and if it is greater than one then it will
never be emulated)

# Functions only Controller0 can do
exit application: Left Thumb Stick Button + DPad Down Button + Start Button or unplugging Controller0 from the computer
(GPC2PCC can also be exit by going into the "Task Manager", selecting GPC2PCC, and pressing "End Task" but this may cause problems)
turn volume up: Left Thumb Stick Button + DPad Down Button + A Button
turn volume down: Left Stick Thumb Button + DPad Down Button + B Button
mute volume: Left Thumb Stick Down + Button Down Button + Y Button
move mouse pointer: Left Thumb Stick or Right Thumb Stick depending on settings (Left Thumb Stick is set by default)
left mouse button: Left Trigger or Right Trigger depending on settings (Left Trigger is set by default)
right mouse button: Left Trigger or Right Trigger depending on settings (Right Trigger is set by default)


# Known Compatible Game Pad
License USB Wired Xbox 360 Controller

# Prerequisites
XInput 1.4
Microsoft Windows 8 or greater

# Download
Not SETUP YET

# Built With
Microsoft Visual Studeo 2019 Version 16.2.1
with
Desktop development with C++ workload
and Game development with C++ workload
for
code writing,
debugging,
compiling,
and icon creation

# Version
0.1.0
(THE FUNCTIONALITY FOR THE SECOND CONTROLLER HAS NOT BEEN TESTED)

# Author
Stephen Baxter

# License
This project is licensed under the
MIT License - see the LICENSE.md
file for details
