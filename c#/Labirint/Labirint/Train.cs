using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Labirint
{
    public enum СlocWiseDirection
    {
        ClockWise = 0,
        ContrClockWise = 1
    }    
    class Train: IMovingObject
    {
        private Game gm;
        private int _moveCount = 0;
        public Train(Game gm)
        {
            this.gm = gm;
            clocWiseDirection = (СlocWiseDirection)gm.rnd.Next(2);
            direction = 1 + (Direction)gm.rnd.Next(4);
        }
        public СlocWiseDirection clocWiseDirection;
        public Direction direction;

        private Point _position;
        public Point Position
        {
            get
            {
                return _position;
            }

            set
            {
                if (_position == value)
                {
                    return;
                }

                if (_position.X != 0)
                {
                    Cell newCell = gm.map[value.Y][value.X];
                    Cell currentCell = gm.map[_position.Y][_position.X];

                    newCell.type += (int)CellType.Train;
                    newCell.Damage = currentCell.Damage;

                    newCell.obj = CopyFrom(currentCell.obj);
                    ((Train)newCell.obj).Position = value;

                    currentCell.obj = null;
                    newCell.Damage = 0;
                    currentCell.type -= CellType.Train;

                    _position = value;
                }
                else
                {
                    _position = value;
                    return;
                }
            }
        }

        public bool IsRailAtCell(int i, int j)
        {
            if ((i >=0) && (j>=0) && (i < gm.map.Count) && (j < gm.map[i].Count))
            {
                return gm.map[i][j].type.HasFlag(CellType.Rail);
            }

            return false;
        }

        public void Move(Direction direction = Direction.None)
        {
            _moveCount++;
            int dx = 0;
            int dy = 0;

            if (direction == Direction.None)
            {
                direction = this.direction;
            }

            Direction NextMove = Direction.None;
            switch (direction)
            {
                case Direction.Right:
                    if (IsRailAtCell(_position.Y, _position.X + 1))
                    {
                        dx++;
                    }
                    else {
                        if (clocWiseDirection == СlocWiseDirection.ClockWise)
                        {
                            NextMove = Direction.Down;
                        }
                        else {
                            NextMove = Direction.Up;
                        }
                    }
                    
                    break;
                case Direction.Up:
                    if (IsRailAtCell(_position.Y - 1 , _position.X))
                    {
                        dy--;
                    }
                    else
                    {
                        if (clocWiseDirection == СlocWiseDirection.ClockWise)
                        {
                            NextMove = Direction.Right;
                        }
                        else
                        {
                            NextMove = Direction.Left;
                        }
                    }               
                    break;

                case Direction.Down:
                    if (IsRailAtCell(_position.Y + 1, _position.X))
                    {
                        dy++;
                    }
                    else
                    {
                        if (clocWiseDirection == СlocWiseDirection.ClockWise)
                        {
                            NextMove = Direction.Left;
                        }
                        else
                        {
                            NextMove = Direction.Right;
                        }
                    }
                    break;
                case Direction.Left:
                    if (IsRailAtCell(_position.Y, _position.X - 1))
                    {
                        dx--;
                    }
                    else
                    {
                        if (clocWiseDirection == СlocWiseDirection.ClockWise)
                        {
                            NextMove = Direction.Up;
                        }
                        else
                        {
                            NextMove = Direction.Down;
                        }
                    }
                    break;               
            }


            if (NextMove != Direction.None)
            {
                if (_moveCount <= 4)
                {
                    this.direction = NextMove;
                    Move(NextMove);
                }
                else
                {

                }
               
            }

            Position = new Point(Position.X + dx, Position.Y + dy);
            _moveCount = 0;
        }

        public object CopyFrom(object source)
        {
            Train sourceTrain = (Train)source;
            Train result = new Train(sourceTrain.gm);
            result.direction = sourceTrain.direction;
            result.clocWiseDirection = sourceTrain.clocWiseDirection;

            return result;
        }
    }
}
