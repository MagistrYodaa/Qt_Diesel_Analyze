//---------------------------------------------------------------------------
#include "ModBusUSB.h"
//---------------------------------------------------------------------------
//                          ?????????? ??????????
//---------------------------------------------------------------------------

//uint8_t temp_buff[256];
//int32_t temp_returnTX;
//int32_t temp_returnRX;


TUsbData  usbData;
TConfigUSBPort configUSBPort;
//---------------------------------------------------------------------------
#define WORK_INTERFACE          0x00   // ??????? ?????????

#define EP_IN_CONTROL           0x81
#define EP_OUT_CONTROL          0x02
#define EP_IN_DATA              0x83


#define READ_DATA_ADC           1  // ??????? ?????????? ?????? ??????
#define START_SAMPLE_ADC        2  // ??????? ????????? ???????????? ???
#define SET_FREQ_SAMPLE_ADC     3  // ??????? ?????????? ????????? ??????? ???????  ???.
#define SET_COUNT_SAMPLE_ADC    4  // ??????? ?????????? ????????? ???????? ???.
#define SET_ENABLE_ADC          5  // ??????? ?????????? ?????? ? ??????? ?????????? ?????? ??????? ???
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//                          ?????????? ???????
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//                ??????? ????????? ? ??????????? ????
//---------------------------------------------------------------------------
bool  OpenPort(TConfigUSBPort * AConfigUSBPort)
{
  memcpy(&configUSBPort, AConfigUSBPort, sizeof(TConfigUSBPort));

  libusb_device**						devList;
  struct libusb_device_descriptor 		desc;
  ssize_t number_dev;					//number of usb_devices

  if( (libusb_init(NULL)) < 0 )
  {
    return( false );										//libusb_init_error
  }

  number_dev = libusb_get_device_list(NULL, &devList);					//initializing OS usb library
  if ( number_dev == 0 )
  {
    return( false );								//no usb_devices
  }

  for( int i = 0; i < number_dev; i++)
  {
    if( (libusb_get_device_descriptor(devList[i],&desc)) < 0 )		//getting descriptors of all USB devices
    {
      return( false );					//can't get device descriptor
    }

    //printf("%x \n", desc.idProduct);printf("%x \n", desc.idVendor);
    if (( desc.idVendor == configUSBPort.vid ) & ( desc.idProduct == configUSBPort.pid )) //our scanners have the special PID & VID
    {
      usbData.devpnt = devList[i];    //using in opening device
      usbData.bcdDevice = desc.bcdDevice;	//????? ?????? ?????????? ? ???????-?????????? ????
      usbData.iManufacturer = desc.iManufacturer;
      usbData.iProduct = desc.iProduct;
      usbData.iSerialNumder =  desc.iSerialNumber;

      if( (libusb_open(usbData.devpnt ,&usbData.device_handle)) < 0 )	 		//open usb_device by pointer in ScannerList
      {
            return( false );				//Error opening scanner
        }

      #ifdef __linux__  // ??? Linux ?? ????????? ???????
      if( libusb_kernel_driver_active(usbData.device_handle,WORK_INTERFACE) )
      {
        if( (libusb_detach_kernel_driver(usbData.device_handle, WORK_INTERFACE)) < 0 )
        {
                return( false );		//Error detach internal usb driver
        }
      }
      #endif

      if( (libusb_claim_interface(usbData.device_handle, WORK_INTERFACE )) < 0)
      {
          return( false );	//Error claim interface
      }
      return(true);
    }
  }
  return(false);
}
//---------------------------------------------------------------------------
//                                  ???????? ?????
//---------------------------------------------------------------------------
void   ClosePort(void)
{
  if (!usbData.device_handle){return;}

  libusb_release_interface(usbData.device_handle,WORK_INTERFACE);

  #ifdef __linux__  // ??? Linux ?? ????????? ??????? ???????
    libusb_attach_kernel_driver(usbData.device_handle, WORK_INTERFACE);
  //libusb_attach_kernel_driver(scanner.device_handle, WORK_INTERFACE);
  #endif

  libusb_close(usbData.device_handle);										//closing usb_device
    libusb_exit(NULL);											//usb library exit
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//                      ??????? ???????? ?????? ModBusRTU
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//        ???????  ?????????? ????? ?????? ? ????
//---------------------------------------------------------------------------
int32_t   TransmitFrameControl(uint8_t * data_buff, uint32_t length, uint32_t waite)
{
  if (!usbData.device_handle){return(ERROO_CONNECT_PORT);}

  int32_t actual;
  int32_t unswer;
  unswer = libusb_bulk_transfer(usbData.device_handle,EP_OUT_CONTROL,data_buff,length,&actual,waite);

  if( unswer < 0 | (actual != length))
  {
    return(ERROR_TRANSMIT);
  }
  return(actual);
}
//---------------------------------------------------------------------------
//      ???????  ????????? ????? ?????? ?? ?????
//---------------------------------------------------------------------------
int32_t  ReseiveFrameControl(uint8_t * data_buff, uint32_t length, uint32_t waite)
{
  if (!usbData.device_handle){ return(ERROO_CONNECT_PORT);}

  int32_t actual;
  int32_t unswer;
  unswer= libusb_bulk_transfer(usbData.device_handle,EP_IN_CONTROL, data_buff,length,&actual,waite);

  if(unswer < 0){return(ERROR_RECEIVE);}

  return(actual);
}
//---------------------------------------------------------------------------
//      ???????  ????????? ????? ?????? ?? ?????
//---------------------------------------------------------------------------
int32_t  ReseiveFrameData(uint8_t * data_buff, uint32_t length, uint32_t waite)
{
  if (!usbData.device_handle){ return(ERROO_CONNECT_PORT);}

  int32_t actual;
  int32_t unswer;
  unswer= libusb_bulk_transfer(usbData.device_handle,EP_IN_DATA, data_buff,length,&actual,waite);

  if(unswer < 0){return(ERROR_RECEIVE);}

  return(actual);
}
//---------------------------------------------------------------------------
//        ??????? ?????????? ????????? ??????? ??????? ?????????? ???.
//---------------------------------------------------------------------------
int32_t  SetFreqSampleADC(uint8_t freq)
{
  uint8_t temp_buff[2];
  int32_t temp_returnTX;
  int32_t temp_returnRX;

  temp_buff[0]= SET_FREQ_SAMPLE_ADC;
  temp_buff[1]= freq;
  if((temp_returnTX= TransmitFrameControl(temp_buff,2,configUSBPort.timeOut)) > 0)
  {
    if((temp_returnRX= ReseiveFrameControl(temp_buff,2,configUSBPort.timeOut)) > 0)
    {
      return(temp_buff[1]);
    }
    else  { return(temp_returnRX);  }
  }
  else  { return(temp_returnTX);  }
}
//---------------------------------------------------------------------------
//                  ??????? ?????????? ????????? ???????? ???.
//---------------------------------------------------------------------------
int32_t  SetCountSampleADC(uint32_t count_adc)
{
  uint8_t temp_buff[4];
  int32_t temp_returnTX;
  int32_t temp_returnRX;

  temp_buff[0]= SET_COUNT_SAMPLE_ADC;
  temp_buff[1]= (uint8_t)( ( (count_adc) >> 16) & 0x000000FF );	// ??????? ?????
  temp_buff[2]= (uint8_t)( ( (count_adc) >> 8) & 0x000000FF );	// ??????? ?????
    temp_buff[3]= (uint8_t)( (count_adc)  & 0x000000FF );	// ??????? ?????

  if((temp_returnTX= TransmitFrameControl(temp_buff,4,configUSBPort.timeOut)) > 0)
  {
    if((temp_returnRX= ReseiveFrameControl(temp_buff,4,configUSBPort.timeOut)) > 0)
    {
      return( (temp_buff[1] <<16) | (temp_buff[2] <<8) | temp_buff[3]  );
    }
    else  { return(temp_returnRX);  }
  }
  else  { return(temp_returnTX);  }

}
//---------------------------------------------------------------------------
//      ??????? ?????????? ?????? ? ??????? ?????????? ?????? ??????? ???
//---------------------------------------------------------------------------
int32_t  SetEnableChannelADC(uint32_t enable)
{
  uint8_t temp_buff[4];
  int32_t temp_returnTX;
  int32_t temp_returnRX;

  temp_buff[0]= SET_ENABLE_ADC;
  temp_buff[1]= (uint8_t)( ( (enable) >> 16) & 0x000000FF );	// ??????? ?????
  temp_buff[2]= (uint8_t)( ( (enable) >> 8) & 0x000000FF );	// ??????? ?????
    temp_buff[3]= (uint8_t)( (enable)  & 0x000000FF );	// ??????? ?????

  if((temp_returnTX= TransmitFrameControl(temp_buff,4,configUSBPort.timeOut)) > 0)
  {
    if((temp_returnRX= ReseiveFrameControl(temp_buff,4,configUSBPort.timeOut)) > 0)
    {
      return( (temp_buff[1] <<16) | (temp_buff[2] <<8) | temp_buff[3]  );
    }
    else  { return(temp_returnRX);  }
  }
  else  { return(temp_returnTX);  }

}
//---------------------------------------------------------------------------
// ??????? ?????????? ?????? ?????? ????? ?????????? ???????  ? 65 START SAMPLE ADC
//---------------------------------------------------------------------------
int32_t  ReadDataADC(uint32_t size_reg, uint8_t num_adc, uint16_t *buff_data)
{
  uint8_t *receive_buff= new uint8_t[size_reg *2];

  //uint8_t receive_buff[2000];
  uint8_t send_buff[5];
  int32_t temp_returnTX;
  int32_t temp_returnRX;

  send_buff[0]= READ_DATA_ADC;
  send_buff[1]= num_adc;
  send_buff[2]= (uint8_t)( ( (size_reg) >> 16) & 0x000000FF );	// ??????? ?????
  send_buff[3]= (uint8_t)( ( (size_reg) >> 8) & 0x000000FF );	// ??????? ?????
    send_buff[4]= (uint8_t)( (size_reg)  & 0x000000FF );	// ??????? ?????

  if((temp_returnTX= TransmitFrameControl(send_buff,5,configUSBPort.timeOut)) > 0)
  {
    if((temp_returnRX= ReseiveFrameData(receive_buff,(size_reg*2), 5000)) > 0)
    {
      for(uint32_t i =0; i < size_reg;i++)
      {
        buff_data[i] =  ( (receive_buff[1+(i*2)] <<8) | receive_buff[(i*2)]);
      }
      return(temp_returnRX);
    }
    else  { delete [] receive_buff; return(temp_returnRX);}
  }
  else  { delete [] receive_buff; return(temp_returnTX);}
}

//---------------------------------------------------------------------------
//                    ??????? ????????? ???????????? ???
//---------------------------------------------------------------------------
int32_t  StartSampleADC(uint32_t wait)
{
  uint8_t temp_buff[1];
  int32_t temp_returnTX;
  int32_t temp_returnRX;

  temp_buff[0]= START_SAMPLE_ADC;

  if((temp_returnTX= TransmitFrameControl(temp_buff,1,configUSBPort.timeOut)) > 0)
  {
    if((temp_returnRX= ReseiveFrameControl(temp_buff,1,wait)) > 0)
    {
      return(temp_buff[0]);
    }
    else  { return(temp_returnRX);  }
  }
  else  { return(temp_returnTX);  }
}

