using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace бактерии
{
    class Life
    {
        public List<Bact> pb = new List<Bact>();
        public SizeF MapSize;
        public Point MapP;
        public RectangleF ClipRectangle;
        private Random rnd = new Random();
        public float LiderArea = 50;//сторона прямоугольника вокруг главной бактерии 

        public List<Area> areas = new List<Area>();

        public float p = 80;//количество травоядных%
        public float q;


        public Life()//жизнь, запуск всего
        {
           
            q = 100 - p;
            InitMap();

            for (int i = 0; i < 100; i++)
            {
                AddBact((BactType)(rnd.Next(101) < q ? 1 : 0));
            }
        }

        public Bact AddBact(BactType bt, PointF? p = null)
        {
            Bact b = new Bact(bt);

            if (p == null)
            {
                b.PosStart = GetRandomPoint(MapP, MapSize);
            }
            else {
                b.PosStart = (PointF)p;
            }
            b.Pos = b.PosStart;
            b.PosFinish = GetRandomPoint(MapP, MapSize);

            pb.Add(b);
            return b;
        }

        public void InitMap()
        {
            MapSize = new SizeF(1920, 1017);
            MapP = new Point(0,0);
            areas = new List<Area>();
            InitAreas(100);
        }

        public void InitAreas(int f)
        {
            for (int i = 0; i < f; i++)
            {
                areas.Add(new Area()
                {
                    rect = new RectangleF(GetRandomPoint(MapP, MapSize), new Size(rnd.Next(100) + 50, rnd.Next(100) + 50)),
                    FoodMax = 10,
                    FoodRestoreSpeed = 0.005f
                });

            }
        }

        public void Check()
        {
            foreach (var evil in pb.Where(x=>x.type == BactType.Evil))
            {
                foreach (var piece in pb.Where(x => x.type == BactType.Piece))
                {
                    if (GetDistance(evil.Pos, piece.Pos) < evil.AttacDistance)
                    {                                                
                        if (evil.TargetAtack == null || GetDistance(evil.Pos, piece.Pos) < GetDistance(evil.Pos, evil.TargetAtack.Pos))//проверяем, кого проще атаковать или есть ли цель
                        {
                            evil.TargetAtack = piece; 
                        }
                        if (piece == evil.TargetAtack)
                        {
                            piece.heal -= evil.damage;
                            evil.Food += evil.FoodCorm;
                            evil.heal += evil.VosHeal* evil.FoodCorm;
                            evil.PosStart = evil.Pos;
                            evil.PosFinish = piece.Pos;
                            evil.t = 0;

                            
                        }
                    }
                    if (GetDistance(piece.Pos, evil.Pos) < piece.AttacDistance)
                    {
                        
                        piece.PosFinish.X = piece.Pos.X + (evil.Pos.X - piece.Pos.X);
                        piece.PosFinish.Y = piece.Pos.Y + (evil.Pos.Y - piece.Pos.Y);
                        piece.PosStart = piece.Pos;
                        piece.t = 0;
                        if (piece.TargetAtack == null)
                        {
                            piece.TargetAtack = evil;
                        }
                        if (evil == piece.TargetAtack)
                        {
                            evil.heal -= piece.damage;
                        }
                    }
                }
            }

            foreach (var piece in pb.Where(x => x.type == BactType.Piece && x.IsAlive))
            {
                foreach (var a in areas.Where(x=>x.FoodCount>2))
                {
                    if (a.rect.IntersectsWith(new RectangleF(
                        piece.Pos.X - piece.AttacDistance,
                        piece.Pos.Y - piece.AttacDistance,
                        2 * piece.AttacDistance,
                        2 * piece.AttacDistance
                        )))
                    {
                        a.FoodCount -= 0.01f;
                        piece.Food += piece.FoodCorm;
                    }
                }
                piece.TargetMove = pb.FirstOrDefault(x => x.type == BactType.Piece
                && x.IsAlive
                && GetDistance(piece.Pos, x.Pos) < piece.AttacDistance
                && x.heal > piece.heal
                && x!=piece);
                if (piece.TargetMove != null)
                {
                    piece.TargetAtack = piece.TargetMove.TargetAtack;
                    piece.PosStart = piece.Pos;
                    piece.t = 0;
                }
            }


            List<Bact> pab = new List<Bact>();
            foreach (var B in pb.Where(x => x.Food>x.FoodMax && x.IsAlive))
            {               
                B.Food = B.FoodMax/2;
                Bact Child = B.Born();
                Child.Pos = GetRandomPoint(new PointF(B.Pos.X - LiderArea / 2, B.Pos.Y - LiderArea / 2), new SizeF(LiderArea, LiderArea));
                Child.PosStart = Child.Pos;
                Child.PosFinish = GetRandomPoint(new PointF(B.Pos.X - LiderArea / 2, B.Pos.Y - LiderArea / 2), new SizeF(LiderArea, LiderArea));
                pab.Add(Child);              
            }
            for (int i = pab.Count - 1; i >= 0; i--)
            {
                pb.Add(pab[i]);
                pab.RemoveAt(i);
            }
        

            for (int i = 0; i< areas.Count; i++)
            { 
                 areas[i].FoodCount +=areas[i].FoodRestoreSpeed;
                
            }

            for (int i = pb.Count-1; i >= 0; i--)
            {
                pb[i].Food -= pb[i].FoodLostSpd;
                if (!pb[i].IsAlive)
                {
                    foreach (var bact in pb.Where(x=>x.TargetMove == pb[i] || x.TargetAtack == pb[i]))
                    {
                        bact.TargetMove = null;
                        bact.TargetAtack = null;
                    }
                    pb.RemoveAt(i);
                }
            }
        }


        private PointF GetRandomPoint(PointF P, SizeF Sz)//случайное место на прямоугольнике
        {
            PointF res = new PointF(-1, -1);
            int a = 0;
            while (res.X>MapSize.Width || res.Y > MapSize.Height || res.X<0 || res.Y < 0)
            {
                res = new PointF(rnd.Next((int)Sz.Width) + P.X, rnd.Next((int)Sz.Height) + P.Y);
                if (a++>100)
                {
                    res = GetRandomPoint(MapP, MapSize);
                }
            }
                
            return res;
        }

        private float To(float km)
        {
            float k;

            k = ClipRectangle.Width / MapSize.Width;
            if (MapSize.Height * k > ClipRectangle.Height)
            {
                k = ClipRectangle.Height / MapSize.Height;
            }

            return km*k;
        }

        private PointF To(PointF p)
        {
            return new PointF(To(p.X), To(p.Y));
        }

        private RectangleF To(RectangleF r)
        {
            return new RectangleF(To(r.Location), new SizeF(To(r.Width), To(r.Height)));
        }

        public void Moove()
        {

            foreach (var piece in pb.Where(x => x.type == BactType.Piece && x.IsAlive))
            {
                foreach (var a in areas.Where(x => x.FoodCount > 0))//ищем бактерий в еде
                {
                    if (a.rect.IntersectsWith(new RectangleF(
                        piece.Pos.X - piece.AttacDistance,
                        piece.Pos.Y - piece.AttacDistance,
                        2 * piece.AttacDistance,
                        2 * piece.AttacDistance
                        )))
                    {
                        piece.t = 0;
                        piece.PosStart = piece.Pos;
                        Point poin = new Point(Convert.ToInt32(a.rect.Left), Convert.ToInt32(a.rect.Top));
                        piece.PosFinish = GetRandomPoint(poin, a.rect.Size);
                    }
                }
            }
            foreach (var b in pb)
            {
                float vx, vy;

                PointF TargetPoint = b.TargetMove == null || b.type == BactType.Evil ? 
                    b.PosFinish : 
                    GetRandomPoint(
                        new PointF(b.TargetMove.Pos.X - LiderArea, b.TargetMove.Pos.X - LiderArea), 
                        new SizeF(LiderArea * 2, LiderArea * 2));

                float StartDist = GetDistance(b.PosStart, TargetPoint);

                vx = (TargetPoint.X - b.PosStart.X) / StartDist * b.v;
                vy = (TargetPoint.Y - b.PosStart.Y) / StartDist * b.v;
                b.t += 1f;

                b.Pos.X = b.PosStart.X + vx * b.t;
                b.Pos.Y = b.PosStart.Y + vy * b.t;

                if (GetDistance(b.Pos, b.PosStart)> StartDist)
                {
                    b.t = 0;
                    b.Pos = TargetPoint;
                    b.PosStart = b.Pos;
                    b.PosFinish = GetRandomPoint(MapP, MapSize);
                }
            }          
        }

        private float GetDistance(PointF p1, PointF p2)
        {
            return (float)Math.Sqrt(Math.Pow(p2.X - p1.X,2) + Math.Pow(p2.Y - p1.Y,2));
        }


        public void Paint(Graphics g, Rectangle ClipRectangle)
        {
            this.ClipRectangle = ClipRectangle;

            g.FillRectangle(Brushes.Black, To(0), To(0), To(MapSize.Width), To(MapSize.Height));

            foreach (var a in areas)
            {
                int c = (int)(a.FoodCount / a.FoodMax*255);
                SolidBrush sl = new SolidBrush(Color.FromArgb(c, Color.Lime));
                g.FillRectangle(sl, To(a.rect));
            }

            foreach (var b in pb)
            {
                SolidBrush sl = new SolidBrush( b.type == BactType.Piece ? Color.Blue : Color.Red );
                
                 // g.FillEllipse(sl, To(b.Pos.X - b.R), To(b.Pos.Y - b.R), To(2 * b.R), To(2 * b.R));
                g.FillEllipse(sl, To(b.Pos.X - b.heal / 10), To(b.Pos.Y - b.heal / 10), To(2 * b.heal / 10), To(2 * b.heal / 10));
                //g.DrawLine(Pens.Red, To(b.Pos), To(b.PosFinish));
            }
        }
    }
}
