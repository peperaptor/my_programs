using System;
using System.Collections.Generic;
using System.Linq;

namespace govno_stepica
{
    public class Tree
    {

        private Tree _parent = null;
        public Tree Parent
        {
            get
            {
                return _parent;
            }
            set
            {
                _parent = value;
            }
        }
        private Tree _left = null;
        public Tree Left
        {
            get
            {
                return _left;
            }
            set
            {
                _left = value;
            }
        }
        private Tree _right = null;
        public Tree Right
        {
            get
            {
                return _right;
            }
            set
            {
                _right = value;
            }
        }

        private int _value = 0;
        public int Value
        {
            get
            {
                int res = _value;
                if (Left != null)
                {
                    res += Left.Value;
                }
                if (Right != null)
                {
                    res += Right.Value;
                }
                return res;
            }
            set
            {
                _value = value;
            }
        }
        private char _simbol = 'A';
        public char Simbol
        {
            get
            {
                return _simbol;
            }
        }

        private string _myCode;
        public string MyCode
        {
            get
            {
                return _myCode;
            }
            set
            {
                _myCode = value + _myCode;
            }
        }
        public void ChangeCode(int newPartCode)
        {
            MyCode = newPartCode.ToString();
            if (Right != null)
            {
                Right.ChangeCode(newPartCode);
            }
            if (Left != null)
            {
                Left.ChangeCode(newPartCode);
            }
        }

        public Tree(int val, char smb)
        {
            Value = val;
            _simbol = smb;
        }
        public Tree(Tree left, Tree right)
        {
            AddChildren(left, right);
        }
        public void AddChildren(Tree left, Tree right)
        {
            AddLeftChild(left);
            AddRightChild(right);
        }
        public void AddLeftChild(Tree left)
        {
            Left = left;
            Left.Parent = this;
            Left.ChangeCode(1);
        }
        public void AddRightChild(Tree right)
        {
            Right = right;
            Right.Parent = this;
            Right.ChangeCode(0);
        }

        public string[] GetAsString()
        {
            List<string> res = new List<string>();
            //res.Add("Symbol: " + this.Simbol + " Value: " + this.Value + " My code: " + this.MyCode);
            res.Add(this.Simbol + "+" + this.Value + "+" + this.MyCode);
            if (Right != null)
            {
                //res.Add("Right: ");
                Right.GetAsString().ToList().ForEach(x => res.Add(x));
            }
            if (Left != null)
            {
                //res.Add("Left: ");
                Left.GetAsString().ToList().ForEach(x => res.Add(x));
            }
            return res.ToArray();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            string str = Console.ReadLine();

            Dictionary<char, int> Smbls = new Dictionary<char, int>();
            foreach (var bkv in str)
            {
                if (!Smbls.ContainsKey(bkv))
                {
                    Smbls.Add(bkv, 1);
                }
                else
                {
                    Smbls[bkv] += 1;
                }
            }

            List<Tree> Hoff = new List<Tree>();
            foreach (var item in Smbls)
            {
                Hoff.Add(new Tree(item.Value, item.Key));
            }

            bool govnokostyl = true;
            if ((Hoff.Count == 1))
            {
                Console.WriteLine("1 " + str.Length);
                Console.WriteLine(Hoff[0].Simbol + ": 0");
                str.ToList().ForEach(x => Console.Write(0));
                Hoff.RemoveAt(0);
                govnokostyl = false;
            }

            while (Hoff.Count > 1)
            {
                Hoff = Hoff.OrderByDescending(x => x.Value).ToList();
                int k = Hoff.Count() - 1;
                Tree lst = new Tree(Hoff[k - 1], Hoff[k]);
                Hoff.RemoveAt(k);
                Hoff.RemoveAt(k - 1);
                Hoff.Add(lst);
            }


            if (govnokostyl)
            {
                int countSimbAns = 0;
                Dictionary<char, string> AnsToShif = new Dictionary<char, string>();

                string[] res = Hoff[0].GetAsString();
                foreach (var versina in res)
                {
                    string[] part = versina.Split('+');

                    char simbol = part[0][0];
                    int value = Int32.Parse(part[1]);
                    string myCode = part[2];

                    if (Smbls.ContainsKey(simbol))
                    {
                        countSimbAns += myCode.Length * value;

                        if (!AnsToShif.ContainsKey(simbol))
                        {
                            AnsToShif.Add(simbol, myCode);
                        }
                    }
                }

                Console.WriteLine(AnsToShif.Count + " " + countSimbAns);
                foreach (var code in AnsToShif.OrderBy(x => x.Value.Length))
                {
                    Console.WriteLine(code.Key + ": " + code.Value);
                }
                foreach (var item in str)
                {
                    Console.Write(AnsToShif[item]);
                }
            }
            Console.ReadKey();
        }
    }
}