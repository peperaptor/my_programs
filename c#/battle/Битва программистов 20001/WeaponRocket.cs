using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public class WeaponRocket: BaseWeapon
    {
        public WeaponRocket()
        {

        }

        public void Draw(Graphics e)
        {
            e.FillEllipse(new SolidBrush(Color.Black), new RectangleF(Position.X, Position.Y, 5, 5));
        }
    }
}
