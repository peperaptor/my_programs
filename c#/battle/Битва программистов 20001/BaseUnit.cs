using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public class BaseUnit: IMoveObject
    {
        public Game game;
        public Player owner;
        public float r = 10;
        public bool selected = false;
        public float viewDistance;
        public float attackDistance;
        public int OpositCount = 0;
        public int reloadTime = 1;
        public int currentReloadTime = 0;
        public List<Cell> sleds = new List<Cell>();

        public List<Cell> moveCells = new List<Cell>();

        public int id;

        public List<Cell> Cells {
            get {
                var _cells = new List<Cell>();
                game.map.cells
                    .ForEach(row =>
                        row
                        .Where(cell => cell.rect.IntersectsWith(UnitRect))
                        .ToList()
                        .ForEach(cell => _cells.Add(cell))
                    );
                return _cells;
            }
        }
        public List<WeaponRocket> Rockets = new List<WeaponRocket>();

        protected float borderDistance = 5;
        public void NexMove()
        {
            if (IsMove)
            { 
                moveCells = game.map.GetNextCell(this);
                Cell nextCell = moveCells[0];
                sleds.Insert(0, nextCell);
                if (sleds.Count > 2)
                {
                    sleds.RemoveAt(sleds.Count-1);
                }
                PointF newTargetPoint = new PointF(nextCell.rect.Left+ nextCell.rect.Width/2, nextCell.rect.Top + nextCell.rect.Height / 2);
                SetDirection(newTargetPoint.X-Position.X, newTargetPoint.Y - Position.Y);
            }
        }
        public RectangleF UnitRect {
            get {
                return new RectangleF(Position, new SizeF(2*r,2*r)); 
            }
        }

        #region Описание свойств

        private bool _isMove = false;
        private PointF _position = new PointF();
        private PointF _direction = new PointF();
        private PointF _targetPoint = new PointF();
        private MoveVariant _moveVariant = MoveVariant.none;
        private float _speed = 1;
        public float _health;

        public float Health
        {
            get
            {
                return _health;
            }
            set
            {
                _health = value;

                if (_health < 0)
                {
                    game.textures.AddExplotion(Position, new SizeF(2*r, 2*r));
                }
            }
        }

        public bool IsAlive
        {
            get
            {
                return Health >= 0;
            }
        }

        public bool IsMove
        {
            get
            {
                return _isMove;
            }
            set
            {
                _isMove = value;
            }
        }


        public PointF Position
        {
            get
            {
                return _position;
            }
            set
            {
                _position = value;
            }
        }
        public PointF Direction
        {
            get
            {
                return _direction;
            }
            set
            {
                _direction = value;
            }
        }
        public float Speed
        {
            get
            {
                return _speed;
            }
            set
            {
                _speed = value;
            }
        }
        public PointF TargetPoint
        {
            get
            {
                return _targetPoint;
            }
            set
            {
                _targetPoint = value;
            }
        }
        public MoveVariant moveVariant
        {
            get
            {
                return _moveVariant;
            }
            set
            {
                _moveVariant = value;
            }
        }

        public float Acceleration { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        #endregion


        public void Shoot(PointF target)
        {
            if (currentReloadTime >= reloadTime)
            {
                WeaponRocket wr = new WeaponRocket();
                wr.IsMove = true;
                wr.Position = this.Position;
                wr.SetTarget(target.X, target.Y);

                Rockets.Add(wr);

                currentReloadTime = 0;
            }
        }

        public void IncReloadTime()
        {
            currentReloadTime++;
        }

        public void Attack(BaseUnit bs)
        {
            PointF tr = new PointF(bs.Position.X, bs.Position.Y);
            SetTarget(tr);
            Shoot(tr);
        }
        public void FindAttackTarget()
        {
            
            List<BaseUnit> lbu = new List<BaseUnit>();

            game.Players
                .Where(p => p != owner)
                .ToList()
                .ForEach(p => 
                    lbu.AddRange(
                        p.army.units
                            .Where(u=>u.IsAlive
                                    && Geometry.Distance(u.Position, Position) < viewDistance)
                        )
                );
            if (lbu.Count > 0)
            {
                float min = lbu.Min(u => Geometry.Distance(u.Position, Position));
                BaseUnit Target = lbu.FirstOrDefault(
                    u => Geometry.Distance(u.Position, Position) == min);

                if (Target != null)
                {
                    Attack(Target);
                }
            }

        }

        virtual public void Actions()
        {

        }

        public void SetTarget(PointF p)
        {
            SetTarget(p.X, p.Y);
        }

        public void SetTarget(float x, float y)
        {
            IsMove = true;
            TargetPoint = new PointF(x, y);

            SetDirection(x - Position.X, y - Position.Y);
        }
        public void StopMoove()
        {
            IsMove = false;
            Direction = new PointF(0 , 0);
            OpositCount = 0;
        }

        public bool IsTarget()
        {
            return Geometry.Distance(Position, TargetPoint) < Speed*2;
        }

        virtual public void Draw(Graphics e)
        {
            if (selected)
            {
                e.DrawRectangle(new Pen(Color.DeepSkyBlue),
                    Position.X - borderDistance,
                    Position.Y - borderDistance,
                    2 * (r + borderDistance),
                    2 * (r + borderDistance));
            }

            float fontHeight = SystemFonts.IconTitleFont.SizeInPoints;
            e.DrawString(Health.ToString(), SystemFonts.IconTitleFont, Brushes.Black, Position.X, Position.Y - borderDistance - fontHeight);

            
            moveCells.ForEach(c=>e.FillEllipse(Brushes.Red, c.rect));
            if (IsMove)
            {
                e.DrawRectangle(new Pen(Color.Red, 3),
                    Position.X - borderDistance,
                    Position.Y - borderDistance,
                    2 * (r + borderDistance),
                    2 * (r + borderDistance));
            }
        }

        public bool IsIntersected(float x, float y)
        {
            bool res = false;
            if ((x > Position.X) && (x < Position.X + 2 * r) &&  
                    ((y > Position.Y) && (y < Position.Y + 2 * r)))
            {
                res = true;
            }
            return res;
        }
        public bool IsIntersected(RectangleF borderRect)
        { 
            return borderRect.IntersectsWith(UnitRect);
        }

        public void SetDirection(float dx, float dy)
        {
            float zn = (float)Math.Sqrt(dx * dx + dy * dy);
            Direction = new PointF(dx / zn, dy / zn);
        }
        public void SetOpositPos(float x, float y)
        {
            if (OpositCount < 5)
            {
                PointF dix = new PointF();
                dix.Y = -(float)(y / Math.Sqrt(x * x + y * y));
                dix.X = -(float)(x / Math.Sqrt(x * x + y * y));
                _position.X -= Direction.Y * Speed * 1.5f;
                _position.Y -= Direction.X * Speed * 1.5f;

                SetDirection(TargetPoint.X, TargetPoint.Y);

                OpositCount += 1;
            }
            else
            {
                StopMoove();
            }
        }

        public void Step()
        {
            if (IsMove)
            {
                if (IsTarget())
                {
                    StopMoove();
                }
                else
                {
                    float dx = Direction.X * Speed; 
                    float dy = Direction.Y * Speed;

                    _position.X += dx;
                    _position.Y += dy;

                    if (Cells.Any(c=>c.value > 0 && c.value != id))
                    {
                        _position.X -= dx;
                        _position.Y -= dy;
                    }
                } 
            }
        }

        public void ProjectionToMap()
        {
            game.map.SetBlocks(Cells, id);   
        }
    }
}
