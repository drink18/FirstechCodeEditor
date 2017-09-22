using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClangSharp;

namespace TestClangSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            var index = clang.createIndex(0, 0);
            string[] arr = { "-x", "c++" };
            CXTranslationUnit translationUnit;
            CXUnsavedFile unsavedFile;

            var filename = @"D:\wei_github\TestCSharpCode\testFiles\1pulse_loop.src";
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
