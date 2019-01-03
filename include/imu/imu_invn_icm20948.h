/**-------------------------------------------------------------------------
@file	imu_invn_icm20948.h

@brief	Implementation of an Inertial Measurement Unit for Invensense ICM-20948

This is an implementation wrapper over Invensense SmartMotion for the ICM-20948
9 axis motion sensor

@author	Hoang Nguyen Hoan
@date	Dec. 26, 2018

@license

Copyright (c) 2018, I-SYST inc., all rights reserved

Permission to use, copy, modify, and distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright
notice and this permission notice appear in all copies, and none of the
names : I-SYST or its contributors may be used to endorse or
promote products derived from this software without specific prior written
permission.

For info or contributing contact : hnhoan at i-syst dot com

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------*/
#ifndef __IMU_INVN_ICM20948_H__
#define __IMU_INVN_ICM20948_H__

#include "device_intrf.h"
#include "imu/imu.h"

class ImuInvnIcm20948 : public Imu {
public:

	bool Init(const IMU_CFG &Cfg, uint32_t DevAddr, DeviceIntrf * const pIntrf, Timer * const pTimer = NULL);
	virtual bool Enable();
	virtual void Disable();
	virtual void Reset();
	virtual bool UpdateData();
	virtual void IntHandler();

protected:

private:
	int Read(uint8_t *pCmdAddr, int CmdAddrLen, uint8_t *pBuff, int BuffLen);
	int Write(uint8_t *pCmdAddr, int CmdAddrLen, uint8_t *pData, int DataLen);
	void UpdateData(enum inv_icm20948_sensor sensortype, uint64_t timestamp, const void * data, const void *arg);
	static void SensorEventHandler(void * context, enum inv_icm20948_sensor sensor, uint64_t timestamp, const void * data, const void *arg);
	static int InvnReadReg(void * context, uint8_t reg, uint8_t * rbuffer, uint32_t rlen);
	static int InvnWriteReg(void * context, uint8_t reg, const uint8_t * wbuffer, uint32_t wlen);


	inv_icm20948_t vIcmDevice;
	int32_t vCfgAccFsr; // Default = +/- 4g. Valid ranges: 2, 4, 8, 16
	int32_t vCfgGyroFsr; // Default = +/- 2000dps. Valid ranges: 250, 500, 1000, 2000
};



#endif // __IMU_INVN_ICM20948_H__
