using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Labirint
{
    [Flags]
    public enum CellType
    {
        Empty = 0,
        Wall = 1,
        Pit = 2,
        Spike = 4,
        Prise = 8,
        Rail = 16,
        Train = 32,
        Collapse = 64,
        Player = 128  
    }

    class Cell
    {
        private Size kadrSize = new Size(64, 64);

        public object obj;
        public int Damage = 0;
        public int Experience = 0;

        public Image img;

        private CellType _type;
        public CellType type
        {
            get
            {
                return _type;
            }

            set
            {
                _type = value;
                RePaint();          
            }
        }
        public Rectangle rect;
        public int X, Y;
        public void RePaint()
        {
            Random rnd = new Random();

            img = new Bitmap(kadrSize.Width, kadrSize.Height);         
            Graphics g = Graphics.FromImage(img);
            g.DrawImage(Properties.Resources.Empty,
                new Rectangle(0, 0, img.Width, img.Height),
                new Rectangle(
                    0, 0, 
                    kadrSize.Width, kadrSize.Height
                    ),
                GraphicsUnit.Pixel);
            /*
            if (_type.HasFlag(CellType.Spike))
            {
                g.DrawImage(Properties.Resources.Spike, 0, 0);
            }

            if (_type.HasFlag(CellType.Wall))
            {
                g.DrawImage(Properties.Resources.wall, 0, 0);
            }

            if (_type.HasFlag(CellType.Rail))
            {
                g.DrawImage(Properties.Resources.Rail, 0, 0);
            }

            if (_type.HasFlag(CellType.Train))
            {
                g.DrawImage(Properties.Resources.Train, 0, 0);
            }
            if (_type.HasFlag(CellType.Collapse))
            {
                if (obj != null)
                {
                    Bitmap collapse = Properties.Resources.Collapse;
                    if ((obj as Collapse).Touch)
                    { 
                        g.DrawImage(collapse, 
                            new Rectangle(0,0,img.Width,img.Height), 
                            new Rectangle(collapse.Width / 2, 0, collapse.Width / 2, collapse.Height), 
                            GraphicsUnit.Pixel);
                    }
                    else
                    {
                        g.DrawImage(collapse,
                            new Rectangle(0, 0, img.Width, img.Height),
                            new Rectangle(0, 0, collapse.Width / 2, collapse.Height),
                            GraphicsUnit.Pixel);
                        
                    }
                }
                
            }*/

            if (_type.HasFlag(CellType.Player))
            {
                g.DrawImage(Properties.Resources.Player, 0, 0);
            }
        }
        public void Draw(Graphics g)
        {
            g.DrawImage(
                img,
                rect,
                new Rectangle(0,0, img.Width, img.Height),
                GraphicsUnit.Pixel
                );
        }
    }
}
