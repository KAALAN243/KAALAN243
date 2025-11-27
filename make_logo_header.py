# tools/make_logo_header.py
# Usage: python3 tools/make_logo_header.py path/to/logo.png path/to/output/logo.h
from PIL import Image
import sys
if len(sys.argv) < 3:
    print("Usage: python3 make_logo_header.py logo.png output/logo.h")
    sys.exit(1)
src = sys.argv[1]
out = sys.argv[2]
W = 126
H = 160
img = Image.open(src).convert("RGBA")
img.thumbnail((W,H), Image.LANCZOS)
bg = Image.new("RGBA",(W,H),(0,0,0,255))
x = (W - img.width)//2
y = (H - img.height)//2
bg.paste(img, (x,y), img)
rgb = bg.convert("RGB")
pixels = list(rgb.getdata())
def to565(r,g,b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
vals = [to565(r,g,b) for (r,g,b) in pixels]
with open(out,'w') as f:
    f.write('// Auto-generated logo.h\\n')
    f.write('#define LOGO_W %d\\n' % W)
    f.write('#define LOGO_H %d\\n' % H)
    f.write('static const unsigned short logo_pixels[%d] = {\\n' % (W*H))
    for i in range(0, len(vals), 12):
        line = ','.join(str(v) for v in vals[i:i+12])
        f.write('  ' + line + ',\\n')
    f.write('};\\n')
print("Wrote", out)