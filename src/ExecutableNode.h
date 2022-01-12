// Copyright (C) 2003, 2005 Daisuke Arai <darai@users.sourceforge.jp>
// Copyright (C) 2008, 2013 panacoran <panacoran@users.sourceforge.jp>
// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// 
// This program is part of Protra.
//
// Protra is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
// 

#ifndef DH_EXECUTABLE_NODE_H_
#define DH_EXECUTABLE_NODE_H_

#include <memory>
#include "Scanner.h"
#include "Resource.h"

namespace Protra {
namespace Lib {
namespace Lang {


    enum Result
    {
        Normal,
        Return,
        Break,
        Confinue
    };
    class ExecutableNode
    {
    public:
        Token Token;
        virtual std::shared_ptr<ExecutableNode> Parse(std::shared_ptr<ExecutableNode>&that,Scanner& scanner)
        {
            return that;
        }
        virtual Result Execute(std::shared_ptr<ExecutableNode>&that,Resource& resource, int at, std::string& ats)
        {
			return Result::Break;
        }
    };

}
}
}

#endif


