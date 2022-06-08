using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace бактерии
{
    public enum AreaType
    {
        none = 0,
        field = 1,//поле   еда+2     
        forest = 2,//лес  еда+1 здоровье+1до максимума
        Rock = 3,//скала    здоровье+1  урон+2
        Abyss = 4//пропать  здоровье=0
    }

    class Area
    {
        public RectangleF rect;
        public AreaType type;
        private float _FoodCount;
        public float FoodCount{
            get
            {
                return _FoodCount;
            }
            set
            {
                _FoodCount = Math.Min(value, FoodMax);
                _FoodCount = Math.Max(_FoodCount, 0);
            }

        }

        private float _FoodMax;
        public float FoodMax{
            get
            {
                return _FoodMax;
            }
            set
            {
                _FoodMax = value;
                FoodCount = _FoodMax;
            }
        }

        public float FoodRestoreSpeed = 5;

        public Area()
        {

        }
    }
}
