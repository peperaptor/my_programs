using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Битва_программистов_20001
{
    public partial class Form1 : Form
    {
        public Game gm;
        public Form1()
        {
            InitializeComponent();
        }

        public void InitGame()
        {
            gm = new Game();
            gm.InitGame();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitGame();
            pictureBox1.Paint += PictureBox1_Paint;
        }

        private void PictureBox1_Paint(object sender, PaintEventArgs e)
        {
            gm.Draw(e.Graphics);            
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            gm.MouseDown(e.X, e.Y, e.Button);
            pictureBox1.Invalidate();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            gm.Tick();
            pictureBox1.Invalidate();
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                gm.MouseMove(e.X, e.Y, e.Button);
                pictureBox1.Invalidate();
            } 
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                gm.MouseUp(e.X, e.Y, e.Button);
                pictureBox1.Invalidate();
            }
        }
    }
}
