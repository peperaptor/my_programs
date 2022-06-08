using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace бактерии
{
    public enum BactType
    {
        Piece = 0,
        Evil = 1
    }

    class Bact

    {
        public PointF PosStart, PosFinish, Pos;
        public Bact TargetMove;//бактерия за которой следуют
        public Bact TargetAtack;//бактерия за которой следуют для убийства
        public float t; // Время движения от PosStart до PosFinish
        public float v; // скорость
        public float AttacDistance;

        public float damage;//урон
        public float VosHeal;//востановление урона при поедании чего-либо
        private float _Food;
        public float FoodCorm;//еда с поля
        public float FoodLostSpd;//-еды за ход
        private float _heal;//здоровье
        public float heal
        {
            get {
                return _heal;
            }

            set {
                _heal = Math.Max(0,value);
                IsAlive = _heal > 0;
            }
        }
        public float Food //еда
        {
            get
            {
                return _Food;
            }

            set
            {
                _Food = value;
            }
        }

        public float FoodMax;//еда максимум, рождается ребенок

        public bool IsAlive = true;
        public BactType type;

        public Bact(BactType bt)
        {
            Random rnd = new Random();

            type = bt;
            if (bt == BactType.Piece)//качества, индивидуальные для мирной бактерии
            {
                v = (float)rnd.NextDouble() * 10 + 5f;
                AttacDistance = 50;
                heal = 100 + (float)rnd.NextDouble();
                damage = 1f;
                VosHeal = 6.2f;
                FoodMax = 45f;
                FoodCorm = 0.1f;
                FoodLostSpd = 0.005f;
            }
            else
            {
                heal = 50;//качества, индивидуальные для хищной бактерии
                v = (float)rnd.NextDouble() * 6 + 3f;
                AttacDistance = 100;
                damage = 3f;
                VosHeal = 0.27f;

                FoodMax = 70f;
                FoodCorm = 0.9f;
                FoodLostSpd = 0.01f;
            }
            Food = FoodMax / 2;
        }

        public Bact Born()//рождение новой бактерии
        {
            Bact Child = new Bact(this.type);

            Child.damage = damage + 0.005f;
            Child.heal = heal;

            return Child;
        }

    }
}
