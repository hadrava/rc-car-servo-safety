Work in progress... higher-level features are not implemented yet

Firmware of the servo motor controller for a robot based on a regular RC car.

 - Developed on "Arduino Pro Mini 328p 5V" board (some Chinese clone to be honest)
 - Designed to work with Traxxas receiver (100 Hz signal instead of probably
   more common 50 Hz, high signals are generated in parallel and not
   sequentialy)
 - UART interface
 - 2 channels (hw generated)


Interresting features:

 - The board should be connected between rc receiver and servo. Remote
   controller can act as a quick wireless safety button.
 - You do not have to reconnect anything to switch between regular RC car mode
   and autonomously controlled one
 - Can be used in a way, that remote operator will just sometimes adjust the
   direction of otherwise autonomous car.
 - You can record data from a remote controller and analyze it or replay it.
