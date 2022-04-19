About
-----

This repository is forked from BSAG's repo. I could start from scratch, but
she done all the research and has all features already in place.

Modifying it to my taste was easy.

Thank you BSAG! I recommend her blog it is really pleasure to read!

[but she's a girl...](https://www.rousette.org.uk/)

In this readme you will find all kind of notes, they can be usefull
if you want to fork repo, but aspecialy for me in the future.

BTW: If you are wondering what layout it is - it is klawa. It is 
layout optimized for polish language. If you are interested you can
find more on:
[klawa.pl](http://klawa.pl)
or if main site is still in "emergency mode", here is backup:
[My klawa.pl restored site](https://klawa.zori.pl)

Quickstart
----------

```bash
./setup
qmk flash -kb ferris/sweep -km ernierasta

```
To generate layout images:
```bash
./ernierasta/update-keymap-diagram.py
```
You will get svg image(-s) with keys in foreignObject. This is problematic
for some tools (inkscape, imagemagick, rsvg-convert, ...), so if you want
to get some kind of bitmap image, use browser to generate this. F.e. firefox
with [SVG Export](https://addons.mozilla.org/pl/firefox/addon/svg-export/) works
good, but unfortunatelly no automation this time ...

Files & logic
-------------

In ernierasta dir, there are all files needed to compile layout.
There are some aliases defined in `keycodes.h`, so in `keymap.c`
we can use keycodes like "NUM", "SYN".
So look at `keycodes.h` first, adjust if needed.

PARTS OF ORIGINAL BSAG readme
-----------------------------

I keep this as as separate directory to the forked =qmk_firmware= directory and
use the =setup= script to create symlinks into the relevant directories in
=qmk_firmware= so that I can build the firmware for my boards and layouts. I
shamelessly stole this idea from someone else's QMK configs, but I can't remember
which setup now, I'm afraid. I'm happy to include a link if someone recognises
it.

* ernierasta
This is a keymap for a 34 key [Ferris Sweep v2.1](https://github.com/davidphilipbarr/Sweep) 
which is a super-compact 3x5+2 Kailh Choc keyboard. I've taken inspiration
from a lot of other users' keymaps:

- One-shot mods and single key app switching from [callum](https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum)
- [Layer arrangement](https://github.com/treeman/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/treeman) and 'numword' setup from [Jonas Hietala](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/#base-layer)
- 'capsword' setup from [Pascal Getreuer](https://getreuer.info/posts/keyboards/caps-word/index.html)
<!-- - 'shift|ralt' tap dance inspired by [https://www.reddit.com/r/MechanicalKeyboards/comments/aq5a3c/qmk_tap_dancing_and_oneshot_layers_quick_demo/](Mikeybox (yt: Walker's Keyboard Science), his keymap is [https://github.com/walkerstop/qmk_firmware/blob/fanoe/keyboards/wheatfield/blocked65/keymaps/walker/keymap.c](here) -->

...and probably many others that I've forgotten about.

The layout uses combos on the baselayer to replace keys like enter and escape
that do not fit on a small keyboard, one-shot mods/layers and a combo to
activate a 'numword' layer which automatically de-activates when a non-numerical
character is typed.
