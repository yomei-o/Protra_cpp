// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright (C) 2010, 2011, 2013 panacoran <panacoran@users.sourceforge.jp>
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
// $Id: BrandListConfig.cs 508 2014-02-19 06:05:07Z panacoran $
#ifndef DF_BRANDLISTCONFIG_H_
#define DF_BRANDLISTCONFIG_H_

#include <string>
#include <vector>
#include <memory>

namespace Protra {
namespace Lib {
namespace Config {

class BrandList
{
public:
    std::string Name;
    std::shared_ptr<std::vector<std::string>> List;
};

}
}
}
#endif

