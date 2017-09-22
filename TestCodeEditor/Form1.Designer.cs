namespace TestCodeEditor
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.codeEditor = new System.Windows.Forms.Integration.ElementHost();
            this.firstechCodeEditor1 = new FirstechCodeEditor.FirstechCodeEditor();
            this.btnPrintOut = new System.Windows.Forms.Button();
            this.btnLoadFile = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // codeEditor
            // 
            this.codeEditor.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.codeEditor.Location = new System.Drawing.Point(0, 0);
            this.codeEditor.Name = "codeEditor";
            this.codeEditor.Size = new System.Drawing.Size(284, 210);
            this.codeEditor.TabIndex = 0;
            this.codeEditor.Text = "codeEditor";
            this.codeEditor.Child = this.firstechCodeEditor1;
            // 
            // btnPrintOut
            // 
            this.btnPrintOut.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnPrintOut.Location = new System.Drawing.Point(13, 227);
            this.btnPrintOut.Name = "btnPrintOut";
            this.btnPrintOut.Size = new System.Drawing.Size(75, 23);
            this.btnPrintOut.TabIndex = 1;
            this.btnPrintOut.Text = "Print";
            this.btnPrintOut.UseVisualStyleBackColor = true;
            this.btnPrintOut.Click += new System.EventHandler(this.btnPrintOut_Click);
            // 
            // btnLoadFile
            // 
            this.btnLoadFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnLoadFile.Location = new System.Drawing.Point(145, 227);
            this.btnLoadFile.Name = "btnLoadFile";
            this.btnLoadFile.Size = new System.Drawing.Size(75, 23);
            this.btnLoadFile.TabIndex = 2;
            this.btnLoadFile.Text = "Load File";
            this.btnLoadFile.UseVisualStyleBackColor = true;
            this.btnLoadFile.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.btnLoadFile);
            this.Controls.Add(this.btnPrintOut);
            this.Controls.Add(this.codeEditor);
            this.Name = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Integration.ElementHost elementHost1;
        private System.Windows.Forms.Integration.ElementHost codeEditor;
        private FirstechCodeEditor.FirstechCodeEditor firstechCodeEditor1;
        private System.Windows.Forms.Button btnPrintOut;
        private System.Windows.Forms.Button btnLoadFile;
    }
}

