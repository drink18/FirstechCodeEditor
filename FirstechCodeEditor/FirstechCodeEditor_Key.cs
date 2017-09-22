using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace FirstechCodeEditor
{
    using System.Windows.Input;
    using ICSharpCode.AvalonEdit;
    using ICSharpCode.AvalonEdit.CodeCompletion;
    using ICSharpCode.AvalonEdit.Editing;
    using ICSharpCode.AvalonEdit.Document;
    using static Completer.FunctionVisitor;

    public partial class FirstechCodeEditor : UserControl
    {
        class FTCompletionData : ICompletionData
        {
            public string Text { get; private set; }
            string _description;
            public FTCompletionData(FunctionInfo info)
            {
                this.Text = info.Name;
                _description = info.FunctionSignature();
            }
            
            public System.Windows.Media.ImageSource Image
            {
                get { return null; }
            }

            public object Content { get { return this.Text; } }
            public object Description { get { return _description; } }

            public double Priority { get { return 0.0; } }

            public void Complete(TextArea textArea, ISegment completionSegment, EventArgs insertionRequestEventArgs )
            {
                textArea.Document.Replace(completionSegment, this.Text);
            }
        }

        private void TextArea_KeyDown(object sender, KeyEventArgs e)
        {
        }

        CompletionWindow completionWindow;
        private void TextArea_TextEntered(object sender, TextCompositionEventArgs e)
        {
            if(e.Text == ".")
            {
                completionWindow = new CompletionWindow(textEditor.TextArea);
                IList<ICompletionData> data = completionWindow.CompletionList.CompletionData;
                foreach (var func in _utils.FunctionInfos)
                {
                    data.Add(new FTCompletionData(func.Value));
                }

                completionWindow.Show();
                completionWindow.Closed += delegate { completionWindow = null; };
                e.Handled = true;
            }
        }
    }
}
