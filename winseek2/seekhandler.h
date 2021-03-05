#pragma once
#include "winusb.h"

//typedef PVOID WINUSB_INTERFACE_HANDLE, * PWINUSB_INTERFACE_HANDLE;
//typedef PVOID WINUSB_ISOCH_BUFFER_HANDLE, * PWINUSB_ISOCH_BUFFER_HANDLE;
//
//typedef struct _USB_INTERFACE_DESCRIPTOR {
//    UCHAR   bLength;
//    UCHAR   bDescriptorType;
//    UCHAR   bInterfaceNumber;
//    UCHAR   bAlternateSetting;
//    UCHAR   bNumEndpoints;
//    UCHAR   bInterfaceClass;
//    UCHAR   bInterfaceSubClass;
//    UCHAR   bInterfaceProtocol;
//    UCHAR   iInterface;
//} USB_INTERFACE_DESCRIPTOR, * PUSB_INTERFACE_DESCRIPTOR;
//
//typedef struct _WINUSB_SETUP_PACKET {
//    UCHAR   RequestType;
//    UCHAR   Request;
//    USHORT  Value;
//    USHORT  Index;
//    USHORT  Length;
//} WINUSB_SETUP_PACKET, * PWINUSB_SETUP_PACKET;
//
//typedef enum _USBD_PIPE_TYPE {
//    UsbdPipeTypeControl,
//    UsbdPipeTypeIsochronous,
//    UsbdPipeTypeBulk,
//    UsbdPipeTypeInterrupt
//} USBD_PIPE_TYPE;
//
//typedef struct _WINUSB_PIPE_INFORMATION {
//    USBD_PIPE_TYPE  PipeType;
//    UCHAR           PipeId;
//    USHORT          MaximumPacketSize;
//    UCHAR           Interval;
//} WINUSB_PIPE_INFORMATION, * PWINUSB_PIPE_INFORMATION;
//
//typedef struct _WINUSB_PIPE_INFORMATION_EX {
//    USBD_PIPE_TYPE PipeType;
//    UCHAR          PipeId;
//    USHORT         MaximumPacketSize;
//    UCHAR          Interval;
//    ULONG          MaximumBytesPerInterval;
//} WINUSB_PIPE_INFORMATION_EX, * PWINUSB_PIPE_INFORMATION_EX;
//
//typedef LONG USBD_STATUS;
//
//typedef struct _USBD_ISO_PACKET_DESCRIPTOR {
//    ULONG Offset;
//    ULONG Length;
//    USBD_STATUS Status;
//} USBD_ISO_PACKET_DESCRIPTOR, * PUSBD_ISO_PACKET_DESCRIPTOR;

std::string arConvert(byte* inArr, int length);

struct pColor {
	int r, g, b;
};

struct palette {
	pColor palette[1000];
};

