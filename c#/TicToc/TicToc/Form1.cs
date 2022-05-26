using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicToc
{
    public partial class Form1 : Form
    {
        Game game;
        public Form1()
        {
            InitializeComponent();
        }

        private void Init()
        {
            game = new Game(Convert.ToInt32(numericUpDown1.Value), (int)numericUpDown3.Value);
            Resize();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Init();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            game.Paint(e.Graphics);
           
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            game.MouseDown(new Point(e.X, e.Y));
            switch (game.status)
            {
                case Game.GameStatus.On:
                    Text = "Игра продолжается";
                    break;
                case Game.GameStatus.WinFirst:
                    Text = "Выиграл первый игрок";
                    break;
                case Game.GameStatus.WinSecond:
                    Text = "Выиграл второй игрок";
                    break;
                case Game.GameStatus.Draw:
                    Text = "Ничья!";
                    break;
                default:
                    break;
            }
            pictureBox1.Invalidate();
        }

        private void Resize()
        {
            game.sz = Math.Min(pictureBox1.Width, pictureBox1.Height) / game.N;
            pictureBox1.Invalidate();
        }

        private void pictureBox1_Resize(object sender, EventArgs e)
        {
            Resize();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Init();
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            if (numericUpDown3.Value > numericUpDown1.Value)
            {
                numericUpDown3.Value = numericUpDown1.Value;
            }
            numericUpDown3.Maximum = numericUpDown1.Value;
        }
    }
}
