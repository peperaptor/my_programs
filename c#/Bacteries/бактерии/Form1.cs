using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace бактерии
{  
    public partial class Form1 : Form
    {
        Life life;

        public Form1()
        {
            InitializeComponent();
        }

        private void Init()
        {
            life = new Life();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Init();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            life.Paint(e.Graphics, e.ClipRectangle);
         
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            life.Moove();
            life.Check();
            int piece = life.pb.Count(x => x.type == BactType.Piece && x.IsAlive);
            int evil = life.pb.Count(x => x.type == BactType.Evil && x.IsAlive);
            int count = life.pb.Count;

            this.Text = String.Format("{0} / {1}   ({2:0.0}/{3:0.0})", piece, evil, 100.0 * piece / count, 100.0 * evil / count);

            pictureBox1.Invalidate();
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
 
                if (e.Button == MouseButtons.Left)
                {
                    life.AddBact(BactType.Evil, new PointF(e.X, e.Y));
                }
                else if (e.Button == MouseButtons.Right)
                {
                    life.AddBact(BactType.Piece, new PointF(e.X, e.Y));
                }
           
            
              
        }

        private void pictureBox1_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyData == Keys.Space)
            {
                Init();
            }
        }
    }
}
