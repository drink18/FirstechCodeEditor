using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClangSharp;
using System.IO;

namespace TestClangSharp
{
    internal sealed class FunctionVisitor : ICXCursorVisitor
    {
        private readonly TextWriter tw;

        private readonly HashSet<string> visitedFunctions = new HashSet<string>();
        public HashSet<string> VisistedFunctions { get { return visitedFunctions; } }

        private readonly string prefixStrip;

        public FunctionVisitor(TextWriter tw, string libraryPath, string prefixStrip)
        {
            this.prefixStrip = prefixStrip;
            this.tw = tw;
            this.tw.WriteLine("        private const string libraryPath = \"" + libraryPath + "\";");
            this.tw.WriteLine();
        }

        public CXChildVisitResult Visit(CXCursor cursor, CXCursor parent, IntPtr data)
        {
            if (cursor.IsInSystemHeader())
            {
                return CXChildVisitResult.CXChildVisit_Continue;
            }

            CXCursorKind curKind = clang.getCursorKind(cursor);

            // look only at function decls
            if (curKind == CXCursorKind.CXCursor_FunctionDecl)
            {
                var functionName = clang.getCursorSpelling(cursor).ToString();

                if (this.visitedFunctions.Contains(functionName))
                {
                    return CXChildVisitResult.CXChildVisit_Continue;
                }

                this.visitedFunctions.Add(functionName);

                //Extensions.WriteFunctionInfoHelper(cursor, this.tw, this.prefixStrip);

                return CXChildVisitResult.CXChildVisit_Continue;
            }

            return CXChildVisitResult.CXChildVisit_Recurse;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            string root = @"D:\wei_github\TestCSharpCode\testFiles\";
            var index = clang.createIndex(0, 0);
            string[] arr = { "-x", "c", @"-I" + root + @"include" };
            CXTranslationUnit translationUnit;
            CXUnsavedFile unsavedFile;

            var filename = root + @"1pulse_loop.src";
            var translationUnitError = clang.parseTranslationUnit2(index, filename, arr, 3, out unsavedFile, 0, 0, out translationUnit);
            if (translationUnitError != CXErrorCode.CXError_Success)
            {
                Console.WriteLine("Error: " + translationUnitError);
            }
            var numDiagnostics = clang.getNumDiagnostics(translationUnit);

            for (uint i = 0; i < numDiagnostics; ++i)
            {
                var diagnostic = clang.getDiagnostic(translationUnit, i);
                var loc = clang.getDiagnosticLocation(diagnostic);
                var cat = clang.getDiagnosticCategoryName(clang.getDiagnosticCategory(diagnostic));

                uint line, col, offset;
                CXFile file;

                clang.getSpellingLocation(loc, out file, out line, out col, out offset);
                Console.Write(string.Format("{0}_{1}:({2}, {3}) :", cat, clang.getFileName(file).ToString(), line, col )); 
                Console.WriteLine(clang.getDiagnosticSpelling(diagnostic).ToString());
                clang.disposeDiagnostic(diagnostic);
            }


            string outputFile = "testresult.txt";
            using (var sw = new StreamWriter(outputFile))
            {
                var funcVisitor = new FunctionVisitor(sw, "", "");
                clang.visitChildren(clang.getTranslationUnitCursor(translationUnit), funcVisitor.Visit, new CXClientData(IntPtr.Zero));
                foreach (var fn in funcVisitor.VisistedFunctions)
                {
                    Console.WriteLine("visited " + fn);
                }
            }

            Console.ReadKey();
        }
    }
}
