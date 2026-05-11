<h1 align="center">visa</h1>
  
<p align="center">
    <img src="https://img.shields.io/badge/license-MIT-green?style=flat-square" alt="MIT License" />
  <img src="https://img.shields.io/github/last-commit/simon-danielsson/visa/main?style=flat-square&color=blue" alt="Last commit" />
</p>
  
<p align="center">
  <a href="#info">Info</a> •
  <a href="#install">Install</a> •
  <a href="#usage">Usage</a> •
  <a href="#license">License</a>
</p>  
  
---
<div id="info"></div>

## Info
  
visa generates html slide presentations from a single text file which can then be viewed in the browser, using left and right arrow keys for navigation.  
  
### Features
+ Image support  
+ Plain-text presentation writing  
+ Browser-based slideshow navigation  
+ Static HTML output  
+ Readable syntax  
  
### Why does this exist?  
+ Since this program only outputs raw html, its presentations are extremely portable between computers. The only software needed to run a presentation is a web-browser, which all computers have.
+ Writing presentations in visa is quicker than traditional presentation software.
+ The benefit of running presentations in the browser is that you can make use of
  the browsers built-in features for quite a few things, such as zoom-in/out,
  fullscreen and fonts.
  
> [!IMPORTANT]  
> Only support for unix systems.
  
visa relies on [nob.h](https://github.com/tsoding/nob.h) (a header-only
build-system) for compilation.  
  
<div id="install"></div>
  
## Install
  
``` terminal
git clone https://github.com/simon-danielsson/visa.git
cd visa
cenv release

# Now you have an executable ready to run within ./build/release/
# Add this to a binary path or bash alias
```
  
---
<div id="usage"></div>
  
## Usage
  
``` terminal
visa -s <presentation file> -d <dest path> -o [open directly in browser]

The destination path is where the generated html files will be placed and any
static files defined in the presentation file will be copied to.

example:
cd ./my_project
mkdir -p presentation
visa -s presentation.txt -d ./presentation -o
```
  
**Example presentation file.** You can choose any file extension you like for the
presentation file - my own preference is .txt. The syntax and workflow is explained
within the example itself. The document is parsed top-down, meaning that the
first slide is on top and the last is at the bottom.  
  
The following example file covers all of this programs functionality, what you
see is what you get!  
  
Blocks:  
- o {}: options  
- s {}: slide  
  
``` txt
o {
    h1 : #B9B9BC
    h2 : #6E6E87
    p  : #B9B9BC
    bg : #25252d
}

s {
    h1(This is a header)
    h2(A subheader)
    The initial 'o' table at the beginning
    is not necessary if you're okay using
    the default values (black on white).
}

s {
    h1(Here is slide two)
    This is the second slide with a neat picture.
    All images are copied into a "/static" folder
    within the destination directory at generation.
    img(images/IMG_4354.png)
}

Any text that's not inside of a block is ignored,
so you can type any extra notes or comments between them.

o {
    h1 : #ff0000
}

s {
    h1(This is the second last slide)
    h2(For this slide I wanted a red header)
    This new h1 color will persist for upcoming
    slides if it isn't changed.
}

o {
    h1 : #B9B9BC
    bg : #C48283
}

s {
    h1(This is the last slide)
    h2(Works like a charm)
    I've been thinking about adding more
    elements such as links and lists,
    as well as extra options, such as font settings.
}
```
  
---
<div id="license"></div>

## License
  
This project is licensed under the [MIT License](https://github.com/simon-danielsson/visa/blob/main/LICENSE).  
 
