using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestClangSharp
{
    using ClangSharp;

    internal static class Extensions
    {
        public static bool IsInSystemHeader(this CXCursor cursor) { return clang.Location_isInSystemHeader(clang.getCursorLocation(cursor)) != 0;
        }
    }
}
