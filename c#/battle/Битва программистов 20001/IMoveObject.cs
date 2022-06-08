using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public interface IMoveObject
    {
        bool IsMove { get; set; }
        PointF Position { get; set; }
        PointF Direction { get; set; }
        float Speed { get; set; }
        float Acceleration { get; set; }
        PointF TargetPoint { get; set; }
        MoveVariant moveVariant { get; set; }
        void Step();
        void SetTarget(float x, float y);
        void StopMoove();
        bool IsTarget();
        void SetDirection(float dx, float dy);
    }
}
