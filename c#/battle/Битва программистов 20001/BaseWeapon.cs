using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public class BaseWeapon : IMoveObject
    {
        public float Damage = 10;
        public float DamageRadius = 10;
        #region Описание свойств

        private bool _isMove = false;
        private PointF _position = new PointF();
        private PointF _direction = new PointF();
        private PointF _targetPoint = new PointF();
        private MoveVariant _moveVariant = MoveVariant.none;
        private float _speed = 1;
        private float _acceleration = 0.25f;

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

        public float Acceleration
        {
            get
            {
                return _acceleration;
            }
            set
            {
                _acceleration = value;
            }
        }
        #endregion


        public RectangleF DamageArea{
            get {
                return 
                    new RectangleF(
                        Position.X - DamageRadius, 
                        Position.Y - DamageRadius,
                        DamageRadius*2, DamageRadius*2
                        );
            }

            set {

            }
        }

        public bool IsTarget()
        {
            return Geometry.Distance(Position, TargetPoint) < Speed;
        }

        public void SetDirection(float dx, float dy)
        {
            float zn = (float)Math.Sqrt(dx * dx + dy * dy);
            Direction = new PointF(dx / zn, dy / zn);
        }

        public void SetTarget(float x, float y)
        {
            IsMove = true;
            TargetPoint = new PointF(x, y);
            SetDirection(x - Position.X, y - Position.Y);
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
                    _position.X += Direction.X * Speed;
                    _position.Y += Direction.Y * Speed;
                    Speed += Acceleration;
                }
            }
        }

        public void StopMoove()
        {
            IsMove = false;
            Direction = new PointF(0, 0);
        }

    } 
}
