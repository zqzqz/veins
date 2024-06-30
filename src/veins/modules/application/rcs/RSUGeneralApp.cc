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

#include "RSUGeneralApp.h"
#include "common.h"
#include "veins/modules/messages/CoinRequest_m.h"
#include "veins/modules/messages/CoinAssignment_m.h"
#include "veins/modules/messages/CoinDeposit_m.h"
#include "veins/modules/messages/CoinDepositSignatureRequest_m.h"
#include "veins/modules/messages/CoinDepositSignatureResponse_m.h"
#include "veins/modules/messages/CoinSubmission_m.h"
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

using namespace veins;

Define_Module(veins::RSUGeneralApp);

void RSUGeneralApp::initialize(int stage) {
    RSUApp::initialize(stage);
    int numCpuCores = par("numCpuCores");
    cpuModel.init(numCpuCores);
    EV_WARN << "[RSU]: Address " << myId << endl;
}

void RSUGeneralApp::handleSelfMsg(cMessage* msg) {

}

void RSUGeneralApp::onWSM(BaseFrame1609_4* wsm) {
    if (CoinRequest* req = dynamic_cast<CoinRequest*>(wsm)) {
        EV_WARN << "[RSU]: I received a message of CoinRequest from " << req->getVid() << endl;
        int vid = req->getVid();

        CoinAssignment* res = new CoinAssignment();
        populateWSM(res, vid);
        res->setVid(vid);
        res->setByteLength(COIN_ASSIGNMENT_BYTE_SIZE);

        CpuModel::Latency latencyInfo = cpuModel.getLatencyInfo(simTime().dbl(), COIN_ASSIGNMENT_LATENCY_MEAN, COIN_ASSIGNMENT_LATENCY_STDDEV);
        sendDelayedDown(res->dup(), latencyInfo.all);
        coinAssignmentStages[vid] = CoinAssignmentStage::SENT;
        EV_WARN << "[RSU]: I sent a message of CoinAssignment to " << req->getVid()
                << ". Queue time " << latencyInfo.queue_time << " Computation time " << latencyInfo.computation_time << endl;
    } else if (CoinDeposit* req = dynamic_cast<CoinDeposit*>(wsm)) {
        EV_WARN << "[RSU]: I received a message of CoinDeposit from " << req->getVid() << endl;
        int vid = req->getVid();
        CoinDepositSignatureRequest* res = new CoinDepositSignatureRequest();
        populateWSM(res, vid);
        res->setVid(vid);
        res->setByteLength(COIN_DEPOSIT_SIGNATURE_REQUEST_BYTE_SIZE);
        CpuModel::Latency latencyInfo = cpuModel.getLatencyInfo(simTime().dbl(), COIN_DEPOSIT_SIGNATURE_REQUEST_LATENCY_MEAN, COIN_DEPOSIT_SIGNATURE_REQUEST_LATENCY_STDDEV);
        sendDelayedDown(res->dup(), latencyInfo.all);
        coinDepositStages[vid] = CoinDepositStage::SIGNATURE_REQUESTED;
        EV_WARN << "[RSU] I sent a message of CoinDepositSignatureRequest to " << req->getVid()
                << ". Queue time " << latencyInfo.queue_time << " Computation time " << latencyInfo.computation_time << endl;
    } else if (CoinDepositSignatureResponse* req = dynamic_cast<CoinDepositSignatureResponse*>(wsm)) {
        EV_WARN << "[RSU]: I received a message of CoinDepositSignatureResponse from " << req->getVid() << endl;
        int vid = req->getVid();
        if (coinDepositStages.find(vid) != coinDepositStages.end() && coinDepositStages[vid] == CoinDepositStage::SIGNATURE_REQUESTED) {
            // TODO: The communication to central database.
            coinDepositStages[vid] = CoinDepositStage::SUBMITTED;
            EV_WARN << "[Vehicle " << vid << "]: Coin deposit succeed." << endl;
        }
    }
}
