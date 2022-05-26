using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace гексагональная_сетка
{
    public partial class Form1 : Form
    {
        public Game gm;

        Bitmap bmp;
        public Form1()
        {
            InitializeComponent();
        }



        private void Form1_Load(object sender, EventArgs e)
        {
            gm = new Game();
           
            bmp = new Bitmap(600, 600);
            pictureBox1.Paint += PictureBox_Paint;
        }

        private void CheckGameState()
        {
            if (gm.gs==GameState.GameOver)
            {
                GameOverForm gameOverForm = new GameOverForm();
                gameOverForm.winners = gm.Winners;
                gameOverForm.ShowDialog(this);
            }
        }

        private void PictureBox_Paint(object sender, PaintEventArgs e)
        {
            Graphics gr = Graphics.FromImage(bmp);
            gm.Draw(gr);
            e.Graphics.DrawImage(bmp, 0, 0);
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
    
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
           // gm.Select(new PointF(e.X, e.Y));
            //    Invalidate();
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                gm.NextPlayer();
                gm.gs = GameState.SelectFishka;
            }
            else
                gm.Select(new PointF(e.X, e.Y));

            CheckGameState();
            pictureBox1.Invalidate();
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            //gm.Select(new PointF(e.X, e.Y));
           // pictureBox1.Invalidate();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            gm = new Game();
            gm.StartGame(trackBar1.Value);
            pictureBox1.Invalidate();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            gm.NextPlayer();
            pictureBox1.Invalidate();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
