# super_cat_game
>Final product:
>- [3D-printed case on Onshape](https://cad.onshape.com/documents/4ded436d6b7f683e9c68b6fa/w/fe5cc562122e090332767be7/e/47f68735415d642cd0337abf?renderMode=0&uiState=6a4c752463182663bd85f4b8)
>- [KiCAD Project](kicad-project)
>- Arduino Code


- zine first thing
- how to use instructions
- fully-assembled CAD and PCB 3D
- (fix the LINK) BOM for whole project, pcb is one item? include the psu, led strip, velostat, conductive fabric tape...


## backstory
So basically my friend had a cat, and I was just getting into arduino electronics, so I wanted to make a chasing game for the both of them! I ended up deciding on a pressure-sensitive LED mat, for an interactive laser-pointer kind-of game, with wifi connectivity for convenience. It could be nice to use regularly to keep your pets fit, but really this is just a fun beginner project to me.

Then, in between reels, I discovered Fallout, a 2026 hardware hackathon for 13-18yos backed by Hack Club. I was drawn in by the promise of full project funding and a free trip to Shenzhen, and was enthralled by the experienced and helpful community ready to help. I would highly recommend Hack Club hackathons like this if you're new/intermediate like me and within the age range :>

The scope expanded when I realised that there's so much more potential with my setup! I used a powerful ESP32 S3 N16R8 Devkit, so I broke out the pins for prototyping. You can hook up any peripherals you want for your game! Like, with a [3D printed kibble dispenser](https://electronoobs.com/tutorial/3d-printed-arduino-cat-feeder), you could implement scheduled feeding and dispense treats as an in-game currency :> You can program anything, maybe even something like [Osu](https://osu.ppy.sh/), and interact by touch with the full spectrum of colours! You might even want to host an online multiplayer game...





++++++++++
frame rate?
++++++++++













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

The game logic is up to the user, but I made a template in Arduino that handles interactions with the hardware.

I also bundled OTA flashing for convenience...











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


