using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public static class Geometry
    {
        public static float Distance(PointF start, PointF finish)
        {
            return (float)Math.Sqrt(Math.Pow(start.Y - finish.Y, 2) + Math.Pow(start.X - finish.X, 2));
        }
    }
}
