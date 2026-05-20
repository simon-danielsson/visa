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
  
visa is not a PowerPoint replacement or a Markdown presentation tool. It is a small plain-text format for writing structured slide decks that export to a portable HTML file.  
  
### Features
+ Plain-text presentation writing  
+ Static HTML output  
+ Image support  
+ Left/right arrow key navigation  
+ Intuitive syntax  
  
### Why does this exist?  
+ Since this program only outputs raw html, its presentations are extremely portable between computers. The only software needed to run a presentation is a web-browser with JavaScript support.
+ Writing presentations in visa is quicker than traditional presentation software.
+ The benefit of running presentations in the browser is that you can make use of the browsers built-in features for quite a few things, such as zoom-in/out, fullscreen and fonts. In your presentations you might also want to cite a website or play a youtube video, and in these cases visa is also convenient since you don't have to switch programs in the middle of a presentation.
+ visa intentionally removes manual layouts and positioning of text/images. The program formats slides dynamically, so that you can focus on writing content instead of arranging elements.
  
> [!IMPORTANT]  
> Only support for unix systems.
  
<div id="install"></div>
  
## Install
  
``` terminal
git clone https://github.com/simon-danielsson/visa.git
cd visa
run release

# Now you have an executable ready to run within ./build/release/
# Add this to a binary path or bash alias
```
  
---
<div id="usage"></div>
  
## Usage
  
### CLI
    
``` terminal
visa -s <presentation file> -d <dest path> [-o] 

-o: open directly in default browser

The destination path is where the generated html files will be generated and any
static files defined in the presentation file will be copied into.

example:
cd ./my_project
mkdir -p presentation
visa -s presentation.txt -d ./presentation -o
```
  
### Syntax
  
``` terminal
o {}: options  
│ h1  : <hex_color>
│ h2  : <hex_color>
│ p   : <hex_color>
│ img : <hex_color>

s {}: slide  
│ h1(<text>)
│ h2(<text>)
│ img(<path>)
│ list(<text>, <text>, <text> ...)
│ a(<name>, <link>)
│ text [p]
```
  
### Example presentation file  
You can choose any file extension you like for the
presentation file - my own preference is .txt. The syntax and workflow is explained
within the example itself. The document is parsed top-down, meaning that the
first slide is on top and the last is at the bottom.  
  
The following example file covers all of this programs functionality; what you
see is what you get!  
  
  
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
    The path to an image can be either relative or absolute.
    img(images/IMG_4354.png)
}

Any text that's not inside of a block is ignored. This makes writing comments
and personal notes easy and ergonomic.

o {
    h1 : #ff0000
}

s {
    h1(Here is another slide!)
    h2(For this slide I wanted a red header)
    This new h1 color will persist for upcoming
    slides if it isn't changed.
    list(this is a list, here's the second item, this list is a bullet point list)
}

Right now, list(), h1(), h2(), a() and img() items are only single-line, but I
am planning to implement multiline parsing for list() items at least.

o {
    h1 : #B9B9BC
    bg : #C48283
}

s {
    h1(This is the second last slide)
}

o {
    h1 : #B9B9BC
    h2 : #6E6E87
    p  : #B9B9BC
    bg : #25252d
}
s {
    h1(This is the last slide)
    h2(My favorite search engine!)
    Here is a link to a duck that goes quack quack.
    a(DuckDuckGo, https://duckduckgo.com/)
}

```
  
---
<div id="license"></div>

## License
  
This project is licensed under the [MIT License](https://github.com/simon-danielsson/visa/blob/main/LICENSE).  
 
