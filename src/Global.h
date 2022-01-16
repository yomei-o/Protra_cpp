// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright (C) 2003 Daisuke Arai <darai@users.sourceforge.jp>
// Copyright (C) 2005, 2010 panacoran <panacoran@users.sourceforge.jp>
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
// $Id: Global.cs 389 2010-11-28 06:45:45Z panacoran $

#ifndef DF_GLOBAL_H_
#define DF_GLOBAL_H_

#include "BrandData.h"

namespace Protra {
namespace Lib {

class GlobalEnv
{
public:
    static std::shared_ptr<Data::BrandData>& BrandData() {
        static std::shared_ptr<Data::BrandData> bd;
        return bd;
    };
};

}
}


#endif


