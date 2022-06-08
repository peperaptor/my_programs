using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public class SpaceShip : BaseUnit
    {
        public SpaceShip(Game game, Player owner): base()
        {
           
            this.owner = owner;
            this.game = game;
            id = game.NewId;
            Speed = 4;
            Health = 50;
            viewDistance = 100;
            reloadTime = 5;
            r = 15;
            moveVariant = MoveVariant.air;
        }

        public override void Draw(Graphics e)
        {
            base.Draw(e);
            e.FillRectangle(new SolidBrush(Color.Black), new RectangleF(Position.X+5, Position.Y+5, 2 * r, 2 * r));
            e.FillRectangle(new SolidBrush(Color.Green), new RectangleF(Position.X, Position.Y, 2*r, 2*r));
        }
    }
}
