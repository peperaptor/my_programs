using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Labirint
{
    interface IMovingObject
    {
        Point Position { get; set; }
        void Move(Direction direction = Direction.None);

        object CopyFrom(object source);
    }
}
