using ICSharpCode.AvalonEdit;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ClangSharp;

namespace FirstechCodeEditor
{
    /// <summary>
    /// UserControl1.xaml 的交互逻辑
    /// </summary>
    public partial class FirstechCodeEditor : UserControl
    {
        public TextEditor Editor
        {
            get { return textEditor; }
        }

        public FirstechCodeEditor()
        {
            InitializeComponent();
            parseTranslationUnit();
        }
        
        public void parseTranslationUnit()
        {
            var index = clang.createIndex(0, 0);
            string[] arr = { "-x", "c++" };
            CXTranslationUnit translationUnit;
            CXUnsavedFile unsavedFile;

            var filename = @"D:\wei_github\TestCSharpCode\testCFiles\test1.cpp";
            var translationUnitError = clang.parseTranslationUnit2(index, filename, arr, 2, out unsavedFile, 0, 0, out translationUnit);
            if (translationUnitError != CXErrorCode.CXError_Success)
            {
                Console.WriteLine("Error: " + translationUnitError);
            }
            var numDiagnostics = clang.getNumDiagnostics(translationUnit);

            for (uint i = 0; i < numDiagnostics; ++i)
            {
                var diagnostic = clang.getDiagnostic(translationUnit, i);
                Console.WriteLine(clang.getDiagnosticSpelling(diagnostic).ToString());
                clang.disposeDiagnostic(diagnostic);
            }
        }
    }
}
