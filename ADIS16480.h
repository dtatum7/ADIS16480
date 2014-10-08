////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Analog Devices, Inc.
//  October 2014
//  By: Daniel H. Tatum
////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADIS16480.h
////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  This file is part of Interfacing ADIS16480 with Arduino example.
//
//  Interfacing ADIS16480 with Arduino example is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Interfacing ADIS16480 with Arduino example is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser Public License for more details.
//
//  You should have received a copy of the GNU Lesser Public License
//  along with Interfacing ADIS16480 with Arduino example.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ADIS16480_h
#define ADIS16480_h
#include "Arduino.h"
#include <SPI.h>

#define DEBUG // uncomment for DEBUG mode

// User Register Memory Map from Table 9
#define PAGE_ID 0x00 // 0x00, R/W, No, Page identifier, N/A
// Name, {PAGE_ID, Address} // Default, R/W, Flash, Register Description, Format
#define SEQ_CNT {0x00, 0x06} // N/A, R, No, Sequence counter, Table 68
#define SYS_E_FLAG {0x00, 0x08} // 0x0000, R, No, Output - system error flags, Table 59
#define DIAG_STS {0x00, 0x0A} // 0x0000, R, No, Output - self-test error flags, Table 60
#define ALM_STS {0x00, 0x0C} // 0x0000, R, No, Output - alarm error flags, Table 61
#define TEMP_OUT {0x00, 0x0E} // N/A, R, No, Output - temperature, Table 57
#define X_GYRO_LOW {0x00, 0x10} // N/A, R, No, Output - x-axis gyroscope low word, Table 14
#define X_GYRO_OUT {0x00, 0x12} // N/A, R, No, Output - x-axis gyroscope high word, Table 10
#define Y_GYRO_LOW {0x00, 0x14} // N/A, R, No, Output - y-axis gyroscope low word, Table 15
#define Y_GYRO_OUT {0x00, 0x16} // N/A, R, No, Output - y-axis gyroscope high word, Table 11
#define Z_GYRO_LOW {0x00, 0x18} // N/A, R, No, Output - z-axis gyroscope low word, Table 16
#define Z_GYRO_OUT {0x00, 0x1A} // N/A, R, No, Output - z-axis gyroscope high word, Table 12
#define X_ACCL_LOW {0x00, 0x1C} // N/A, R, No, Output - x-axis accelerometer low word, Table 21
#define X_ACCL_OUT {0x00, 0x1E} // N/A, R, No, Output - x-axis accelerometer high word, Table 17
#define Y_ACCL_LOW {0x00, 0x20} // N/A, R, No, Output - y-axis accelerometer low word, Table 22
#define Y_ACCL_OUT {0x00, 0x22} // N/A, R, No, Output - y-axis accelerometer high word, Table 18
#define Z_ACCL_LOW {0x00, 0x24} // N/A, R, No, Output - z-axis accelerometer low word, Table 23
#define Z_ACCL_OUT {0x00, 0x26} // N/A, R, No, Output - z-axis accelerometer high word, Table 19
#define X_MAGN_OUT {0x00, 0x28} // N/A, R, No, Output - x-axis magnetometer high word, Table 38
#define Y_MAGN_OUT {0x00, 0x2A} // N/A, R, No, Output - y-axis magnetometer high word, Table 39
#define Z_MAGN_OUT {0x00, 0x2C} // N/A, R, No, Output - z-axis magnetometer high word, Table 40
#define BAROM_LOW {0x00, 0x2E} // N/A, R, No, Output - barometer low word, Table 56
#define BAROM_OUT {0x00, 0x30} // N/A, R, No, Output - barometer high word, Table 54
#define X_DELTANG_LOW {0x00, 0x40} // N/A, R, No, Output - x-axis delta angle low word, Table 28
#define X_DELTANG_OUT {0x00, 0x42} // N/A, R, No, Output - x-axis delta angle high word, Table 24
#define Y_DELTANG_LOW {0x00, 0x44} // N/A, R, No, Output - y-axis delta angle low word, Table 29
#define Y_DELTANG_OUT {0x00, 0x46} // N/A, R, No, Output - y-axis delta angle high word, Table 25
#define Z_DELTANG_LOW {0x00, 0x48} // N/A, R, No, Output - z-axis delta angle low word, Table 30
#define Z_DELTANG_OUT {0x00, 0x4A} // N/A, R, No, Output - z-axis delta angle high word, Table 26
#define X_DELTVEL_LOW {0x00, 0x4C} // N/A, R, No, Output - x-axis delta velocity low word, Table 35
#define X_DELTVEL_OUT {0x00, 0x4E} // N/A, R, No, Output - x-axis delta velocity high word, Table 31
#define Y_DELTVEL_LOW {0x00, 0x50} // N/A, R, No, Output - y-axis delta velocity low word, Table 36
#define Y_DELTVEL_OUT {0x00, 0x52} // N/A, R, No, Output - y-axis delta velocity high word, Table 32
#define Z_DELTVEL_LOW {0x00, 0x54} // N/A, R, No, Output - z-axis delta velocity low word, Table 37
#define Z_DELTVEL_OUT {0x00, 0x56} // N/A, R, No, Output - z-axis delta velocity high word, Table 33
#define Q0_C11_OUT {0x00, 0x60} // N/A, R/W, Yes, Quaternion q0 or rotation matrix C11, Table 42
#define Q1_C12_OUT {0x00, 0x62} // N/A, R/W, Yes, Quaternion q1 or rotation matrix C12, Table 43
#define Q2_C13_OUT {0x00, 0x64} // N/A, R/W, Yes, Quaternion q2 or rotation matrix C13, Table 44
#define Q3_C21_OUT {0x00, 0x66} // N/A, R/W, Yes, Quaternion q3 or rotation matrix C21, Table 45
#define C22_OUT {0x00, 0x68} // N/A, R/W, Yes, Rotation matrix C22, Table 46
#define ROLL_C23_OUT {0x00, 0x6A} // N/A, R/W, Yes, Euler angle / roll axis / or rotation matrix C23, Table 47
#define PITCH_C31_OUT {0x00, 0x6C} // N/A, R/W, Yes, Euler angle / pitch axis / or rotation matrix C31, Table 48
#define YAW_C32_OUT {0x00, 0x6E} // N/A, R/W, Yes, Euler angle / yaw axis / or rotation matrix, C32, Table 49
#define C33_OUT {0x00, 0x70} // N/A, R/W, Yes, Rotation matrix C33, Table 50
#define TIME_MS_OUT {0x00, 0x78} // N/A, R, Yes, Factory configuration time: minutes/seconds, Table 156
#define TIME_DH_OUT {0x00, 0x7A} // N/A, R, Yes, Factory configuration date/time: day/hour, Table 157
#define TIME_YM_OUT {0x00, 0x7C} // N/A, R, Yes, Factory configuration date: year/month, Table 158
#define PROD_ID {0x00, 0x7E} // 0x4060, R, Yes, Output, product identification (16,480), Table 65
#define X_GYRO_SCALE {0x02, 0x04} // 0x0000, R/W, Yes, Calibration scale - x-axis gyroscope, Table 103
#define Y_GYRO_SCALE {0x02, 0x06} // 0x0000, R/W, Yes, Calibration scale - y-axis gyroscope, Table 104
#define Z_GYRO_SCALE {0x02, 0x08} // 0x0000, R/W, Yes, Calibration scale - z-axis gyroscope, Table 105
#define X_ACCL_SCALE {0x02, 0x0A} // 0x0000, R/W, Yes, Calibration scale - x-axis accelerometer, Table 113
#define Y_ACCL_SCALE {0x02, 0x0C} // 0x0000, R/W, Yes, Calibration scale - y-axis accelerometer, Table 114
#define Z_ACCL_SCALE {0x02, 0x0E} // 0x0000, R/W, Yes, Calibration scale - z-axis accelerometer, Table 115
#define XG_BIAS_LOW {0x02, 0x10} // 0x0000, R/W, Yes, Calibration offset - gyroscope x-axis low word, Table 100
#define XG_BIAS_HIGH {0x02, 0x12} // 0x0000, R/W, Yes, Calibration offset - gyroscope x-axis high word, Table 97
#define YG_BIAS_LOW {0x02, 0x14} // 0x0000, R/W, Yes, Calibration offset - gyroscope y-axis low word, Table 101
#define YG_BIAS_HIGH {0x02, 0x16} // 0x0000, R/W, Yes, Calibration offset - gyroscope y-axis high word, Table 98
#define ZG_BIAS_LOW {0x02, 0x18} // 0x0000, R/W, Yes, Calibration offset - gyroscope z-axis low word, Table 102
#define ZG_BIAS_HIGH {0x02, 0x1A} // 0x0000, R/W, Yes, Calibration offset - gyroscope z-axis high word, Table 99
#define XA_BIAS_LOW {0x02, 0x1C} // 0x0000, R/W, Yes, Calibration offset - accelerometer x-axis low word, Table 110
#define XA_BIAS_HIGH {0x02, 0x1E} // 0x0000, R/W, Yes, Calibration offset - accelerometer x-axis high word, Table 107
#define YA_BIAS_LOW {0x02, 0x20} // 0x0000, R/W, Yes, Calibration offset - accelerometer y-axis low word, Table 111
#define YA_BIAS_HIGH {0x02, 0x22} // 0x0000, R/W, Yes, Calibration offset - accelerometer y-axis high word, Table 108
#define ZA_BIAS_LOW {0x02, 0x24} // 0x0000, R/W, Yes, Calibration offset - accelerometer z-axis low word, Table 112
#define ZA_BIAS_HIGH {0x02, 0x26} // 0x0000, R/W, Yes, Calibration offset - accelerometer z-axis high word, Table 109
#define HARD_IRON_X {0x02, 0x28} // 0x0000, R/W, Yes, Calibration / hard iron - magnetometer x-axis, Table 116
#define HARD_IRON_Y {0x02, 0x2A} // 0x0000, R/W, Yes, Calibration / hard iron - magnetometer y-axis, Table 117
#define HARD_IRON_Z {0x02, 0x2C} // 0x0000, R/W, Yes, Calibration / hard iron - magnetometer z-axis, Table 118
#define SOFT_IRON_S11 {0x02, 0x2E} // 0x0000, R/W, Yes, Calibration / soft iron - magnetometer S11, Table 120
#define SOFT_IRON_S12 {0x02, 0x30} // 0x0000, R/W, Yes, Calibration / soft iron - magnetometer S12, Table 121
#define SOFT_IRON_S13 {0x02, 0x32} // 0x0000, R/W, Yes, Calibration / soft iron - magnetometer S13, Table 122
#define SOFT_IRON_S21 {0x02, 0x34} // 0x0000, R/W, Yes, Calibration / soft iron - magnetometer S21, Table 123
#define SOFT_IRON_S22 {0x02, 0x36} // 0x0000, R/W, Yes, Calibration / soft iron - magnetometer S22, Table 124
#define SOFT_IRON_S23 {0x02, 0x38} // 0x0000, R/W, Yes, Calibration / soft iron - magnetometer S23, Table 125
#define SOFT_IRON_S31 {0x02, 0x3A} // 0x0000, R/W, Yes, Calibration / soft iron - magnetometer S31, Table 126
#define SOFT_IRON_S32 {0x02, 0x3C} // 0x0000, R/W, Yes, Calibration / soft iron - magnetometer S32, Table 127
#define SOFT_IRON_S33 {0x02, 0x3E} // 0x0000, R/W, Yes, Calibration / soft iron - magnetometer S33, Table 128
#define BR_BIAS_LOW {0x02, 0x40} // 0x0000, R/W, Yes, Calibration offset -, barometer low word, Table 131
#define BR_BIAS_HIGH {0x02, 0x42} // 0x0000, R/W, Yes, Calibration offset -, barometer high word, Table 130
#define REFMTX_R11 {0x02, 0x62} // 0x7FFF, R/W, Yes, Reference transformation matrix R11, Table 84
#define REFMTX_R12 {0x02, 0x64} // 0x0000, R/W, Yes, Reference transformation matrix R12, Table 85
#define REFMTX_R13 {0x02, 0x66} // 0x0000, R/W, Yes, Reference transformation matrix R13, Table 86
#define REFMTX_R21 {0x02, 0x68} // 0x0000, R/W, Yes, Reference transformation matrix R21, Table 87
#define REFMTX_R22 {0x02, 0x6A} // 0x7FFF, R/W, Yes, Reference transformation matrix R22, Table 88
#define REFMTX_R23 {0x02, 0x6C} // 0x0000, R/W, Yes, Reference transformation matrix R23, Table 89
#define REFMTX_R31 {0x02, 0x6E} // 0x0000, R/W, Yes, Reference transformation matrix R31, Table 90
#define REFMTX_R32 {0x02, 0x70} // 0x0000, R/W, Yes, Reference transformation matrix R32, Table 91
#define REFMTX_R33 {0x02, 0x72} // 0x7FFF, R/W, Yes, Reference transformation matrix R33, Table 92
#define USER_SCR_1 {0x02, 0x74} // 0x0000, R/W, Yes, User Scratch Register 1, Table 152
#define USER_SCR_2 {0x02, 0x76} // 0x0000, R/W, Yes, User Scratch Register 2, Table 153
#define USER_SCR_3 {0x02, 0x78} // 0x0000, R/W, Yes, User Scratch Register 3, Table 154
#define USER_SCR_4 {0x02, 0x7A} // 0x0000, R/W, Yes, User Scratch Register 4, Table 155
#define FLSHCNT_LOW {0x02, 0x7C} // N/A, R, Yes, Diagnostic - flash memory count low word, Table 147
#define FLSHCNT_HIGH {0x02, 0x7E} // N/A, R, Yes, Diagnostic - flash memory count high word, Table 148
#define GLOB_CMD {0x03, 0x02} // N/A, W, No, Control - global commands, Table 146
#define FNCTIO_CTRL {0x03, 0x06} // 0x000D, R/W, Yes, Control - I/O pins functional definitions, Table 149
#define GPIO_CTRL {0x03, 0x08} // 0x00X01, R/W, Yes, Control - I/O pins general purpose, Table 150
#define CONFIG {0x03, 0x0A} // 0x00C0, R/W, Yes, Control - clock and miscellaneous correction, Table 106
#define DEC_RATE {0x03, 0x0C} // 0x0000, R/W, Yes, Control - output sample rate decimation, Table 67
#define SLP_CNT {0x03, 0x10} // N/A, R/W, No, Control - power-down/sleep mode, Table 151
#define FILTR_BNK_0 {0x03, 0x16} // 0x0000, R/W, Yes, Filter selection, Table 69
#define FILTR_BNK_1 {0x03, 0x18} // 0x0000, R/W, Yes, Filter selection, Table 70
#define ALM_CNFG_0 {0x03, 0x20} // 0x0000, R/W, Yes, Alarm configuration, Table 142
#define ALM_CNFG_1 {0x03, 0x22} // 0x0000, R/W, Yes, Alarm configuration, Table 143
#define ALM_CNFG_2 {0x03, 0x24} // 0x0000, R/W, Yes, Alarm configuration, Table 144
#define XG_ALM_MAGN {0x03, 0x28} // 0x0000, R/W, Yes, Alarm - x-axis gyroscope threshold setting, Table 132
#define YG_ALM_MAGN {0x03, 0x2A} // 0x0000, R/W, Yes, Alarm - y-axis gyroscope threshold setting, Table 133
#define ZG_ALM_MAGN {0x03, 0x2C} // 0x0000, R/W, Yes, Alarm - z-axis gyroscope threshold setting, Table 134
#define XA_ALM_MAGN {0x03, 0x2E} // 0x0000, R/W, Yes, Alarm - x-axis accelerometer threshold, Table 135
#define YA_ALM_MAGN {0x03, 0x30} // 0x0000, R/W, Yes, Alarm - y-axis accelerometer threshold, Table 136
#define ZA_ALM_MAGN {0x03, 0x32} // 0x0000, R/W, Yes, Alarm - z-axis accelerometer threshold, Table 137
#define XM_ALM_MAGN {0x03, 0x34} // 0x0000, R/W, Yes, Alarm - x-axis magnetometer threshold, Table 138
#define YM_ALM_MAGN {0x03, 0x36} // 0x0000, R/W, Yes, Alarm - y-axis magnetometer threshold, Table 139
#define ZM_ALM_MAGN {0x03, 0x38} // 0x0000, R/W, Yes, Alarm - z-axis magnetometer threshold, Table 140
#define BR_ALM_MAGN {0x03, 0x3A} // 0x0000, R/W, Yes, Alarm - barometer threshold setting, Table 141
#define EKF_CNFG {0x03, 0x50} // 0x0200, R/W, Yes, Extended Kalman filter configuration, Table 94
#define DECLN_ANGL {0x03, 0x54} // 0x0000, R/W, Yes, Declination angle, Table 93
#define ACC_DISTB_THR {0x03, 0x56} // 0x0020, R/W, Yes, Accelerometer disturbance threshold, Table 95
#define MAG_DISTB_THR {0x03, 0x58} // 0x0030, R/W, Yes, Magnetometer disturbance threshold, Table 96
#define QCVR_NOIS_LWR {0x03, 0x60} // 0xC5AC, R/W, Yes, Process covariance - gyroscope noise lower word, Table 77
#define QCVR_NOIS_UPR {0x03, 0x62} // 0x3727, R/W, Yes, Process covariance - gyroscope noise upper word, Table 76
#define QCVR_RRW_LWR {0x03, 0x64} // 0xE6FF, R/W, Yes, Process covariance - gyroscope RRW lower word, Table 79
#define QCVR_RRW_UPR {0x03, 0x66} // 0x2E5B, R/W, Yes, Process covariance - gyroscope RRW upper word, Table 78
#define RCVR_ACC_LWR {0x03, 0x6C} // 0x705F, R/W, Yes, Measurement covariance - accelerometer upper, Table 81
#define RCVR_ACC_UPR {0x03, 0x6E} // 0x3189, R/W, Yes, Measurement covariance - accelerometer lower, Table 80
#define RCVR_MAG_LWR {0x03, 0x70} // 0xCC77, R/W, Yes, Measurement covariance - magnetometer upper, Table 83
#define RCVR_MAG_UPR {0x03, 0x72} // 0x32AB, R/W, Yes, Measurement covariance - magnetometer lower, Table 82
#define FIRM_REV {0x03, 0x78} // N/A, R, Yes, Firmware revision, Table 62
#define FIRM_DM {0x03, 0x7A} // N/A, R, Yes, Firmware programming date: day/month, Table 63
#define FIRM_Y {0x03, 0x7C} // N/A, R, Yes, Firmware programming date: year, Table 64
#define SERIAL_NUM {0x04, 0x20} // N/A, R, Yes, Serial number, Table 66
#define FIR_COEF_A_LOW {0x05, 0x02} // to 0x7E N/A, R/W, Yes, FIR Filter Bank A Coefficients 0 through 59, Table 71
#define FIR_COEF_A_HIGH {0x06, 0x02} // to 0x7E N/A, R/W, Yes, FIR Filter Bank A Coefficients 60 through 119, Table 71
#define FIR_COEF_B_LOW {0x07, 0x02} // to 0x7E N/A, R/W, Yes, FIR Filter Bank B Coefficients 0 through 59, Table 72
#define FIR_COEF_B_HIGH {0x08, 0x02} // to 0x7E N/A, R/W, Yes, FIR Filter Bank B Coefficients 60 through 119, Table 72
#define FIR_COEF_C_LOW {0x09, 0x02} // to 0x7E N/A, R/W, Yes, FIR Filter Bank C Coefficients 0 through 59, Table 73
#define FIR_COEF_C_HIGH {0x0A, 0x02} // to 0x7E N/A, R/W, Yes, FIR Filter Bank C Coefficients 60 through 119, Table 73
#define FIR_COEF_D_LOW {0x0B, 0x02} // to 0x7E N/A, R/W, Yes, FIR Filter Bank D Coefficients 0 through 59, Table 74
#define FIR_COEF_D_HIGH {0x0C, 0x02} // to 0x7E N/A, R/W, Yes, FIR Filter Bank D Coefficients 60 through 119, Table 74

// ADIS16480 class definition
class ADIS16480{

public:
  // Constructor with configurable CS pin, and Destructor
  ADIS16480(int CS);
  ~ADIS16480();

private:
  // Chip select pin
  int _CS;

};
#endif
