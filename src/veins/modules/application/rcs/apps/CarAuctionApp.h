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

#ifndef APPS_CARAUCTIONAPP_H_
#define APPS_CARAUCTIONAPP_H_

#include "../CarApp.h"

using namespace omnetpp;

namespace veins {

class CarAuctionApp : public CarApp {
public:
    void initialize(int stage) override;
protected:
    double lastDistanceToRSU;
protected:
    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
    void onWSM(BaseFrame1609_4* wsm) override;
};

} // veins namespace

#endif /* APPS_CARAUCTIONAPP_H_ */
