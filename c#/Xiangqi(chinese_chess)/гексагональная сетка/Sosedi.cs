using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace гексагональная_сетка
{
    public class Sosedi
    {
        public Cell Near;
        public Cell Far;

        public List<Cell> Items {
            get {
                return new List<Cell>() {
                    Near,
                    Far
                };
            }
        }
    }
}
