These are the files that have been edited to enable the micro:bit to sense and drive the mega:bit.

All blocks of our code are surrounded by commented dashes (//-------------------------------------------------------------)

Item | Description
--- | --- 
MicroBitDisplay.cpp | Small edit to allow for display brightness changes
MicroBitImage.cpp | Major edits to implement all code to sense and drive I2C LED dot matrix
MicroBitImage.h | Header file with small edit to allow MicroBitDisplay.cpp to access brightness command from MicroBitImage.cpp
main.cpp | Development of code to sense the square wave handshake
