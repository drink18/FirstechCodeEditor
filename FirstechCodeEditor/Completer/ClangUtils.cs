using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstechCodeEditor.Completer
{
    using ClangSharp;
    using System.Diagnostics;
    using System.IO;
    using static FunctionVisitor;

    class ClangUtils
    {
        string _filename;
        string[] _include;
        string[] _options;

        public Dictionary<string, FunctionInfo> FunctionInfos;

        public ClangUtils(string file_name, string[] includes)
        {
            var index = clang.createIndex(0, 0);
            _include = includes;
            var incl = includes.Select(o => "-I" + o);
            string[] arr = { "-x", "c"};
            arr = arr.Concat(incl).ToArray();
            _options = arr;

            CXTranslationUnit translationUnit;
            CXUnsavedFile unsavedFile;

            _filename = file_name;
            var translationUnitError = clang.parseTranslationUnit2(index, _filename, arr, arr.Length, out unsavedFile, 0, 0, out translationUnit);
            if (translationUnitError != CXErrorCode.CXError_Success)
            {
                Console.WriteLine("Error: " + translationUnitError);
            }
            var cursor = clang.getTranslationUnitCursor(translationUnit);
            FunctionInfos = FunctionVisitor.ParseFunctionInfo(cursor);
#if false
            var numDiagnostics = clang.getNumDiagnostics(translationUnit);

            for (uint i = 0; i < numDiagnostics; ++i)
            {
                var diagnostic = clang.getDiagnostic(translationUnit, i);
                var loc = clang.getDiagnosticLocation(diagnostic);
                var cat = clang.getDiagnosticCategoryName(clang.getDiagnosticCategory(diagnostic));

                uint line, col, offset;
                CXFile file;

                clang.getSpellingLocation(loc, out file, out line, out col, out offset);
                Debug.Write(string.Format("{0}_{1}:({2}, {3}) :", cat, clang.getFileName(file).ToString(), line, col )); 
                Debug.WriteLine(clang.getDiagnosticSpelling(diagnostic).ToString());
                clang.disposeDiagnostic(diagnostic);
            }
            string outputFile = "testresult.txt";
            using (var sw = new StreamWriter(outputFile))
            {
                var funcVisitor = new FunctionVisitor(sw, "", "");
                clang.visitChildren(clang.getTranslationUnitCursor(translationUnit), funcVisitor.Visit, new CXClientData(IntPtr.Zero));
                _allfunctions = funcVisitor.VisistedFunctions;
            }
#endif
        }
    }
}
