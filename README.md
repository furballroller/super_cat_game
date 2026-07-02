# super_cat_game
I wanted to build a chasing game for a cat, so it can stay healthy while having fun. The game could also be adapted for humans instead, if cats don't find it interesting. I really wanted to use some cool tech to detect when a cat catches its target.

I built this for Fallout, a 2026 hardware hackathon for 13-18yos backed by Hack Club. There was a really fun and helpful community in this event, and Hack Club even funds your project! I would highly recommend hackathons like this if you're new/intermediate like I was (and still am :>)

<img width="1081" height="628" alt="image" src="https://github.com/user-attachments/assets/d636669c-b6bd-40b9-a8e7-e3426bc417cf" />
A 3D model of the pcb so far (V0)
looks so professional!! It's so overpriced tho :(

The design I ended up with is a mat, running a feedback loop for an LED grid (WS2812B) and a pressure sensor matrix (velostat). The brains are an ESP32 S3 Devkit clone off of Aliexpress, programmable over the air (OTA) for easy game dev 👍

After building, I realised that there's so much more potential with this setup! you could write any game you want, and represent it smartly with the endless colours (sorry the resolution is not very good)
