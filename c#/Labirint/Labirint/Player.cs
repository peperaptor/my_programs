using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Labirint
{
    class Player: IMovingObject
    {
        private Game gm;
        public Player(Game gm)
        {
            this.gm = gm;
            Position = new Point(1, 1);
        }

        private int _Health;
        public int Health {
            get { return _Health; }
            set {
                _Health = value;
                if (_Health == 0)
                {

                }
            }
        }
        public int Scores;

        private Point _position;
        public Point Position
        {
            get
            {
                return _position;
            }

            set
            {
                if (gm.map[value.Y][value.X].type.HasFlag(CellType.Wall))
                {
                    return;
                }
                else if (gm.map[value.Y][value.X].type.HasFlag(CellType.Pit))
                {
                    Health = 0;
                }

                if (_position.X != 0)
                {
                    gm.map[_position.Y][_position.X].type -= CellType.Player;
                }
                int dx = value.X - _position.X;
                int dy = value.Y - _position.Y;

                
                Health -= gm.map[value.Y][value.X].Damage;
                Scores += gm.map[value.Y][value.X].Experience;
                _position = value;
                //gm.MoveRects(dx, dy);
                gm.ChecPrise();
                gm.map[_position.Y][_position.X].type += (int)CellType.Player;
            }
        }

        public void Move(Direction direction = Direction.None)
        {
            int dx = 0;
            int dy = 0;

            switch (direction)
            {
                case Direction.Right:
                    dx++;
                    break;
                case Direction.Up:
                    dy--;
                    break;
                case Direction.Down:
                    dy++;
                    break;
                case Direction.Left:
                    dx--;
                    break;
                default:
                    break;
            }
            Position = new Point(Position.X + dx, Position.Y + dy);
            gm.checCollapse(Position);           
        }

        public object CopyFrom(object source)
        {
            throw new NotImplementedException();
        }
    }
}
