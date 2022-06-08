using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public class Texture
    {
        public PointF position;
        public SizeF cadrSize;
        public SizeF realSize;
        public int cadrCountHor;
        public int cadrCountVer;

        public int currentCadr;

        public int maxTicks = 1;
        

        public Image img;

        public Image Cadr {
            get {
                return img;
            }
        }

        public Texture(Image img) {
            this.img = img;
        }

        public void Next()
        {
            currentCadr++;
            if (currentCadr >= cadrCountVer * cadrCountHor)
            {
                currentCadr = 0;
            }
            maxTicks--;
        }

        public void Draw(Graphics gr)
        {
            int x = currentCadr%cadrCountHor;
            int y = currentCadr/cadrCountVer;

            PointF sourcePos = new PointF() {
                X = x * realSize.Width,
                Y = y * realSize.Height
            };

            RectangleF destRect = new RectangleF(position, cadrSize);

            gr.DrawImage(img,
                destRect,
                new RectangleF(sourcePos, realSize)
                ,GraphicsUnit.Pixel);
        }
    }
}
