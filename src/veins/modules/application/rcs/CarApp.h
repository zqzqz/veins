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

#ifndef APPS_CARAPP_H_
#define APPS_CARAPP_H_

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "common.h"
#include "CpuModel.h"

using namespace omnetpp;

namespace veins {

class CarApp : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;
protected:
    CoinAssignmentStage coinAssignmentStage;
    CoinDepositStage coinDepositStage;
    Coord rsuPosition;
    LAddress::L2Type rsuAddress;
    CpuModel cpuModel;
    double coinAssignmentLastTry;
    double coinDepositLastTry;
protected:
    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
    void onWSM(BaseFrame1609_4* wsm) override;
};

} // veins namespace

#endif /* APPS_CARAPP_H_ */
