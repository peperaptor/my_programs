//using Engine3d;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace гексагональная_сетка
{
    public class Cell
    {
        public Type currentType = Type.none;
        public Type needType = Type.none;
        public bool select = false;
        public List<Sosedi> sosedi = new List<Sosedi>();
        public PointF grPos = new PointF();
        public Point mapPos = new Point();
        //public Shape shape = new Cylinder();
    }
}
