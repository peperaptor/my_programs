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
        public List<Cell> GetNextCell(BaseUnit un)
        {
            List<Cell> res = new List<Cell>();
            cells.ForEach(row => row
                .Where(c => c.value == un.id)
                .ToList()
                .ForEach(c => c.value = 0)
            );
            //.ForEach(c => c.value =  c.value == un.id ? 0 : c.value));

            int startIndX = 0, startIndY = 0;
            int finishIndX = 0, finishIndY = 0;
            Cell Start = GetCEllByPoint(un.Position, out startIndX, out  startIndY);
            Cell Finish = GetCEllByPoint(un.TargetPoint, out finishIndX, out finishIndY);
            res.Add(Finish);

            Start.value = -un.id;

            int left = startIndX;
            int right = startIndX;
            int top = startIndY;
            int bottom = startIndY;
            int t = Start.value;

            int radius = 50000;
            int stepCount = 0;
            bool wasStep = true;
            bool hasWay = false;

            while (wasStep && stepCount <= radius)
            {
                wasStep = false;
                for (int i = top; i <= bottom; i++)
                {
                    for (int j = left; j <= right; j++)
                    {
                        if (cells[i][j].value == t)
                        {
                            for (int iwind = i - 1; iwind <= i + 1; iwind++)
                            {
                                for (int jwind = j - 1; jwind <= j + 1; jwind++)
                                {
                                    //if (Math.Abs(iwind - i) * Math.Abs(jwind - j) == 0)
                                    {
                                        int windValue = cells[iwind][jwind].value;
                                        if (windValue == 0)
                                        {
                                            cells[iwind][jwind].value = t - 1;
                                            left = Math.Min(left, jwind);
                                            right = Math.Max(right, jwind);
                                            bottom = Math.Max(bottom, iwind);
                                            top = Math.Min(top, iwind);

                                            wasStep = true;
                                        }
                                        else if (Finish == cells[iwind][jwind])
                                        {
                                            hasWay = true;
                                            t--;
                                            goto EndWave;
                                        }
                                    }


                                }
                            }
                        }
                    }
                }
                t--;
                stepCount++;
            }

            EndWave:
           
           
            if (hasWay)
            {
                t++;
                Point current = new Point(finishIndX, finishIndY);
                while (t != -un.id)
                {
                    for (int i =  - 1; i <=  1; i++)
                    {
                        for (int j = - 1; j <=  1; j++)
                        {
                            Cell currentCell = cells[current.Y + i][current.X + j];
                            if (un.sleds.Contains(currentCell))
                            {
                                continue;
                            }

                            if (currentCell.value == t)
                            {
                                res.Insert(0, currentCell);

                                current.Y = current.Y + i;
                                current.X = current.X + j;

                                goto NextCell;
                            }
                        }
                    }
                    NextCell:
                    t++;
                }
            }

            cells.ForEach(row => row
            .Where(c => c.value < 0)
            .ToList()
            .ForEach(c => c.value = 0)
            );


            return res;
        }

        public Cell GetCEllByPoint(PointF pos, out int indX, out int indY)
        {
            Cell res = new Cell();
            indY = (int)Math.Truncate(cells.Count / size.Height * pos.Y);
            indX = (int)Math.Truncate(cells[0].Count / size.Width * pos.X);
            return cells[indY][indX];
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
            e.DrawRectangle(Pens.Black, c.rect.Left, c.rect.Top, c.rect.Width, c.rect.Height);
            if (c.value != 0)
            {
                e.FillRectangle(Brushes.BurlyWood, c.rect);
            }
        }
        public void SetBlocks(List<Cell> cell, int value)
        {
            cell.ForEach(c => c.value = value);
        }
    }
}
