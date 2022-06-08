using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Битва_программистов_20001
{
    public class Game
    {
        public Map map = new Map();
        public GameState gameState = GameState.none;

        public Player player1 = new Player();
        public Player player2 = new Player();

        public Textures textures = new Textures();

        public bool mouseMove = false;

        public Point mouseStart;
        public Point mouseFinish;

        private int _newId = 2;
        public int NewId {
            get {
                return _newId++;
            }
        }


        public List<Player> Players = new List<Player>();
        public Rectangle MouseRect {
            get {

                int x = Math.Min(mouseStart.X, mouseFinish.X);
                int y = Math.Min(mouseStart.Y, mouseFinish.Y);
                int w = Math.Abs(mouseStart.X - mouseFinish.X);
                int h = Math.Abs(mouseStart.Y - mouseFinish.Y);
                return new Rectangle(x, y, w, h);
            }
        }

        public bool ShiftPressed {
            get {
                return (Control.ModifierKeys & Keys.Shift) == Keys.Shift;
            }
        }

        public bool AltPressed
        {
            get
            {
                return (Control.ModifierKeys & Keys.Alt) == Keys.Alt;
            }
        }

        public bool CtrlPressed
        {
            get
            {
                return (Control.ModifierKeys & Keys.Control) == Keys.Control;
            }
        }

        public void SetGameState(GameState gs)
        {
            switch (gs)
            {
                case GameState.none:
                    break;
                case GameState.select:
                    break;
                case GameState.move:
                    break;
                default:
                    break;
            }

            gameState = gs;
        }

        

        public void InitGame()//инициализация игры
        {
            map.location = new PointF(0, 0);
            map.size = new SizeF(1000, 600);//в единицах измерения карты
            map.InitMap();
            for (int i = 0; i < 16; i++)
            {
                player1.army.units.Add(new SpaceShip(this, player1));

                player1.army.units.Add(new SpaceSoldier(this, player1));

                player2.army.units.Add(new SpaceShip(this, player2));
                player2.army.units.Add(new SpaceSoldier(this, player2));

            }

            player1.army.SetCoordinate(1);
            player2.army.SetCoordinate(400);

            Players.Add(player1);
            Players.Add(player2);
            //textures.AddExplotion(new PointF(100, 100), new SizeF(20,20));
        }

        public void Draw(Graphics e)
        {
            map.Draw(e);
            player1.army.Draw(e);
            player2.army.Draw(e);
            if (mouseMove)
            {
                e.DrawRectangle(Pens.Green, MouseRect);
            }
            textures.Draw(e);
        }
        public void MouseDown(int x, int y, MouseButtons mb)
        {

            if (mb == MouseButtons.Left)
            {
                mouseStart = new Point(x, y);
            }
            else if  (mb == MouseButtons.Right)
            {

                foreach (var unit in player1.army.units.Where(u => u.selected))
                {
                    if (CtrlPressed)
                    {
                        unit.Shoot(new PointF(x, y));
                    }
                    else 
                        unit.SetTarget(x, y);
                }
            }
        }

        public void MouseMove(int x, int y, MouseButtons mb)
        {
            if (mb == MouseButtons.Left)
            {
                mouseMove = true;
                mouseFinish = new Point(x, y);

            }
        }

        public void MouseUp(int x, int y, MouseButtons mb)
        {
            if (mb == MouseButtons.Left)
            {
                if (!ShiftPressed)
                {
                    player1.army.SetSelectedToAll(false);
                }
                if (mouseMove)
                {
                    player1.army.SetSelectedUnits(MouseRect);
                }
                else
                {
                    player1.army.SetSelectedUnit(x, y);
                }
                mouseMove = false;
            }
  
        }

        public void SelectUnit()
        {

        }


        public void Tick()
        {
            List<BaseUnit> baseUnits = new List<BaseUnit>();
            baseUnits.AddRange(player1.army.units);
            baseUnits.AddRange(player2.army.units);
            map.Clear();
            baseUnits.ForEach(u => u.ProjectionToMap());
            foreach (var unit in baseUnits.Where(u=>u.IsMove))
            {
                unit.NexMove();
                unit.Step();

                //BaseUnit unit2 = baseUnits
                //    .Where(x => x != unit && x.moveVariant == unit.moveVariant)
                //    .FirstOrDefault(y => unit.IsIntersected(y.UnitRect));

                //if (unit2 != null)
                //{
                //    unit.SetOpositPos(unit2.Position.X, unit2.Position.Y);
                //}
            }

            foreach (var unit in baseUnits)
            {
                unit.FindAttackTarget();

                foreach (var rocket in unit.Rockets)
                {
                    rocket.Step();
                    if (rocket.IsTarget())
                    {
                        baseUnits
                            .Where(u => u.IsIntersected(rocket.DamageArea))
                            .Where(u => !u.Rockets.Contains(rocket))
                            //.Where(u => u.owner != unit.owner)
                            .ToList()
                            .ForEach(u => u.Health -= rocket.Damage);
                    }
                }

                List<WeaponRocket> rc = unit.Rockets
                    .Where(r => !r.IsMove)
                    .ToList();

                rc.ForEach(r => textures.AddExplotion(r.Position, new SizeF(5,5)));
                rc.ForEach(r => unit.Rockets.Remove(r));
            }

            player1.army.DeletDead();
            player2.army.DeletDead();

            Players.ForEach(p => p.army.IncReloadTime());



            textures.Next();
        }
    }
}
