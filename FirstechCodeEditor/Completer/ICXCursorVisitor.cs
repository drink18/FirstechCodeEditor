using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstechCodeEditor.Completer
{
    using ClangSharp;
    internal interface ICXCursorVisitor
    {
        CXChildVisitResult Visit(CXCursor cursor, CXCursor parent, IntPtr data);
    }
}
