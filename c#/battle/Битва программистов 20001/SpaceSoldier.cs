using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Битва_программистов_20001
{
    public class SpaceSoldier: BaseUnit
    {
        public SpaceSoldier(Game game, Player owner) : base()
        {
            this.owner = owner;
            this.game = game;
            id = game.NewId;
            Health = 10;
            viewDistance = 50;
            reloadTime = 10;
            moveVariant = MoveVariant.land;
        }
        public override void Draw(Graphics e)
        {
            base.Draw(e);
            e.FillEllipse(new SolidBrush(Color.Blue), new RectangleF(Position.X, Position.Y, 2 * r, 2 * r));
        }
    }
}
