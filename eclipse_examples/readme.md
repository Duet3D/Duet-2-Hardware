Example Eclipse projects for Arduino Due 

Eclipse version Juno SR1, CDT 8.1.1

ArduinoDueCore should be in the Eclipse Workspace along with other 
Eclipse Due projects which reference this Core project - this allows
for easily debugging by following what core functions do.

The DueTemplate project is a simple "hello world"/blink project which
is easy to copy and adapt for other projects as it is setup with the
required libraries and toolchain directories

The SD_HSMCI_TEST project provides the same functionality as the
hsmci_example sketch within ..\test_sketches\hsmci_example. It writes
and reads a number of test files to an SD card.

The steps to integrate Due into Eclipse is based on the forum posts
here:
http://forum.arduino.cc/index.php/topic,135403.0.html
especially the posts by Nassarane