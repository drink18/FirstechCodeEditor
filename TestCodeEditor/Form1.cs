using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TestCodeEditor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnPrintOut_Click(object sender, EventArgs e)
        {
            Debug.WriteLine(firstechCodeEditor1.Editor.Text);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var od = new OpenFileDialog();
            od.Filter = "src files (*.src) | *.src|header files (*.h)|*.h";
            od.FilterIndex = 1;
            od.RestoreDirectory = true;

            if(od.ShowDialog() == DialogResult.OK)
            {
                firstechCodeEditor1.OpenFile(od.FileName);
            }
        }
    }
}
