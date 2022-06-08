using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Labirint
{
    class Collapse
    {
        public bool Touch = false;
        private Game gm;
        public Collapse(Game gm)
        {
            this.gm = gm;
        }
        public void CollapseFail(Point P)
        {
            if (Touch)
            {
                return;
            }

            Touch = true;
            gm.map[P.Y][P.X].RePaint();

            List<Cell> collapses = new List<Cell>();
            collapses.Add(gm.map[P.Y + 1][P.X]);
            collapses.Add(gm.map[P.Y - 1][P.X]);
            collapses.Add(gm.map[P.Y][P.X + 1]);
            collapses.Add(gm.map[P.Y][P.X - 1]);

            foreach (var cell in collapses)
            {
                if (cell.type.HasFlag(CellType.Wall))
                {
                    continue;
                }
                if (cell.type.HasFlag(CellType.Train))
                {
                    cell.type -= (CellType.Train);
                    cell.obj = null;                    
                }


                Collapse collapse = new Collapse(gm);
                collapse.Touch = true;
                cell.obj = collapse;
                cell.type += (int)(CellType.Collapse);
            }

        }
    }
}
