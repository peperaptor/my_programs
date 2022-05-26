using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace гексагональная_сетка
{
    public class Player
    {
        public Type cellType = Type.none;
        public string Name = "";

        public override string ToString()
        {
            return Name + " " + cellType.ToString();
        }
    }
}
