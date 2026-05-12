#ifndef STATIC_H
#define STATIC_H

static const char footer_part1[] = "<footer>\n"
"<script>\n";

static const char footer_part2[] =
"document.addEventListener(\"keydown\", function (event) {\n"
"  let match = window.location.pathname.match(/(\\d+)\\.html$/);\n"
"  if (!match) return;\n"

"  let current = parseInt(match[1]);\n"

"  if (event.key === \"ArrowLeft\" && current > 0) {\n"
"window.location.href = (current - 1) + \".html?v=\" + Date.now();\n"
"  }\n"
"\n"
"  if (event.key === \"ArrowRight\" && current < MAX_PAGE) {\n"
"window.location.href = (current + 1) + \".html?v=\" + Date.now();\n"
"  }\n"
"});\n"
"</script>\n"
"</footer>\n";

static const char header_part1[] =

"<!DOCTYPE html>\n"
"<html lang=\"sv\">\n"
"<head>\n"
"<style>\n";

static const char header_part2[] =
"html,\n"
"body {\n"
"  margin: 0;\n"
"  min-height: 100%;\n"
"  font-family: Helvetica, Arial, sans-serif;\n"
"  color: var(--c_h1);\n"
"  background: var(--c_bg);\n"
"}\n"
"\n"
"body {\n"
"  min-height: 100vh;\n"
"  display: grid;\n"
"  place-items: center;\n"
"  overflow: hidden;\n"
"}\n"

".screen {\n"
// "  width: min(90vw, 1200px);\n"
"  text-align: center;\n"
// "  padding: 5vw;\n"
"}\n"

"h1,\n"
"h2,\n"
" {\n"
"  margin: 0;\n"
"  padding: 0;\n"
"  background: var(--c_bg);\n"
"}\n"
"\n"
"h1 {\n"
"  color: var(--c_h1);\n"
"  font-size: clamp(3rem, 10vw, 10rem);\n"
"}\n"
"\n"
"h2 {\n"
"  color: var(--c_h2);\n"
"  font-size: clamp(2rem, 6vw, 6rem);\n"
"}\n"
"\n"
"p {\n"
"  color: var(--c_p);\n"
"  font-size: clamp(1.5rem, 4vw, 4rem);\n"
"}\n"
"    img {\n"
"  max-width: 90vw;\n"
"  max-height: 50vh;   /* keeps it from pushing text out */\n"
"  object-fit: contain;\n"
"  border-radius: 0.5rem;\n"
"}\n"

"</style>\n"
"</head>\n";

#endif
