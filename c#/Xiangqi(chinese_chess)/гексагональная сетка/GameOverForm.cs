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
    public partial class GameOverForm : Form
    {
        public List<Player> winners = new List<Player>();
        public GameOverForm()
        {
            InitializeComponent();
        }

        private void GameOverForm_Load(object sender, EventArgs e)
        {
            listBox1.DataSource = winners;
        }
    }
}
