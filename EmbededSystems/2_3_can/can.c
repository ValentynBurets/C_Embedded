#include "can.h"

int sendDataToCan(const uint32_t id, uint8_t* data, int sizeInBytes){
	CanTxMsg message;	
	
	message.DLC = 8;
	message.ExtId = id;
	message.IDE = CAN_Id_Extended;
	message.RTR = CAN_RTR_DATA;
	message.StdId = 0x321;
	
	int res = 0;
	
	if(sizeInBytes > 8 || sizeInBytes <0){
		res = -1;
	}
	else{
		for(int i=0; i< sizeInBytes; ++i){
			message.Data[i] = *data;
		}
	
		int status = CAN_Transmit(CAN1, &message);
		if(status == CAN_TxStatus_Failed){
			res = -1;
		}
	}
	
	return res;
}

int receiveDataFromCan(const uint32_t id, uint8_t* data, int sizeInBytes){
	int status = 0;
	CanRxMsg message;
	message.IDE = CAN_Id_Extended;
	message.DLC = sizeInBytes;
	message.ExtId = id;
	message.RTR= CAN_RTR_DATA;
	message.FMI = 0;
	CAN_Receive(CAN1,1, &message);
	data = message.Data;
	return status;
}
