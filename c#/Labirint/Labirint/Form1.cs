using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Labirint
{
    public partial class Form1 : Form
    {
        Game gm;
        public Form1()
        {
            InitializeComponent();
            Init();
        }

        public void Init()
        {
            gm = new Game();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            gm.Draw(e.Graphics, e.ClipRectangle);
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Right) gm.player.Move(Direction.Right);
            else if (e.KeyData == Keys.Down) gm.player.Move(Direction.Down);
            else if (e.KeyData == Keys.Left) gm.player.Move(Direction.Left);
            else if (e.KeyData == Keys.Up) gm.player.Move(Direction.Up);
            
            Text = String.Format("Scores: {0}", gm.player.Scores.ToString());
            pictureBox1.Invalidate();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void pictureBox1_MouseDoubleClick_1(object sender, MouseEventArgs e)
        {
            Init();
            pictureBox1.Invalidate();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            gm.TrainMove();
            pictureBox1.Invalidate();
        }
    }
}
