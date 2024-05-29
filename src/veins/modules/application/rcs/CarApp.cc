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
#include "veins/modules/messages/CoinAssignment_m.h"
#include "veins/modules/messages/CoinDeposit_m.h"
#include "veins/modules/messages/CoinDepositSignatureRequest_m.h"
#include "veins/modules/messages/CoinDepositSignatureResponse_m.h"
#include "veins/modules/messages/CoinSubmission_m.h"
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

using namespace veins;

Define_Module(veins::CarApp);

void CarApp::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    cpuModel.init(1);
    coinAssignmentStage = CoinAssignmentStage::INIT;
    coinDepositStage = CoinDepositStage::INIT;
    rsuPosition = Coord(par("rsu_x"), par("rsu_y"));
    rsuAddress = par("rsu_address").intValue();
}

void CarApp::handleSelfMsg(cMessage* msg) {
    DemoBaseApplLayer::handleSelfMsg(msg);
}

void CarApp::handlePositionUpdate(cObject* obj) {
    DemoBaseApplLayer::handlePositionUpdate(obj);
    ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
    curPosition = mobility->getPositionAt(simTime());
    double distanceToRSU = sqrt(pow(curPosition.x - rsuPosition.x, 2) + pow(curPosition.y - rsuPosition.y, 2));

    if (coinAssignmentStage != CoinAssignmentStage::INIT && coinAssignmentStage != CoinAssignmentStage::FINISHED && coinAssignmentStage != CoinAssignmentStage::FAILED) {
        if (simTime().dbl() > coinAssignmentLastTry + 5) {
            coinAssignmentStage= CoinAssignmentStage::INIT;
        }
    }
    if (coinDepositStage != CoinDepositStage::INIT && coinDepositStage != CoinDepositStage::SIGNATURE_SENT && coinDepositStage != CoinDepositStage::FAILED) {
        if (simTime().dbl() > coinDepositLastTry + 5) {
            coinDepositStage= CoinDepositStage::INIT;
        }
    }

    if (distanceToRSU < 150) {
        if (coinAssignmentStage == CoinAssignmentStage::INIT) {
            coinAssignmentLastTry = simTime().dbl();
            CoinRequest* msg = new CoinRequest();
            populateWSM(msg, rsuAddress);
            msg->setVid(myId);
            msg->setByteLength(COIN_REQUEST_BYTE_SIZE);
            CpuModel::Latency latencyInfo = cpuModel.getLatencyInfo(simTime().dbl(), COIN_REQUEST_LATENCY_MEAN, COIN_REQUEST_LATENCY_STDDEV);
            sendDelayedDown(msg->dup(), latencyInfo.all);
            coinAssignmentStage = CoinAssignmentStage::REQUESTED;
            EV << "[Vehicle " << myId << "]: I sent a message of CoinRequest"
                    << ". Queue time " << latencyInfo.queue_time << " Computation time " << latencyInfo.computation_time << endl;
        }
        if (coinDepositStage == CoinDepositStage::INIT) {
            coinDepositLastTry = simTime().dbl();
            CoinDeposit* msg = new CoinDeposit();
            populateWSM(msg, rsuAddress);
            msg->setVid(myId);
            msg->setByteLength(COIN_DEPOSIT_BYTE_SIZE);
            CpuModel::Latency latencyInfo = cpuModel.getLatencyInfo(simTime().dbl(), COIN_DEPOSIT_LATENCY_MEAN, COIN_DEPOSIT_LATENCY_STDDEV);
            sendDelayedDown(msg->dup(), latencyInfo.all);
            coinDepositStage = CoinDepositStage::REQUESTED;
            EV << "[Vehicle " << myId << "]: I sent a message of CoinDeposit"
                    << ". Queue time " << latencyInfo.queue_time << " Computation time " << latencyInfo.computation_time << endl;
        }
    }
    if (distanceToRSU > 150) {
        if (coinAssignmentStage != CoinAssignmentStage::INIT && coinAssignmentStage != CoinAssignmentStage::FINISHED && coinAssignmentStage != CoinAssignmentStage::FAILED) {
            coinAssignmentStage = CoinAssignmentStage::FAILED;
            EV << "[Vehicle " << myId << "]: Coin assignment failed." << endl;
        }
        if (coinDepositStage != CoinDepositStage::INIT && coinDepositStage != CoinDepositStage::SIGNATURE_SENT && coinDepositStage != CoinDepositStage::FAILED) {
            coinDepositStage = CoinDepositStage::FAILED;
            EV << "[Vehicle " << myId << "]: Coin deposit failed." << endl;
        }
    }
}

void CarApp::onWSM(BaseFrame1609_4* wsm) {
    DemoBaseApplLayer::onWSM(wsm);
    if (CoinAssignment* req = dynamic_cast<CoinAssignment*>(wsm)) {
        EV << "[Vehicle " << myId << "]: I received a message of CoinAssignment" << endl;
        coinAssignmentStage = CoinAssignmentStage::FINISHED;
    } else if (CoinDepositSignatureRequest* req = dynamic_cast<CoinDepositSignatureRequest*>(wsm)) {
        EV << "[Vehicle " << myId << "]: I received a message of CoinDepositSignatureRequest" << endl;
        CoinDepositSignatureResponse* msg = new CoinDepositSignatureResponse();
        populateWSM(msg, rsuAddress);
        msg->setVid(myId);
        msg->setByteLength(COIN_DEPOSIT_SIGNATURE_RESPONSE_BYTE_SIZE);
        CpuModel::Latency latencyInfo = cpuModel.getLatencyInfo(simTime().dbl(), COIN_DEPOSIT_SIGNATURE_RESPONSE_LATENCY_MEAN, COIN_DEPOSIT_SIGNATURE_RESPONSE_LATENCY_STDDEV);
        sendDelayedDown(msg->dup(), latencyInfo.all);
        coinDepositStage = CoinDepositStage::SIGNATURE_SENT;
        EV << "[Vehicle " << myId << "]: I sent a message of CoinDepositSignatureResponse"
                << ". Queue time " << latencyInfo.queue_time << " Computation time " << latencyInfo.computation_time << endl;
    }
}
