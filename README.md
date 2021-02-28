dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


About this fork
---------------

![](https://github.com/OliverLew/oliverlew.github.io/blob/pictures/dwm.png?raw=true)

### Patches

You can check the first few commits in the git repo. The main features added are:

- Clickable status bar
  - You can add `\000` to `\017` in the `xsetroot` command to specify clickable areas.
  - Once you click on one area *following* `\0NN`, the specified script (`statuscmd` in `config.h`) will be called with hex form of `NN` as first argument.
  - E.g. If you
    - Set `xsetroot -name " 0 $(printf "\001") 1 "`
    - Status bar shows ` 0  1 `
    - Click on ` 1 `, then:
    - The script will called like `<statuscmd_script> 1`
- base-8 color on status bar
  - You can add `\020` to `\037` in the `xsetroot` command to specify different colors:
    - `\020` to `\027` specifies foreground color
    - `\030` to `\037` specifies background color
    - `0` to `7` on the last digit represents 8 basic colors in `Xresources`.
  - E.g. If you
    - Set `xsetroot -name " 0 $(printf "\021\033") 1 "`
    - Status bar shows ` 0  1 `. The ` 1 ` has red foreground and yellow background
- Center and sticky rules
- Per-tag patches
- Gaps (it is also per-tag)
- Navigation abilities, e.g. put new windows at bottom, shift tags, cycle layouts, move stack, resize on all corners, etc.

### Key/mouse bindings

- Only window manger related keybindings are in `config.h` file, like tag/client management.
- Other window manager independent key bindings (such as application launching) are in `sxhkd` configuration in my dotfiles repo.
- Mouse binding on status bar is dealt with `dwm-status` script in my dotfiles repo.

### Maintenance

I am putting my changes to dwm in a different branch, similar to what's recommended here:

https://dwm.suckless.org/customisation/patches_in_git/

Whenever I pull the update from suckless.org, I can rebase my changes onto the new commits. So the commits are clean, my changes won't be mixed together within official commits.

I will force push until either I found out a better way to maintain the different patches or, not quite possibly, anyone else wants to fork and use my patched dwm.

Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
