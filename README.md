<h1 align="center">visa</h1>
  
<p align="center">
    <img src="https://img.shields.io/badge/license-MIT-green?style=flat-square" alt="MIT License" />
  <img src="https://img.shields.io/github/last-commit/simon-danielsson/visa/main?style=flat-square&color=blue" alt="Last commit" />
</p>
  
<p align="center">
  <a href="#info">Info</a> •
  <a href="#install">Usage</a> •
  <a href="#usage">Usage</a> •
  <a href="#license">License</a>
</p>  
  
---
<div id="info"></div>

## Info
  
visa generates html slide presentations from text and image files. The generated
html presentation can then be browsed using left and right arrow keys.
  
> [!IMPORTANT]  
> 1. Only support for unix systems.
> 2. Since visa is heavily opinionated and built for my own specific workflow, I can't
> guarantee that this will function properly on your machine (or be enjoyable
> to use.)
  
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
visa -s <config file> -d <dest path> -o [open directly in browser]

The destination path is where the generated html files will be placed and any
static files defined in the config file will be copied to.

example:
cd ./my_project
mkdir -p presentation
visa -s my_presentation.txt -d ./presentation -o
```
  
**Example config file.** You can choose any file extension you like for the
config file - my own preference is .txt. The syntax and workflow is explained
within the example itself. The document is parsed top-down, meaning that the
first slide is on top and the last is at the bottom.  
  
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
 
