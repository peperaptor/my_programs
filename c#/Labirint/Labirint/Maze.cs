using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Labirint
{
    class Maze
    {
        Random rnd = new Random(DateTime.Now.Millisecond);
        public class MazeRoom
        {
            public bool Left;
            public bool Top;
            public bool Right;
            public bool Down;
            public int group;
        }

        public List<List<MazeRoom>> rs;
        public Maze(int w, int h)
        {
            rs = new List<List<MazeRoom>>();
            for (int i = 0; i < h; i++)
            {
                List<MazeRoom> row = new List<MazeRoom>();
                for (int j = 0; j < w; j++)
                {
                    row.Add(new MazeRoom());
                }
                rs.Add(row);
            }

            Generate();
        }

        public void Clear()
        {
            for (int i = 0; i < rs.Count; i++)
                for (int j = 0; j < rs[i].Count; j++)
                    rs[i][j] = new MazeRoom();;
        }

        public void SetBorder()
        {
            for (int i = 0; i < rs.Count; i++)
            {
                for (int j = 0; j < rs[i].Count; j++)
                {
                    if (i == 0) rs[i][j].Top = true;
                    if (i == rs.Count - 1) rs[i][j].Down = true;
                    if (j == 0) rs[i][j].Left = true;
                    if (j == rs[i].Count - 1) rs[i][j].Right = true;
                }
            }
        }

        public void Generate()
        {
            Clear();

            for (int i = 0; i < rs.Count; i++)
            {
                List<MazeRoom> row = rs[i];

                if (i == 0)
                {
                    SetMultiplicity(row);
                    MakeRandomWalls(row);
                    MakeDownWalls(row);
                }
                else if (i < rs.Count - 1)
                {
                    CopyRow(row, i - 1);
                    DeleteRightWalls(row);
                    ClearGroupWithDownWall(row);
                    DeleteDownWalls(row);

                    SetMultiplicity(row);

                    MakeRandomWalls(row);
                    MakeDownWalls(row);
                }
                else
                {
                    CopyRow(row, i - 1);
                    DeleteRightWalls(row);
                    ClearGroupWithDownWall(row);

                    MakeWallsBitweenSames(row);          
                }       
            }

            SetBorder();
        }

        private void SetMultiplicity(List<MazeRoom> row)
        {
            int group = 1;
            foreach (var room in row.Where(x=>x.group == 0))
            {
                while (row.Any(x => x.group == group)) group++;

                room.group = group;
            }  
        }

        private bool DoRightWall()
        {
            return rnd.Next(2) == 1;
        }

        private bool DoDownWall()
        {
            return rnd.Next(2) == 1;
        }

        private void MakeWallsBitweenSames(List<MazeRoom> row)
        {
            for (int i = 0; i < row.Count - 1; i++)
            {
                if (row[i + 1].group == row[i].group && row[i].group > 0)
                {
                    row[i].Right = true;
                }
            }
        }

        private void MakeRandomWalls(List<MazeRoom> row)
        {
            MakeWallsBitweenSames(row);

            for (int i = 0; i < row.Count - 1; i++)
            {
                if (!row[i].Right)
                {
                    row[i].Right = DoRightWall();
                    if (!row[i].Right)
                    {
                        row[i + 1].group = row[i].group;
                    }
                }
            }
        }

        private void MakeDownWalls(List<MazeRoom> row)
        {
            int groupMax = row.Max(x=>x.group);
            for (int g = 0; g <= groupMax; g++)
            {
                List<MazeRoom> group = row.Where(x => x.group == g).ToList();

                for (int i = 0; i < group.Count; i++)
                {
                    int downCountAtGroup = group.Count(x => x.Down);

                    if (downCountAtGroup >= group.Count - 1)
                    {
                        group[i].Down = false;
                    }
                    else
                        group[i].Down = DoDownWall();
                }
            }
        }

        private void CopyRow(List<MazeRoom> row, int sourceIndex)
        {
            for (int i = 0; i < row.Count; i++)
            {
                row[i].group = rs[sourceIndex][i].group;
                row[i].Left = rs[sourceIndex][i].Left;
                row[i].Right = rs[sourceIndex][i].Right;
                row[i].Top = rs[sourceIndex][i].Top;
                row[i].Down = rs[sourceIndex][i].Down;
            }
        }

        private void DeleteRightWalls(List<MazeRoom> row)
        {
            foreach (var room in row)
                room.Right = false;
        }

        private void DeleteDownWalls(List<MazeRoom> row)
        {
            foreach (var room in row)
                room.Down = false;
        }

        private void ClearGroupWithDownWall(List<MazeRoom> row)
        {
            foreach (var room in row.Where(x => x.Down))
                room.group = 0;
        }

        private void MakeLastRow(List<MazeRoom> row)
        {
            for (int i = 0; i < row.Count - 1; i++)
            {
                if (row[i + 1].group != row[i].group)
                {
                    row[i].Right = false;
                    row[i + 1].group = row[i].group;
                }
            }
        }
    }
}
