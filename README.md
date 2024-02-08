# TestOS-WyoOS
A small Operating System for me to gain knowledge on OS development, with help of http://wyoos.org.

## Introduction
As I know very little to 0 about OS development and kernel stuff, I decided I'd try to create a small operating system for x86 so that I get knowledge on that darker part of programming ahah.

I'm following the videos from this playlist: https://www.youtube.com/channel/UCQdZltW7bh1ta-_nCH7LWYw_ (or http://wyoos.org) - thank you so much to Viktor Engelmann for making it. I finally found a good guide to make one (aside from wiki.osdev.org, but that takes much more time and I'd like a quicker introduction so that after that I can dive deeper more slowly).

Aside from following the playlist, I may also try to implement my own things. For example so far, after the 3rd lesson I decided to make some print functions to print characters, strings and numbers. The numbers one was already useful for me to see a mistake on the GDT preparation (I was shifting a wrong number of bits).

## Compiling and running the OS
Just go on the Makefile, make mykernel.iso, and give that to a Virtual Machine as a CD and that's it. Currently, I'm using VirtualBox as Viktor uses. I may switch to QEMU some time when I figure out why it doesn't work with me, as it was recommended to me ([João Rodrigues](https://github.com/Joao-Ex-Machina)) and it seems it's recommended for OSDev.

## Licensing
This project and all source code is licensed under Apache 2.0 License - http://www.apache.org/licenses/LICENSE-2.0.

## Support
If you have any questions, try creating an Issue or a Discussion.

## Final notes
Hope you like it! So far it's being very fun to make it!
