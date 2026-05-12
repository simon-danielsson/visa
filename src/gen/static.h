#ifndef STATIC_H
#define STATIC_H

static const char footer[] =

"<footer>\n"
"<script>\n"

"const slides = document.querySelectorAll(\".slide\");\n"
"const activeStyle = document.getElementById(\"active-slide-style\");\n"
"let currentSlide = 0;\n"
"let isAnimating = false;\n"
"function showSlide(index) {\n"
"  if (isAnimating) return;\n"
"  isAnimating = true;\n"
" slides[currentSlide].classList.remove(\"active\");\n"
" currentSlide = index;\n"
" const slideStyle = slides[currentSlide].querySelector(\"style\");\n"
" if (slideStyle) {\n"
"   activeStyle.textContent = slideStyle.textContent;\n"
" }\n"
" slides[currentSlide].classList.add(\"active\");\n"
" setTimeout(() => {\n"
"   isAnimating = false;\n"
" }, 200);\n"
"}\n"

"slides[0].classList.add(\"active\");\n"
"const initialStyle = slides[0].querySelector(\"style\");\n"
"if (initialStyle) {\n"
"activeStyle.textContent = initialStyle.textContent;\n"
"}\n"

"document.addEventListener(\"keydown\", (event) => {\n"
"  if (\n"
"    event.key === \"ArrowRight\" &&\n"
"    currentSlide < slides.length - 1\n"
"  ) {\n"
"    showSlide(currentSlide + 1);\n"
"  }\n"
"  if (\n"
"    event.key === \"ArrowLeft\" &&\n"
"    currentSlide > 0\n"
"  ) {\n"
"    showSlide(currentSlide - 1);\n"
"  }\n"
"});\n"

"</script>\n"
"</footer>\n";

static const char header[] =

"<!DOCTYPE html>\n"
"<html lang=\"sv\">\n"
"<head>\n"
"<style>\n"

"html,\n"
"body {\n"
"  margin: 0;\n"
"  min-height: 100%;\n"
"  font-family: Helvetica, Arial, sans-serif;\n"
"}\n"

"body {\n"
"  min-height: 100vh;\n"
"  display: grid;\n"
"  place-items: center;\n"
"  overflow: hidden;\n"
"}\n"

" .screen {\n"
"  width: 100vw;\n"
"  height: 100vh;\n"

"  display: flex;\n"
"  flex-direction: column;\n"

"  justify-content: center; \n"
"  align-items: center;     \n"

"  text-align: center;\n"
"}\n"

".slide {\n"
"  position: absolute;\n"
"  inset: 0;\n"

"  opacity: 0;\n"
"  visibility: hidden;\n"

"  transition:\n"
"    opacity 0.15s ease-in-out,\n"
"    visibility 0.15s ease-in-out;\n"

"  pointer-events: none;\n"
"}\n"

".slide.active {\n"
"  opacity: 1;\n"
"  visibility: visible;\n"
"  pointer-events: auto;\n"
"}\n"

"h1 {\n"
"  font-size: clamp(1rem, 6vw, 6rem);\n"
"  margin: 2rem;\n"
"  width:70%;\n"
"}\n"

"h2 {\n"
"  font-size: clamp(2rem, 6vw, 6rem);\n"
"  margin: 2rem;\n"
"  width:70%;\n"
"}\n"

"ul {\n"
"  display: inline-block;\n"
"  list-style-type: circle;\n"
"  text-align: left;\n"
"  margin: 1rem auto;\n"
"  padding-left: 1.5rem;\n"
"  font-size: clamp(1.5rem, 4vw, 4rem);\n"
"}\n"

"p,a {\n"
"  margin: 2rem;\n"
"  font-size: clamp(1.5rem, 4vw, 4rem);\n"
"  width:70%;\n"
"}\n"
"    img {\n"
"  max-width: 90vw;\n"
"  max-height: 50vh;   \n"
"  object-fit: contain;\n"
"  border-radius: 0.5rem;\n"
"}\n"
"</style>\n"
"<style id=\"active-slide-style\"></style>\n"
"</head>\n";

#endif
