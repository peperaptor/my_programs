using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public class Textures
    {
        public Image imgExploition = (Image)Properties.Resources.drawn_explosion_sprite_3;

        public List<Texture> items = new List<Texture>();

        public void AddTExture(Texture t)
        {
            if (items.Count < int.MaxValue)
            {
                items.Add(t);
            }
        }

        public void Clean() {
            items
                .Where(t => t.maxTicks < 0)
                .ToList()
                .ForEach(t => items.Remove(t));
        }

        public void AddExplotion(PointF position, SizeF size)
        {
            Texture t = new Texture(imgExploition);
            t.position = position;
            t.cadrCountHor = 5;
            t.cadrCountVer = 3;
            t.realSize.Width = imgExploition.Size.Width / t.cadrCountHor;
            t.realSize.Height = imgExploition.Size.Height / t.cadrCountVer;
            t.maxTicks = t.cadrCountHor * t.cadrCountVer - 1;
            t.cadrSize = size;

            AddTExture(t);
        }

        public void Next()
        {
            items.ForEach(t => t.Next());
            Clean();
        }

        public void Draw(Graphics gr)
        {
            items.ForEach(t => t.Draw(gr));
        }
    }
}
