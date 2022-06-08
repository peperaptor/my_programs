using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public class Army
    {
        public List<BaseUnit> units = new List<BaseUnit>();

        public Army()
        {

        }

        public void DeletDead()
        {
            units
                .Where(x => !x.IsAlive)
                .ToList()
                .ForEach(r => units.Remove(r));
        }

        public void SetCoordinate(int dstX)
        {
            float dx = dstX;
            float dy = 0;

            float d = units.Max(u => u.r) * 2 + 10;
            for (int i = 0; i < units.Count; i++)
            {
                if (i%8 == 0)
                {
                    dx = dstX;
                    dy += d;
                }

                dx += d;

                units[i].Position = new PointF(dx, dy);
            }
            
        }

        public void Draw(Graphics e)
        {
            foreach (var unit in units.Where(u=>u.moveVariant == MoveVariant.land))
            {
                unit.Draw(e);
            }

            foreach (var unit in units.Where(u => u.moveVariant == MoveVariant.air))
            {
                unit.Draw(e);
            }

            foreach (var unit in units)
            {
                foreach (var rocket in unit.Rockets)
                {
                    rocket.Draw(e);
                }
            }
        }

        public void SetSelectedUnit(float x, float y)
        {
            BaseUnit unit = units.FirstOrDefault(u => u.IsIntersected(x, y));
            if (unit != null)
            {
                unit.selected = true;
            }
        }
        public void SetSelectedUnits(Rectangle mouseRect)
        {
            units
                .Where(u => u.IsIntersected(mouseRect))
                .ToList()
                .ForEach(u => u.selected = true);
        }
        public void IncReloadTime()
        {
            units
                .Where(u => u.IsAlive)
                .ToList()
                .ForEach(u => u.IncReloadTime());
        }
        
        public void SetSelectedToAll(bool newSelected)
        {
            foreach (var unit in units)
            {
                unit.selected = newSelected;
            }
        }
    }
}
