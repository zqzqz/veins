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

#ifndef APPS_BASEAPP_H_
#define APPS_BASEAPP_H_

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "common.h"
#include "CpuModel.h"

using namespace omnetpp;

namespace veins {

class BaseApp : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;
protected:
    CpuModel cpuModel;
    int COIN_REQUEST_BYTE_SIZE;
    int COIN_ASSIGNMENT_BYTE_SIZE;
    int COIN_DEPOSIT_BYTE_SIZE;
    int COIN_DEPOSIT_SIGNATURE_REQUEST_BYTE_SIZE;
    int COIN_DEPOSIT_SIGNATURE_RESPONSE_BYTE_SIZE;
    int COIN_SUBMISSION_BYTE_SIZE;
    double COIN_REQUEST_LATENCY_MEAN;
    double COIN_REQUEST_LATENCY_STDDEV;
    double COIN_ASSIGNMENT_LATENCY_MEAN;
    double COIN_ASSIGNMENT_LATENCY_STDDEV;
    double COIN_DEPOSIT_LATENCY_MEAN;
    double COIN_DEPOSIT_LATENCY_STDDEV;
    double COIN_DEPOSIT_SIGNATURE_REQUEST_LATENCY_MEAN;
    double COIN_DEPOSIT_SIGNATURE_REQUEST_LATENCY_STDDEV;
    double COIN_DEPOSIT_SIGNATURE_RESPONSE_LATENCY_MEAN;
    double COIN_DEPOSIT_SIGNATURE_RESPONSE_LATENCY_STDDEV;
    double COIN_SUBMISSION_LATENCY_MEAN;
    double COIN_SUBMISSION_LATENCY_STDDEV;
protected:
    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
    void onWSM(BaseFrame1609_4* wsm) override;
};

} // veins namespace

#endif /* APPS_BASEAPP_H_ */
