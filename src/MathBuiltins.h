// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright (C) 2008, 2010, 2013 panacoran <panacoran@users.sourceforge.jp>
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

#ifndef DF_MATHBUILTIN_H_
#define DF_MATHBUILTIN_H_

#include <math.h>
#include "PrintBuiltins.h"

namespace Protra {
namespace Lib {
namespace Lang {
namespace Builtins {

class MathBuiltins :public PrintBuiltins {
public:
	virtual std::shared_ptr<Value> Invoke(std::string& name, std::vector<std::shared_ptr<Value> >& args, int at, std::string& ats)override
    {
		if (name == "Random")
        {
            if (args.size() == 0) {
                double d=(double)rand() / RAND_MAX;
                std::shared_ptr<Value>ret;
                ret = std::shared_ptr<Value>(new Value(d));
                return ret;                            }
            if (args.size() == 1) {
                int  x = args[0]->InnerValue().toInt();
                srand(x);
                double d = (double)rand() / RAND_MAX;
                std::shared_ptr<Value>ret;
                ret = std::shared_ptr<Value>(new Value(d));
                return ret;
            }
        }
        else if (args.size() == 1)
        {
            double (*pf)(double) = nullptr;

            if (name == "Exp") {
				pf = exp;
            }
            else if (name == "Log")
            {
				pf = log;
            }
            else if (name == "Sqrt")
			{
                pf = sqrt;
            }
            else if (name == "Sin")
            {
                pf = sin;
            }
            else if (name == "Cos")
            {
				pf = cos;
            }
            else if (name == "Tan")
            {
				pf = tan;
            }
            else if (name == "Asin") {
				pf = asin;
            }
            else if (name == "Acos") {
                pf = acos;
            }
            else if (name == "Atan") {
                pf = atan;
            }
            if (pf) {
                std::shared_ptr<Value> ret;
                ret= std::shared_ptr<Value>(new Value(pf(args[0]->InnerValue().toFloat())));
                return ret;
            }
        }
        else if (args.size() == 2 && name == "Pow")
        {
            double x = args[0]->InnerValue().toFloat();
            double y = args[1]->InnerValue().toFloat();
            double d = pow(x, y);
            std::shared_ptr<Value>ret;
            ret = std::shared_ptr<Value>(new Value(d));
            return ret;
        }
        return PrintBuiltins::Invoke(name, args, at, ats);
    }
};


}
}
}
}
#endif

