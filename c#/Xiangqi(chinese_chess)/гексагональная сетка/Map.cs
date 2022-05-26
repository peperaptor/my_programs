//using Engine3d;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace гексагональная_сетка
{
    public class Map
    {
        public List<List<Cell>> cells;
        public Cell selectedCell;
        public List<Cell> moveCells;
        //public List<int> Win = new List<int>;

        float s;

        float x0;
        float y0;

        public Map()
        {
            Init();
        }

        public Type getNeedType(Type t) {
            Type res = Type.none;
            switch (t)
            {
                case Type.none:
                    break;
                case Type.empty:
                    break;
                default:
                    res = (Type)(((int)t + 2) % 6 + 1);
                    break;
            }
            return res;
        }

        public void Init()
        {
            s = 30;
            float shift = s;

            x0 = shift * 4 / 2 - shift / 2;
            y0 = shift / 2;

            int[,] t = new int[17, 17] {
                {-1,    -1, -1, -1, 1,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {-1,    -1, -1, -1, 1,  1,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {-1,    -1, -1, -1, 1,  1,  1,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {-1,    -1, -1, -1, 1,  1,  1,  1,  -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { 6,    6,  6,  6,  0,  0,  0,  0,  0,  2,  2,  2,  2,  -1, -1, -1, -1},
                {-1,    6,  6,  6,  0,  0,  0,  0,  0,  0,  2,  2,  2,  -1, -1, -1, -1},
                {-1,    -1, 6,  6,  0,  0,  0,  0,  0,  0,  0,  2,  2,  -1, -1, -1, -1},
                {-1,    -1, -1, 6,  0,  0,  0,  0,  0,  0,  0,  0,  2,  -1, -1, -1, -1},
                {-1,    -1, -1, -1, 0,  0,  0,  0,  0,  0,  0,  0,  0,  -1, -1, -1, -1},
                {-1,    -1, -1, -1, 5,  0,  0,  0,  0,  0,  0,  0,  0,  3,  -1, -1, -1},
                {-1,    -1, -1, -1, 5,  5,  0,  0,  0,  0,  0,  0,  0,  3,  3,  -1, -1},
                {-1,    -1, -1, -1, 5,  5,  5,  0,  0,  0,  0,  0,  0,  3,  3,  3,  -1},
                {-1,    -1, -1, -1, 5,  5,  5,  5,  0,  0,  0,  0,  0,  3,  3,  3,  3},
                {-1,    -1, -1, -1, -1, -1, -1, -1, -1, 4,  4,  4,  4,  -1, -1, -1, -1},
                {-1,    -1, -1, -1, -1, -1, -1, -1, -1, -1, 4,  4,  4,  -1, -1, -1, -1},
                {-1,    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4,  4,  -1, -1, -1, -1},
                {-1,    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4,  -1, -1, -1, -1}
            };

            cells = new List<List<Cell>>();


            for (int i = 0; i < 17; i++)
            {
                float y = y0 + s * i;
                List<Cell> cellRow = new List<Cell>();
                for (int j = 0; j < 17; j++)
                {
                    float x = x0 + j * s + shift;

                    int typeId = t[i, j];
                    Type tp = (Type)typeId;

                    

                    cellRow.Add(new Cell() {
                        currentType = tp,
                        needType = getNeedType(tp),
                        mapPos = new Point(j, i),
                        grPos = new PointF(x, y)
                    });
                }
                cells.Add(cellRow);
                shift -= s / 2;
            }



            for (int i = 0; i < 17; i++)
            {
                for (int j = 0; j < 17; j++)
                {
                    for (int ii = -1; ii <= 1; ii++)
                    {
                        for (int jj = -1; jj <= 1; jj++)
                        {
                            if (ii != -jj)
                            {
                                Sosedi s = new Sosedi();
                                if (CanAddSosed(cells[i][j], i + ii, j + jj))
                                {
                                    s.Near = cells[i + ii][j + jj];
                                }
                                if (CanAddSosed(cells[i][j], i + ii * 2, j + jj * 2))
                                {
                                    s.Far = cells[i + ii * 2][j + jj * 2];
                                }

                                cells[i][j].sosedi.Add(s);
                            }
                        }
                    }
                }
            }
        }

        private bool CanAddSosed(Cell cell, int i, int j)
        {
            return (i >= 0 && i < 17 && j >= 0 && j < 17) && (cells[i][j].currentType != Type.none);
        }

        public Color GetColorByType(Type ct)
        {
            switch (ct)
            {
                case Type.none:
                    return SystemColors.Control;
                case Type.empty:
                    return Color.Silver;
                case Type.red:
                    return Color.Red;
                case Type.yellow:
                    return Color.Yellow;
                case Type.blue:
                    return Color.Blue;
                case Type.orange:
                    return Color.Orange;
                case Type.green:
                    return Color.Green;
                case Type.black:
                    return Color.FromArgb(60,60,60);
                default:
                    return Color.Black;
            }
        }

        public void SetMoveCells(Cell cell, bool SetNearSosed = true)
        {
            moveCells = new List<Cell>();

            if (cell != null)
            {
                foreach (var item in cell.sosedi)
                {
                    if ((item.Near != null && item.Near.currentType == Type.empty))
                    {
                        if ((SetNearSosed))
                        {
                            moveCells.Add(item.Near);
                        }
                    }
                    else if (item.Far != null && item.Far.currentType == Type.empty)
                    {
                        moveCells.Add(item.Far);
                    }
                }
            }
        }

        public Cell GetCell(PointF p)
        {
            Cell res = null;
            int selectedY = -1;
            int selectedX = -1;

            for (int i = 0; i < 17; i++)
            {
                for (int j = 0; j < 17; j++)
                {
                    Cell cell = cells[i][j];
                    if (cell.currentType != Type.none)
                    {
                        if (Math.Pow(p.X - cell.grPos.X, 2) + Math.Pow(p.Y - cell.grPos.Y, 2) < Math.Pow(s / 2, 2))
                        {
                            selectedY = i;
                            selectedX = j;
                        }
                    }
                }
            }

            if (selectedY >= 0 && selectedY < 17 && selectedX >= 0 && selectedX < 17)
            {
                res = cells[selectedY][selectedX];
            }

            return res;
        }

        public void SetSelectedCell(Cell cell = null, bool SetNearSosed = true)
        {
            selectedCell = cell;
            SetMoveCells(cell, SetNearSosed);
        }

        public void Draw(Graphics gr)
        {
            float sdvig = 1.5f;

            for (int i = 0; i < 17; i++)
            {
                for (int j = 0; j < 17; j++)
                {
                    Cell cell = cells[i][j];
                    gr.FillEllipse(new SolidBrush(GetColorByType(cell.currentType)), cell.grPos.X - s / 2, cell.grPos.Y - s / 2, s, s);
                }
            }

            if (selectedCell != null)
            {
                gr.FillEllipse(new SolidBrush(Color.White), selectedCell.grPos.X - s / 2 / sdvig, selectedCell.grPos.Y - s / 2 / sdvig, s / sdvig, s / sdvig);

                moveCells.ForEach(cell =>
                 gr.FillEllipse(new SolidBrush(Color.Brown), cell.grPos.X - s / 2 / sdvig, cell.grPos.Y - s / 2 / sdvig, s / sdvig, s / sdvig)
                );
            }




            //    for (int i = 0; i < 17; i++)
            //    {
            //        for (int j = 0; j < 17; j++)
            //        {
            //            Cell cell = cells[i][j];
            //            //gr.FillEllipse(new SolidBrush(GetColorByType(cell.currentType)), cell.grPos.X - s / 2, cell.grPos.Y - s / 2, s, s);
            //            Shape sh = GetShapeByType(cell.currentType);
            //            sh.MoveTo(new Vector3d(cell.grPos.X, cell.grPos.Y, 0));

            //            gr.DrawShape(sh);

            //        }
            //    }

            //}
            //public Shape GetShapeByType(Type ct)
            //{        
            //    if ((ct == Type.none) || (ct == Type.empty))
            //    {
            //        return new Cylinder()
            //        {
            //            RadiusBottom = s / 2,
            //            RadiusTop = s / 2,
            //            Height = s,
            //            Color = GetColorByType(ct)
            //        };
            //    }
            //    else
            //    {
            //        return new Sphere()
            //        {
            //            RadiusTop = s / 2,
            //            Height = s,
            //            Color = GetColorByType(ct)
            //        };
            //    }
        }
    }
}
