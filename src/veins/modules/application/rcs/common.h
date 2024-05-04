/*
 * common.h
 *
 *  Created on: Apr 21, 2024
 *      Author: veins
 */

#ifndef COMMON_H_
#define COMMON_H_

// Enumeration types tracking the stage of protocol.
enum class CoinAssignmentStage {
    INIT,
    REQUESTED,
    SENT,
    FINISHED,
    FAILED
};

enum class CoinDepositStage {
    INIT,
    REQUESTED,
    SIGNATURE_REQUESTED,
    SIGNATURE_SENT,
    SUBMITTED,
    FINISHED,
    FAILED
};

// Sizes of messages.
#define COIN_REQUEST_BYTE_SIZE 60
#define COIN_ASSIGNMENT_BYTE_SIZE 15000
#define COIN_DEPOSIT_BYTE_SIZE 15000
#define COIN_DEPOSIT_SIGNATURE_REQUEST_BYTE_SIZE 60
#define COIN_DEPOSIT_SIGNATURE_RESPONSE_BYTE_SIZE 60
#define COIN_SUBMISSION_BYTE_SIZE 15000

// Computation workloads.
// TODO: Should be a model involving latencies and CPU loads.

#endif
