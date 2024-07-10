//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef RCS_APPS_RSUAPP_H_
#define RCS_APPS_RSUAPP_H_

#include "BaseApp.h"
#include "common.h"
#include "CpuModel.h"
#include <map>

using namespace omnetpp;

namespace veins {

class RSUApp : public BaseApp {
public:
    void initialize(int stage) override;
protected:
    std::map<int, CoinAssignmentStage> coinAssignmentStages;
    std::map<int, CoinDepositStage> coinDepositStages;

    void onWSM(BaseFrame1609_4* wsm) override;
};
} // veins namespace

#endif /* RCS_APPS_RSUAPP_H_ */
