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

#include "CarApp.h"
#include "common.h"
#include "veins/modules/messages/CoinRequest_m.h"
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

using namespace veins;

Define_Module(veins::CarApp);

void CarApp::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    coinAssignmentStage = CoinAssignmentStage::INIT;
    coinDepositStage = CoinDepositStage::INIT;
    rsuPosition = Coord(par("rsu_x"), par("rsu_y"));
    rsuAddress = par("rsu_address").intValue();
}

void CarApp::handlePositionUpdate(cObject* obj) {
    DemoBaseApplLayer::handlePositionUpdate(obj);
    ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
    curPosition = mobility->getPositionAt(simTime());
    double distanceToRSU = sqrt(pow(curPosition.x - rsuPosition.x, 2) + pow(curPosition.y - rsuPosition.y, 2));

    if (distanceToRSU < 100 && coinAssignmentStage == CoinAssignmentStage::INIT) {
        CoinRequest* msg = new CoinRequest();
        populateWSM(msg, 10);
        msg->setVid(myId);
        msg->setByteLength(16);
        sendDown(msg);
        coinAssignmentStage = CoinAssignmentStage::REQUESTED;
    }
}

void CarApp::onWSM(BaseFrame1609_4* wsm) {
    DemoBaseApplLayer::onWSM(wsm);
    if (CoinRequest* req = check_and_cast<CoinRequest*>(wsm)) {
        EV << "Vehicle: I received a message!!!" << endl;
    }
}
