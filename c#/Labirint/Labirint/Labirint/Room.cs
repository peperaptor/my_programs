using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Labirint
{
    class Room
    {
        public Maze.MazeRoom Borders;
        public List<List<Cell>> cells;
        private Game gm;

        private Point Position;

        public Room(Game gm, Point position)
        {
            this.gm = gm;
            Position = position;
        }

        public void GenerateRandom(Random rnd)
        {
            foreach (var row in cells)
            {
                foreach (var cell in row)
                {

                    if (rnd.Next(100) < 10 && cell.type == CellType.Empty)
                    {                      
                        cell.type += (int)CellType.Spike;
                    }
                    if (rnd.Next(100) < 1 && cell.type == CellType.Empty)
                    {
                        cell.type += (int)CellType.Collapse;
                        Collapse collapse = new Collapse(gm);
                        cell.obj = collapse;
                        cell.RePaint();
                    }
                }
            }            
        }

        public void GenerateTrain(Random rnd)
        {
            int X = rnd.Next(2);
            int riad = rnd.Next(cells[0].Count);
            List<Cell> rails = new List<Cell>();

            for (int i = 0; i < cells.Count; i++)
            {

                for (int j = 0; j < cells[i].Count; j++)
                {
                    if ((i == riad && X == 0)
                    || (j == riad && X == 1))
                    {
                    rails.Add(cells[i][j]);
                    }
                }
            }
            foreach (var item in rails)
            {
                item.type += (int)CellType.Rail;
            }

            if (rails.Count > 0)
            {
                int rail = rnd.Next(rails.Count);
                Cell tarinCell = rails[rail];
                tarinCell.type += (int)CellType.Train;
                Train train = new Train(gm);
                train.Position = new Point(tarinCell.X, tarinCell.Y);

                tarinCell.obj = train;
            }
        }
    }
}
