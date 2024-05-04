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

#include "RSUApp.h"
#include "common.h"
#include "veins/modules/messages/CoinRequest_m.h"
#include "veins/modules/messages/CoinAssignment_m.h"
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

using namespace veins;

Define_Module(veins::RSUApp);

void RSUApp::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
}

void RSUApp::onWSM(BaseFrame1609_4* wsm) {
    DemoBaseApplLayer::onWSM(wsm);
    if (CoinRequest* req = check_and_cast<CoinRequest*>(wsm)) {
        EV << "RSU: I received a message!!!" << endl;
        int vid = req->getVid();
        CoinAssignment* res = new CoinAssignment();
        populateWSM(res, vid);
        res->setVid(vid);
        res->setByteLength(COIN_ASSIGNMENT_BYTE_SIZE);
        scheduleAt(simTime() + 0.5, res->dup());
        coinAssignmentStages[vid] = CoinAssignmentStage::SENT;
    }
}
