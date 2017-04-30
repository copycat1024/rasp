
https://github.com/copycat1024/rasp.git

--------------------------------
   Acoustic Sensor using RPi3
--------------------------------

 Table of content
  1. Confguration Instruction
  2. Installation Instruction
  3. Server service

--------------------------------
 1. Configuration Instruction

 This section contains 2 part: hardware configuration and software configuration

  1.a. Hardware configuration

  This program is designed for to ultilize a Rasperry Pi 3 with USB soundcard and microphone.
  Ethernet connection is required for saving data to a remote server.
  RPi onboard sound card doesn’t have microphone interface. We have to change the default audio device to be USB sound card.

  To do this, follow these instructions:
   - Make sure the soundcard and micro phone is plugged in.
   - Use “lsusb” command to check if your USB sound card is mounted.
   - Use “sudo nano /etc/asound.conf” command and put following content to the file

    pcm.!default {
     type plug
     slave {
      pcm "hw:1,0"
     }
    }
    ctl.!default {
     type hw
     card 1
    }

  Run “alsamixer” you should be able to see that USB sound card is the default audio device

  1.b. Software configuration

  This program require alsa-utils 1.0.25
  If your system is using the 1.0.28 version, it is recommended to downgrade to the 1.0.25 version in order to avoid bugs.

  To downgrade alsa-ultis, follow these instructions:
   - Use “sudo nano /etc/apt/sources.list” command and add the last line
   - Run “sudo apt-get update
   - Run “sudo aptitude versions alsa-utils” to check if version 1.0.25 of alsa-util is available:
   - Run “sudo apt-get install alsa-utils=1.0.25-4” to downgrade.
   - Reboot (if necessary)

  To make sure alsa-ultils installation was ready:
   - Run “arecord -r44100 -c1 -f S16_LE -d5 test.wav” to test that your microphone is working. You should see a “test.wav” file in the current folder.
   - Put earphone on. Run “aplay test.wav” to check that your recording is okay.

  This program also requrie libcurl library
  To install libcurl, follow these instructions:
   - First use command “ls /usr/include/curl” to identify that /usr/include/curl/ folder exists or not.
   - If the folder doesn’t exist. Run “sudo apt-get update” to update the application list.
   - Run “sudo apt-get install libcurl3” to install the libcurl3.
   - Run “sudo apt-get install libcurl4-openssl-dev” to install the development API of libcurl4.

 2. Installation instruction
  The source code can be obtain from github by the command:
   git pull https://github.com/copycat1024/rasp.git

  Once the source code has been downloaded, open the file comm.h to edit the url to your own receiving php file:
   #define SERVER_URL your_url_here

  Then use the command make to automatically compile the program:
   make

  Run the program from the file wave.a as followed:
   ./wave.a your_device_name

 3. Server service
  The PHP program used to store the data from the Raspo and view them on browser can be found in the php folder in the git respitory.
