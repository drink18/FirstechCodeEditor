using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstechCodeEditor.Completer
{
    using ClangSharp;

    internal sealed class FunctionVisitor : ICXCursorVisitor
    {
        public class FunctionInfo
        {
            public CXCursor Cursor;
            public string Name;
            public List<Tuple<string, string>> Args = new List<Tuple<string, string>>();

            public string FunctionSignature()
            {
                string sig = Name + "(";
                for(int i = 0; i < Args.Count; ++i)
                {

                    sig += string.Format("{0} {1}", Args[i].Item1, Args[i].Item2);
                    if (i != Args.Count - 1)
                        sig += ", ";
                }
                sig += ")";

                return sig;
            }
        }
        private readonly HashSet<string> visitedFunctions = new HashSet<string>();
        public HashSet<string> VisistedFunctions { get { return visitedFunctions; } }

        public Dictionary<string, FunctionInfo> FunctionInfos = new Dictionary<string, FunctionInfo>();
        public FunctionVisitor()
        {
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

                if (FunctionInfos.ContainsKey(functionName))
                {
                    return CXChildVisitResult.CXChildVisit_Continue;
                }

                var fi = new FunctionInfo();
                fi.Name = functionName;
                fi.Cursor = cursor;

                FunctionInfos[functionName] = fi;

                return CXChildVisitResult.CXChildVisit_Continue;
            }

            return CXChildVisitResult.CXChildVisit_Recurse;
        }

        public CXChildVisitResult ArgsVisit(CXCursor cursor, CXCursor parent, IntPtr data)
        {
            if (cursor.IsInSystemHeader())
            {
                return CXChildVisitResult.CXChildVisit_Continue;
            }

            CXCursorKind curKind = clang.getCursorKind(cursor);

            // look only at function parameter
            if (curKind == CXCursorKind.CXCursor_ParmDecl)
            {
                var functionName = clang.getCursorSpelling(parent).ToString();
                var argTypeName = clang.getCursorType(cursor).ToString();
                var argName = clang.getCursorSpelling(cursor).ToString();

                var fi = FunctionInfos[functionName];
                fi.Args.Add(new Tuple<string, string>(argTypeName, argName));

                return CXChildVisitResult.CXChildVisit_Continue;
            }

            return CXChildVisitResult.CXChildVisit_Recurse;
        }

        public static Dictionary<string, FunctionInfo> ParseFunctionInfo( CXCursor start)
        {
            var visitor = new FunctionVisitor();
            clang.visitChildren(start, visitor.Visit,new CXClientData(IntPtr.Zero));

            foreach (var fiPair in visitor.FunctionInfos)
            {
                var fi = fiPair.Value;
                clang.visitChildren(fi.Cursor, visitor.ArgsVisit, new CXClientData(IntPtr.Zero));
            }

            return visitor.FunctionInfos;
        }
    }
}
