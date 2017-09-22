using FirstechCodeEditor.Completer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace FirstechCodeEditor
{
    public partial class FirstechCodeEditor : UserControl
    {
        string _fileName;
        public string OpenedFilename
        {
            get { return _fileName; }
        }

        ClangUtils _utils;
        public void OpenFile(string file_name)
        {
            _fileName = file_name;
            textEditor.Load(file_name);

            var incl = new string[]
            {
                @"D:\wei_github\TestCSharpCode\testFiles\include"
            };
            _utils = new ClangUtils(_fileName, incl);
        }
    }
}
