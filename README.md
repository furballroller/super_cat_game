# super_cat_game

> [!CAUTION]
> This is my first PCB, so right now it's probably not very good. It may be cost-inefficient and buggy.

> [!WARNING]
> **if regenerating production files from KICAD, the LCSC Part # in the BOM and component orientations in CPL may be incorrect. Make sure to double check part numbers and orientation in JLCPCB before paying** I don't know how to fix it and had to directly edit BOM.csv :<

> [!TIP]
> these banners are so cool lol

_Final product:_

- [_3D-printed case on Onshape_](https://cad.onshape.com/documents/4ded436d6b7f683e9c68b6fa/w/fe5cc562122e090332767be7/e/b2ba9b935da609d900851709?renderMode=0&uiState=6a58e4a5db7545b8e7dbac50) (proper assembly instructions below)
- [_KiCAD Project_](kicad-project)
- [_Arduino Sketches_](arduino_sketches) (PlatformIO IDE)

<img width="1748" height="2480" alt="A5 - 1 (1)" src="https://github.com/user-attachments/assets/2de8649b-de12-4aaa-9155-4af353fd5fe8" />

## backstory

So basically my friend had a cat, and I was just getting into arduino electronics, so I wanted to make a chasing game for the both of them! I ended up deciding on a pressure-sensitive LED mat, for an interactive laser-pointer kind-of game, with wifi connectivity for convenience. It could be nice to use regularly to keep your pets fit, but really this is just a fun beginner project to me.

Then, in between reels, I discovered Fallout, a 2026 hardware hackathon for 13-18yos backed by Hack Club. I was drawn in by the promise of full project funding and a free trip to Shenzhen, and was enthralled by the experienced and helpful community ready to help. I would highly recommend Hack Club hackathons like this if you're new/intermediate like me and within the age range :>

The scope expanded when I realised that there's so much more potential with my setup! I used a powerful ESP32 S3 N16R8 Devkit, so I broke out the pins for prototyping. You can hook up any peripherals you want for your game! Like, with a [3D printed kibble dispenser](https://electronoobs.com/tutorial/3d-printed-arduino-cat-feeder), you could implement scheduled feeding and dispense treats as an in-game currency :>

But you can program anything, not just for a cat! Chess online/locally would be easy and super fun! Maybe even something like [Osu](https://osu.ppy.sh/), make use of the full spectrum of colours! You might even want to host an online multiplayer game...

## overview

This project hardwires a pressure-sensitive LED mat to a powerful general-purpose devkit, intended for making inuitive arcade-style games (for a cat, if you'd like! :> )

I used Arduino to code up a simple cat game ([Arduino sketch](arduino_sketches/cat_game)), where a laser dot darts around, avoids people, and resets the game when caught. To use this, just upload the code to the devkit (using it's built-in USB-C port), plug it into the PCB, then plug the PCB into the wall!

The devkit opens the project to endless posibilities, including bluetooth game controllers, network games, and over-the-air coding for easy game dev ([template Arduino sketch with ArduinoOTA](arduino_sketches/template+OTA)). This project is meant to function as a very cool extension of the microcontroller, for those who might want to jump straight into making games using this touch interface.

### specs

- ~45*45cm play area
  - 14*14 Velostat pressure sensor matrix
  - 13*13 WS2812B LED matrix (very low resolution tho)
- Wifi/Bluetooth capability
  - Cheap ESP32 S3 N16R8 Devkit clone off [AliExpress](https://www.aliexpress.com/item/1005008790513258.html)
- Broken-out devkit pins and 5V power supply for any peripherals you might like to add
  - e.g. [3D printed kibble dispenser](https://electronoobs.com/tutorial/3d-printed-arduino-cat-feeder)

### cost

[Overall BOM.csv](bom.csv) | [PCB BOM.csv](kicad_project/production/bom.csv)

The overall BOM represents what I plan to order: 5 populated PCB boards (JLCPCB minimum order quantity), but only 1 housing/mat/devkit. Though, I did include a laptop charger and the LED strips that I already have. This comes out to 111.83 USD.

I didn't include tools (not consumed) like soldering equipment and a 3D printer, but I did approximate the cost of consumables like solder, tape rolls, screws and filament.

#### Per unit

|Cost (USD)|Stuff|
|--|--|
|14.11|Power supply|
|22.15|Electronics|
|2.32|Housing|
|33.32|Mat|

Excluding shipping, it's about 71.90 USD per unit.

<!--
## big_picture
the mat should roll up

-->

### hardware

<!-- a flowchart -->
<img width="715" height="770" alt="image" src="https://github.com/user-attachments/assets/d144fde1-c4fd-4c2a-886b-7ac50897572b" />

I decided to use a USBC PD laptop charger as the PSU since it's quite common and versatile and it's not too expensive.

The velostat matrix is connected with two 45cm lengths of 16-way IDC cables (not shown in CAD). One individual line will be cut, stripped, and stuck to the sensor lines at regular intervals along the mat, 14 horizontally and 14 vertically. There's more detail in the assembly walkthrough below.

#### Velostat pressure sensor matrix

The rest of the system is quite self-explanatory except for the Velostat pressure sensor matrix, so I'll try my best to explain. There's a good video of it by [MarcoReps on YouTube](https://www.youtube.com/watch?v=0uPZwMg5B3k).

Velostat is a thin plastic sheet with electrical resistance that decreases as it is pressed or deformed.

Each "sensor" works by sandwiching a square of Velostat between perpendicular strips of conductive fabric tape, such that it acts as a resistor between them.

<img width="597" height="460" alt="velostat sensor" src="https://github.com/user-attachments/assets/32694cdd-1730-411f-80f8-207c9374ec48" />

When the Velostat is compressed, the resistance between the two strips decreases. Connecting one tape to 3.3V through a normal resistor (e.g. 10k Ohms) and the other to GND, the circuit becomes a voltage divider between the Velostat and the normal resistor. The microcontroller can read the voltage at this point (relative to GND) to figure out the resistance of the Velostat, which tells you approximately how much pressure is on it!

<img width="382" height="465" alt="circuit" src="https://github.com/user-attachments/assets/b8ebd086-3dc4-4730-9d96-48d32fe3a2a2" />

Along one long conductive strip, multiple perpendicular strips can be laid across with Velostat between, creating a line of sensors. By connecting all the perpendicular lines to a multiplexer's channels, they are all left in a high-impedance state except the selected channel. The normal resistor and ADC pin can be connected on the single output of the multiplexer, so they can be reused when the channel is switched.

Conventional diagram

<img width="382" height="368" alt="image" src="https://github.com/user-attachments/assets/4c1e4bd7-a76c-40c4-af19-d9529678c5d4" />

Another way to show the same circuit:

<img width="535" height="594" alt="image" src="https://github.com/user-attachments/assets/b98a0acc-5e34-499d-83b5-e710a59f568c" />

The matrix in the mat is 14 conductive lines crossed with 14 perpendicular lines, making a total of 14^2=196 "sensors." It's the same as the line of sensors, but there are multiple lines of sensors, with one ground connection each. The ground connections are controlled by another multiplexer, only allowing one line to be active at once.

<img width="1042" height="773" alt="image" src="https://github.com/user-attachments/assets/6f0cf098-df57-4ca6-be74-134b2d49d7ea" />

This is a 4 by 4 example. Multiplexer 1 picks the line of sensors connected to GND, and multiplexer 2 picks the sensor from that line to read.

The real mat works using two 16 channel multiplexers (CD74HC4067) on the PCB: the ESP32 specifies a channel, the multiplexers switch to the corresponding Velostat sensor, then the ESP32 takes a reading through it's ADC pin. Instead of the normal resistor, there is a potentiometer (variable resistor) that allows you to adjust sensitivity.

<img width="1002" height="733" alt="image" src="https://github.com/user-attachments/assets/27092ed9-db3d-4566-8acc-c02c8fecde97" />

This is how the sensors are tiled

### code

[My example sketches:](arduino_sketches) (currently untested)

- [press_light](arduino_sketches/press_light): intended to be a test of function, that should simply light up LEDs around where you press. This would be great for making sure the hardware is behaving, or as a fun starting point if you want to experiment with code and get the hang of Arduino.
- [cat_game](arduino_sketches/cat_game): a simple cat game where the computer controls a red laser-pointer-like dot to avoid people.
- [template](arduino_sketches/template): an empty template for your project! I set up some useful functions in functions.cpp and put all the initialisation code in for you.
- [template+OTA](arduino_sketches/template+OTA): same as [template](arduino_sketches/template), but I also set up [ArduinoOTA](https://github.com/JAndrassy/ArduinoOTA). I think it's really cool that you can upload code wirelesly like magic! ([a cool tutorial page](https://www.programmingelectronics.com/arduinoota/))

I used PlatformIO on Visual Studio Code to write my Arduino programs for the microcontroller. This may sound convoluted, but I did it this way because Arduino programs are easy to write (compared to industrial languages) but Arduino IDE is horrible!

If you want to use Arduino IDE, you can quite easily copy-paste my code into the IDE. For a given project folder in [arduino_sketches](arduino_sketches), you just kinda paste the stuff from functions.cpp first, then the stuff from main.cpp... it may take a bit of fiddling around though, so I would recommend looking into PlatformIO (after getting used to it, I find it way way better :>)

I used [FastLED](https://github.com/fastled/fastled) to control the WS2812B neopixels

## assembly

![assembly image](https://github.com/user-attachments/assets/02625bfc-674e-4e6e-94d2-2b4add3a4ae9)

<!-- <img width="360" height="360" alt="image" src="https://github.com/user-attachments/assets/02625bfc-674e-4e6e-94d2-2b4add3a4ae9" />   -->

I thought it was cool to include the little thumb, and the vents are accurate too! They're like LHS/RHS prints from a cat grabbing the case or something :>
Also, the USB port is on a 45 degree angle so the wire leaves perpendicular to the mat.

I'll touch on the key features of the design below. For more info, see the 3D model for this is in [my Onshape doc](https://cad.onshape.com/documents/4ded436d6b7f683e9c68b6fa/w/fe5cc562122e090332767be7/e/b2ba9b935da609d900851709?renderMode=0&uiState=6a58e4a5db7545b8e7dbac50), under the tab "boxV1"
(my bad for the bad organisation, I'm still learning CAD)  

If you want to change the tolerances (they're untested), I haven't tried, sorry if something is inaccurate. It may be best to change the tolerances in your slicer.
> [!TIP]
> the Onshape link might not work. I had to click it, then **Ctrl+X Ctrl+V Enter** from the address bar

### electronics

I contained the circuit in a PCB attached to the corner of the mat, and I've also desgined a 3D-printed housing for it.

The whole project runs off an ESP32 S3 N16R8 microcontroller devkit, which is like an Arduino but better (in my opinion)

[On Aliexpress](https://www.aliexpress.com/item/1005008790513258.html)
(**I would recommend getting "S3 KIT" because the screw terminals are very handy, but I put the board by itself into the BOM**)

When choosing a microcontroller, I noticed that a lot of clone (knockoff) ESP32 S3 devkits, including the one I bought, have the antenna port but also an antenna built into the PCB. I think they give you the option to change to an external antenna by doing a bit of soldering, but by default it is connected to the onboard antenna.

#### PCB

![PCB](https://github.com/user-attachments/assets/e44a234c-e4cd-436b-a006-abbbb84ec489)
<!-- <img width="360" height="360" alt="PCB" src="" />   -->

> [!CAUTION]
>
> - Ignore the capacitor going off the edge, the EasyEDA model is wrong
> - The two parallel rows of vertical pin headers (for the devkit) should be female, again the EasyEDA model is wrong

About the design:

- JL1 and JR1 hold the ESP32 devkit
- The USB-C is for power only
- JLED1 is for the LED strip
- JPWR1 is 5V power for any peripherals you might want to add
- The IDC sockets are for the pressure-sensing data lines
- The fancy ICs are just CD74HC4067 multiplexers for selecting the pressure-sensing channel to read
- The potentiometer is for adjusting the sensitivity of the pressure sensing (it's part of a voltage divider)
- U1 is a logic level converter for the LEDs.

Regarding soldering: I designed the PCB to be hand-soldered, hence the abundance of THT and the large 0805 capacitors/resistors. My only concerns are the SSOP 74HC4067 and 6-pin USB-C port, but other than that the rest should be beginner friendly, from what I can gather. I'm thinking of going to my local makerspace to solder this. In Melbourne, Library at the Dock has one equipped with a digital microscope, flux/solder/wick, and  Hakko FX-888 soldering stations, all free of charge. Maybe be careful around ESD, I'll update on my degree of success when I build it.

#### housing

![housing](https://github.com/user-attachments/assets/c8540786-b5d8-4412-b8d4-58c8dfad0934)
<!-- <img width="412" height="319" alt="housing" src="https://github.com/user-attachments/assets/c8540786-b5d8-4412-b8d4-58c8dfad0934" /> -->

I'm not very good at 3D CAD either, but this should work... I think  
The design is quite self-explanatory, but below are some key features that I thought I should highlight:

<img width="360" height="360" alt="bottom of base" src="https://github.com/user-attachments/assets/c6708018-b717-4e0e-a288-0dc7df241541" />  

On the base, there is a cutout for those holes on the mat. The holes are truncated cones, inspired by [this video by BV3D](https://youtu.be/zaphoWIwSGI). 
I designed my case to work with 3M screws, and the truncated cones means you can use machine screws or self-tapping (I think)

<img width="360" height="360" alt="top of base" src="https://github.com/user-attachments/assets/bc8f3e00-2247-40b6-9aa1-018b0c52e8b4" />  
<img width="360" height="360" alt="top of base, PCB overlaid" src="https://github.com/user-attachments/assets/37531324-df05-4bd8-b068-4380c774be07" />  

The base supports the PCB with a few stilts through the holes in the PCB, again using M3 truncated cones. The smaller stilts give some support to the IDC connectors, which I expect may require some force to plug in and out.

<img width="360" height="360" alt="top" src="https://github.com/user-attachments/assets/f3105c5a-5614-4d5b-8f91-1b39d023feea" />  
<img width="360" height="360" alt="image" src="https://github.com/user-attachments/assets/4c3514b5-abc3-4234-9f71-46d3d9c08b4c" />  

The top fits on the bottom with M3 screws, and features holes for IDC, the LED strip, the USB-C power port, optional 5V power lines, and the broken-out GPIO from the devkit. Also there are (very stylish) vents :>

<img width="360" height="360" alt="lid" src="https://github.com/user-attachments/assets/0b9b47c7-cb6f-4f81-b08d-1c5de6ffdb71" />  
<img width="360" height="360" alt="image" src="https://github.com/user-attachments/assets/2e14f6f5-8676-4ff2-8766-b6f6b6c741d4" />  

There's also a lid that slides onto the top, so the devkit is protected but can be accessed easily during game development. 
I included a cool thinner section where the onboard LED is, so the status light should look like a cat's paw.


### sensor_mat

> [!TIP]
> You'll see two holes in the top-right corner of the mat. These fit M3 screw heads, and should help anchor the PCB to the mat.

1. The LED strips
<img width="480" height="360" alt="LED strips assembled" src="https://github.com/user-attachments/assets/301c7ca1-797a-4f35-a080-5cb5b0335b92" />  

I used 13 LED long sections of 30 LED/m WS2812B individually addressable LEDs
With pads on either side, each section is about 43.333mm long (theoretically)  
[Similar product on AliExpress](https://www.aliexpress.com/item/1005007989207832.html)
(**MAKE SURE THE SPACING IS 30 LEDs/m; I'd recommend buying 2 "3m 30 IP30"**)

There are 13 of these sections, forming a 13*13 grid (169 LEDs)
The ends can be soldered together with jumper wires, preferably with stranded wire, like so:

<figure>
	<img width="360" height="360" alt="Suggested LED strip interconnection" src="https://github.com/user-attachments/assets/93750281-5b07-4886-9c9a-9c0e8ca138e4" />
	<img width="360" height="360" alt="Suggested fold to connect to PCB" src="https://github.com/user-attachments/assets/a732999c-8d8a-4d61-a87e-026df36bc777" />  
	<figcaption>(don't crease too much tho!)</figcaption>
</figure>

2. The popsicle sticks  

<img width="360" height="360" alt="Popsicle sticks assembled" src="https://github.com/user-attachments/assets/a3648ad5-4c80-44b2-b568-f299d7914e47" />  

I used 2mm thick, 18mm wide popsicle sticks (jumbo craft sticks)  
[My local option (Australia)](https://www.officeworks.com.au/shop/officeworks/p/kadink-jumbo-craft-sticks-natural-50-pack-showk0137)

In the CAD, I made very long, 18mm-wide rectangles for simplicity. 
They represent the area that should be filled with popsicle sticks. 
It may be useful to trim off the rounded ends for a fuller surface, but the space could alternatively be filled with hot glue for better adhesion.

They will be adhered together with the conductive tape that goes on top (see below). 
They should be adhered to the LED strip with high-temperature hot glue or silicone (not being lazy! it's good for sticking to wood and flex-PCB, trust). 
Please ensure hot glue doesn't get under the popsicle sticks, as this may affect the pressure detection and make the mat lumpy. 

<figure>  
	<img width="480" height="360" alt="Where to smush the glue" src="https://github.com/user-attachments/assets/5b506c56-6841-4907-afe1-7974d9a9486b" /> 
	<figcaption>Try smushing the glue into the corner where the edge of the popsicle sticks meets the LED's flex-PCB</figcaption>
</figure>

 
3. Conductive fabric tape (bottom)  

<img width="360" height="360" alt="Conductive fabric tape (bottom) assembled" src="https://github.com/user-attachments/assets/faad9d07-6b57-4aba-bd81-2c03844582fe" />

I used 0.1mm thick, 8mm wide conductive fabric tape. This acts as the bottom layer of the velostat matrix.  
[Similar product on AliExpress](https://www.aliexpress.com/item/1005007568611729.html)  
(**I'd recommend buying 1 "8mm"**)

The tape sticks onto the wood to connect it together. If this isn't sturdy enough, the sticks can keep their rounded ends, and hot glue can help hold them together (in the gap made by the rounded ends)

An IDC wire needs to be attached to one end of each strip, so I recommend the following:

<img width="360" height="360" alt="Leave a 1-2cm tape overhang" src="https://github.com/user-attachments/assets/37ac813d-01ac-4a59-839d-43e88d249c35" />  

Leave a 1-2cm tape overhang

<img width="480" height="360" alt="Press the stripped IDC wire here" src="https://github.com/user-attachments/assets/6f7c7e34-28e7-4d6e-a111-2b3af42abdfc" />  

Peel the stripped IDC wire away from the rest and press it here. for extra security, you could wrap the tape around the entire row of IDC wires.


<img width="480" height="360" alt="super cat game (6)" src="https://github.com/user-attachments/assets/cd4c3be9-5aa7-4fd8-b7be-c4857d9f542e" />  

Press another section of tape here, sticking the sticky sides together and securing the wire's insulation and popsicle stick together

<img width="480" height="360" alt="super cat game (7)" src="https://github.com/user-attachments/assets/ccd98e8e-0387-4b15-813c-f922b456c592" />  

Wrap the main tape over the other strip and the wire (ensure it has contact with both the insulation and the bare metal, and press it into the crevices and flush to the bottom of the mat

4. Velostat

<img width="360" height="360" alt="Velostat assembled" src="https://github.com/user-attachments/assets/a48bf022-2008-4c28-90df-4b435305891e" />  

I used a 0.1mm thick, 280mm square sheet of velostat, cut up into ~18mm squares (this stuff is expensive!!)  
[My local option (Australia)](https://www.pakronics.com.au/products/pressure-sensitive-conductive-sheet-velostat-linqstat-ada1361)

The squares will be adhered to the popsicles with thin-film double-sided tape, with two 4mm wide sections flanking the conductive tape running down the middle of the popsicles.

It is important that the tape is as thin or thinner than the velostat (≤0.1mm), or it may squish instead of the velostat, lowering the sensitivity, and so resolution, of pressure readings.

[Double-sided tape on AliExpress](https://www.aliexpress.com/item/1005012157309588.html)  
(**I'd recommend buying 1 "5mm"**)

5. Conductive fabric tape (top)

<img width="360" height="360" alt="Conductive fabric tape (top) assembled" src="https://github.com/user-attachments/assets/69c3594c-6ca5-43d5-9739-251c7f744e02" />  

This layer is sticky-side-up, so in real life you would stick it onto the top EVA first (see below). Please make sure the tape is aligned such that it doesn't touch the bottom layer directly anywhere, only conducting through the Velostat squares.

An IDC wire needs to be attached just like in the other layer, so I would recommend the same strategy, but wrapped upwards around the EVA. The ugly tape overhangs on top of the EVA will be covered by electrical tape later.

6. Frosted plastic sheet (EVA)

<img width="360" height="360" alt="image" src="https://github.com/user-attachments/assets/4cd52af2-93c7-49c0-bcf7-70226786162b" />  

I used a ~1mm thick, 450mm square of EVA plastic intended to line drawers.  
[My local option (Australia)](https://www.rejectshop.com.au/p/drawer-and-shelf-liner-45x150cm)

The top layer of conductive tape should be stuck to the bottom of this sheet, on the smooth side. This EVA layer can be adhered to the bottom construction with electrical tape, not just because it's easy to design, but because of it's suitable properties. The mat is designed to loosely roll up for easy transport/storage, requiring flexibility, and the edges must be soft to keep flying fingers/paws safe around the mat :)

## the_future

Some ideas I have:

- multiplexing/charlieplexing/shift registers instead of expensive neopixels
- using an ESP32 S3 WROOM SOC module (no more clone devkit! Smaller and cheaper PCB)
- using something like NeoPixelBus instead of FastLED to make the Arduino code faster/efficient
- a way to attach/detatch IDC without needing to unscrew the lid (for portability/storage)

Lemme know if you've got any suggestions!
My email: [aydeny8k@gmail.com](mailto:aydeny8k@gmail.com)

## references

The Velostat pressure matrix idea: [Youtube video by MarcoReps](https://www.youtube.com/watch?v=0uPZwMg5B3k)

Truncated-cone screw holes idea: [Youtube video by BV3D](https://youtu.be/zaphoWIwSGI)

Sliding lid shape: [Wuodan0 on Thingiverse](https://www.thingiverse.com/thing:5201077)

[FastLED](https://github.com/fastled/fastled) Arduino library

[ArduinoOTA](https://github.com/JAndrassy/ArduinoOTA) Arduino library

[easyeda2kicad.py](https://github.com/uPesy/easyeda2kicad.py) Python script

Pictures annotated in Google Drawings
