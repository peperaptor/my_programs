using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TicToc
{
    class Game
    {
        public enum GameStatus
        {
            On = 0,
            WinFirst = 1,
            WinSecond = -1,
            Draw = 2
        }

        public int N;
        public int WinN;
        public List<List<int>> m;
        public int sz = 50;
        public int pm = 1;
        public GameStatus status = GameStatus.On;

        private int SelI = -1, SelJ = -1;

        public Game(int N, int WinN)
        {
            this.N = N;
            this.WinN = WinN;
            m = new List<List<int>>();
            for (int i = 0; i < N; i++)
            {
                List<int> row = new List<int>();
                for (int j = 0; j < N; j++)
                {
                    row.Add(0);
                }
                m.Add(row);
            }
        }

        private int IsWinRow(int i, int j, ref int t, ref int K)
        {
            if (t != m[i][j])
            {
                t = m[i][j];
                K = Math.Abs(t);
            }
            else
            {
                K += Math.Abs(t);
            }

            if (K >= WinN)
            {
                return t;
            }

            return 0;
        }

        private int Check()
        {
            int t;
            int K;
            for (int i = 0; i < N; i++)
            {
                t = m[i][0];
                K = Math.Abs(t);
                for (int j = 1; j < N; j++)
                {
                    int res = IsWinRow(i, j, ref t, ref K);
                    if (res != 0) return res;
                }
            }

            for (int i = 0; i < N; i++)
            {
                t = m[0][i];
                K = Math.Abs(t);
                for (int j = 1; j < N; j++)
                {
                    int res = IsWinRow(j, i, ref t, ref K);
                    if (res != 0) return res;
                }
            }

            for (int i = 0; i < N - WinN+1; i++) 
                for(int sw = 0; sw<=1; sw++){
                    t = m[i*(1-sw)][i*sw];
                    K = Math.Abs(t);
                    for (int j = 1; j < N-i; j++)
                    {
                        int res = IsWinRow(j+i*(1-sw), j+i*sw, ref t, ref K);
                        if (res != 0) return res;
                    }
                }

            for (int i = 0; i < N - WinN + 1; i++)
                for (int sw = 0; sw <= 1; sw++)
                {
                    t = m[N-1-i * (1 - sw)][i * sw];
                    K = Math.Abs(t);
                    for (int j = 1; j < N - i; j++)
                    {
                        int res = IsWinRow(N -1- i * (1 - sw)-j, j + i * sw, ref t, ref K);
                        if (res != 0) return res;
                    }
                }

            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (m[i][j] == 0)
                    {
                        return 0;
                    }
                }
            }

            
            return 2;
        }

        public Rectangle GetRect(int i, int j)
        {
            return new Rectangle(sz * j, sz * i, sz, sz);
        }

        public void Paint(Graphics g)
        {
            
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j< N; j++)
                {
                    Rectangle rect = GetRect(i, j);

                    SolidBrush brush = new SolidBrush(Color.White);                   
                    if (SelI == i && SelJ == j)
                    {
                        brush = new SolidBrush(Color.Blue);
                    }

                    g.FillRectangle(brush, rect);
                    g.DrawRectangle(Pens.Black, rect);

                    if (m[i][j] == 1)
                    {
                        g.DrawLine(Pens.Red,rect.X, rect.Y, rect.X + sz, rect.Y + sz);
                        g.DrawLine(Pens.Red,rect.X+sz, rect.Y, rect.X, rect.Y + sz);
                    }
                    else if (m[i][j] == -1)
                    {
                        g.DrawEllipse(Pens.Red, rect);
                    }

                    Rectangle rect1 = GetRect(0, N+1);
                }
            }
        }

        public void MouseDown(Point p)
        {
            SelI = p.Y / sz;
            SelJ = p.X / sz;
            if (SelI >= 0 && SelJ >= 0 && SelI < N && SelJ < N && m[SelI][SelJ]==0)
            {  
                m[SelI][SelJ] = pm;
                pm = -pm;

                status = (GameStatus)Check();             
            }      
        }
    }
}
