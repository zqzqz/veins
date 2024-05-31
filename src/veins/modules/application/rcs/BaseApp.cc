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

#include "BaseApp.h"
#include "common.h"

using namespace veins;

Define_Module(veins::BaseApp);

void BaseApp::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    int numCpuCores = par("numCpuCores");
    cpuModel.init(numCpuCores);
    HEADER_BYTE_SIZE = par("HEADER_BYTE_SIZE");
    COIN_REQUEST_BYTE_SIZE = par("COIN_REQUEST_BYTE_SIZE");
    COIN_ASSIGNMENT_BYTE_SIZE = par("COIN_ASSIGNMENT_BYTE_SIZE");
    COIN_DEPOSIT_BYTE_SIZE = par("COIN_DEPOSIT_BYTE_SIZE");
    COIN_DEPOSIT_SIGNATURE_REQUEST_BYTE_SIZE = par("COIN_DEPOSIT_SIGNATURE_REQUEST_BYTE_SIZE");
    COIN_DEPOSIT_SIGNATURE_RESPONSE_BYTE_SIZE = par("COIN_DEPOSIT_SIGNATURE_RESPONSE_BYTE_SIZE");
    COIN_SUBMISSION_BYTE_SIZE = par("COIN_SUBMISSION_BYTE_SIZE");
    COIN_REQUEST_LATENCY_MEAN = par("COIN_REQUEST_LATENCY_MEAN");
    COIN_REQUEST_LATENCY_STDDEV = par("COIN_REQUEST_LATENCY_STDDEV");
    COIN_ASSIGNMENT_LATENCY_MEAN = par("COIN_ASSIGNMENT_LATENCY_MEAN");
    COIN_ASSIGNMENT_LATENCY_STDDEV = par("COIN_ASSIGNMENT_LATENCY_STDDEV");
    COIN_DEPOSIT_LATENCY_MEAN = par("COIN_DEPOSIT_LATENCY_MEAN");
    COIN_DEPOSIT_LATENCY_STDDEV = par("COIN_DEPOSIT_LATENCY_STDDEV");
    COIN_DEPOSIT_SIGNATURE_REQUEST_LATENCY_MEAN = par("COIN_DEPOSIT_SIGNATURE_REQUEST_LATENCY_MEAN");
    COIN_DEPOSIT_SIGNATURE_REQUEST_LATENCY_STDDEV = par("COIN_DEPOSIT_SIGNATURE_REQUEST_LATENCY_STDDEV");
    COIN_DEPOSIT_SIGNATURE_RESPONSE_LATENCY_MEAN = par("COIN_DEPOSIT_SIGNATURE_RESPONSE_LATENCY_MEAN");
    COIN_DEPOSIT_SIGNATURE_RESPONSE_LATENCY_STDDEV = par("COIN_DEPOSIT_SIGNATURE_RESPONSE_LATENCY_STDDEV");
    COIN_SUBMISSION_LATENCY_MEAN = par("COIN_SUBMISSION_LATENCY_MEAN");
    COIN_SUBMISSION_LATENCY_STDDEV = par("COIN_SUBMISSION_LATENCY_STDDEV");
}

void BaseApp::handleSelfMsg(cMessage* msg) {

}

void BaseApp::handlePositionUpdate(cObject* obj) {

}

void BaseApp::onWSM(BaseFrame1609_4* wsm) {

}
