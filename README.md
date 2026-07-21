# super_cat_game
>Final product:
>- [3D-printed case on Onshape](https://cad.onshape.com/documents/4ded436d6b7f683e9c68b6fa/w/fe5cc562122e090332767be7/e/b2ba9b935da609d900851709?renderMode=0&uiState=6a58e4a5db7545b8e7dbac50)
>- [KiCAD Project](kicad-project)
>- Arduino Code


- zine first thing
- how to use instructions
- fully-assembled CAD and PCB 3D
- (fix the LINK) BOM for whole project, pcb is one item? include the psu, led strip, velostat, conductive fabric tape...






## Assembly

For more info, see the 3D model for this is in [my Onshape doc](https://cad.onshape.com/documents/4ded436d6b7f683e9c68b6fa/w/fe5cc562122e090332767be7/e/b2ba9b935da609d900851709?renderMode=0&uiState=6a58e4a5db7545b8e7dbac50), under the tab "boxV1" 
(my bad for the poor quality, I'm still learning CAD)
> [!TIP]
> the Onshape link might not work. I had to click it, then **Ctrl+X Ctrl+V Enter** from the address bar

### The mat
Through the series of images, you'll see two holes in the top-right corner of the mat. These fit M3 screw heads, and should help anchor the PCB to the mat.

1. The LED strips
<img width="960" height="720" alt="LED strips assembled" src="https://github.com/user-attachments/assets/301c7ca1-797a-4f35-a080-5cb5b0335b92" />  

I used 13 LED long sections of 30 LED/m WS2812B individually addressable LEDs
With pads on either side, each section is about 43.333mm long (theoretically)  
[Similar product on AliExpress](https://www.aliexpress.com/item/1005007989207832.html)
(**MAKE SURE THE SPACING IS 30 LEDs/m; I'd recommend buying 2 "3m 30 IP30"**)

There are 13 of these sections, forming a 13*13 grid (169 LEDs)
The ends can be soldered together with jumper wires, preferably with stranded wire, like so:

<img width="960" height="720" alt="Suggested wire arrangement" src="https://github.com/user-attachments/assets/6223ca25-1cf1-458b-b5ee-f00b0fbbbf31" />

<img width="960" height="720" alt="Suggested fold to connect to PCB" src="https://github.com/user-attachments/assets/2d9c9ec4-ff06-4c3d-bcb3-49640d34458e" />  
(don't crease too much tho!)

2. The popsicle sticks  
<img width="720" height="721" alt="Popsicle sticks assembled" src="https://github.com/user-attachments/assets/a3648ad5-4c80-44b2-b568-f299d7914e47" />  

I used 2mm thick, 18mm wide popsicle sticks (jumbo craft sticks)  
[My local option (Australia)](https://www.officeworks.com.au/shop/officeworks/p/kadink-jumbo-craft-sticks-natural-50-pack-showk0137)

In the CAD, I made very long, 18mm-wide rectangles for simplicity. 
They represent the area that should be filled with popsicle sticks. 
It may be useful to trim off the rounded ends for a fuller surface, but the space could alternatively be filled with hot glue for better adhesion.

They will be adhered together with the conductive tape that goes on top (see below). 
They should be adhered to the LED strip with high-temperature hot glue or silicone (not being lazy! it's good for sticking to wood and flex-PCB, trust). 
Please ensure hot glue doesn't get under the popsicle sticks, as this may affect the pressure detection and make the mat lumpy. 
Try smushing the glue into the corner where the edge of the popsicle sticks meets the LED's flex-PCB  
<img width="960" height="720" alt="Where to smush the glue" src="https://github.com/user-attachments/assets/5b506c56-6841-4907-afe1-7974d9a9486b" />
 
3. Conductive fabric tape (bottom)  
<img width="720" height="721" alt="Conductive fabric tape (bottom) assembled" src="https://github.com/user-attachments/assets/faad9d07-6b57-4aba-bd81-2c03844582fe" />

I used 0.1mm thick, 10mm wide conductive fabric tape. 
This acts as the bottom layer of the velostat matrix.  
[Similar product on AliExpress](https://www.aliexpress.com/item/1005008406303623.html)  
(**I'd recommend buying 1 "10mm"**)

The tape sticks onto the wood to connect it together. If this isn't sturdy enough, the sticks can keep their rounded ends, and hot glue can help hold them together (in the gap made by the rounded ends)

An IDC wire needs to be attached to one end of each strip, so I recommend the following:

<img width="720" height="721" alt="Leave a 1-2cm tape overhang" src="https://github.com/user-attachments/assets/37ac813d-01ac-4a59-839d-43e88d249c35" />  
Leave a 1-2cm tape overhang

<img width="960" height="720" alt="Press the stripped IDC wire here" src="https://github.com/user-attachments/assets/6f7c7e34-28e7-4d6e-a111-2b3af42abdfc" />  
Peel the stripped IDC wire away from the rest and press it here. for extra security, you could wrap the tape around the entire row of IDC wires.


<img width="960" height="720" alt="super cat game (6)" src="https://github.com/user-attachments/assets/cd4c3be9-5aa7-4fd8-b7be-c4857d9f542e" />  
Press another section of tape here, sticking the sticky sides together and securing the wire's insulation and popsicle stick together

<img width="960" height="720" alt="super cat game (7)" src="https://github.com/user-attachments/assets/ccd98e8e-0387-4b15-813c-f922b456c592" />  
Wrap the main tape over the other strip and the wire (ensure it has contact with both the insulation and the bare metal, and press it into the crevices and flush to the bottom of the mat

4. Velostat
<img width="720" height="721" alt="Velostat assembled" src="https://github.com/user-attachments/assets/a48bf022-2008-4c28-90df-4b435305891e" />  

I used a 0.1mm thick, 280mm square sheet of velostat, cut up into ~18mm squares (this stuff is expensive!!)  
[My local option (Australia)](https://www.pakronics.com.au/products/pressure-sensitive-conductive-sheet-velostat-linqstat-ada1361)

The squares will be adhered to the popsicles with double-sided kapton tape, on both sides of the conductive fabric tape (bottom).
Kapton tape is necessary because it is also 0.1mm thick so that the velostat maintains electrical contact.

[Kapton tape on AliExpress](https://www.aliexpress.com/item/4000389589500.html)  
(**I'd recommend buying 1 "8mm" and splitting it in half lengthwise before applying**)

5. Conductive fabric tape (top)
<img width="720" height="721" alt="Conductive fabric tape (top) assembled" src="https://github.com/user-attachments/assets/69c3594c-6ca5-43d5-9739-251c7f744e02" />  

This layer is sticky-side-up, so in real life you would stick it onto the top EVA first (see below). 
Please make sure the tape is aligned such that it doesn't touch the bottom layer directly anywhere, only conducting through the Velostat squares.

An IDC wire needs to be attached just like in the other layer, so I would recommend the same strategy, but wrapped upwards around the EVA. If you don't like the look of the overhang on the top EVA, you can use another strip of tape to wrap around the bottom, but the security of the tape may be compromised (easier to peel away)

6. Frosted plastic sheet (EVA)
<img width="720" height="721" alt="image" src="https://github.com/user-attachments/assets/4cd52af2-93c7-49c0-bcf7-70226786162b" />  

I used a ~1mm thick, 450mm square of EVA plastic intended to line drawers.  
[My local option (Australia)](https://www.rejectshop.com.au/p/drawer-and-shelf-liner-45x150cm)

The top layer of conductive tape should be stuck to the bottom of this sheet, on the smooth side. 
This layer can be adhered to the construction beneath it with 

### The PCB









## backstory
So basically my friend had a cat, and I was just getting into arduino electronics, so I wanted to make a chasing game for the both of them! I ended up deciding on a pressure-sensitive LED mat, for an interactive laser-pointer kind-of game, with wifi connectivity for convenience. It could be nice to use regularly to keep your pets fit, but really this is just a fun beginner project to me.

Then, in between reels, I discovered Fallout, a 2026 hardware hackathon for 13-18yos backed by Hack Club. I was drawn in by the promise of full project funding and a free trip to Shenzhen, and was enthralled by the experienced and helpful community ready to help. I would highly recommend Hack Club hackathons like this if you're new/intermediate like me and within the age range :>

The scope expanded when I realised that there's so much more potential with my setup! I used a powerful ESP32 S3 N16R8 Devkit, so I broke out the pins for prototyping. You can hook up any peripherals you want for your game! Like, with a [3D printed kibble dispenser](https://electronoobs.com/tutorial/3d-printed-arduino-cat-feeder), you could implement scheduled feeding and dispense treats as an in-game currency :> You can program anything, maybe even something like [Osu](https://osu.ppy.sh/), and interact by touch with the full spectrum of colours! You might even want to host an online multiplayer game...





### overview (tldr)
This project hardwires a pressure-sensitive LED mat to a powerful general-purpose devkit, intended for making arcade-style games (for a cat, if you'd like! :> )

It has:
- ~45*45cm play area
 - Velostat pressure sensor matrix
 - WS2812B LED matrix (very low resolution tho)
- Wifi/Bluetooth capability
 - Cheap ESP32 S3 Devkit clone off [AliExpress](https://www.aliexpress.com/item/1005008790513258.html?spm=a2g0o.order_list.order_list_main.5.10771802dQlBSP#nav-description)
 - Remote control?
 - Network multiplayer?
 - Over-the-air coding for ez game dev?
- Broken-out devkit pins and 5V power supply for any peripherals you might like to add
  - e.g. [3D printed kibble dispenser](https://electronoobs.com/tutorial/3d-printed-arduino-cat-feeder))

## system
The game should work like:
```
for each frame:
	read the pressure sensor matrix

	do game logic accordingly

	output to LED display
```

Programming a game is up to the user, but I made a few simple programs and a template for your own game. The template handles interactions with the hardware! Here's how to use it ...











### hardware

- screenshots of kicad, pcb, full 3d model

> [!CAUTION]
> This is my first PCB, so right now it's probably not optimised and has uneccesary components. It may cost more than neccesary to order, and it may not function properly.

> [!WARNING]
> **if regenerating production files from KICAD, the LCSC Part # in the BOM and component orientations in CPL may be incorrect. Make sure to double check part numbers and orientation in JLCPCB before paying** I don't know how to fix it and had to directly edit BOM.csv :<

> [!TIP]
> these banners are so cool lol

If you want to order the PCB, I've used components from JLCPCB and the production files are [here](kicad-project/production). I'd recommend at least hand-soldering the THT components, PCBA gets really expensive...

It might look complex, but it's really simple:
- the two counter ICs (74HC163) count from 0 to 255, incrementing every time the devkit sends a pulse
- the binary output of the 74HC163s is fed into the MUX ICs (74HC4067), which changes the channel accordingly



You'll need to buy stuff like the velostat, conductive tape, and LEDs as well. The specific items and recommended purchase sites (the ones I used) are [here]()

## firmware instructions
- set up the OTA stuff on uc

## software instructions
- how to use the example game?

## the future
This can *definitely* be improved:
short term:
- reduction of number of ICs, using more devkit GPIO instead
- swapping onboard LED for a logic level shifter

long term:
- using an ESP32 S3 WROOM SOC module (no more clone devkit! Smaller and cheaper)

<img width="1081" height="628" alt="image" src="https://github.com/user-attachments/assets/d636669c-b6bd-40b9-a8e7-e3426bc417cf" />
A 3D model of the pcb so far (V0)
looks so professional!! It's so overpriced tho :(


