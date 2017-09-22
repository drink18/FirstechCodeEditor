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

            string code = "int main(int nargs, char** nargs)\n {\n return 0;\n }\n";

            firstechCodeEditor1.Editor.Text = code;
        }
    }
}