const DWORD paletteLookup[] = { 0x00000001, 0x00010101, 0x00020202, 0x00020304, 0x00040404, 0x00040505, 0x00060606, 0x00070707, 0x00080808, 0x0009090A, 0x000A0B0A, 0x000B0B0C, 0x000C0C0C, 0x000D0E0D, 0x000E0E0E, 0x000F0F0F, 0x00110F11, 0x00101211, 0x00121112, 0x00121413, 0x00141414, 0x00151514, 0x00171516, 0x00171717, 0x00181818, 0x0019191A, 0x001A1A1A, 0x001A1B1A, 0x001C1C1C, 0x001D1D1C, 0x001E1E1E, 0x00201F1F, 0x00202020, 0x00212121, 0x00222222, 0x00232323, 0x00242424, 0x00252525, 0x00262726, 0x00272827, 0x00282828, 0x00282929, 0x002A2A2A, 0x002C2B2B, 0x002C2C2C, 0x002D2D2E, 0x002E2E2D, 0x002F2E30, 0x00303130, 0x00313131, 0x00333232, 0x00333333, 0x00343534, 0x00353535, 0x00363636, 0x00373737, 0x00383838, 0x0039383A, 0x003A3A3A, 0x003B3B3B, 0x003C3C3D, 0x003E3D3C, 0x003F3E3E, 0x003F403F, 0x00404040, 0x00414141, 0x00424243, 0x00434343, 0x00444443, 0x00454546, 0x00464646, 0x00484648, 0x00484848, 0x0049494A, 0x004A4B4A, 0x004A4B4B, 0x004C4B4D, 0x004D4D4E, 0x004E4E4E, 0x004F504F, 0x00505050, 0x00515151, 0x00525252, 0x00535353, 0x00545355, 0x00545655, 0x00575655, 0x00575757, 0x00585858, 0x005A5959, 0x00595B5A, 0x005B5B5C, 0x005C5D5C, 0x005D5D5D, 0x005E5E5E, 0x00605F5F, 0x00616060, 0x00616061, 0x00626262, 0x00626462, 0x00646464, 0x00666565, 0x00656765, 0x00686768, 0x00696868, 0x00696969, 0x006A6B6A, 0x006B6C6B, 0x006C6C6C, 0x006E6D6D, 0x006E6E6F, 0x00706E6F, 0x0070716F, 0x00727170, 0x00727173, 0x00737373, 0x00747474, 0x00757675, 0x00777677, 0x00777877, 0x00787878, 0x00797979, 0x00797B7A, 0x007B7B7C, 0x007B7D7C, 0x007D7D7E, 0x007E7E7E, 0x007F7F7F, 0x00808080, 0x00818181, 0x00838282, 0x00848283, 0x00848585, 0x00868585, 0x00868686, 0x00878787, 0x00888889, 0x00898989, 0x008B898B, 0x008B8B8B, 0x008C8C8C, 0x008D8D8D, 0x008D8E8E, 0x008F9090, 0x00909090, 0x00929191, 0x00929392, 0x00939493, 0x00949494, 0x00959595, 0x00979696, 0x00979797, 0x00989898, 0x00999999, 0x009A999B, 0x009B9B9B, 0x009D9C9C, 0x009E9D9D, 0x009E9F9E, 0x009FA09F, 0x00A0A1A0, 0x00A2A1A2, 0x00A3A2A1, 0x00A3A3A3, 0x00A5A4A4, 0x00A5A5A5, 0x00A6A6A6, 0x00A8A7A7, 0x00A8A9A8, 0x00A9AAA9, 0x00AAAAAB, 0x00ACABAB, 0x00ADACAD, 0x00ADAEAD, 0x00AEAFAE, 0x00AFAEB0, 0x00B0B0B0, 0x00B1B1B1, 0x00B2B3B2, 0x00B3B3B3, 0x00B4B4B4, 0x00B5B5B5, 0x00B6B7B6, 0x00B8B7B7, 0x00B9B9B8, 0x00B9B9BA, 0x00BABABA, 0x00BCBBBB, 0x00BCBCBD, 0x00BDBEBD, 0x00BFBDBF, 0x00C0BFBF, 0x00C0C0C0, 0x00C1C1C1, 0x00C3C2C3, 0x00C4C2C3, 0x00C5C4C4, 0x00C5C4C6, 0x00C6C6C7, 0x00C7C8C7, 0x00C8C9C8, 0x00C9CAC9, 0x00CACACA, 0x00CBCBCB, 0x00CBCDCC, 0x00CDCDCD, 0x00CECECE, 0x00D0CFCF, 0x00D0D1D1, 0x00D1D2D1, 0x00D2D3D1, 0x00D3D3D3, 0x00D5D4D5, 0x00D6D5D6, 0x00D6D6D6, 0x00D7D7D7, 0x00D9D8D8, 0x00DAD9DA, 0x00DADBDA, 0x00DADBDC, 0x00DCDCDC, 0x00DEDDDD, 0x00DEDEDF, 0x00DFDFDF, 0x00E0E0E0, 0x00E1E2E1, 0x00E2E3E2, 0x00E3E4E3, 0x00E5E4E5, 0x00E5E5E5, 0x00E6E6E7, 0x00E7E7E7, 0x00E8E9E9, 0x00E9E9E9, 0x00EAEBEA, 0x00ECEAEC, 0x00EDECED, 0x00EDEDEE, 0x00EEEFEF, 0x00EFEFF0, 0x00F0F1F1, 0x00F2F1F1, 0x00F3F1F2, 0x00F3F3F4, 0x00F3F5F4, 0x00F5F5F6, 0x00F6F6F6, 0x00F8F7F7, 0x00F8F8F8, 0x00F9FAF9, 0x00FAFBFB, 0x00FBFBFB, 0x00FCFDFC, 0x00FEFDFE, 0x00FEFFFE, 0x00FFFFFF, 0x00FEFEFF, 0x00FDFDFD, 0x00FCFCFC, 0x00FBFBFB, 0x00FAFAFA, 0x00F9FAF8, 0x00F8F8F7, 0x00F7F7F7, 0x00F5F6F7, 0x00F5F5F5, 0x00F4F4F4, 0x00F4F3F3, 0x00F2F1F2, 0x00F1F1F1, 0x00EFF1F0, 0x00EFF0EF, 0x00EEEEED, 0x00EDEDEC, 0x00EBECED, 0x00EAECEB, 0x00EAE9EA, 0x00E9E9E9, 0x00E8E8E7, 0x00E7E7E7, 0x00E6E6E6, 0x00E5E5E5, 0x00E5E4E4, 0x00E4E3E3, 0x00E2E2E2, 0x00E1E1E2, 0x00E0E0E1, 0x00DFDFDF, 0x00DEDEDE, 0x00DDDEDD, 0x00DCDBDC, 0x00DBDBDB, 0x00DADBD9, 0x00D8D9D9, 0x00D8D8D8, 0x00D8D6D7, 0x00D6D7D6, 0x00D5D5D5, 0x00D4D4D4, 0x00D4D3D3, 0x00D2D2D2, 0x00D1D1D1, 0x00D0D0D0, 0x00CECFCF, 0x00CECECE, 0x00CECCCD, 0x00CCCCCC, 0x00CACBCB, 0x00CACACA, 0x00C9CAC9, 0x00C8C8C9, 0x00C7C7C7, 0x00C6C5C7, 0x00C5C5C6, 0x00C4C4C4, 0x00C3C3C3, 0x00C2C2C2, 0x00C1C1C1, 0x00C1BFC0, 0x00BFBEBF, 0x00BEBEBD, 0x00BEBCBD, 0x00BBBCBC, 0x00BBBCBB, 0x00BBBABA, 0x00BAB9B9, 0x00B8B8B8, 0x00B7B7B7, 0x00B6B6B7, 0x00B4B5B5, 0x00B4B4B4, 0x00B3B3B2, 0x00B1B2B2, 0x00B1B1B1, 0x00AFB0AF, 0x00AFAEAF, 0x00AFAEAE, 0x00AEADAD, 0x00ACACAC, 0x00ABAAAB, 0x00AAAAAA, 0x00AAA8AA, 0x00A8A8A8, 0x00A6A7A7, 0x00A6A7A5, 0x00A4A6A5, 0x00A4A4A4, 0x00A3A2A3, 0x00A2A1A3, 0x00A1A1A1, 0x00A0A0A0, 0x00A09F9F, 0x009E9D9E, 0x009D9C9E, 0x009C9D9C, 0x009C9B9B, 0x009B999A, 0x00989999, 0x00989897, 0x00969797, 0x00959696, 0x00959595, 0x00939494, 0x00939394, 0x00939292, 0x00919191, 0x00909090, 0x00908E8F, 0x008E8E8E, 0x008D8C8E, 0x008C8C8C, 0x008A8B8B, 0x00898A8A, 0x00888988, 0x00888789, 0x00878787, 0x00868686, 0x00868585, 0x00858484, 0x00838284, 0x00828281, 0x00808181, 0x007F8180, 0x007F7F7F, 0x007E7E7E, 0x007D7C7D, 0x007B7C7C, 0x007B7B7A, 0x007A7A7A, 0x00797878, 0x00787878, 0x00777776, 0x00767576, 0x00757575, 0x00747474, 0x00737373, 0x00727272, 0x00707271, 0x006F706F, 0x006F706F, 0x006E6E6D, 0x006C6D6C, 0x006C6C6B, 0x006B6B6B, 0x006A6A6A, 0x00696A68, 0x00686868, 0x00666767, 0x00666665, 0x00646565, 0x00646464, 0x00636363, 0x00626261, 0x00616160, 0x00606060, 0x005F5E5F, 0x005E5E5E, 0x005D5D5D, 0x005C5C5C, 0x005B5B5B, 0x005A5A5A, 0x00595959, 0x00585758, 0x00575757, 0x00555655, 0x00555555, 0x00535553, 0x00535353, 0x00525151, 0x00505151, 0x00505051, 0x004E504E, 0x004E4D4E, 0x004E4D4D, 0x004C4B4C, 0x004B4B4B, 0x004B4A4A, 0x00494949, 0x00484848, 0x00484647, 0x00464645, 0x00454544, 0x00434445, 0x00434342, 0x00424242, 0x00424141, 0x0040403F, 0x003E403F, 0x003F3E3E, 0x003D3D3D, 0x003C3D3C, 0x003B3A3B, 0x00393A3A, 0x00393839, 0x00393738, 0x00363737, 0x00363635, 0x00353635, 0x00343534, 0x00333333, 0x00323132, 0x00313130, 0x002F3030, 0x002F2F2F, 0x002E2E2D, 0x002D2D2D, 0x002C2C2B, 0x002A2B2A, 0x002A2A2A, 0x00282928, 0x00282828, 0x00272726, 0x00262627, 0x00252525, 0x00242423, 0x00232323, 0x00222122, 0x00212121, 0x00202020, 0x001E1F1F, 0x001D1E1E, 0x001C1C1D, 0x001B1B1C, 0x001B1B1A, 0x00191A1A, 0x00191A19, 0x00181817, 0x00171716, 0x00151517, 0x00151415, 0x00141414, 0x00131313, 0x00111212, 0x00111110, 0x00100F10, 0x000F0F0F, 0x000E0D0E, 0x000D0D0D, 0x000C0C0C, 0x000B0A0B, 0x000A0A0A, 0x00090809, 0x00070807, 0x00060707, 0x00050606, 0x00050505, 0x00040404, 0x00040203, 0x00010202, 0x00010101, 0x00FFFEFF, 0x00FFFDFE, 0x00FDFEFD, 0x00FCFBFD, 0x00FBFBFC, 0x00FAFAFA, 0x00F9F9F8, 0x00F8F8F8, 0x00F7F7F7, 0x00F6F6F7, 0x00F4F5F6, 0x00F4F4F4, 0x00F4F3F3, 0x00F2F1F2, 0x00F1F1F2, 0x00F0F0EF, 0x00F0EFEF, 0x00EDEEEE, 0x00EDEEEC, 0x00EDEBED, 0x00EBEBEB, 0x00FFF17D, 0x00FFF173, 0x00FFF06D, 0x00FFEF66, 0x00FFEF60, 0x00FFEE59, 0x00FFED54, 0x00FFEB4E, 0x00FFEA48, 0x00FFE942, 0x00FFE73D, 0x00FFE635, 0x00FFE531, 0x00FFE42A, 0x00FFE326, 0x00FFE123, 0x00FFE01F, 0x00FFDE1B, 0x00FFDD16, 0x00FFDC13, 0x00FFDB11, 0x00FFDA0F, 0x00FED80C, 0x00FED70B, 0x00FED50A, 0x00FED308, 0x00FED106, 0x00FECF04, 0x00FECE03, 0x00FECC02, 0x00FECB01, 0x00FECA01, 0x00FEC800, 0x00FEC700, 0x00FEC600, 0x00FEC300, 0x00FEC100, 0x00FEBF00, 0x00FEBD00, 0x00FEBC00, 0x00FEBA00, 0x00FEB900, 0x00FEB700, 0x00FEB400, 0x00FEB200, 0x00FEB100, 0x00FEAF00, 0x00FDAE00, 0x00FDAC00, 0x00FDAA00, 0x00FDA800, 0x00FDA700, 0x00FDA300, 0x00FDA100, 0x00FC9F00, 0x00FC9D00, 0x00FB9B00, 0x00FB9800, 0x00FA9600, 0x00FA9400, 0x00F99200, 0x00F99000, 0x00F98F00, 0x00F98E00, 0x00F88C00, 0x00F88B00, 0x00F88900, 0x00F88800, 0x00F88700, 0x00F78500, 0x00F78300, 0x00F68200, 0x00F68000, 0x00F57E00, 0x00F57C00, 0x00F47A00, 0x00F47700, 0x00F47500, 0x00F47400, 0x00F37201, 0x00F37101, 0x00F26F01, 0x00F26D01, 0x00F16C01, 0x00F16A02, 0x00F16902, 0x00F16703, 0x00F16603, 0x00F06503, 0x00F06303, 0x00EF6104, 0x00EF5F04, 0x00EE5E05, 0x00EE5C05, 0x00ED5B06, 0x00ED5A07, 0x00EC5808, 0x00EC5608, 0x00EB5409, 0x00EB520A, 0x00EB510B, 0x00EA4E0C, 0x00E94D0D, 0x00E84C0F, 0x00E84B11, 0x00E74913, 0x00E64715, 0x00E64518, 0x00E5431A, 0x00E4411D, 0x00E43F21, 0x00E33E25, 0x00E23C2B, 0x00E13931, 0x00E03836, 0x00E0373B, 0x00DF3541, 0x00DE3347, 0x00DD314D, 0x00DC3052, 0x00DB2F57, 0x00DA2D5D, 0x00D92A5F, 0x00D82862, 0x00D72665, 0x00D62368, 0x00D5226D, 0x00D42170, 0x00D31F72, 0x00D21D73, 0x00D11B77, 0x00D01A79, 0x00CF197C, 0x00CE177F, 0x00CD1681, 0x00CB1483, 0x00CA1385, 0x00C91286, 0x00C80F88, 0x00C70E8A, 0x00C50D8C, 0x00C40C8D, 0x00C30B8E, 0x00C2098F, 0x00C10890, 0x00C00791, 0x00BF0692, 0x00BE0592, 0x00BC0593, 0x00BB0594, 0x00B90495, 0x00B80395, 0x00B70295, 0x00B50296, 0x00B30197, 0x00B10197, 0x00B00198, 0x00AE0198, 0x00AC0099, 0x00AB0099, 0x00A9009A, 0x00A7009A, 0x00A3009B, 0x00A2009B, 0x00A0009B, 0x009D009B, 0x009B009B, 0x0099009B, 0x0096009B, 0x0093009C, 0x0090009C, 0x008D009D, 0x008A009D, 0x0088009D, 0x0085009D, 0x0082009D, 0x0080009D, 0x007D009D, 0x007A009D, 0x0077009D, 0x0072009D, 0x0071009D, 0x006F009C, 0x006C009C, 0x0069009B, 0x0066009B, 0x0063009B, 0x005F009B, 0x005D009A, 0x005A0099, 0x00570098, 0x00520098, 0x00500097, 0x004D0097, 0x004B0096, 0x00480096, 0x00450096, 0x00420095, 0x00400094, 0x003E0092, 0x003A0091, 0x00380090, 0x0035008E, 0x0032008D, 0x002F008B, 0x002A008A, 0x00270088, 0x00240087, 0x00210085, 0x001E0082, 0x001B0080, 0x0018007E, 0x0013007B, 0x00110079, 0x000F0077, 0x000D0076, 0x000B0073, 0x000A006F, 0x0008006B, 0x00060068, 0x00050065, 0x00040061, 0x0003005D, 0x00020059, 0x00010054, 0x0000004F, 0x00000048, 0x00000042, 0x0000003A, 0x00000033, 0x0000002D, 0x00000024, 0x00000014, 0x00000004, 0x00FFF4F7, 0x00FFF1F8, 0x00FFE9EC, 0x00FFDEE1, 0x00FFDCD8, 0x00FFD6D5, 0x00FFCECE, 0x00FFC5C5, 0x00FFBEBD, 0x00FFB6B5, 0x00FFADAC, 0x00FFA5A4, 0x00FF9E9D, 0x00FF9190, 0x00FF8A89, 0x00FF8282, 0x00FF7B79, 0x00FF7371, 0x00FF6A68, 0x00FF615E, 0x00FF5956, 0x00FF524E, 0x00FF4A45, 0x00FF413E, 0x00FF3835, 0x00FF312D, 0x00FF2A25, 0x00FF241F, 0x00FF1C17, 0x00FF150F, 0x00FF0C07, 0x00FF0300, 0x00FF0000, 0x00FF0600, 0x00FF0B00, 0x00FF1100, 0x00FF1700, 0x00FF1C00, 0x00FF2100, 0x00FF2600, 0x00FF2B00, 0x00FF2E00, 0x00FF3300, 0x00FF3800, 0x00FF3D00, 0x00FF4200, 0x00FF4700, 0x00FF4C00, 0x00FF5100, 0x00FF5600, 0x00FF5B00, 0x00FF6100, 0x00FF6600, 0x00FF6C00, 0x00FF6F00, 0x00FF7400, 0x00FF7900, 0x00FF7F00, 0x00FF8300, 0x00FF8900, 0x00FF8D00, 0x00FF9200, 0x00FF9700, 0x00FF9C00, 0x00FFA100, 0x00FFA700, 0x00FFAC00, 0x00FFB100, 0x00FFB400, 0x00FFB700, 0x00FFB900, 0x00FFBA00, 0x00FFBD00, 0x00FFC000, 0x00FFC200, 0x00FFC300, 0x00FFC600, 0x00FFC900, 0x00FFCB00, 0x00FFCC00, 0x00FFCD00, 0x00FFCF00, 0x00FFD100, 0x00FFD300, 0x00FFD600, 0x00FFD900, 0x00FFDB00, 0x00FFDD00, 0x00FFDF00, 0x00FFE100, 0x00FFE400, 0x00FFE600, 0x00FFE800, 0x00FFEA00, 0x00FFEC00, 0x00FFEF00, 0x00FFF000, 0x00FFF200, 0x00FFF400, 0x00FFF600, 0x00FFF900, 0x00FFFC00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FCFF00, 0x00F9FF00, 0x00F5FF00, 0x00F0FF00, 0x00ECFF00, 0x00E8FF00, 0x00E4FF00, 0x00E1FF00, 0x00DFFF00, 0x00DAFF00, 0x00D7FF00, 0x00D3FF00, 0x00CFFF00, 0x00CBFD00, 0x00C7FC00, 0x00C4FB00, 0x00C0FA00, 0x00BCF900, 0x00B8F800, 0x00B4F800, 0x00B0F600, 0x00ACF500, 0x00A8F500, 0x00A5F400, 0x00A1F300, 0x009CF200, 0x0099F100, 0x0096F000, 0x0092EF00, 0x008EEE00, 0x008AEE04, 0x0088EE08, 0x0084EE0D, 0x0081EE12, 0x007DEE17, 0x007AEE1B, 0x0077EE20, 0x0073EE26, 0x0070EE2B, 0x006CEE2F, 0x0069EE34, 0x0066EE39, 0x0062EE3E, 0x005FEE43, 0x005CEE48, 0x0059EE4D, 0x0055EE52, 0x0051EE56, 0x004EEE5B, 0x004CEE5E, 0x0049EE63, 0x0046EE68, 0x0042EE6D, 0x003DEE72, 0x003AEE78, 0x0037EE7C, 0x0034EE81, 0x0030EE86, 0x002DEE8B, 0x0029EE90, 0x0026EE95, 0x0023EE9A, 0x0021EE9E, 0x001DEEA3, 0x001AEEA7, 0x0017EEAC, 0x0013EEB1, 0x0010EEB5, 0x000CEEBC, 0x0008EEC1, 0x0005EEC6, 0x0001EECA, 0x0000EDCF, 0x0000E9D0, 0x0000E5D0, 0x0000E2D1, 0x0000DED2, 0x0000DBD2, 0x0000D7D3, 0x0000D2D4, 0x0000CED4, 0x0000CBD5, 0x0000C7D6, 0x0000C3D6, 0x0000BFD7, 0x0000BBD8, 0x0000B6D8, 0x0000B2D9, 0x0000AEDA, 0x0000ABDA, 0x0000A7DA, 0x0000A3DC, 0x00009FDC, 0x00009BDC, 0x000098DE, 0x000095DE, 0x000090DE, 0x00008CDF, 0x000089E0, 0x000085E0, 0x000081E1, 0x00007CE1, 0x000079E2, 0x000075E4, 0x000072DE, 0x00006FD8, 0x00006CD2, 0x000068CC, 0x000065C6, 0x000062BF, 0x00005FBA, 0x00005CB4, 0x000058AE, 0x000055A8, 0x000052A2, 0x0000509C, 0x00004D97, 0x00004A90, 0x00004689, 0x00004283, 0x0000407E, 0x00003D77, 0x00003971, 0x0000376B, 0x00003365, 0x00002F5F, 0x00002D59, 0x00002A53, 0x0000274C, 0x00002448, 0x00002142, 0x00001D3C, 0x00001A36, 0x0000182F, 0x00001429, 0x00001022, 0x00000D1C, 0x00000A16, 0x00000710, 0x0000050A, 0x00000104, 0x00000000, 0x0012FF01, 0x0012FF02, 0x0011FF04, 0x0012FF06, 0x0012FF09, 0x0011FF0B, 0x0011FF0D, 0x0010FF10, 0x0010FF13, 0x0010FF16, 0x000FFF19, 0x0010FF1C, 0x000FFF20, 0x000EFF23, 0x000EFF25, 0x000FFF28, 0x000EFF2D, 0x000DFF30, 0x000DFF33, 0x000CFF37, 0x000CFF3B, 0x000CFF3F, 0x000CFF43, 0x000BFF47, 0x000BFF4B, 0x000AFF4F, 0x000AFF53, 0x0009FF56, 0x000AFF5B, 0x0009FF5E, 0x0009FF63, 0x0008FF67, 0x0008FF6B, 0x0007FF6F, 0x0007FF74, 0x0006FF78, 0x0006FF7D, 0x0006FF81, 0x0005FF85, 0x0005FF89, 0x0005FF8D, 0x0005FF90, 0x0004FF94, 0x0003FF98, 0x0003FF9C, 0x0003FFA0, 0x0003FFA4, 0x0002FFA7, 0x0002FFAB, 0x0002FFAF, 0x0002FFB3, 0x0001FFB6, 0x0001FFBA, 0x0001FFBD, 0x0001FFBF, 0x0001FFC2, 0x0000FFC5, 0x0001FFC8, 0x0000FFCC, 0x0000FFCD, 0x0000FFD1, 0x0000FFD3, 0x0000FFD5, 0x0000FFD7, 0x0000FED9, 0x0000FBDC, 0x0000F9DD, 0x0000F6DF, 0x0000F4E0, 0x0000F1E1, 0x0000EEE3, 0x0000EBE5, 0x0000E8E7, 0x0000E4E8, 0x0000E0E9, 0x0000DDEB, 0x0000D9EC, 0x0000D5ED, 0x0000D1EE, 0x0000CDEF, 0x0000C8F1, 0x0000C5F1, 0x0000C1F3, 0x0000BBF3, 0x0000B7F4, 0x0000B2F4, 0x0000ADF5, 0x0000A8F6, 0x0000A3F6, 0x00009FF8, 0x00009AF8, 0x000094F9, 0x000090F9, 0x00008AFA, 0x000087FA, 0x000081FA, 0x00007DFB, 0x000077FC, 0x000072FB, 0x00006EFC, 0x000069FC, 0x000063FD, 0x00005FFC, 0x000059FD, 0x000055FD, 0x000050FD, 0x00004AFE, 0x000047FE, 0x000043FE, 0x00003EFE, 0x00003AFE, 0x000036FE, 0x000031FE, 0x00002DFE, 0x000029FE, 0x000025FF, 0x000221FF, 0x00021EFE, 0x00031AFE, 0x000516FF, 0x000613FE, 0x000811FE, 0x00090DFF, 0x000A0BFE, 0x000C08FF, 0x000E05FF, 0x000F02FF, 0x001200FF, 0x001300FF, 0x001500FF, 0x001800FF, 0x001A00FF, 0x001D00FF, 0x002000FF, 0x002400FF, 0x002600FF, 0x002900FF, 0x002C00FF, 0x003000FF, 0x003300FF, 0x003700FF, 0x003B00FF, 0x003F00FF, 0x004200FF, 0x004700FF, 0x004B00FF, 0x004F00FF, 0x005400FF, 0x005700FF, 0x005B00FF, 0x006000FF, 0x006400FF, 0x006900FF, 0x006D00FF, 0x007200FF, 0x007700FF, 0x007B00FF, 0x008000FF, 0x008500FF, 0x008900FF, 0x008E00FF, 0x009300FF, 0x009600FF, 0x009A00FF, 0x009F00FF, 0x00A400FF, 0x00A900FF, 0x00AD00FF, 0x00B200FF, 0x00B600FF, 0x00BA00FE, 0x00BF00FE, 0x00C300FD, 0x00C700FC, 0x00CB00FB, 0x00CE00FA, 0x00D200FA, 0x00D600F8, 0x00DA00F7, 0x00DE00F6, 0x00E100F6, 0x00E400F4, 0x00E800F3, 0x00EB00F1, 0x00EE00F0, 0x00F100EF, 0x00F400ED, 0x00F700EC, 0x00F800EA, 0x00FB00E8, 0x00FC00E6, 0x00FF00E4, 0x00FF00E2, 0x00FF00E0, 0x00FF00DD, 0x00FF00DB, 0x00FF00D8, 0x00FF00D5, 0x00FF00D3, 0x00FF00CF, 0x00FF00CC, 0x00FF00CA, 0x00FF00C7, 0x00FF00C3, 0x00FF00C0, 0x00FF00BC, 0x00FF00B7, 0x00FF00B4, 0x00FF00B0, 0x00FF00AC, 0x00FF00A8, 0x00FF00A3, 0x00FF00A0, 0x00FF009B, 0x00FF0097, 0x00FF0094, 0x00FF008F, 0x00FF008B, 0x00FF0087, 0x00FF0082, 0x00FF007D, 0x00FF0079, 0x00FF0075, 0x00FF0070, 0x00FF006C, 0x00FF0067, 0x00FF0062, 0x00FF005F, 0x00FF005A, 0x00FF0056, 0x00FF0052, 0x00FF004E, 0x00FF004A, 0x00FF0045, 0x00FF0041, 0x00FF003D, 0x00FF0038, 0x00FF0035, 0x00FF0031, 0x00FF002D, 0x00FF002A, 0x00FF0025, 0x00FF0023, 0x00FF001F, 0x00FF001C, 0x00FF0019, 0x00FF0016, 0x00FF0013, 0x00FF000F, 0x00FF000D, 0x00FF000B, 0x00FF0008, 0x00FF0005, 0x00FF0003, 0x00FF0002, 0x00EE2024, 0x00ED2024, 0x00ED2124, 0x00EE2224, 0x00EE2324, 0x00EE2324, 0x00EE2323, 0x00EE2424, 0x00EE2524, 0x00EF2623, 0x00EF2723, 0x00EF2823, 0x00EF2823, 0x00EF2923, 0x00F02A23, 0x00EF2A23, 0x00F02B23, 0x00F02C22, 0x00F02D22, 0x00F02F22, 0x00F02F22, 0x00F13021, 0x00F23121, 0x00F13221, 0x00F23321, 0x00F23420, 0x00F33621, 0x00F33621, 0x00F33720, 0x00F43820, 0x00F33A20, 0x00F43A20, 0x00F43B20, 0x00F53D1F, 0x00F53E1E, 0x00F63F1E, 0x00F6411F, 0x00F6411E, 0x00F7431E, 0x00F7441D, 0x00F8451E, 0x00F7461D, 0x00F8471D, 0x00F9481D, 0x00F84A1C, 0x00F94B1D, 0x00FA4C1C, 0x00FA4D1C, 0x00FB4F1C, 0x00FB501B, 0x00FB511B, 0x00FA531A, 0x00FA541A, 0x00FA561A, 0x00FA571A, 0x00FA581A, 0x00FA591A, 0x00FA5A1A, 0x00FB5C1A, 0x00FA5D19, 0x00FA5F1A, 0x00FA5F19, 0x00FA611A, 0x00FB6219, 0x00FA6419, 0x00FB651A, 0x00FB661A, 0x00FA6719, 0x00FB691A, 0x00FA6A1A, 0x00FA6C19, 0x00FB6D19, 0x00FB6E1A, 0x00FB6F1A, 0x00FA7119, 0x00FA7219, 0x00FB741A, 0x00FB741A, 0x00FA7619, 0x00FA781A, 0x00FB7919, 0x00FA791A, 0x00FB7B19, 0x00FA7C1A, 0x00FA7E1A, 0x00FA7F19, 0x00FB801A, 0x00FA8119, 0x00FA821A, 0x00FA8419, 0x00FA8519, 0x00FA861A, 0x00FA871A, 0x00FA8819, 0x00FB8919, 0x00FA8B19, 0x00FA8C19, 0x00FA8D1A, 0x00FA8E19, 0x00FA8F19, 0x00FB901A, 0x00FB9119, 0x00FA931A, 0x00FA941A, 0x00FB951A, 0x00FA951A, 0x00FB971A, 0x00FB9819, 0x00FB991A, 0x00FA9A1A, 0x00FA9A19, 0x00FA9B1A, 0x00FA9C1A, 0x00FB9E1A, 0x00FB9E1A, 0x00FA9F19, 0x00FAA019, 0x00FBA11A, 0x00FAA21A, 0x00FAA319, 0x00FBA31A, 0x00FAA41A, 0x00FBA41A, 0x00FAA519, 0x00FBA61A, 0x00FAA71A, 0x00FBA819, 0x00FAA81A, 0x00FAA81A, 0x00F9A91B, 0x00F8AA1B, 0x00F7AA1C, 0x00F6AB1C, 0x00F5AB1D, 0x00F4AC1E, 0x00F4AC1E, 0x00F3AD1E, 0x00F2AD1F, 0x00F0AE1F, 0x00EFAE20, 0x00EEAF21, 0x00EDAF21, 0x00ECB023, 0x00EBAF23, 0x00EAB124, 0x00E9B024, 0x00E6B125, 0x00E6B126, 0x00E4B227, 0x00E3B227, 0x00E2B229, 0x00E0B329, 0x00DFB22A, 0x00DDB32B, 0x00DCB32C, 0x00DBB42C, 0x00D9B42E, 0x00D7B42F, 0x00D7B530, 0x00D5B531, 0x00D3B531, 0x00D1B632, 0x00D1B533, 0x00CFB534, 0x00CDB635, 0x00CBB636, 0x00C9B637, 0x00C8B638, 0x00C7B739, 0x00C4B73A, 0x00C3B73B, 0x00C1B73C, 0x00C0B73E, 0x00BEB83F, 0x00BCB83F, 0x00BAB841, 0x00B8B842, 0x00B7B842, 0x00B5B843, 0x00B3B944, 0x00B2B946, 0x00B0B847, 0x00AEB948, 0x00ACB849, 0x00ABB94A, 0x00A8B94C, 0x00A6B94D, 0x00A5B94E, 0x00A3B94F, 0x00A1B950, 0x00A0B951, 0x009EB952, 0x009CBA53, 0x009AB954, 0x0099B956, 0x0096B956, 0x0095B958, 0x0093B958, 0x0091BA5A, 0x008FBA5B, 0x008DB95C, 0x008BBA5D, 0x008ABA5E, 0x0088BA5F, 0x0086BA60, 0x0084BA61, 0x0083BA63, 0x0081B963, 0x007FB965, 0x007DBA65, 0x007CBA66, 0x007AB968, 0x0078B968, 0x0077B96A, 0x0075BA6B, 0x0074B96C, 0x0072B96D, 0x0070BA6E, 0x006FBA6F, 0x006DB970, 0x006CB971, 0x006ABA71, 0x0068BA73, 0x0067B974, 0x0065BA74, 0x0063BA76, 0x0062BA76, 0x0060BA78, 0x005FBA79, 0x005EBA7A, 0x005CB97A, 0x005BBA7B, 0x005AB97B, 0x0058B97C, 0x0057B97E, 0x0056BA7F, 0x0055B980, 0x0053BA80, 0x0052BA81, 0x0051BA82, 0x004FBA82, 0x004EB983, 0x004DB983, 0x004DB984, 0x004BBA85, 0x004AB985, 0x0049B986, 0x0048BA86, 0x0047BA88, 0x0046BA88, 0x0046BA89, 0x0044BA89, 0x0043BA8A, 0x0043BA8A, 0x0042BA8B, 0x00FF0000, 0x00FE0001, 0x00FE0000, 0x00FE0001, 0x00FE0101, 0x00FD0101, 0x00FC0201, 0x00FC0102, 0x00FB0202, 0x00FB0203, 0x00FB0203, 0x00FA0303, 0x00F90304, 0x00F90404, 0x00F80404, 0x00F70404, 0x00F70504, 0x00F70504, 0x00F50505, 0x00F50605, 0x00F50606, 0x00F40606, 0x00F30607, 0x00F20707, 0x00F20707, 0x00F10808, 0x00F10909, 0x00F00909, 0x00EF0909, 0x00EE0A09, 0x00EE0A09, 0x00ED0B0A, 0x00EC0A0B, 0x00EC0C0B, 0x00EB0C0C, 0x00EA0C0C, 0x00EA0D0D, 0x00E90D0D, 0x00E80D0E, 0x00E80E0F, 0x00E60F0F, 0x00E50F0F, 0x00E50F10, 0x00E51110, 0x00E31011, 0x00E21111, 0x00E21111, 0x00E11212, 0x00E01212, 0x00E01313, 0x00DF1314, 0x00DD1414, 0x00DD1515, 0x00DC1615, 0x00DC1616, 0x00DB1616, 0x00DA1717, 0x00D91717, 0x00D81818, 0x00D71818, 0x00D61919, 0x00D6191A, 0x00D41A1A, 0x00D41A1A, 0x00D31B1B, 0x00D21C1C, 0x00D11D1D, 0x00CF1D1D, 0x00CF1D1D, 0x00CF1E1E, 0x00CD1E1E, 0x00CD201F, 0x00CC2020, 0x00CA2020, 0x00C92120, 0x00C82122, 0x00C72222, 0x00C62222, 0x00C52323, 0x00C42424, 0x00C32525, 0x00C12525, 0x00C02627, 0x00BE2727, 0x00BC2728, 0x00BB2828, 0x00BA2A29, 0x00B82A2B, 0x00B72B2B, 0x00B52C2B, 0x00B42C2D, 0x00B22E2E, 0x00B12E2E, 0x00AF2E2F, 0x00AE2F2F, 0x00AD3030, 0x00AC3031, 0x00AA3231, 0x00A93232, 0x00A73233, 0x00A53334, 0x00A43434, 0x00A23435, 0x00A13535, 0x00A03635, 0x009E3637, 0x009C3737, 0x009B3738, 0x009A3838, 0x00993838, 0x00973839, 0x00963939, 0x00943A39, 0x00933A3A, 0x00923A3B, 0x00903B3B, 0x008E3B3B, 0x008E3B3B, 0x008C3C3C, 0x008A3C3C, 0x00893C3C, 0x00883C3D, 0x00873D3D, 0x00853C3D, 0x00843D3D, 0x00823D3D, 0x00823D3D, 0x00803D3E, 0x007F3E3D, 0x007E3D3D, 0x007C3D3E, 0x007C3E3D, 0x007A3D3E, 0x007A3D3D, 0x00783D3D, 0x00783D3D, 0x00773D3D, 0x00763C3D, 0x00743D3D, 0x00733C3C, 0x00723C3C, 0x00713C3B, 0x00703C3C, 0x006F3B3C, 0x006E3B3B, 0x006C3B3B, 0x006C3B3B, 0x006A3A3A, 0x00693A3A, 0x00693939, 0x00673A39, 0x00663939, 0x00653939, 0x00643838, 0x00633738, 0x00623838, 0x00603737, 0x00603636, 0x005E3636, 0x005D3635, 0x005B3536, 0x005A3435, 0x00593435, 0x00583434, 0x00583333, 0x00563333, 0x00553232, 0x00543232, 0x00523231, 0x00513131, 0x00503030, 0x004E3030, 0x004D2F2F, 0x004D2F2E, 0x004B2E2E, 0x004A2D2D, 0x00492D2C, 0x00482C2C, 0x00472B2B, 0x00462B2B, 0x00452B2A, 0x0043292A, 0x00432929, 0x00412929, 0x00402828, 0x003F2727, 0x003E2627, 0x003C2625, 0x003B2525, 0x003A2425, 0x003A2424, 0x00382423, 0x00372222, 0x00362221, 0x00352121, 0x00342020, 0x00322020, 0x00311F1F, 0x00301F1F, 0x002F1E1E, 0x002E1D1D, 0x002D1C1D, 0x002C1C1C, 0x002B1B1B, 0x002A1B1B, 0x00291A19, 0x00281A19, 0x00271919, 0x00261717, 0x00251717, 0x00241716, 0x00221616, 0x00211515, 0x00211514, 0x00201414, 0x001F1313, 0x001E1313, 0x001D1211, 0x001B1112, 0x001B1111, 0x001A1110, 0x00190F10, 0x00170F0F, 0x00170F0F, 0x00160D0E, 0x00150D0D, 0x00140C0C, 0x00140C0C, 0x00130B0B, 0x00120B0A, 0x00120A0A, 0x00100A0A, 0x0010090A, 0x000F0909, 0x000E0808, 0x000D0808, 0x000C0707, 0x000B0707, 0x000A0706, 0x000A0606, 0x00090505, 0x00090505, 0x00080405, 0x00080404, 0x00070304, 0x00060303, 0x00050303, 0x00050202, 0x00040203, 0x00040202, 0x00030102, 0x00020101, 0x00020101, 0x00010001, 0x00000000 };

typedef struct _DEVICE_DATA {

	BOOL                    HandlesOpen;
	WINUSB_INTERFACE_HANDLE WinusbHandle;
	HANDLE                  DeviceHandle;
	TCHAR                   DevicePath[MAX_PATH];

} DEVICE_DATA, * PDEVICE_DATA;

struct rawThermalFrameContainer {
	byte frameType;
	byte data[64896];
	USHORT convertedData[32448];
	int frameMin;
	int frameMax;
};

class seekThermalCamera {
public:
	DEVICE_DATA dd;
	void initialise();
	void uninitialise();
	void printCamInfo();
	bool getFrame(rawThermalFrameContainer* empty);
};

void initWinusb(seekThermalCamera* stc);
bool connectSeek(seekThermalCamera* destination);