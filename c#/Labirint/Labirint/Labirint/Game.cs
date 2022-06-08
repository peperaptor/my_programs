using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Labirint
{
    class Game
    {
        public Size size = new Size(8, 6);
        public List<List<Cell>> map;
        public int Density = 4;
        public int CellSize = 32;
        public Maze maze;
        public Player player;
        public int Window = 5;
        public Bitmap imgMap;

        private List<List<Room>> rooms;

        public Random rnd = new Random();    
        
        public void ChecPrise()
        {
           // if (map[pos.Y][pos.X].obj != null)
           // {
               // player.Scores += map[pos.Y][pos.X].Obj.ExpValue;
              //  player.Health += map[pos.Y][pos.X].Obj.hpValue;
          //  }
        }

        public Game()
        {           
            maze = new Maze(size.Width, size.Height);
            FillMapByMaze();
            player = new Player(this);

            imgMap = new Bitmap(
                    map[0].Count*CellSize,
                    map.Count *CellSize
                );
        }

        public void TrainMove()
        {
            //Point NextMoveTrain = new Point();

            List<Cell> trains = new List<Cell>();
            foreach (var mapline in map)
            {
                trains.AddRange(mapline.Where(x=>x.type.HasFlag(CellType.Train)).ToList());
            }

            foreach (var train in trains)
            {
                (train.obj as Train).Move();
            } 
        }
        public void checCollapse(Point Position)
        {
            if (map[Position.Y][Position.X].type.HasFlag(CellType.Collapse) )
            {
                (map[Position.Y][Position.X].obj as Collapse).CollapseFail(Position);
            }
        }
        public void MoveRects(int dx, int dy)
        {
            if (player == null)
            {
                return;
            }
            if (player.Position.X < Window)
            {

                return;
            } 
            if (player.Position.Y < Window) return;



            dx *= CellSize;
            dy *= CellSize;
            foreach (List < Cell > row in map)
            {
                foreach (Cell cell in row)
                {
                    cell.rect.X -= dx;
                    cell.rect.Y -= dy;
                }
            }
        }
        public void Draw(Graphics g, Rectangle ClipRect)
        {
            Graphics gim = Graphics.FromImage(imgMap);

            int L = (player.Position.X - Window) * CellSize;
            int R = (player.Position.X + Window) * CellSize;
            int U = (player.Position.Y - Window) * CellSize;
            int D = (player.Position.Y + Window) * CellSize;

            for (int i = 0;i < map.Count; i++)
            {               
                for (int j = 0; j < map[0].Count; j++)
                {
                    map[i][j].Draw(gim);
                }
            }
            g.DrawImage(imgMap,
                ClipRect,
                new Rectangle(L,U,Math.Abs(R-L) , Math.Abs(D-U)),
                GraphicsUnit.Pixel);

            #region Вывод групп
            /*
            
            Pen penLine = new Pen(Color.Red, 3);
            int roomSize = CellSize * Density*2;
            Font fontGroup = new Font("Arial", (int)(roomSize*0.7));
            for (int i = 0; i < maze.rs.Count; i++)
            {
                for (int j = 0; j < maze.rs[i].Count; j++)
                {
                    int left = j * roomSize;
                    int right = (j + 1) * roomSize;
                    int top = i * roomSize;
                    int down = (i + 1) * roomSize;

                    Maze.Room room = maze.rs[i][j];

                    if (room.Left) g.DrawLine(penLine, left, top, left, down);
                    if (room.Right) g.DrawLine(penLine, right, top, right, down);
                    if (room.Top) g.DrawLine(penLine, left, top, right, top);
                    if (room.Down) g.DrawLine(penLine, left, down, right, down);

                    g.DrawString(
                        room.group.ToString(),
                        fontGroup,
                        Brushes.Red,
                        new Point(left, top)
                        );
                }
               
            }
            
            */
            #endregion
        }

        private void CreateMap(int w, int h)
        {
            map = new List<List<Cell>>();
            for (int i = 0; i < h; i++)
            {
                List<Cell> row = new List<Cell>();
                for (int j = 0; j < w; j++)
                {
                    Cell cell = new Cell();
                    cell.type = CellType.Empty;
                    cell.rect = new Rectangle(
                        j * CellSize,
                        i * CellSize,
                        CellSize,
                        CellSize
                    );

                    row.Add(cell);
                }
                map.Add(row);
            }
        }

        private void FillRooms()
        {
            foreach (var row in rooms)
            {
                foreach (var room in row)
                {                  
                    if (rnd.Next(100) < 100)
                    {
                        room.GenerateTrain(rnd);
                    }
                    room.GenerateRandom(rnd);
                }
            }
        }

        private void FillMapByMaze()
        {
            rooms = new List<List<Room>>();
            for (int i = 0; i < maze.rs.Count; i++)
            {
                List<Room> room_row = new List<Room>();
                for (int j = 0; j < maze.rs[i].Count; j++)
                {
                    Point roomPosition = new Point(
                        1+j*(Density+1),
                        1 + i * (Density + 1));
                    Room room = new Room(this, roomPosition);
                    room.cells = new List<List<Cell>>();
                    for (int ii = 0; ii < Density; ii++)
                    {
                        List<Cell> row = new List<Cell>();

                        for (int jj = 0; jj < Density; jj++)
                        {
                            row.Add(new Cell());
                        }
                        room.cells.Add(row);
                    }

                    room_row.Add(room);
                }
                rooms.Add(room_row);
            }

            int cellCountWidth = 1 + (Density + 1) * size.Width;
            int cellCountHeight = 1 + (Density + 1) * size.Height;

            CreateMap(cellCountWidth, cellCountHeight);
            for (int i = 0; i < cellCountHeight; i++)
            {
                for (int j = 0; j < cellCountWidth; j++)
                {
                    Cell cell = map[i][j];
                    cell.X = j;
                    cell.Y = i;

                    int roomX = (j - 1) / (Density + 1);
                    int roomY = (i - 1) / (Density + 1);

                    if ((i == 0) || (i == cellCountHeight - 1) || (j == 0) || (j == cellCountWidth - 1))
                    {
                        cell.type = CellType.Wall;
                    }
                    else
                    {
                        if ((j) % (Density + 1) == 0 && maze.rs[roomY][roomX].Right)
                        {
                            cell.type = CellType.Wall;
                            map[i-1][j].type = CellType.Wall;
                        }
                        if ((i) % (Density + 1) == 0 && maze.rs[roomY][roomX].Down)
                        {
                            cell.type = CellType.Wall;
                            map[i][j-1].type = CellType.Wall;
                        }
                    }

                    if ((cell.type == CellType.Empty)
                        && (j % (Density + 1) != 0)
                        && (i % (Density + 1) != 0))
                    {
                        int cellX = j - Density * roomX - roomX - 1;
                        int cellY = i - Density * roomY - roomY - 1;
                        rooms[roomY][roomX].Borders = maze.rs[roomY][roomX];
                        rooms[roomY][roomX].cells[cellY][cellX] = cell;
                    }

                }
            }
            FillRooms();

        }
    }
}
