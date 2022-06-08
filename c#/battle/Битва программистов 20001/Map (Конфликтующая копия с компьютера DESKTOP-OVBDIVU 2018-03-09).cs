using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public class Map
    {
        public SizeF size;
        public PointF location;
        public List<List<Cell>> cells = new List<List<Cell>>();
        public float s = 10;

        public void InitMap()
        {
            cells = new List<List<Cell>>();
            for (float y = 0; y < size.Height; y+=s)
            {
                List<Cell> row = new List<Cell>();
                for (float x = 0; x < size.Width; x += s)
                {
                    row.Add(new Cell()
                    {
                        rect = new RectangleF(x, y, s, s)
                    });
                }
                cells.Add(row);
            }
            Clear();
        }
        public void Clear()
        {
            cells.ForEach(row => row.ForEach(c => c.value = 0));
            cells[0].ForEach(c => c.value = 1);
            cells[cells.Count - 1].ForEach(c => c.value = 1);
            cells.ForEach(row => row[0].value = 1);
            cells.ForEach(row => row[row.Count - 1].value = 1);
        }
        public void Draw(Graphics e)//рисовка карты
        {
            e.FillRectangle(new SolidBrush(Color.Aqua), new RectangleF(location, size));

            cells.ForEach(row =>
                row.ForEach(c =>
                    DrawCell(e, c)
                    )
                );
        }

        public void DrawCell(Graphics e, Cell c)
        {
            //e.DrawRectangle(Pens.Black, c.rect.Left, c.rect.Top, c.rect.Width, c.rect.Height);
            //if (c.value != 0)
            //{
            //    e.FillRectangle(Brushes.BurlyWood, c.rect);
            //}
        }
        public void SetBlocks(List<Cell> cell, int value)
        {
            cell.ForEach(c => c.value = value);
        }
    }
}
